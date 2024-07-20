// admin.h
#ifndef ADMIN_H
#define ADMIN_H

#include <QString>
#include <QMap>
#include <QVector>

class Admin
{
public:
    explicit Admin(const QString& username, const QString& password);
    ~Admin();

private:
    QString username;
    QString password;
    QMap<QString, QString> staff;

};

#endif // ADMIN_H
