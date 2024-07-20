#ifndef STAFF_H
#define STAFF_H

#include <QString>
#include <QMap>

class Staff {
public:
    Staff(const QString& username, const QString& password, const QString& gender, int age, int id);

    static void readAdminData(const QString& filename, QMap<int, Staff>& staffMap);

    QString getUsername() const;
    QString getPassword() const;
    QString getGender() const;
    int getAge() const;
    int getId() const;

    void setUsername(const QString& username);
    void setPassword(const QString& password);
    void setGender(const QString& gender);
    void setAge(int age);
    void setId(int id);

private:
    QString m_username;
    QString m_password;
    QString m_gender;
    int m_age;
    int m_id;
};

#endif // STAFF_H
