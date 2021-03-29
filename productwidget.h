#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H

#include <QString>

using namespace std;

class Product{

public:
    QString getId() const;
    void setId(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    float getPrice() const;
    void setPrice(const float &value);

private:
    QString id;
    QString name;
    float price;
};

#endif // PRODUCTWIDGET_H

