QT       += core gui widgets charts 3dcore 3drender 3dinput 3dextras 3dlogic opengl 3danimation multimedia

INCLUDEPATH +=  include \
                include/ui \
                include/lib \
                include/client

LIBS += lib/libqt3dwidget.a

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

OBJECTS_DIR = obj

SOURCES += \
    src/*.cpp \
    src/client/*.cpp

HEADERS += \
    include/*.hpp \
    include/ui/*.h \
    include/lib/*.h \
    include/client/*.hpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target