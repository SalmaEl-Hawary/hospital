// staffdashboard.h
#ifndef STAFFDASHBOARD_H
#define STAFFDASHBOARD_H

#include <QDialog>
#include <QMap>
#include "patient.h"
#include "staff.h"
class LoginWindow;

namespace Ui {
class StaffDashboard;
}

class StaffDashboard : public QDialog
{
    Q_OBJECT

public:
    explicit StaffDashboard(QMap<int, Patient>& patients, QWidget *parent = nullptr);
    ~StaffDashboard();
    void setStaffInfo(const QString& password, const QString& username, const QString& gender, const QString& age, const QString& id);

private slots:
    void on_StaffToPatientPshButton_clicked();

    void on_pushButton_clicked();


private:
    Ui::StaffDashboard *ui;
    QMap<int, Patient>& m_patients;
    QMap<int, Staff> staffs;
    LoginWindow* loginWindow;
};

#endif // STAFFDASHBOARD_H
