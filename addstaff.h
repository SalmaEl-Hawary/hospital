#ifndef ADDSTAFF_H
#define ADDSTAFF_H

#include <QDialog>
#include <QMap>
#include <staff.h>

namespace Ui {
class addstaff;
}

class addstaff : public QDialog
{
    Q_OBJECT

public:
    explicit addstaff(QMap<int, Staff>& staffs, QWidget *parent = nullptr);
    ~addstaff();

private slots:
    void on_add_clicked();

private:
    Ui::addstaff *ui;
    QMap<int, Staff>& m_staffs;
};

#endif // ADDSTAFF_H





