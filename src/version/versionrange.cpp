#include "versionrange.h"

QTX_BEGIN_NAMESPACE


class VersionRangePrivate
{
public:
    typedef enum {
        UnknownOperator,
        EqualToOperator,
        GreaterThanOperator,
        GreaterThanOrEqualToOperator,
        LessThanOperator,
        LessThanOrEqualToOperator,
        NotEqualToOperator
    } Operator;

    typedef QPair<Operator, Version> RequirementPair;
    
    void parse(const QString & string);
    
    QList<RequirementPair> requirements;
};


VersionRange::VersionRange()
    : d_ptr(new VersionRangePrivate())
{
}

VersionRange::VersionRange(const QString & string)
    : d_ptr(new VersionRangePrivate())
{
    d_ptr->parse(string);
}

VersionRange::VersionRange(const QStringList & strings)
    : d_ptr(new VersionRangePrivate())
{
    foreach (QString string, strings) {
        d_ptr->parse(string);
    }
}

VersionRange::VersionRange(const VersionRange & other)
    : d_ptr(new VersionRangePrivate())
{
    d_ptr->requirements = other.d_ptr->requirements;
}

bool VersionRange::isSatisfiedBy(const Version & version) const
{
    if (!version.isValid()) {
        return false;
    }

    foreach (VersionRangePrivate::RequirementPair requirement, d_ptr->requirements) {
        bool satisfied = false;
        
        if (requirement.second.isValid()) {
          // switch on the operation
          switch (requirement.first)
          {
          case VersionRangePrivate::EqualToOperator:
              satisfied = (version == requirement.second);
              break;
          case VersionRangePrivate::GreaterThanOperator:
              satisfied = (version > requirement.second);
              break;
          case VersionRangePrivate::GreaterThanOrEqualToOperator:
              satisfied = (version >= requirement.second);
              break;
          case VersionRangePrivate::LessThanOperator:
              satisfied = (version < requirement.second);
              break;
          case VersionRangePrivate::LessThanOrEqualToOperator:
              satisfied = (version <= requirement.second);
              break;
          case VersionRangePrivate::NotEqualToOperator:
              satisfied = (version != requirement.second);
              break;
          default:
              satisfied = false;
              break;
          }
        }
        
        if (!satisfied) { return false; }
    }
    
    return true;
}

VersionRange & VersionRange::operator= (const VersionRange & rhs)
{
    if (this == &rhs) { return *this; }

    d_ptr->requirements = rhs.d_ptr->requirements;
    return *this;
}


void VersionRangePrivate::parse(const QString & string)
{
    QRegExp rx("([\\W ]*)([\\S]+)");
    int pos = 0;
    while ((pos = rx.indexIn(string, pos)) != -1) {
        //qDebug() << "CAP 1: " << rx.cap(1);
        //qDebug() << "CAP 2: " << rx.cap(2);
        
        Operator op = UnknownOperator;
        QString o = rx.cap(1).simplified();
        QString version = rx.cap(2).simplified();
        
        if (o == "") {
            op = EqualToOperator;
        } else if (o == "=") {
            op = EqualToOperator;
        } else if (o == ">") {
            op = GreaterThanOperator;
        } else if (o == ">=") {
            op = GreaterThanOrEqualToOperator;
        } else if (o == "<") {
            op = LessThanOperator;
        } else if (o == "<=") {
            op = LessThanOrEqualToOperator;
        } else if (o == "!=") {
            op = NotEqualToOperator;
        }
        
        RequirementPair requirement = qMakePair(op, Version(version)); 
        requirements.append(requirement);
        
        pos += rx.matchedLength();
    }
  }


QTX_END_NAMESPACE
