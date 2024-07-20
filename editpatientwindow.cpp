#include "editpatientwindow.h"
#include "ui_editpatientwindow.h"
#include <QDebug>
#include "operations.h"

EditPatientWindow::EditPatientWindow(QMap<int, Patient>& patients, int patientId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPatientWindow),
    m_patients(patients),
    m_patientId(patientId)
{
    ui->setupUi(this);
    displayPatientInfo();
}

EditPatientWindow::~EditPatientWindow()
{
    delete ui;
}

void EditPatientWindow::displayPatientInfo()
{
    // Find the patient in the map by ID (assuming patientId is valid)
    auto it = m_patients.find(m_patientId);
    if (it != m_patients.end()) {
        Patient& patient = it.value();

        // Set patient information in labels
        ui->label_9->setText(patient.getUsername());
        ui->IDLabel->setText(QString::number(patient.getId()));
        ui->label_13->setText(patient.getGender());
        ui->IDLabel_2->setText(QString::number(patient.getAge()));

        // Display medical records, treatment plans, and test results in text browsers
        ui->MedRectextBrowser_2->setText(patient.viewMedicalRecords());
        ui->textBrowser_3->setText(patient.getTestResults());
        ui->textBrowser_4->setText(patient.getTreatmentPlans());
        ui->ACCESSMESS->setText(patient.getMessages().join("\n"));

    }
}

void EditPatientWindow::on_AppendpushButton_clicked()
{
    qDebug() << "Append button clicked";

    QString newMedRecords = ui->MedRecordslineEdit->text();

    // Find the patient in the map by ID (assuming patientId is valid)
    auto it = m_patients.find(m_patientId);
    if (it != m_patients.end()) {
        qDebug() << "Patient found in the map";
        // Append the new medical record to the existing medical history
        QString currentMedicalHistory = it.value().viewMedicalRecords();
        currentMedicalHistory += newMedRecords;
        it.value().medicalRecords = currentMedicalHistory;

        // Update the medical history
        writePatientsToFile(m_patients, ":/Systemdata/Systemdata/data.txt");
        ui->MedRectextBrowser_2->setText(currentMedicalHistory);

    } else {
        qDebug() << "Patient not found in the map";
    }
}

void EditPatientWindow::on_AddNewPshButton_clicked()
{
    QString newMedRecords = ui->MedRecordslineEdit->text();

    // Find the patient in the map by ID (assuming patientId is valid)
    auto it = m_patients.find(m_patientId);
    if (it != m_patients.end()) {
        it.value().medicalRecords = newMedRecords;
        // Update the medical history
        writePatientsToFile(m_patients, ":/Systemdata/Systemdata/data.txt");
        ui->MedRectextBrowser_2->setText(newMedRecords);
    }
}

void EditPatientWindow::on_ResultspushButton_clicked()
{
    QString newResults = ui->plansandReslineEdit->text();

    // Find the patient in the map by ID (assuming patientId is valid)
    auto it = m_patients.find(m_patientId);
    if (it != m_patients.end()) {
        QString currentResults = it.value().getTestResults();
        currentResults += newResults; // Append new results
        it.value().setTestResults(currentResults);

        // Update the test results
        writePatientsToFile(m_patients, ":/Systemdata/Systemdata/data.txt");

        // Update the display
        ui->textBrowser_3->setText(currentResults);
    }
}

void EditPatientWindow::on_TPlanspushButton_clicked()
{
    QString newPlans = ui->plansandReslineEdit->text();

    // Find the patient in the map by ID (assuming patientId is valid)
    auto it = m_patients.find(m_patientId);
    if (it != m_patients.end()) {
        QString currentPlans = it.value().getTreatmentPlans();
        currentPlans += newPlans; // Append new plans
        it.value().setTreatmentPlans(currentPlans);

        // Update the treatment plans
        writePatientsToFile(m_patients, ":/Systemdata/Systemdata/data.txt");

        // Update the display
        ui->textBrowser_4->setText(currentPlans);
    }
}

void EditPatientWindow::on_BackButton2_clicked()
{
    hide();
}

