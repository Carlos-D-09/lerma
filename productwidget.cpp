#include "productwidget.h"
<<<<<<< HEAD

QString Product::getId() const
=======
#include <QString>
#include "ui_productwidget.h"

productWidget::productWidget(QWidget *parent, QString id, QString name, float price) :
    QWidget(parent),
    ui(new Ui::productWidget)
{
    ui->setupUi(this);
    QPixmap pix(":/Productos/imgs/"+ id);
    ui->productImage->setPixmap(pix);
    ui->productDescription->setText(name + "\n" + "$ " + QString::number(price));
}

productWidget::~productWidget()
{
    delete ui;
}

QString productWidget::getId() const
>>>>>>> widget_interfaz_grafica
{
    return id;
}

<<<<<<< HEAD
void Product::setId(const QString &value)
=======
void productWidget::setId(const QString &value)
>>>>>>> widget_interfaz_grafica
{
    id = value;
}

<<<<<<< HEAD
QString Product::getName() const
=======
QString productWidget::getName() const
>>>>>>> widget_interfaz_grafica
{
    return name;
}

<<<<<<< HEAD
void Product::setName(const QString &value)
=======
void productWidget::setName(const QString &value)
>>>>>>> widget_interfaz_grafica
{
    name = value;
}

<<<<<<< HEAD
float Product::getPrice() const
=======
float productWidget::getPrice() const
>>>>>>> widget_interfaz_grafica
{
    return price;
}

<<<<<<< HEAD
void Product::setPrice(const float &value)
=======
void productWidget::setPrice(float value)
>>>>>>> widget_interfaz_grafica
{
    price = value;
}
