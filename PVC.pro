QT -= gui
QT+=qml quick
QT += widgets
CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    funccan.cpp \
    mainw.cpp \
    parsedbc.cpp \
    mulgetmess.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    funccan.h \
    mainw.h \
    parsedbc.h \
    mulgetmess.h



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -lvxlapi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -lvxlapid

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Python36/libs/ -lpython36
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Python36/libs/ -lpython36d
else:unix: LIBS += -L$$PWD/../../../../../../Python36/libs/ -lpython36

INCLUDEPATH += $$PWD/../../../../../../Python36/include
DEPENDPATH += $$PWD/../../../../../../Python36/include

RESOURCES += \
    videoshow.qrc
