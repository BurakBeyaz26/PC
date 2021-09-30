QT += quick network serialport quickcontrols2 websockets core

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        configdatas.cpp \
        datamanagement.cpp \
        log.cpp \
        main.cpp \
        serialcommunication.cpp \
        tcpsocketcommunication.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    configdatas.h \
    datamanagement.h \
    log.h \
    serialcommunication.h \
    tcpsocketcommunication.h


#NOTES
#   socat -d -d pty,raw,echo=0 pty,raw,echo=0           //to bridge
#   echo "Test" > /dev/pts/3                            //to send data from terminal
#
#
#
3

