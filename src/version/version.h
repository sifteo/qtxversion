#ifndef QTXVERSION_VERSION_H
#define QTXVERSION_VERSION_H

#include "versionglobal.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


// http://semver.org/
// Based on RubyGems versioning scheme.
// See https://github.com/rubygems/rubygems/blob/master/lib/rubygems/version.rb

class VersionPrivate;

class Version
{
public:
    Version();
    Version(const QString & string);
    Version(const Version & other);
    ~Version();
    
    QString segment(int i) const;
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
    
protected:
    VersionPrivate *d_ptr;
private:
    Q_DECLARE_PRIVATE(Version);
};


QTX_END_NAMESPACE

#endif // QTXVERSION_VERSION_H
