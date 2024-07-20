// patientdashboard.cpp
#include "patientdashboard.h"
#include "loginwindow.h"
#include "ui_patientdashboard.h"
#include "schedulepage.h"
#include "AppointmentPage.h"
#include <QStringListModel>

PatientDashboard::PatientDashboard(const QString& username, const QMap<int, Patient>& patients, const QMap<int, Staff>& staffs, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PatientDashboard),
    m_username(username),
    m_patients(patients),
    m_staffs(staffs)
{
    ui->setupUi(this);

    // Display the username in the window
    ui->label_9->setText(m_username);
    sendMessageButton = ui->sendMessageButton;
    connect(sendMessageButton, &QPushButton::clicked, this, &PatientDashboard::on_sendMessageButton_clicked);
    textBrowser_messages = ui->messages_view;
    // Find the patient with the username
    int patientId = -1;
    for (auto it = m_patients.begin(); it != m_patients.end(); ++it) {
        if (it.value().getUsername() == username) {
            patientId = it.key();
            break;
        }
    }

    // Check if patient with the username exists
    if (patientId != -1) {
        const Patient& patient = m_patients.value(patientId);

        // Display patient data in the window
        ui->IDLabel->setText(QString::number(patient.getId()));

        // Display medical record using a QListView
        QStringList medicalRecords;
        medicalRecords << patient.viewMedicalRecords();
        QStringListModel *model = new QStringListModel(medicalRecords, this);
        ui->MedReclistView->setModel(model);

        // Display appointments
        QString appointments;
        for (const QString& appointment : patient.getAppointments()) {
            appointments += appointment + "\n";
        }
        ui->textBrowser_3->setText(appointments);

        // Display treatment plans
        ui->textBrowser_2->setText(patient.getTreatmentPlans());

        // Display test results
        ui->textBrowser->setText(patient.getTestResults());

        // Display the message in the text browser
        QStringList messages = patient.getMessages();
       // qDebug() << "Retrieved message for patient: " << message; // Debugging statement
      //  ui->messages_view->setText(message);
        ui->messages_view->setText(patient.getMessages().join("\n"));
    }
}

void PatientDashboard::on_pushButton_2_clicked()
{
    SchedulePage* schedulepage = new SchedulePage(m_patients, m_username, this);
    schedulepage->show();
}

void PatientDashboard::on_manageAppPshButton_clicked()
{
    // Find the patient with the current username
    int patientId = -1;
    for (auto it = m_patients.begin(); it != m_patients.end(); ++it) {
        if (it.value().getUsername() == m_username) {
            patientId = it.key();
            break;
        }
    }

    if (patientId != -1) {
        const Patient& patient = m_patients.value(patientId);
        QStringList appointments = patient.getAppointments();

        // Create an instance of AppointmentPage
        AppointmentPage* appointmentPage = new AppointmentPage(this);
        appointmentPage->setAppointmentsText(appointments.join("\n"));

        // Show the AppointmentPage dialog
        appointmentPage->QDialog::exec();

        // After the dialog is closed, update the appointments text in the dashboard
        ui->textBrowser_3->setText(patient.getAppointments().join("\n"));
    }

    // // Create an instance of the SchedulePage dialog
    // SchedulePage* schedulePage = new SchedulePage(m_patients, m_username, this);

    // // Find the patient with the current username
    // int patientId = -1;
    // for (auto it = m_patients.begin(); it != m_patients.end(); ++it) {
    //     if (it.value().getUsername() == m_username) {
    //         patientId = it.key();
    //         break;
    //     }
    // }

    // // Check if patient with the username exists
    // if (patientId != -1) {
    //     // Get the appointments for the current patient
    //     const Patient& patient = m_patients.value(patientId);
    //     QStringList appointments = patient.getAppointments();

    //     // Display the appointments in the ApptextEdit widget
    //     QString appointmentsText;
    //     for (const QString& appointment : appointments) {
    //         appointmentsText += appointment + "\n";
    //     }
    //     schedulePage->setAppointmentsText(appointmentsText);
    // }
    // hide();
    // // Show the SchedulePage dialog
    // schedulePage->exec();

}
void PatientDashboard::on_sendMessageButton_clicked()
{
    // Get the message from the text edit
    QString message = ui->textEdit_chat->toPlainText();

    if (!message.isEmpty()) {
        // Find the patient with the current username
        int patientId = -1;
        for (auto it = m_patients.begin(); it != m_patients.end(); ++it) {
            if (it.value().getUsername() == m_username) {
                patientId = it.key();
                break;
            }
        }

        if (patientId != -1) {
            // Store the message in the Patient object
            m_patients[patientId].addMessage(message);

            // Append the message to the messages text browser
            ui->messages_view->append(message);
            ui->messages_view->setText(m_patients[patientId].getMessages().join("\n"));

            // Optionally, you can also display the message immediately if needed
            // ui->messages_view->setText(m_patients[patientId].getMessage());

            // Clear the text edit after sending the message
            ui->textEdit_chat->clear();
        } else {
            qDebug() << "Patient not found in the map";
        }
    } else {
        qDebug() << "Message is empty, nothing to send.";
    }
}
PatientDashboard::~PatientDashboard()
{
    delete ui;
}

void PatientDashboard::on_BackButton4_clicked()
{
    hide();
    LoginWindow* loginwindow = new LoginWindow(m_patients, m_staffs);
    loginwindow->show();
}

