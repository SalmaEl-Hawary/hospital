// operations.cpp

#include "operations.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMap>
#include "patient.h"
#include "staff.h"

void writePatientsToFile(const QMap<int, Patient>& patients, const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing:" << file.errorString();
        return;
    }

    QTextStream out(&file);
    for (const auto& patient : patients) {
        out << patient.getUsername() << ","
            << patient.getPassword() << ","
            << patient.getId() << ","
            << patient.viewMedicalRecords() << ","
            << patient.getTestResults() << ","
            << patient.getTreatmentPlans() << ","
            << patient.getAge() << ","
            << patient.getGender() << ",";

        const QStringList appointments = patient.getAppointments();
        if (!appointments.isEmpty()) {
            out << appointments.join(";"); // Appointments separated by semicolon
        }
        out << "\n";
    }

    file.close();
    qDebug() << "Data has been written to file successfully.";
}

void loadPatientsFromFile(QMap<int, Patient>& patients, const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');
        if (parts.size() < 9) continue; // Skip invalid lines

        QString username = parts[0];
        QString password = parts[1];
        int id = parts[2].toInt();
        QString medicalRecords = parts[3];
        QString testResults = parts[4];
        QString treatmentPlans = parts[5];
        int age = parts[6].toInt();
        QString gender = parts[7];

        // Retrieve appointments if available
        QStringList appointments;
        if (parts.size() >= 9 && !parts[8].isEmpty()) {
            appointments = parts[8].split(';'); // Appointments separated by semicolon
        }

        Patient newPatient(username, password, id, medicalRecords, gender, age);
        newPatient.setTestResults(testResults);
        newPatient.setTreatmentPlans(treatmentPlans);
        for(const QString& appointment : appointments) {
            newPatient.requestAppointment(appointment);
        }
        patients.insert(id, newPatient);
    }

    file.close();
    qDebug() << "Data has been loaded from file successfully.";
}

void readAdminData(const QString& filename, QMap<int, Staff>& staffMap) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open admin data file:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');
        if (parts.size() == 5) {
            QString username = parts[0];
            QString password = parts[1];
            QString gender = parts[2];
            int age = parts[3].toInt();
            int id = parts[4].toInt();
            Staff staff("", "", "", 0, 0); // Create a temporary staff object
            staff.setUsername(username);
            staff.setPassword(password);
            staff.setGender(gender);
            staff.setAge(age);
            staff.setId(id);
            staffMap.insert(id, staff); // Insert staff into the QMap with id as key
        }
    }
    file.close();
}

void writeAdminData(const QString& filename, const QMap<int, Staff>& staffMap) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open admin data file for writing:" << file.errorString();
        return;
    }

    QTextStream out(&file);
    for (auto it = staffMap.begin(); it != staffMap.end(); ++it) {
        const Staff& staff = it.value();
        out << staff.getUsername() << "," << staff.getPassword() << "," << staff.getGender() << "," << staff.getAge() << "," << staff.getId() << "\n";
    }

    file.close();
}
