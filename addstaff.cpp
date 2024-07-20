#include "addstaff.h"
#include "ui_addstaff.h"
#include <QMap>
#include <operations.h>
#include <staff.h>
addstaff::addstaff(QMap<int, Staff>& staffs, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addstaff),
    m_staffs(staffs)
{
    ui->setupUi(this);
}
addstaff::~addstaff()
{
    delete ui;
}

void addstaff::on_add_clicked()
{
    QString username = ui->staffname->text();
    QString password = ui->staffpassword->text();
    QString gender = ui->staffgender_2->text();
    int age = ui->staffage->text().toInt();
    int id = m_staffs.size() + 1;

    // Create a new staff member
    Staff newStaff(username, password, gender, age, id);

    // Add the staff member to the map
    m_staffs.insert(id, newStaff);

    // Update the staff data file
    writeAdminData(":/Systemdata/Systemdata/staffdata.txt", m_staffs);

    // Close the window
    //this->accept();
    hide();
}

