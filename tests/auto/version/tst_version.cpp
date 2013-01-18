#include "tst_version.h"
#include "version.h"


void tst_Version::init()
{
    mVersion = 0;
}

void tst_Version::cleanup()
{
    if (mVersion) {
        delete mVersion;
        mVersion = 0;
    }
}

void tst_Version::defaultConstructorTest()
{
    Version version;
    QCOMPARE(version.toString(), QString(""));
    QVERIFY(!version.isValid());
}

void tst_Version::stringConstructorTest()
{
    Version v1_2_3("1.2.3");
    QCOMPARE(v1_2_3.toString(), QString("1.2.3"));
    QVERIFY(v1_2_3.isValid());
}

void tst_Version::copyConstructorTest()
{
    Version original("1.2.3");
    Version copy(original);
    
    QCOMPARE(original.toString(), QString("1.2.3"));
    QCOMPARE(original.toString(), copy.toString());
    QVERIFY(original.isValid());
    QVERIFY(copy.isValid());
}

void tst_Version::parseNormalVersionTest()
{
    // normal versions are allowed to contain alphabetic characters, which is a
    // looser interpretation of the Semantic Versioning specification
    Version v1_0_b1("1.0.b1");
    QCOMPARE(v1_0_b1.toString(), QString("1.0.b1"));
    QVERIFY(v1_0_b1.isNormal());
    QVERIFY(!v1_0_b1.isPrerelease());
    QVERIFY(!v1_0_b1.hasBuild());
    QVERIFY(v1_0_b1.isValid());
    
    // normal version segments are separated by any non-alphanumeric character,
    // which is a looser interpretation of the Semantic Versioning specification
    Version v9_0_21022_8("9_0_21022_8");
    QCOMPARE(v9_0_21022_8.toString(), QString("9_0_21022_8"));
    QVERIFY(v9_0_21022_8.isNormal());
    QVERIFY(!v9_0_21022_8.isPrerelease());
    QVERIFY(!v9_0_21022_8.hasBuild());
    QVERIFY(v9_0_21022_8.isValid());
}

void tst_Version::parsePrereleaseVersionTest()
{
    Version v1_0_0_alpha("1.0.0-alpha");
    QCOMPARE(v1_0_0_alpha.toString(), QString("1.0.0-alpha"));
    QVERIFY(!v1_0_0_alpha.isNormal());
    QVERIFY(v1_0_0_alpha.isPrerelease());
    QVERIFY(!v1_0_0_alpha.hasBuild());
    QVERIFY(v1_0_0_alpha.isValid());

    Version v1_0_0_alpha_1("1.0.0-alpha.1");
    QCOMPARE(v1_0_0_alpha_1.toString(), QString("1.0.0-alpha.1"));
    QVERIFY(!v1_0_0_alpha_1.isNormal());
    QVERIFY(v1_0_0_alpha_1.isPrerelease());
    QVERIFY(!v1_0_0_alpha_1.hasBuild());
    QVERIFY(v1_0_0_alpha_1.isValid());

    Version v1_0_0_0_3_7("1.0.0-0.3.7");
    QCOMPARE(v1_0_0_0_3_7.toString(), QString("1.0.0-0.3.7"));
    QVERIFY(!v1_0_0_0_3_7.isNormal());
    QVERIFY(v1_0_0_0_3_7.isPrerelease());
    QVERIFY(!v1_0_0_0_3_7.hasBuild());
    QVERIFY(v1_0_0_0_3_7.isValid());

    Version v1_0_0_x_7_z_92("1.0.0-x.7.z.92");
    QCOMPARE(v1_0_0_x_7_z_92.toString(), QString("1.0.0-x.7.z.92"));
    QVERIFY(!v1_0_0_x_7_z_92.isNormal());
    QVERIFY(v1_0_0_x_7_z_92.isPrerelease());
    QVERIFY(!v1_0_0_x_7_z_92.hasBuild());
    QVERIFY(v1_0_0_x_7_z_92.isValid());
}

void tst_Version::parseBuildVersionTest()
{
    Version v1_0_0_build_1("1.0.0+build.1");
    QCOMPARE(v1_0_0_build_1.toString(), QString("1.0.0+build.1"));
    QVERIFY(v1_0_0_build_1.isNormal());
    QVERIFY(!v1_0_0_build_1.isPrerelease());
    QVERIFY(v1_0_0_build_1.hasBuild());
    QVERIFY(v1_0_0_build_1.isValid());

    Version v1_3_7_build_11("1.3.7+build.11.e0f985a");
    QCOMPARE(v1_3_7_build_11.toString(), QString("1.3.7+build.11.e0f985a"));
    QVERIFY(v1_3_7_build_11.isNormal());
    QVERIFY(!v1_3_7_build_11.isPrerelease());
    QVERIFY(v1_3_7_build_11.hasBuild());
    QVERIFY(v1_3_7_build_11.isValid());
}

