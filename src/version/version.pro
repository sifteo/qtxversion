include(../../modules/qtx_version.pri)
include(../../mkspecs/features/qtx_module.prf)


contains(QT_VERSION, ^5\\.[0-9]\\..*) {
    # QtxVersion makes use of features that that have been deprecated in Qt 5.0.
    # Set QT_DISABLE_DEPRECATED_BEFORE to 4 to enable deprecated Qt 4.x APIs.
    DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x040800
}

include(version.pri)
