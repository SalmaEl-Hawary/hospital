// schedulepage.h
#ifndef SCHEDULEPAGE_H
#define SCHEDULEPAGE_H

#include <QDialog>
#include <QMap>
#include <QList>
#include "patient.h"
#include "staff.h"
class PatientDashboard;

namespace Ui {
class SchedulePage;
}

class SchedulePage : public QDialog
{
    Q_OBJECT

public:
    explicit SchedulePage(const QMap<int, Patient>& patients, const QString& username, QWidget *parent = nullptr);
    ~SchedulePage();

    void setAppointmentsText(const QString& text);
    void registerpopulateComboBox();
    void cancelpopulateComboBox();
private slots:
    void on_updateschedulepshbutton_clicked();

    void on_updateappointmentbutton_clicked();

    void on_cancelappointmentbutton_clicked();

    void on_Back5_clicked();

private:
    Ui::SchedulePage *ui;
    QMap<int, Patient> m_patients;
    QString m_username;
    QMap<int, Staff> m_staffs;
    PatientDashboard* patientDashboard;
};

#endif // SCHEDULEPAGE_H
