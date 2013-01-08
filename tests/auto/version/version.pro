TEMPLATE = app
TARGET = tst_version

QT += testlib
macx:CONFIG -= app_bundle

include(../../../mkspecs/test.pri)

HEADERS += tst_version.h
SOURCES += tst_version.cpp
