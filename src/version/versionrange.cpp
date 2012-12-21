#include "versionrange.h"


VersionRange::VersionRange()
{
}

VersionRange::VersionRange(const QString & string)
{
    RequirementPair requirement = parse(string);
    mRequirements.append(requirement);
}

VersionRange::VersionRange(const QStringList & strings)
{
    foreach (QString string, strings) {
        RequirementPair requirement = parse(string);
        mRequirements.append(requirement);
    }
}

VersionRange::VersionRange(const VersionRange & other)
{
    mRequirements = other.mRequirements;
}

bool VersionRange::isSatisfiedBy(const Version & version) const
{
    foreach (RequirementPair requirement, mRequirements) {
        bool satisfied = false;
        
        // switch on the operation
        switch (requirement.first)
        {
        case EqualToOperator:
            satisfied = (version == requirement.second);
            break;
        case GreaterThanOperator:
            satisfied = (version > requirement.second);
            break;
        case GreaterThanOrEqualToOperator:
            satisfied = (version >= requirement.second);
            break;
        case LessThanOperator:
            satisfied = (version < requirement.second);
            break;
        case LessThanOrEqualToOperator:
            satisfied = (version <= requirement.second);
            break;
        case NotEqualToOperator:
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

    mRequirements = rhs.mRequirements;
    return *this;
}

VersionRange::RequirementPair VersionRange::parse(const QString & string)
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
