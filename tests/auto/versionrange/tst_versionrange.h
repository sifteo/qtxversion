#ifndef TST_VERSIONRANGE_H
#define TST_VERSIONRANGE_H

#include <QtTest/QtTest>

class VersionRange;

class tst_VersionRange : public QObject
{
Q_OBJECT

private slots:
    void init();
    void cleanup();
    
    void unspecifiedRequirementTest();
    void noOperatorTest();
    void equalToOperatorTest();
    void greaterThanOperatorTest();
    void greaterThanOrEqualToOperatorTest();
    void lessThanOperatorTest();
    void lessThanOrEqualToOpeatorTest();
    void notEqualToOperatorTest();
    
    void exclusiveRangeTest();
    void inclusiveRangeTest();
    
public:
    VersionRange *mVersionRange;
};

#endif // TST_VERSIONRANGE_H
