// fileoperations.h

#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <QMap>
#include "patient.h"
#include "staff.h"

void writePatientsToFile(const QMap<int, Patient>& patients, const QString& filePath);
void loadPatientsFromFile(QMap<int, Patient>& patients, const QString& filePath);
void readAdminData(const QString& filename, QMap<int, Staff>& staffMap);
void writeAdminData(const QString& filename, const QMap<int, Staff>& staffMap);


#endif // FILEOPERATIONS_H
