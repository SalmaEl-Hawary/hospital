#include "schedulepage.h"
#include "patientdashboard.h"
#include "ui_schedulepage.h"
#include <QStringListModel>
#include "operations.h"

SchedulePage::SchedulePage(const QMap<int, Patient>& patients, const QString& username, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SchedulePage),
    m_patients(patients),
    m_username(username),
    patientDashboard(nullptr)
{
    ui->setupUi(this);
    registerpopulateComboBox();
    cancelpopulateComboBox();
}

SchedulePage::~SchedulePage()
{
    delete ui;
}

void SchedulePage::setAppointmentsText(const QString& text)
{
    QStringListModel *model = new QStringListModel(this);
    QStringList list;
    list << text;
    model->setStringList(list);
    ui->listView->setModel(model);
}

void SchedulePage::on_updateschedulepshbutton_clicked()
{
    // Handle update schedule button click
}

void SchedulePage::cancelpopulateComboBox()
{
    // Get the appointments for the current user
    QStringList userAppointments;
    for (auto it = m_patients.begin(); it != m_patients.end(); ++it) {
        if (it->getUsername() == m_username) {
            userAppointments = it->getAppointments();
            break;
        }
    }

    // Add the user appointments to the combo box
    ui->AppDateComboBox_2->addItems(userAppointments);
}


void SchedulePage::registerpopulateComboBox()
{
    // Populate the combobox with appointments from 1 to 30
    QStringList appointments;
    for (int i = 1; i <= 30; ++i) {
        appointments << QString::number(i);
    }

    // Iterate through all patients
    for (auto it = m_patients.begin(); it != m_patients.end(); ++it) {
        // Retrieve the appointments for the current user
        QStringList userAppointments = it->getAppointments();

        // Remove the days that already have appointments registered
        for (const QString& appointment : userAppointments) {
            int index = appointments.indexOf(appointment);
            if (index != -1) {
                appointments.removeAt(index);
            }
        }
    }

    ui->AppDateComboBox->addItems(appointments);
}
void SchedulePage::on_updateappointmentbutton_clicked()
{
    // Retrieve the selected appointment from the combo box
    QString selectedAppointment = ui->AppDateComboBox->currentText();

    // Find the patient with the current username
    int patientId = -1;
    for (auto it = m_patients.begin(); it != m_patients.end(); ++it) {
        if (it->getUsername() == m_username) {
            patientId = it.key();
            break;
        }
    }

    // Check if patient with the username exists
    if (patientId != -1) {
        // Get the patient from the map
        Patient& patient = m_patients[patientId];

        // Add the selected appointment to the patient's appointments
        QStringList appointments = patient.getAppointments();
        appointments.append(selectedAppointment);
        patient.setAppointments(appointments);

        // Update the patient's data in the map
        m_patients[patientId] = patient;

        // Write the updated patient data back to the file
        writePatientsToFile(m_patients, ":/Systemdata/Systemdata/data.txt");

        // Remove the selected appointment from the combo box
        ui->AppDateComboBox->removeItem(ui->AppDateComboBox->currentIndex());

        // Update the appointments display
        QString appointmentsText;
        for (const QString& appointment : appointments) {
            appointmentsText += appointment + "\n";
        }
        setAppointmentsText(appointmentsText); // Update display

        // Add the selected appointment to the cancel appointment combo box
        ui->AppDateComboBox_2->addItem(selectedAppointment);
    }
}

void SchedulePage::on_cancelappointmentbutton_clicked()
{
    // Retrieve the selected appointment from the combo box
    QString selectedAppointment = ui->AppDateComboBox_2->currentText();

    // Find the patient with the current username
    int patientId = -1;
    for (auto it = m_patients.begin(); it != m_patients.end(); ++it) {
        if (it->getUsername() == m_username) {
            patientId = it.key();
            break;
        }
    }

    // Check if patient with the username exists
    if (patientId != -1) {
        // Get the patient from the map
        Patient& patient = m_patients[patientId];

        // Remove the selected appointment from the patient's appointments
        QStringList appointments = patient.getAppointments();
        appointments.removeAll(selectedAppointment);
        patient.setAppointments(appointments);

        // Update the patient's data in the map
        m_patients[patientId] = patient;

        // Write the updated patient data back to the file
        writePatientsToFile(m_patients, ":/Systemdata/Systemdata/data.txt");

        // Remove the selected appointment from the combo box
        ui->AppDateComboBox_2->removeItem(ui->AppDateComboBox_2->currentIndex());

        // Update the appointments display
        QString appointmentsText;
        for (const QString& appointment : appointments) {
            appointmentsText += appointment + "\n";
        }
        setAppointmentsText(appointmentsText); // Update display

        // Add the selected appointment back to the register appointment combo box
    }
}

void SchedulePage::on_Back5_clicked()
{
    hide();
    if (!patientDashboard) {
        patientDashboard = new PatientDashboard(m_username, m_patients, m_staffs);
    }
    patientDashboard->show();
}

