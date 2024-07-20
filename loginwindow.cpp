#include "loginwindow.h"
#include "admindashboard.h"
#include "staffdashboard.h"
#include "ui_loginwindow.h"
#include "signupwindow.h"
#include "patientdashboard.h"
#include "QMessageBox"
#include <QCoreApplication>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "staff.h"

LoginWindow::LoginWindow(QMap<int, Patient>& patients,QMap<int, Staff> staffs, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::LoginWindow), patients(patients), staffs(staffs)
{
    ui->setupUi(this);
    connect(ui->LoginPshButtom, &QPushButton::clicked, this, &LoginWindow::on_LoginButton_clicked);
    ui->LoginErrorLabel->hide();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_SignUpPshButton_clicked()
{
    hide();
    SignUpWindow* signupwindow = new SignUpWindow(patients,staffs, this);
    signupwindow->setPatientsMap(patients); // Pass the patients map
    signupwindow->show();
}

void LoginWindow::on_LoginButton_clicked()
{
    bool validCredentials=false;

    qDebug() << "Login button clicked"; // Add this line for debugging
    // Get the entered username and password
    QString username = ui->LoginNameLEdit->text();
    QString password = ui->LoginPassLEdit->text();

    // Check if the user is a staff
    QFile staffFile(":/Systemdata/Systemdata/staffdata.txt");
    if (staffFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&staffFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(','); // Use comma as a delimiter
            if (parts[0] == username && parts[1] == password) {
                // Credentials are correct, open the staff window
                hide();
                QString gender = parts[2];
                QString age = parts[3];
                QString id = parts[4];

                    StaffDashboard* staffWindow = new StaffDashboard(patients, this);
                staffWindow->setStaffInfo(password, username, gender, age, id);
                staffWindow->show();
                staffFile.close();
                validCredentials=true;
                return; // Exit the function early
            }
        }
        staffFile.close();
    }

    QFile adminFile(":/Systemdata/Systemdata/adminsdata.txt");
    if (adminFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&adminFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split('\t'); // Adjust delimiter as needed
            if (parts.size() == 2 && parts[0] == username && parts[1] == password) {
                // Credentials are correct, open the admin window
                hide();
                AdminDashboard* adminWindow = new AdminDashboard(patients,staffs, this);
                adminWindow->setAdminInfo(username);
                adminWindow->show();
                adminFile.close();
                validCredentials=true;
                return; // Exit the function early
            }
        }
        adminFile.close();
    }

    for (const auto& key : patients.keys()) {
        if (patients.value(key).getUsername() == username && patients.value(key).getPassword() == password) {
            // Credentials are correct, open the patient window
            hide();
            PatientDashboard* patientWindow = new PatientDashboard(username, patients, staffs); // Allocate memory
            patientWindow->show();
            validCredentials=true;
            return; // Exit the function early
        }
    }


    // If the loop completes without finding a matching username and password, show an error message
    if(!validCredentials)
    {
        ui->LoginErrorLabel->show();
    }
}
