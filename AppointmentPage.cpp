#include "AppointmentPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>

AppointmentPage::AppointmentPage(QWidget *parent) : QDialog(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Create buttons
    bookAppointmentButton = new QPushButton("Book Appointment", this);
    deleteAppointmentButton = new QPushButton("Delete Appointment", this);

    // Create stacked widget and pages
    stackedWidget = new QStackedWidget(this);
    doctorSelectionPage = new DoctorSelectionPage(this);

    // Create and set up the appointments text edit
    appointmentsTextEdit = new QTextEdit(this);
    appointmentsTextEdit->setReadOnly(true);

    // Add widgets to layout
    mainLayout->addWidget(appointmentsTextEdit);
    mainLayout->addWidget(bookAppointmentButton);
    mainLayout->addWidget(deleteAppointmentButton);
    mainLayout->addWidget(stackedWidget);

    stackedWidget->addWidget(doctorSelectionPage);

    // Connect buttons to slots
    connect(bookAppointmentButton, &QPushButton::clicked, this, &AppointmentPage::showDoctorSelectionPage);
    connect(deleteAppointmentButton, &QPushButton::clicked, this, &AppointmentPage::deleteAppointment);
}

void AppointmentPage::showDoctorSelectionPage() {
    // Switch to the DoctorSelectionPage where users can book appointments
    stackedWidget->setCurrentWidget(doctorSelectionPage);
}

void AppointmentPage::setAppointmentsText(const QString &text) {
    // Set the appointments text in the QTextEdit and store the current appointments
    appointmentsTextEdit->setText(text);
    currentAppointments = text.split("\n");
}

void AppointmentPage::bookAppointment() {
    // Logic for booking an appointment should be implemented here
    // This could involve interacting with `doctorSelectionPage`
}

void AppointmentPage::deleteAppointment() {
    // Prompt the user to select an appointment to delete
    bool ok;
    QString appointmentToDelete = QInputDialog::getItem(this, "Delete Appointment", "Select appointment to delete:", currentAppointments, 0, false, &ok);
    if (ok && !appointmentToDelete.isEmpty()) {
        // Remove the appointment from the list
        currentAppointments.removeAll(appointmentToDelete);
        // Update the text edit with the remaining appointments
        appointmentsTextEdit->setText(currentAppointments.join("\n"));

        // Update the patient data in the backend
        // This part requires access to the patient's data and might involve calling a method to update the data source.
    }
}
