#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QDialog>
#include <QMap>
#include "patient.h"
#include <staff.h>
namespace Ui {
class AdminDashboard;
}

class AdminDashboard : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDashboard(QMap<int, Patient>& patients,QMap<int, Staff> staffs, QWidget *parent = nullptr);
    ~AdminDashboard();
    void setAdminInfo(const QString& username);

private slots:
    void on_AdminViewStaffPshButton_clicked();
    void on_AdminViewPatientPshButton_clicked();

    void on_removepushbutton_clicked();

    void on_pushButton_2_clicked();

    void on_Backbutton_clicked();

private:
    Ui::AdminDashboard *ui;
    QMap<int, Patient>& m_patients;
    QMap<int, Staff> staffs;
};

#endif // ADMINDASHBOARD_H
