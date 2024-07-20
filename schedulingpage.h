#ifndef SCHEDULINGPAGE_H
#define SCHEDULINGPAGE_H

#include <QDialog>

namespace Ui {
class SchedulingPage;
}

class SchedulingPage : public QDialog
{
    Q_OBJECT

public:
    explicit SchedulingPage(QWidget *parent = nullptr);
    ~SchedulingPage();

private:
    Ui::SchedulingPage* ui;
};

#endif // SCHEDULINGPAGE_H