void tst_Version::compareEqualVersionTest()
{
    Version a("1.2.3");
    Version b("1.2.3");
    
    QVERIFY(a.compare(a) == 0);
    QVERIFY(a.compare(b) == 0);
}

void tst_Version::compareDifferentVersionTest()
{
    Version v1_2_3("1.2.3");
    Version v1_2_4("1.2.4");
    Version v1_2_30("1.2.30");
    
    QVERIFY(v1_2_3.compare(v1_2_4) == -1);
    QVERIFY(v1_2_4.compare(v1_2_30) == -1);
    
    QVERIFY(v1_2_30.compare(v1_2_4) == 1);
    QVERIFY(v1_2_4.compare(v1_2_3) == 1);
}

void tst_Version::compareDifferentSegmentCountTest()
{
    Version v1_2("1.2");
    Version v1_2_0("1.2.0");
    Version v1_2_1("1.2.1");
    
    QVERIFY(v1_2.compare(v1_2_0) == 0);
    QVERIFY(v1_2.compare(v1_2_1) == -1);
    QVERIFY(v1_2_0.compare(v1_2) == 0);
    QVERIFY(v1_2_1.compare(v1_2) == 1);
}

void tst_Version::comparePrereleaseSegmentsTest()
{
    Version v1_0("1.0");
    Version v1_0_0("1.0.0");
    Version v1_0_0_beta1("1.0.0-beta1");
    Version v1_0_0_alpha2("1.0.0-alpha2");
    Version v1_0_0_alpha1("1.0.0-alpha1");
    
    QVERIFY(v1_0.compare(v1_0_0_beta1) == 1);
    QVERIFY(v1_0_0.compare(v1_0_0_beta1) == 1);
    QVERIFY(v1_0_0_beta1.compare(v1_0_0_alpha2) == 1);
    QVERIFY(v1_0_0_alpha2.compare(v1_0_0_alpha1) == 1);
    
    QVERIFY(v1_0_0_alpha1.compare(v1_0_0_alpha2) == -1);
    QVERIFY(v1_0_0_alpha2.compare(v1_0_0_beta1) == -1);
    QVERIFY(v1_0_0_beta1.compare(v1_0_0) == -1);
    QVERIFY(v1_0_0_beta1.compare(v1_0) == -1);
}

void tst_Version::compareBuildSegmentsTest()
{
    Version v1_0("1.0");
    Version v1_0_0("1.0.0");
    Version v1_0_0_build("1.0.0+build");
    Version v1_0_0_build_2("1.0.0+build.2.b8f12d7");
    Version v1_0_0_build_11("1.0.0+build.11.e0f985a");
    
    QVERIFY(v1_0.compare(v1_0_0_build) == -1);
    QVERIFY(v1_0_0.compare(v1_0_0_build) == -1);
    QVERIFY(v1_0_0_build.compare(v1_0_0_build_2) == -1);
    QVERIFY(v1_0_0_build_2.compare(v1_0_0_build_11) == -1);
    
    QVERIFY(v1_0_0_build_11.compare(v1_0_0_build_2) == 1);
    QVERIFY(v1_0_0_build_2.compare(v1_0_0_build) == 1);
    QVERIFY(v1_0_0_build.compare(v1_0_0) == 1);
    QVERIFY(v1_0_0_build.compare(v1_0) == 1);
}

void tst_Version::compareNumericVsAlphanumericTest()
{
    Version v1_0_0_80("1.0.0+80");
    Version v1_0_0_8a("1.0.0+8a");
    
    QVERIFY(v1_0_0_80.compare(v1_0_0_8a) == -1);
    QVERIFY(v1_0_0_8a.compare(v1_0_0_80) == 1);
}

void tst_Version::comparePrereleaseVsBuildTest()
{
    Version v1_0_0_pre("1.0.0-foo");
    Version v1_0_0("1.0.0");
    Version v1_0_0_build("1.0.0+foo");
    
    QVERIFY(v1_0_0_pre.compare(v1_0_0_build) == -1);
    QVERIFY(v1_0_0_pre.compare(v1_0_0) == -1);
    QVERIFY(v1_0_0.compare(v1_0_0_build) == -1);
    
    QVERIFY(v1_0_0_build.compare(v1_0_0_pre) == 1);
    QVERIFY(v1_0_0_build.compare(v1_0_0) == 1);
    QVERIFY(v1_0_0.compare(v1_0_0_pre) == 1);
}

