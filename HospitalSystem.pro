QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AppointmentPage.cpp \
    DoctorSelectionPage.cpp \
    addstaff.cpp \
    admin.cpp \
    admindashboard.cpp \
    editpatientwindow.cpp \
    editstaffwindow.cpp \
    main.cpp \
    loginwindow.cpp \
    operations.cpp \
    patient.cpp \
    patientdashboard.cpp \
    schedulepage.cpp \
    signupwindow.cpp \
    staff.cpp \
    staffdashboard.cpp

HEADERS += \
    AppointmentPage.h \
    DoctorSelectionPage.h \
    addstaff.h \
    admin.h \
    admindashboard.h \
    editpatientwindow.h \
    editstaffwindow.h \
    loginwindow.h \
    operations.h \
    patient.h \
    patientdashboard.h \
    schedulepage.h \
    signupwindow.h \
    staff.h \
    staffdashboard.h

FORMS += \
    addstaff.ui \
    admindashboard.ui \
    editpatientwindow.ui \
    editstaffwindow.ui \
    loginwindow.ui \
    patientdashboard.ui \
    schedulepage.ui \
    signupwindow.ui \
    staffdashboard.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Data.qrc
