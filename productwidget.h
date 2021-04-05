#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H

<<<<<<< HEAD
#include <QString>

using namespace std;

class Product{

public:
=======
#include <QWidget>
#include <QString>

namespace Ui {
class productWidget;
}

class productWidget : public QWidget
{
    Q_OBJECT

public:
    explicit productWidget(QWidget *parent = 0, QString id = "", QString name = "", float price = 0);
    ~productWidget();

>>>>>>> widget_interfaz_grafica
    QString getId() const;
    void setId(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    float getPrice() const;
<<<<<<< HEAD
    void setPrice(const float &value);

private:
=======
    void setPrice(float value);

private:
    Ui::productWidget *ui;
>>>>>>> widget_interfaz_grafica
    QString id;
    QString name;
    float price;
};

#endif // PRODUCTWIDGET_H
<<<<<<< HEAD

=======
>>>>>>> widget_interfaz_grafica
