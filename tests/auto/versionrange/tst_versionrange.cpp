#include "tst_versionrange.h"
#include "versionrange.h"


void tst_VersionRange::init()
{
    mVersionRange = 0;
}

void tst_VersionRange::cleanup()
{
    if (mVersionRange) {
        delete mVersionRange;
        mVersionRange = 0;
    }
}

void tst_VersionRange::unspecifiedRequirementTest()
{
    VersionRange range;
    QVERIFY(range.isSatisfiedBy(QString("0")));
    QVERIFY(range.isSatisfiedBy(QString("1")));
    QVERIFY(range.isSatisfiedBy(QString("99")));
    QVERIFY(!range.isSatisfiedBy(QString("")));
}

void tst_VersionRange::noOperatorTest()
{
    // when specified without an operator, defaults to equal (=)
    VersionRange range("1.0.1");
    QVERIFY(!range.isSatisfiedBy(QString("1.0.0")));
    QVERIFY(range.isSatisfiedBy(QString("1.0.1")));
    QVERIFY(!range.isSatisfiedBy(QString("1.0.2")));
    QVERIFY(!range.isSatisfiedBy(QString("")));
}

void tst_VersionRange::equalToOperatorTest()
{
    VersionRange range("= 1.0.1");
    QVERIFY(!range.isSatisfiedBy(QString("1.0.0")));
    QVERIFY(range.isSatisfiedBy(QString("1.0.1")));
    QVERIFY(!range.isSatisfiedBy(QString("1.0.2")));
    QVERIFY(!range.isSatisfiedBy(QString("")));
}

void tst_VersionRange::greaterThanOperatorTest()
{
    VersionRange range("> 1.0.1");
    QVERIFY(!range.isSatisfiedBy(QString("1.0.0")));
    QVERIFY(!range.isSatisfiedBy(QString("1.0.1")));
    QVERIFY(range.isSatisfiedBy(QString("1.0.2")));
    QVERIFY(!range.isSatisfiedBy(QString("")));
}

void tst_VersionRange::greaterThanOrEqualToOperatorTest()
{
    VersionRange range(">= 1.0.1");
    QVERIFY(!range.isSatisfiedBy(QString("1.0.0")));
    QVERIFY(range.isSatisfiedBy(QString("1.0.1")));
    QVERIFY(range.isSatisfiedBy(QString("1.0.2")));
    QVERIFY(!range.isSatisfiedBy(QString("")));
}

void tst_VersionRange::lessThanOperatorTest()
{
    VersionRange range("< 1.0.1");
    QVERIFY(range.isSatisfiedBy(QString("1.0.0")));
    QVERIFY(!range.isSatisfiedBy(QString("1.0.1")));
    QVERIFY(!range.isSatisfiedBy(QString("1.0.2")));
    QVERIFY(!range.isSatisfiedBy(QString("")));
}

void tst_VersionRange::lessThanOrEqualToOpeatorTest()
{
    VersionRange range("<= 1.0.1");
    QVERIFY(range.isSatisfiedBy(QString("1.0.0")));
    QVERIFY(range.isSatisfiedBy(QString("1.0.1")));
    QVERIFY(!range.isSatisfiedBy(QString("1.0.2")));
    QVERIFY(!range.isSatisfiedBy(QString("")));
}

void tst_VersionRange::notEqualToOperatorTest()
{
    VersionRange range("!= 1.0.1");
    QVERIFY(range.isSatisfiedBy(QString("1.0.0")));
    QVERIFY(!range.isSatisfiedBy(QString("1.0.1")));
    QVERIFY(range.isSatisfiedBy(QString("1.0.2")));
    QVERIFY(!range.isSatisfiedBy(QString("")));
}

void tst_VersionRange::exclusiveRangeTest()
{
    QStringList list = (QStringList() << "> 1.2" << "< 1.4");
    
    VersionRange range(list);
    QVERIFY(!range.isSatisfiedBy(QString("1.1")));
    QVERIFY(!range.isSatisfiedBy(QString("1.2")));
    QVERIFY(range.isSatisfiedBy(QString("1.2.1")));
    QVERIFY(range.isSatisfiedBy(QString("1.3")));
    QVERIFY(range.isSatisfiedBy(QString("1.3.9")));
    QVERIFY(!range.isSatisfiedBy(QString("1.4")));
    QVERIFY(!range.isSatisfiedBy(QString("1.5")));
    QVERIFY(!range.isSatisfiedBy(QString("")));
}

void tst_VersionRange::inclusiveRangeTest()
{
    QStringList list = (QStringList() << ">= 1.2" << "<= 1.4");
    
    VersionRange range(list);
    QVERIFY(!range.isSatisfiedBy(QString("1.1")));
    QVERIFY(range.isSatisfiedBy(QString("1.2")));
    QVERIFY(range.isSatisfiedBy(QString("1.2.1")));
    QVERIFY(range.isSatisfiedBy(QString("1.3")));
    QVERIFY(range.isSatisfiedBy(QString("1.3.9")));
    QVERIFY(range.isSatisfiedBy(QString("1.4")));
    QVERIFY(!range.isSatisfiedBy(QString("1.4.1")));
    QVERIFY(!range.isSatisfiedBy(QString("1.5")));
    QVERIFY(!range.isSatisfiedBy(QString("")));
}


QTEST_APPLESS_MAIN(tst_VersionRange)
