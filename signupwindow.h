#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QDialog>
#include <QMap>
#include "patient.h"
#include "staff.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SignUpWindow;
}
QT_END_NAMESPACE

class SignUpWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpWindow(QMap<int, Patient>& patients, QMap<int, Staff> staffs, QWidget *parent = nullptr);
    ~SignUpWindow();

    // Function to set the reference to the map of patients
    void setPatientsMap(QMap<int, Patient>& patients);

signals:
    void addNewPatient(const QString& username, const QString& password, int age, const QString& gender);

private slots:
    void on_SignUpPshButton_clicked();

    void on_SignToLoginpushButton_clicked();

private:
    Ui::SignUpWindow *ui;
    QMap<int, Patient>& patients; // Reference to the patients map
    QMap<int, Staff> staffs;
};

#endif // SIGNUPWINDOW_H
