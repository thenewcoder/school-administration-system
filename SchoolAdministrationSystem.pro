QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp\
        mainwindow.cpp \
    databasemanager.cpp \
    adminmenuform.cpp \
    settings.cpp \
    login.cpp \
    pagehomeform.cpp \
    pagesettingsform.cpp \
    pageteachersform.cpp \
    pagestudentsform.cpp \
    pageclassesform.cpp \
    editteacherdialog.cpp \
    editstudentdialog.cpp \
    teacher.cpp \
    student.cpp \
    schoolsettingsform.cpp \
    personalprofileform.cpp \
    school.cpp \
    user.cpp \
    editclassdialog.cpp \
    class.cpp \
    selectordialog.cpp \
    pageotherform.cpp \
    editotherdialog.cpp \
    wizarddatabasesetup.cpp \
    wizardintropage.cpp \
    wizardsetup.cpp \
    wizardsummarypage.cpp \
    wizardusersetuppage.cpp \
    pageattendanceform.cpp \
    editattendancedialog.cpp \
    classrecord.cpp \
    pageactivitiesform.cpp \
    editactivitydialog.cpp \
    activity.cpp \
    systemsettingsform.cpp

HEADERS  += mainwindow.h \
    databasemanager.h \
    adminmenuform.h \
    settings.h \
    login.h \
    pagehomeform.h \
    pagesettingsform.h \
    pageteachersform.h \
    pagestudentsform.h \
    pageclassesform.h \
    editteacherdialog.h \
    editstudentdialog.h \
    teacher.h \
    student.h \
    schoolsettingsform.h \
    personalprofileform.h \
    school.h \
    user.h \
    editclassdialog.h \
    class.h \
    selectordialog.h \
    pageotherform.h \
    editotherdialog.h \
    wizarddatabasesetup.h \
    wizardintropage.h \
    wizardsetup.h \
    wizardsummarypage.h \
    wizardusersetuppage.h \
    pageattendanceform.h \
    editattendancedialog.h \
    classrecord.h \
    pageactivitiesform.h \
    editactivitydialog.h \
    activity.h \
    systemsettingsform.h

FORMS    += mainwindow.ui \
    adminmenuform.ui \
    pagehomeform.ui \
    pagesettingsform.ui \
    pageteachersform.ui \
    pagestudentsform.ui \
    pageclassesform.ui \
    editteacherdialog.ui \
    editstudentdialog.ui \
    schoolsettingsform.ui \
    personalprofileform.ui \
    editclassdialog.ui \
    selectordialog.ui \
    pageotherform.ui \
    editotherdialog.ui \
    pageattendanceform.ui \
    editattendancedialog.ui \
    pageactivitiesform.ui \
    editactivitydialog.ui \
    systemsettingsform.ui

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:RC_ICONS += images/app.ico
win32:VERSION = 0.2
QMAKE_TARGET_COPYRIGHT = "(c) 2017-2022 Markus Berg"

TRANSLATIONS += translations/trans_zh_CN.ts \
                translations/trans_en_US.ts
