#ifndef USERS_H
#define USERS_H

#include <QString>
#include <QJsonArray>
#include <QJsonObject>

using namespace std;

class User
{
private:
    QString username;
    QString email;
    QString password;
    QJsonArray shoppingHistory;

public:
    User();

    QString getUsername() const;
    void setUsername(const QString &value);

    QString getEmail() const;
    void setEmail(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    void setChart (QJsonObject &shoppingHisoty);
};

#endif // USERS_H
