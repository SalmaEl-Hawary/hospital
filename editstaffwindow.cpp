// editstaffwindow.cpp

#include "editstaffwindow.h"
#include "loginwindow.h"
#include "ui_editstaffwindow.h"
#include "operations.h"
#include "loginwindow.h"
#include "editstaffwindow.h"
#include <QFile>
#include "staff.h"
#include <operations.h>
#include <addstaff.h>

EditStaffWindow::EditStaffWindow(int ID, QMap<int, Staff>& staffMap, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditStaffWindow),
    m_staffID(ID),
    m_staffMap(staffMap)
{
    ui->setupUi(this);
    fillLabels();
}

EditStaffWindow::~EditStaffWindow()
{
    delete ui;
}

void EditStaffWindow::fillLabels() {
    // Find staff member in map
    auto it = m_staffMap.find(m_staffID);
    if (it != m_staffMap.end()) {
        const Staff& staff = it.value();
        // Update labels with staff data
        ui->label_9Name->setText(staff.getUsername());
        ui->PassLabel->setText(staff.getPassword());
        ui->label_13Gender->setText(staff.getGender());
        ui->AgeLabel_2->setText(QString::number(staff.getAge()));
        ui->label_13ID2->setText(QString::number(staff.getId()));
    }
}

void EditStaffWindow::on_pushButtonID_clicked()
{
    QString newId = ui->lineEdit->text();
    updateStaffData(newId, 4); // Index 4 corresponds to ID field in staff data
}

void EditStaffWindow::on_NamepushButton_clicked()
{
    QString newName = ui->lineEdit->text();
    updateStaffData(newName, 0); // Index 0 corresponds to username field in staff data
}
void EditStaffWindow::on_pushButtonPass_clicked()
{
    QString newPassword = ui->lineEdit->text();
    updateStaffData(newPassword, 1); // Index 1 corresponds to password field in staff data
}
void EditStaffWindow::on_GenderpushButton_2_clicked()
{
    QString newGender = ui->lineEdit->text();
    updateStaffData(newGender, 2); // Index 2 corresponds to gender field in staff data
}

void EditStaffWindow::on_AgepushButton_3_clicked()
{
    QString newAge = ui->lineEdit->text();
    updateStaffData(newAge, 3); // Index 3 corresponds to age field in staff data
}

void EditStaffWindow::updateStaffData(const QString& newValue, int fieldIndex)
{
    // Find staff member in map
    for (auto it = m_staffMap.begin(); it != m_staffMap.end(); ++it) {
        Staff& staff = it.value();
        if (staff.getId() == m_staffID) {
            // Update staff data
            switch (fieldIndex) {
            case 0:
                staff.setUsername(newValue);
                break;
            case 1:
                staff.setPassword(newValue);
                break;
            case 2:
                staff.setGender(newValue);
                break;
            case 3:
                staff.setAge(newValue.toInt());
                break;
            case 4:
                staff.setId(newValue.toInt());
                break;
            default:
                // Invalid field index
                return;
            }

            // Write updated staff data to file
            writeAdminData(":/Systemdata/Systemdata/staffdata.txt", m_staffMap);
            // Update labels in window (assuming labels are named appropriately in the UI)
            ui->label_9Name->setText(staff.getUsername());
            ui->PassLabel->setText(staff.getPassword());
            ui->label_13Gender->setText(staff.getGender());
            ui->AgeLabel_2->setText(QString::number(staff.getAge()));
            ui->label_13ID2->setText(QString::number(staff.getId()));

            // Exit loop once staff member is found and updated
            break;
        }
    }
}




void EditStaffWindow::on_BackButton3_clicked()
{
    hide();
}

