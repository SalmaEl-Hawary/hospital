#include "signupwindow.h"
#include "ui_signupwindow.h"
#include "loginwindow.h"
#include <QMessageBox>
#include "staff.h"
#include <operations.h>

SignUpWindow::SignUpWindow(QMap<int, Patient>& patients,QMap<int, Staff> staffs, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpWindow),
    patients(patients), // Initialize the reference member in the constructor initializer list
    staffs(staffs)
{
    ui->setupUi(this);
}

SignUpWindow::~SignUpWindow()
{
    delete ui;
}

void SignUpWindow::setPatientsMap(QMap<int, Patient>& patients)
{
    this->patients = patients;
}

void SignUpWindow::on_SignUpPshButton_clicked()
{
    // Get username, password, and age from line edits
    QString username = ui->SignNamelineEdit->text();
    QString password = ui->SignPasslineEdit->text();
    QString confirmPass = ui->ConfPasslineEdit_3->text();
    QString ageStr = ui->AgelineEdit->text();
    QString gender;

    // Validate username
    if (username.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a username.");
        return;
    }

    // Validate password
    if (password.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a password.");
        return;
    }

    // Validate confirm password
    if (confirmPass.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please confirm your password.");
        return;
    }

    // Check if password matches confirm password
    if (password != confirmPass) {
        QMessageBox::warning(this, "Warning", "Passwords do not match.");
        return;
    }

    // Validate age
    bool ok;
    int age = ageStr.toInt(&ok);
    if (!ok || age <= 0) {
        QMessageBox::warning(this, "Warning", "Please enter a valid age.");
        return;
    }

    // Validate gender
    if (ui->MaleradioButton_2->isChecked()) {
        gender = "Male";
    } else if (ui->FemaleradioButton->isChecked()) {
        gender = "Female";
    } else {
        QMessageBox::warning(this, "Warning", "Please select a gender.");
        return;
    }

    // Emit the signal to add a new patient
    int id = patients.size() + 1;
    Patient newPatient(username, password, id, "", gender, age);
    patients.insert(id, newPatient);
    writePatientsToFile(patients, ":/Systemdata/Systemdata/data.txt");

    hide();

    LoginWindow* loginwindow = new LoginWindow(patients, staffs);
    loginwindow->show();
}

void SignUpWindow::on_SignToLoginpushButton_clicked()
{
    LoginWindow* loginwindow = new LoginWindow(patients,staffs);
    loginwindow->show();

    // Close the sign-up window
    close();
}
