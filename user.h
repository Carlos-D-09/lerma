#ifndef USERS_H
#define USERS_H

#include <QString>

using namespace std;

class User
{
private:
    QString username;
    QString email;
    QString password;
public:
    User();

    QString getUsername() const;
    void setUsername(const QString &value);

    QString getEmail() const;
    void setEmail(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);
};

#endif // USERS_H
