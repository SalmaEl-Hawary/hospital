#include "DoctorSelectionPage.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QBrush>

DoctorSelectionPage::DoctorSelectionPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    doctorComboBox = new QComboBox(this);

    slotTable = new QTableWidget(5, 4, this);
    QStringList days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    QStringList times = {"10:00 AM", "11:00 AM", "12:00 PM", "2:00 PM"};
    slotTable->setHorizontalHeaderLabels(times);
    slotTable->setVerticalHeaderLabels(days);

    layout->addWidget(doctorComboBox);
    layout->addWidget(slotTable);

    loadDoctorData();

    connect(doctorComboBox, &QComboBox::currentTextChanged, this, &DoctorSelectionPage::updateSlots);
    connect(slotTable, &QTableWidget::cellClicked, this, &DoctorSelectionPage::handleSlotClicked);

    if (!doctorComboBox->currentText().isEmpty()) {
        updateSlots(doctorComboBox->currentText());
    }
}

void DoctorSelectionPage::loadDoctorData() {
    QFile file(":/Systemdata/Systemdata/staffdata.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to open staff data file.");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList details = line.split(",");
        if (details.size() >= 5) {
            QString name = details[0];
            QString id = details[1];
            QString gender = details[2];
            QString age = details[3];
            QString experience = details[4];
            doctorComboBox->addItem(name);
            doctorData[name] = {id, gender, age, experience};
        }
    }
    file.close();
}

void DoctorSelectionPage::updateSlots(const QString &doctor) {
    // Clear the table
    for (int row = 0; row < slotTable->rowCount(); ++row) {
        for (int col = 0; col < slotTable->columnCount(); ++col) {
            slotTable->setItem(row, col, new QTableWidgetItem(""));
            slotTable->item(row, col)->setBackground(Qt::green);
        }
    }

    // Simulate doctor's availability based on name
    if (doctor == "ahmed") {
        slotTable->item(0, 1)->setBackground(Qt::red); // Unavailable on Monday at 11:00 AM
        slotTable->item(3, 3)->setBackground(Qt::red); // Unavailable on Thursday at 2:00 PM
    } else if (doctor == "sayed") {
        slotTable->item(1, 0)->setBackground(Qt::red); // Unavailable on Tuesday at 10:00 AM
        slotTable->item(4, 2)->setBackground(Qt::red); // Unavailable on Friday at 12:00 PM
    } else if (doctor == "omar") {
        slotTable->item(2, 1)->setBackground(Qt::red); // Unavailable on Wednesday at 11:00 AM
        slotTable->item(3, 0)->setBackground(Qt::red); // Unavailable on Thursday at 10:00 AM
    }
}

void DoctorSelectionPage::handleSlotClicked(int row, int column) {
    if (slotTable->item(row, column)->background() == Qt::green) {
        QMessageBox::information(this, "Appointment", "Slot is available. Appointment booked.");
        slotTable->item(row, column)->setBackground(Qt::red); // Mark as booked
    } else {
        QMessageBox::warning(this, "Appointment", "Slot is not available. Please choose another slot.");
    }
}
