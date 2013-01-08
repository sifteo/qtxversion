include(../../../mkspecs/features/tests/qtx_test.prf)

TEMPLATE = app
TARGET = tst_version

QT += testlib
macx:CONFIG -= app_bundle

HEADERS += tst_version.h
SOURCES += tst_version.cpp


# ------------
# Dependencies
# ------------
#INCLUDEPATH += \
#    ../../../src/version

#HEADERS += \
#    ../../../src/version/version.h

#SOURCES += \
#    ../../../src/version/version.cpp
