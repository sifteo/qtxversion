#ifndef TST_VERSIONRANGE_H
#define TST_VERSIONRANGE_H

#include "versionrange.h"
#include <QtTest/QtTest>

QTX_USE_NAMESPACE


class tst_VersionRange : public QObject
{
Q_OBJECT

private slots:
    void init();
    void cleanup();
    
    void unspecifiedRequirementTest();
    void noOperatorTest();
    void equalToOperatorTest();
    void equalToOperatorWithoutSpaceTest();
    void greaterThanOperatorTest();
    void greaterThanOperatorWithoutSpaceTest();
    void greaterThanOrEqualToOperatorTest();
    void greaterThanOrEqualToOperatorWithoutSpaceTest();
    void lessThanOperatorTest();
    void lessThanOperatorWithoutSpaceTest();
    void lessThanOrEqualToOpeatorTest();
    void lessThanOrEqualToOpeatorWithoutSpaceTest();
    void notEqualToOperatorTest();
    void notEqualToOperatorWithoutSpaceTest();
    
    void exclusiveRangeAsStringTest();
    void exclusiveRangeAsArrayTest();
    void inclusiveRangeAsStringTest();
    void inclusiveRangeAsArrayTest();
    
    void invalidEqualToThanRequirement();
    void invalidGreaterThanRequirement();
    void invalidLessThanRequirement();
    
public:
    VersionRange *mVersionRange;
};

#endif // TST_VERSIONRANGE_H