void tst_Version::compareInvalidTest()
{
    Version vInvalid("");
    Version vOtherInvalid("");
    Version v1_2("1.2");
    
    QVERIFY(vInvalid.compare(vOtherInvalid) == 0);
    QVERIFY(vInvalid.compare(v1_2) == -1);
    QVERIFY(v1_2.compare(vInvalid) == 1);
}

void tst_Version::semverExampleTest()
{
    Version v1_0_0_alpha("1.0.0-alpha");
    Version v1_0_0_alpha_1("1.0.0-alpha.1");
    Version v1_0_0_beta_2("1.0.0-beta.2");
    Version v1_0_0_beta_11("1.0.0-beta.11");
    Version v1_0_0_rc_1("1.0.0-rc.1");
    Version v1_0_0_rc_1_build_1("1.0.0-rc.1+build.1");
    Version v1_0_0("1.0.0");
    Version v1_0_0_0_3_7("1.0.0+0.3.7");
    Version v1_3_7_build("1.3.7+build");
    Version v1_3_7_build_2("1.3.7+build.2.b8f12d7");
    Version v1_3_7_build_11("1.3.7+build.11.e0f985a");
    
    QVERIFY(v1_0_0_alpha.compare(v1_0_0_alpha_1) == -1);
    QVERIFY(v1_0_0_alpha_1.compare(v1_0_0_beta_2) == -1);
    QVERIFY(v1_0_0_beta_2.compare(v1_0_0_beta_11) == -1);
    QVERIFY(v1_0_0_beta_11.compare(v1_0_0_rc_1) == -1);
    QVERIFY(v1_0_0_rc_1.compare(v1_0_0_rc_1_build_1) == -1);
    QVERIFY(v1_0_0_rc_1_build_1.compare(v1_0_0) == -1);
    QVERIFY(v1_0_0.compare(v1_0_0_0_3_7) == -1);
    QVERIFY(v1_0_0_0_3_7.compare(v1_3_7_build) == -1);
    QVERIFY(v1_3_7_build.compare(v1_3_7_build_2) == -1);
    QVERIFY(v1_3_7_build_2.compare(v1_3_7_build_11) == -1);
    
    QVERIFY(v1_3_7_build_11.compare(v1_3_7_build_2) == 1);
    QVERIFY(v1_3_7_build_2.compare(v1_3_7_build) == 1);
    QVERIFY(v1_3_7_build.compare(v1_0_0_0_3_7) == 1);
    QVERIFY(v1_0_0_0_3_7.compare(v1_0_0) == 1);
    QVERIFY(v1_0_0.compare(v1_0_0_rc_1_build_1) == 1);
    QVERIFY(v1_0_0_rc_1_build_1.compare(v1_0_0_rc_1) == 1);
    QVERIFY(v1_0_0_rc_1.compare(v1_0_0_beta_11) == 1);
    QVERIFY(v1_0_0_beta_11.compare(v1_0_0_beta_2) == 1);
    QVERIFY(v1_0_0_beta_2.compare(v1_0_0_alpha_1) == 1);
    QVERIFY(v1_0_0_alpha_1.compare(v1_0_0_alpha) == 1);
}

void tst_Version::operatorEqualTest()
{
    Version a("1.2.3");
    Version b = a;
    
    QCOMPARE(a.toString(), b.toString());
}

void tst_Version::operatorEqualsTest()
{
    Version a("1.2");
    Version b("1.2");
    
    QVERIFY(a == b);
}

void tst_Version::operatorNotEqualsTest()
{
    Version v1_2("1.2");
    Version same("1.2");
    Version v1_3("1.3");
    
    QVERIFY(v1_2 != v1_3);
    QVERIFY(v1_2 == same);
}

void tst_Version::operatorLessThanTest()
{
    Version v1_2("1.2");
    Version v1_3("1.3");
    
    QVERIFY(v1_2 < v1_3);
}

void tst_Version::operatorGreaterThanTest()
{
    Version v1_2("1.2");
    Version v1_3("1.3");
    
    QVERIFY(v1_3 > v1_2);
}

void tst_Version::operatorLessThanOrEqualTest()
{
    Version v1_2("1.2");
    Version same("1.2");
    Version v1_3("1.3");
    
    QVERIFY(v1_2 <= same);
    QVERIFY(v1_2 <= v1_3);
    QVERIFY(!(v1_3 <= v1_2));
}

void tst_Version::operatorGreaterThanOrEqualTest()
{
    Version v1_2("1.2");
    Version v1_3("1.3");
    Version same("1.3");
    
    QVERIFY(v1_3 >= same);
    QVERIFY(v1_3 >= v1_2);
    QVERIFY(!(v1_2 >= v1_3));
}


QTEST_APPLESS_MAIN(tst_Version)
