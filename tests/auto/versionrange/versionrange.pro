TEMPLATE = app
TARGET = tst_versionrange

QT += testlib
macx:CONFIG -= app_bundle

include(../../../mkspecs/test.pri)

HEADERS += tst_versionrange.h
SOURCES += tst_versionrange.cpp
