#include "admindashboard.h"
#include "loginwindow.h"
#include "ui_admindashboard.h"
#include "editpatientwindow.h"
#include "editstaffwindow.h"
#include <QFile>
#include "staff.h"
#include <operations.h>
#include <addstaff.h>
AdminDashboard::AdminDashboard(QMap<int, Patient>& patients,QMap<int, Staff> staffs, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDashboard),
    m_patients(patients),
    staffs(staffs)
{
    ui->setupUi(this);
    ui->Errorlabel_8->hide();
    ui->Errorlabel_9->hide();
    ui->Errorlabel_10->hide();

}

AdminDashboard::~AdminDashboard()
{
    delete ui;
}

void AdminDashboard::setAdminInfo(const QString& username)
{
    ui->AdminNameLabel->setText(username);
}

void AdminDashboard::on_AdminViewStaffPshButton_clicked()
{
    // Retrieve the staff ID from the user input
    int staffID = ui->AdminToStafflineEdit->text().toInt();

    bool staffFound = false; // Assume staff member not found by default

    // Check if the staff ID exists in the staffs map
    auto it = staffs.find(staffID);
    if (it != staffs.end()) {
        qDebug() << "Staff member found in the map";
        // Create an instance of EditStaffWindow with the staff ID and staffs map
        EditStaffWindow *editStaff = new EditStaffWindow(staffID, staffs);
        // Show the window
        editStaff->show();
        staffFound = true; // Staff member found
    }
    else {
        qDebug() << "Staff member with ID" << staffID << "not found.";
        // Display an error message or handle it as needed
    }

    // Show or hide the error label based on whether the staff member was found
    ui->Errorlabel_9->setVisible(!staffFound);
}




void AdminDashboard::on_AdminViewPatientPshButton_clicked()
{
    // Retrieve the patient ID from the user input
    QString ID = ui->AdminToPatientlineEdit->text();
    qDebug() << "Text from line edit:" << ID;
    int patientId = ID.toInt();
    qDebug() << "Patient ID:" << patientId;

    bool patientFound = false; // Assume patient not found by default

    // Check if the patient ID exists in the map
    auto it = m_patients.find(patientId);
    if (it != m_patients.end()) {
        qDebug() << "Patient found in the map";
        // Create an instance of EditPatientWindow with the patient ID
        EditPatientWindow *editPatient = new EditPatientWindow(m_patients, patientId);
        // Show the window
        editPatient->show();
        patientFound = true; // Patient found
    }
    else {
        qDebug() << "Patient with ID" << patientId << "not found.";
        // Display error message or handle it as needed
    }

    // Show or hide the error label based on whether the patient was found
    ui->Errorlabel_8->setVisible(!patientFound);
}

void AdminDashboard::on_removepushbutton_clicked()
{
    // Retrieve the staff ID from the user input
    int staffID = ui->removelineedit->text().toInt();
    bool errorOccurred = true; // Assume error by default

    // Check if the staff ID exists in the staffs map
    auto it = staffs.find(staffID);
    if (it != staffs.end()) {
        qDebug() << "Staff member found in the map";
        // Remove the staff member from the staffs map
        staffs.remove(staffID);
        // Update the staff data file
        writeAdminData(":/Systemdata/Systemdata/staffdata.txt", staffs);

        // Clear the QLineEdit after successful removal
        ui->removelineedit->clear();
        errorOccurred = false; // No error occurred
    }
    else {
        qDebug() << "Staff member with ID" << staffID << "not found.";
        // Display an error message or handle it as needed
    }

    // Show or hide the error label based on the value of errorOccurred
    ui->Errorlabel_10->setVisible(errorOccurred);
}

void AdminDashboard::on_pushButton_2_clicked()
{
    // Close the current window
    //this->close();

    // Open the AddStaff window
    addstaff addstaffw(staffs);
    addstaffw.exec(); // Modal window
}


void AdminDashboard::on_Backbutton_clicked()
{
    hide();
    LoginWindow* loginwindow = new LoginWindow(m_patients, staffs);
    loginwindow->show();
}

