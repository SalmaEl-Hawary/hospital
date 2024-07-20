#ifndef APPOINTMENTPAGE_H
#define APPOINTMENTPAGE_H

#include <QDialog>
#include <QPushButton>
#include <QStackedWidget>
#include <QTextEdit>
#include <QTableWidget>
#include "DoctorSelectionPage.h"

class AppointmentPage : public QDialog {
    Q_OBJECT

public:
    AppointmentPage(QWidget *parent = nullptr);
    void setAppointmentsText(const QString &text);

private slots:
    void showDoctorSelectionPage();
    void bookAppointment();
    void deleteAppointment();

private:
    QPushButton *bookAppointmentButton;
    QPushButton *deleteAppointmentButton;
    QStackedWidget *stackedWidget;
    DoctorSelectionPage *doctorSelectionPage;
    QTextEdit *appointmentsTextEdit;
    QStringList currentAppointments;
};

#endif // APPOINTMENTPAGE_H
