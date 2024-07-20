// editstaffwindow.h

#ifndef EDITSTAFFWINDOW_H
#define EDITSTAFFWINDOW_H

#include <QDialog>
#include <QMap>
#include "staff.h"

namespace Ui {
class EditStaffWindow;
}

class EditStaffWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditStaffWindow(int username, QMap<int, Staff>& staffMap, QWidget *parent = nullptr);
    void fillLabels();
    ~EditStaffWindow();

private slots:
    void on_pushButtonID_clicked();
    void on_NamepushButton_clicked();
    void on_GenderpushButton_2_clicked();
    void on_AgepushButton_3_clicked();

    void on_pushButtonPass_clicked();

    void on_BackButton3_clicked();

    void on_BackButton4_clicked();

private:
    Ui::EditStaffWindow *ui;
    int m_staffID;
    QMap<int, Staff>& m_staffMap;

    // Private helper function to update staff data in file and window
    void updateStaffData(const QString& newValue, int fieldIndex);
};

#endif // EDITSTAFFWINDOW_H
