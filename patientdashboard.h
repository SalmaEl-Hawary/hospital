// patientdashboard.h
#ifndef PATIENTDASHBOARD_H
#define PATIENTDASHBOARD_H

#include <QDialog>
#include <QString>
#include "patient.h"
#include "staff.h"
#include <QMap>
#include<QTextEdit>
#include<QTextBrowser>

namespace Ui {
class PatientDashboard;
}

class PatientDashboard : public QDialog
{
    Q_OBJECT

public:
    explicit PatientDashboard(const QString& username, const QMap<int, Patient>& patients, const QMap<int, Staff>& staffs, QWidget *parent = nullptr);
    ~PatientDashboard();
    QPushButton *sendMessageButton;
    QTextBrowser *textBrowser_messages;

signals:
    void patientDataChanged(QMap<int, Patient>& patients);

private slots:
    void on_pushButton_2_clicked();
    void on_manageAppPshButton_clicked();

    void on_BackButton4_clicked();
    void on_sendMessageButton_clicked();

private:
    Ui::PatientDashboard *ui;
    QString m_username;
    QMap<int, Patient> m_patients;
    QMap<int, Staff> m_staffs;
    QTextEdit *messageTextEdit;
    Patient patient;

};

#endif // PATIENTDASHBOARD_H
