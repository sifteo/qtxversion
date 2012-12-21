#ifndef QTXVERSION_VERSION_H
#define QTXVERSION_VERSION_H

#include <QtCore>



// http://semver.org/
// Based on RubyGems versioning scheme.
// See https://github.com/rubygems/rubygems/blob/master/lib/rubygems/version.rb
class Version
{
public:
    Version();
    Version(const QString & string);
    Version(const Version & other);
    ~Version();
    
    QString formattedString() const;
    QString toString() const;
    
    bool isNormal() const;
    bool isPrerelease() const;
    bool hasBuild() const;
    bool isValid() const;
    
    int compare(const Version & other) const;
    
    Version & operator= (const Version & rhs);
    bool operator== (const Version & rhs) const;
    bool operator!= (const Version & rhs) const;
    bool operator< (const Version & rhs) const;
    bool operator<= (const Version & rhs) const;
    bool operator> (const Version & rhs) const;
    bool operator>= (const Version & rhs) const;
    
private:
    static const char kNormalSeparator[];
    static const char kPrereleaseSeparator[];
    static const char kBuildSeparator[];
    
    struct Segment {
        QString value;
        QString separator;
    };
    
    void parse(const QString & string);
    
    QList<Segment> mSegments;
};

#endif // QTXVERSION_VERSION_H
