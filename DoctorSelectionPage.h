#ifndef DOCTORSELECTIONPAGE_H
#define DOCTORSELECTIONPAGE_H

#include <QWidget>
#include <QComboBox>
#include <QTableWidget>
#include <QMap>
#include <QString>

class DoctorSelectionPage : public QWidget {
    Q_OBJECT

public:
    DoctorSelectionPage(QWidget *parent = nullptr);

private slots:
    void updateSlots(const QString &doctor);
    void handleSlotClicked(int row, int column);

private:
    void loadDoctorData();
    QComboBox *doctorComboBox;
    QTableWidget *slotTable;
    QMap<QString, QStringList> doctorData;
};

#endif // DOCTORSELECTIONPAGE_H
