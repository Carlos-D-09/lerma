#include "productwidget.h"
#include <QString>
#include "ui_productwidget.h"

productWidget::productWidget(QWidget *parent, QString id, QString name, float price) :
    QWidget(parent),
    ui(new Ui::productWidget)
{
    ui->setupUi(this);
    QPixmap pix(":/Productos/imgs/"+ id);
    ui->productImage->setPixmap(pix);
    ui->productDescription->setText(name);
    ui->productPrice->setText(QString::number(price));
}

productWidget::~productWidget()
{
    delete ui;
}

QString productWidget::getId() const
{
    return id;
}

void productWidget::setId(const QString &value)
{
    id = value;
}

QString productWidget::getName() const
{
    return name;
}

void productWidget::setName(const QString &value)
{
    name = value;
}

float productWidget::getPrice() const
{
    return price;
}

void productWidget::setPrice(float value)
{
    price = value;
}
