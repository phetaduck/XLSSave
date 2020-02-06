QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./QXlsx/         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./QXlsx/header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./QXlsx/source/  # current QXlsx source path is ./source/
include(./QXlsx/QXlsx.pri)

INCLUDEPATH += ./Headers \
    C:/Dev/Mosquitto/devel \
    C:/Dev/protobuf/include

SOURCES += \
    curve.pb.cc \
    las_curve.cpp \
    main.cpp \
    mosquitto.cpp \
    mqtt_impl.cpp \
    xls_exporter.cpp \
    xlssave.cpp

HEADERS += \
    curve.pb.h \
    las_curve.h \
    mosquitto.hpp \
    mqtt_impl.h \
    xls_exporter.h \
    xlssave.h

FORMS += \
    xlssave.ui

LIBS += \
    -LC:/Dev/Mosquitto/devel -lmosquitto \
    -LC:/Dev/protobuf/lib -llibprotobuf \
    -LC:/Dev/protobuf/lib -llibprotobuf-lite \
    -LC:/Dev/protobuf/lib -llibprotoc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    curve.proto
