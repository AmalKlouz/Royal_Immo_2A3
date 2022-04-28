QT       += core gui sql printsupport charts serialport network multimedia svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    acceuil.cpp \
    arduino.cpp \
    arduino1.cpp \
    arduinoEQU.cpp \
    bien.cpp \
    client.cpp \
    connexion.cpp \
    dialogbien.cpp \
    dialogclient.cpp \
    dialogreclamation.cpp \
    dialoguser.cpp \
    employe.cpp \
    equipement.cpp \
    equipmentdialog.cpp \
    main.cpp \
    mainwindowins.cpp \
    mapwindow.cpp \
    menu.cpp \
    notification.cpp \
    qrcodegen.cpp \
    reclamation.cpp \
    user.cpp

HEADERS += \
    acceuil.h \
    arduino.h \
    arduino1.h \
    arduino2.h \
    arduinoEQU.h \
    bien.h \
    client.h \
    connexion.h \
    dialogbien.h \
    dialogclient.h \
    dialogreclamation.h \
    dialoguser.h \
    employe.h \
    equipement.h \
    equipmentdialog.h \
    mainwindowins.h \
    mapwindow.h \
    menu.h \
    notification.h \
    qrcodegen.h \
    reclamation.h \
    user.h

FORMS += \
    acceuil.ui \
    bien.ui \
    dialogbien.ui \
    dialogclient.ui \
    dialogreclamation.ui \
    dialoguser.ui \
    equipmentdialog.ui \
    mainwindowins.ui \
    mapwindow.ui \
    menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc
