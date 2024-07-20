// editpatientwindow.h
#ifndef EDITPATIENTWINDOW_H
#define EDITPATIENTWINDOW_H

#include <QDialog>
#include <QMap>
#include "patient.h"

namespace Ui {
class EditPatientWindow;
}

class EditPatientWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditPatientWindow(QMap<int, Patient>& patients, int patientId, QWidget *parent = nullptr);
    ~EditPatientWindow();

private slots:
    void on_AppendpushButton_clicked();
    void on_AddNewPshButton_clicked();

    void on_ResultspushButton_clicked();

    void on_TPlanspushButton_clicked();

    void displayPatientInfo();

    void on_BackButton2_clicked();

private:
    Ui::EditPatientWindow *ui;
    QMap<int, Patient>& m_patients;
    int m_patientId;
};

#endif // EDITPATIENTWINDOW_H
