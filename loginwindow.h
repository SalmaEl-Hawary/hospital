#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "patient.h"
#include "staff.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QMap<int, Patient>& patients, QMap<int, Staff> staffs, QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_SignUpPshButton_clicked();
    void on_LoginButton_clicked(); // New slot for login button

private:
    Ui::LoginWindow *ui;
    QMap<int, Patient>& patients; // Reference to the patients map
    QMap<int, Staff> staffs;
};

#endif // LOGINWINDOW_H
