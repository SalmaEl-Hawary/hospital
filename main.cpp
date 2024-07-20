#include "signupwindow.h"
#include "editpatientwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMap>
#include "patient.h"
#include "operations.h"



void addPatient(QMap<int, Patient>& patients, const QString& username, const QString& password, int age, const QString& gender) {
    int id = patients.size() + 1;
    Patient newPatient(username, password, id, "", gender, age);
    patients.insert(id, newPatient);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QString filePath = ":/Systemdata/Systemdata/data.txt";
    QMap<int, Patient> patients;

    QMap<int, Staff> staffMap;
    readAdminData(":/Systemdata/Systemdata/staffdata.txt", staffMap);

    loadPatientsFromFile(patients, filePath);
    SignUpWindow w(patients, staffMap);
    w.show();


    return a.exec();
}
