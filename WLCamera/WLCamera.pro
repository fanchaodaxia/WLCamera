QT += core
QT -= gui

CONFIG += c++11
CONFIG += create_prl
CONFIG += link_prl


TARGET = WLCamera
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    wlcamera.cpp

INCLUDEPATH += "C:\Program Files\Basler\pylon 5\Development\include"

HEADERS += \
    wlcamera.h \
    PylonIncludes.h \
    BaslerUsbInstantCamera.h \
    PylonGUI.h


DEPENDPATH += $$PWD



win32:CONFIG(release, debug|release): \
message (Adding Basler release libs) \
LIBS += -L$$PWD/lib/Win32 \
        -lGenApi_MD_VC120_v3_0_Basler_pylon_v5_0 \
        -lPylonGUI_MD_VC120_v5_0 \
        -lGCBase_MD_VC120_v3_0_Basler_pylon_v5_0 \
        -lPylonC_MD_VC120 \
        -lPylonUtility_MD_VC120_v5_0 \
        -lPylonBase_MD_VC120_v5_0

else:win32:CONFIG(debug, debug|release): \
message (Adding Basler debug libs) \
LIBS += -L$$PWD/lib/Win32 \
        -lGenApi_MD_VC120_v3_0_Basler_pylon_v5_0 \
        -lPylonGUI_MD_VC120_v5_0 \
        -lGCBase_MD_VC120_v3_0_Basler_pylon_v5_0 \
        -lPylonC_MD_VC120 \
        -lPylonUtility_MD_VC120_v5_0 \
        -lPylonBase_MD_VC120_v5_0




