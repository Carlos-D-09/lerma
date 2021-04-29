#include "user.h"


QString User::getUsername() const
{
    return username;
}

void User::setUsername(const QString &value)
{
    username = value;
}

QString User::getEmail() const
{
    return email;
}

void User::setEmail(const QString &value)
{
    email = value;
}

QString User::getPassword() const
{
    return password;
}

void User::setPassword(const QString &value)
{
    password = value;
}

void User::setChart(QJsonObject &obj)
{
    if(obj.contains("purchase") == true)
    {
        this->shoppingHistory = obj["purchase"].toArray();
    }
}

User::User()
{

}
