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
    static RequirementPair parse(const QString & string);
    
    QList<RequirementPair> requirements;
};


VersionRange::VersionRange()
    : d_ptr(new VersionRangePrivate())
{
}

VersionRange::VersionRange(const QString & string)
    : d_ptr(new VersionRangePrivate())
{
    VersionRangePrivate::RequirementPair requirement = VersionRangePrivate::parse(string);
    d_ptr->requirements.append(requirement);
}

VersionRange::VersionRange(const QStringList & strings)
    : d_ptr(new VersionRangePrivate())
{
    foreach (QString string, strings) {
        VersionRangePrivate::RequirementPair requirement = VersionRangePrivate::parse(string);
        d_ptr->requirements.append(requirement);
    }
}

VersionRange::VersionRange(const VersionRange & other)
    : d_ptr(new VersionRangePrivate())
{
    d_ptr->requirements = other.d_ptr->requirements;
}

bool VersionRange::isSatisfiedBy(const Version & version) const
{
    foreach (VersionRangePrivate::RequirementPair requirement, d_ptr->requirements) {
        bool satisfied = false;
        
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


VersionRangePrivate::RequirementPair VersionRangePrivate::parse(const QString & string)
{
    QStringList components = string.simplified().split(" ");
    
    Operator op = UnknownOperator;
    QString version = "";
    
    if (components.size() == 1) {
        op = EqualToOperator;
        version = components.at(0);
    } else {
        QString o = components.at(0);
        version = components.at(1);
        
        if (o == "=") {
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
    }
    
    return qMakePair(op, Version(version));
}


QTX_END_NAMESPACE
