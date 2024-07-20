#include "patient.h"
#include <QFile>
#include <QList>
#include <QTextStream>
#include "patient.h"

Patient::Patient(const QString& username, const QString& password, int id, const QString& medicalRecords, const QString& gender, int age)
    : username(username), password(password), id(id), medicalRecords(medicalRecords), gender(gender), age(age)
{
    // Initialize member variables
}

Patient::Patient() : id(0), age(0)
{
    // Initialize member variables or leave them uninitialized as per your requirement
}

Patient::~Patient()
{
    // Clean up
}
void Patient::addMessage(const QString& message) {
    messages.append(message);
}

QStringList Patient::getMessages() const {
    return messages;
}
// QString Patient::getMessage() const {
//     return message;
// }


void Patient::requestAppointment(const QString& date)
{
    // Request an appointment for the patient
    // Implementation details may vary based on your requirements
    appointments.push_back(date);
}

void Patient::cancelAppointment(const QString& date)
{
    // Cancel an appointment for the patient
    // Implementation details may vary based on your requirements
    for (auto it = appointments.begin(); it != appointments.end(); ++it) {
        if (*it == date) {
            appointments.erase(it);
            break;
        }
    }
}

void Patient::setUsername(const QString& newUsername)
{
    username = newUsername;
}

QString Patient::viewMedicalRecords() const
{
    // View medical records for the patient
    return medicalRecords;
}

QString Patient::getUsername() const
{
    return username;
}

QString Patient::getPassword() const
{
    return password;
}

int Patient::getId() const
{
    return id;
}

void Patient::setAge(int newAge)
{
    age = newAge;
}

void Patient::setGender(const QString& newGender)
{
    gender = newGender;
}

int Patient::getAge() const
{
    return age;
}

QString Patient::getGender() const
{
    return gender;
}

QList<QString> Patient::getAppointments() const {
    QList<QString> qAppointments;
    for (const auto& appointment : appointments) {
        qAppointments.append(appointment);
    }
    return qAppointments;
}

void Patient::setAppointments(const QList<QString>& newAppointments) {
    // Convert QList<QString> to std::vector<QString>
    appointments.clear(); // Clear existing appointments
    for (const QString& appointment : newAppointments) {
        appointments.push_back(appointment);
    }
}
