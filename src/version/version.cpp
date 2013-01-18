#include "version.h"

QTX_BEGIN_NAMESPACE


class VersionPrivate
{
public:
    static const char kNormalSeparator[];
    static const char kPrereleaseSeparator[];
    static const char kBuildSeparator[];

public:
    void parse(const QString & string);
    
    struct Segment {
        QString value;
        QString separator;
    };
    
    QList<Segment> segments;
};

const char VersionPrivate::kNormalSeparator[] = ".";
const char VersionPrivate::kPrereleaseSeparator[] = "-";
const char VersionPrivate::kBuildSeparator[] = "+";


Version::Version()
    : d_ptr(new VersionPrivate())
{
}

Version::Version(const QString & string)
    : d_ptr(new VersionPrivate())
{
    d_ptr->parse(string);
}

Version::Version(const Version & other)
    : d_ptr(new VersionPrivate())
{
    d_ptr->segments = other.d_ptr->segments;
}

Version::~Version()
{
    if (d_ptr) {
        delete d_ptr;
        d_ptr = 0;
    }
}

QString Version::toString() const
{
    QString s;
    foreach (VersionPrivate::Segment segment, d_ptr->segments) {
        s.append(segment.separator);
        s.append(segment.value);
    }
    return s;
}

bool Version::isNormal() const
{
    foreach (VersionPrivate::Segment segment, d_ptr->segments) {
        if (segment.separator == VersionPrivate::kPrereleaseSeparator) {
            return false;
        }
    }
    return true;
}

bool Version::isPrerelease() const
{
    foreach (VersionPrivate::Segment segment, d_ptr->segments) {
        if (segment.separator == VersionPrivate::kPrereleaseSeparator) {
            return true;
        }
    }
    return false;
}

bool Version::hasBuild() const
{
    foreach (VersionPrivate::Segment segment, d_ptr->segments) {
        if (segment.separator == VersionPrivate::kBuildSeparator) {
            return true;
        }
    }
    return false;
}

bool Version::isValid() const
{
    return d_ptr->segments.size() > 0;
}

int Version::compare(const Version & other) const
{
    if (this == &other) { return 0; }
    
    int limit = (d_ptr->segments.size() > other.d_ptr->segments.size()) ? d_ptr->segments.size() : other.d_ptr->segments.size();
    
    for (int i = 0; i < limit; i++) {
        VersionPrivate::Segment lhsSegment;
        VersionPrivate::Segment rhsSegment;
        int lhs = 0;
        int rhs = 0;
        bool lhsIsNumber = true;
        bool rhsIsNumber = true;
        
        if (i < d_ptr->segments.size()) {
            lhsSegment = d_ptr->segments.at(i);
        } else {
            lhsSegment.value = "0";
            lhsSegment.separator = VersionPrivate::kNormalSeparator;
        }
        if (i < other.d_ptr->segments.size()) {
            rhsSegment = other.d_ptr->segments.at(i);
        } else {
            rhsSegment.value = "0";
            rhsSegment.separator = VersionPrivate::kNormalSeparator;
        }
        
        
        if (lhsSegment.separator != rhsSegment.separator) {
            if (lhsSegment.separator == VersionPrivate::kPrereleaseSeparator) { return -1; }
            if (lhsSegment.separator == VersionPrivate::kBuildSeparator) { return 1; }
            if (rhsSegment.separator == VersionPrivate::kPrereleaseSeparator) { return 1; }
            if (rhsSegment.separator == VersionPrivate::kBuildSeparator) { return -1; }
        }
        
        lhs = lhsSegment.value.toInt(&lhsIsNumber);
        rhs = rhsSegment.value.toInt(&rhsIsNumber);
        
        if (lhsIsNumber && !rhsIsNumber) { return -1; }
        if (!lhsIsNumber && rhsIsNumber) { return 1; }
        
        if (lhsIsNumber && rhsIsNumber) {
            // Numeric comparison
            if (lhs < rhs) {
                return -1;
            } else if (lhs > rhs) {
                return 1;
            }
        } else {
            // Alphabetic comparison
            if (lhsSegment.value < rhsSegment.value) {
                return -1;
            } else if (lhsSegment.value > rhsSegment.value) {
                return 1;
            }
        }
        // if equal, continue loop
    }

    return 0;
}

Version & Version::operator= (const Version & rhs)
{
    if (this == &rhs) { return *this; }

    d_ptr->segments = rhs.d_ptr->segments;
    return *this;
}

bool Version::operator== (const Version & rhs) const
{
    return (this->compare(rhs) == 0);
}

bool Version::operator!= (const Version & rhs) const
{
    return (this->compare(rhs) != 0);
}

bool Version::operator< (const Version & rhs) const
{
    return (this->compare(rhs) < 0);
}

bool Version::operator> (const Version & rhs) const
{
    return (this->compare(rhs) > 0);
}

bool Version::operator<= (const Version & rhs) const
{
    return (this->compare(rhs) <= 0);
}

bool Version::operator>= (const Version & rhs) const
{
    return (this->compare(rhs) >= 0);
}


void VersionPrivate::parse(const QString & string)
{
    QRegExp rx("([0-9A-Za-z]+)");
    int pos = 0;
    while ((pos = rx.indexIn(string, pos)) != -1) {
        Segment segment;
        segment.value = rx.cap(1);
        if (segments.size() > 0) {
            segment.separator = string.at(pos - 1).toAscii();
        }
        segments.append(segment);
        
        pos += rx.matchedLength();
    }
}


QTX_END_NAMESPACE
