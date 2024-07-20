#include "staffdashboard.h"
#include "loginwindow.h"
#include "ui_staffdashboard.h"
#include "editpatientwindow.h"
#include <QFile>

StaffDashboard::StaffDashboard(QMap<int, Patient>& patients, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StaffDashboard),
    m_patients(patients),
    loginWindow(nullptr)

{
    ui->setupUi(this);
    ui->label_9->hide();
}

StaffDashboard::~StaffDashboard()
{
    delete ui;
}

void StaffDashboard::setStaffInfo(const QString& password, const QString& username, const QString& gender, const QString& age, const QString& id)
{
    ui->StaffNameLabel->setText(username);
    ui->StaffGenderLabel->setText(gender);
    ui->StaffAgeLabel->setText(age);
    ui->STaffIDLabel->setText(id);
    // Write staff information to file
    QFile file("staff_info.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << username << "," << password << "," << gender << "," << age << "\n";
        file.close();
    }
}

void StaffDashboard::on_StaffToPatientPshButton_clicked()
{
    // Retrieve the patient ID from the user input
    QString ID = ui->id->text();
    qDebug() << "Text from line edit:" << ID;
    int patientId = ID.toInt();
    qDebug() << "Patient ID:" << patientId;

    // Check if the patient ID exists in the map
    auto it = m_patients.find(patientId);
    if (it != m_patients.end()) {
        qDebug() << "Patient found in the map";
        // Create an instance of EditPatientWindow with the patient ID
        EditPatientWindow *editPatient = new EditPatientWindow(m_patients, patientId);
        // Show the window
        editPatient->show();
    }
    else {
        qDebug() << "Patient with ID" << patientId << "not found.";
        ui->label_9->show();
    }
}

void StaffDashboard::on_pushButton_clicked()
{
    hide();
    if (!loginWindow) { // Add this condition
        loginWindow = new LoginWindow(m_patients, staffs);
    }
    loginWindow->show();
}

