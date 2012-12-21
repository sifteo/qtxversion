TEMPLATE = app
TARGET = tst_versionrange

QT += testlib
macx:CONFIG -= app_bundle

HEADERS += tst_versionrange.h
SOURCES += tst_versionrange.cpp


# ------------
# Dependencies
# ------------
INCLUDEPATH += \
    ../../../src/version

HEADERS += \
    ../../../src/version/version.h \
    ../../../src/version/versionrange.h

SOURCES += \
    ../../../src/version/version.cpp \
    ../../../src/version/versionrange.cpp
