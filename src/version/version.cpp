#include "version.h"

const char Version::kNormalSeparator[] = ".";
const char Version::kPrereleaseSeparator[] = "-";
const char Version::kBuildSeparator[] = "+";


Version::Version()
{
}

Version::Version(const QString & string)
{
    parse(string);
}

Version::Version(const Version & other)
{
    mSegments = other.mSegments;
}

Version::~Version()
{
}

QString Version::formattedString() const
{
    if (!isValid()) {
        return "";
    }
    
    QList<Segment> segments = mSegments;
    while (segments.size() < 2) {
        Segment segment;
        segment.value = "0";
        segment.separator = ".";
        segments.append(segment);
    }
    
    QString s;
    foreach (Segment segment, segments) {
        s.append(segment.separator);
        s.append(segment.value);
    }
    return s;
}

QString Version::toString() const
{
    QString s;
    foreach (Segment segment, mSegments) {
        s.append(segment.separator);
        s.append(segment.value);
    }
    return s;
}

bool Version::isNormal() const
{
    foreach (Segment segment, mSegments) {
        if (segment.separator == kPrereleaseSeparator) {
            return false;
        }
    }
    return true;
}

bool Version::isPrerelease() const
{
    foreach (Segment segment, mSegments) {
        if (segment.separator == kPrereleaseSeparator) {
            return true;
        }
    }
    return false;
}

bool Version::hasBuild() const
{
    foreach (Segment segment, mSegments) {
        if (segment.separator == kBuildSeparator) {
            return true;
        }
    }
    return false;
}

bool Version::isValid() const
{
    return mSegments.size() > 0;
}

int Version::compare(const Version & other) const
{
    if (this == &other) { return 0; }
    
    int limit = (mSegments.size() > other.mSegments.size()) ? mSegments.size() : other.mSegments.size();
    
    for (int i = 0; i < limit; i++) {
        Segment lhsSegment;
        Segment rhsSegment;
        int lhs = 0;
        int rhs = 0;
        bool lhsIsNumber = true;
        bool rhsIsNumber = true;
        
        if (i < mSegments.size()) {
            lhsSegment = mSegments.at(i);
        } else {
            lhsSegment.value = "0";
            lhsSegment.separator = kNormalSeparator;
        }
        if (i < other.mSegments.size()) {
            rhsSegment = other.mSegments.at(i);
        } else {
            rhsSegment.value = "0";
            rhsSegment.separator = kNormalSeparator;
        }
        
        
        if (lhsSegment.separator != rhsSegment.separator) {
            if (lhsSegment.separator == kPrereleaseSeparator) { return -1; }
            if (lhsSegment.separator == kBuildSeparator) { return 1; }
            if (rhsSegment.separator == kPrereleaseSeparator) { return 1; }
            if (rhsSegment.separator == kBuildSeparator) { return -1; }
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

    mSegments = rhs.mSegments;
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

void Version::parse(const QString & string)
{
    QRegExp rx("([0-9A-Za-z]+)");
    int pos = 0;
    while ((pos = rx.indexIn(string, pos)) != -1) {
        Segment segment;
        segment.value = rx.cap(1);
        if (mSegments.size() > 0) {
            segment.separator = string.at(pos - 1).toAscii();
        }
        mSegments.append(segment);
        
        pos += rx.matchedLength();
    }
}
