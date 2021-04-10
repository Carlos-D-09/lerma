#include "productwidget.h"
#include "ui_productwidget.h"
#include <QString>

using namespace std;

productWidget::productWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::productWidget)
{
    ui->setupUi(this);
}

productWidget::~productWidget()
{
    delete ui;
}

QString productWidget::getName() const
{
    return name;
}

void productWidget::setName(const QString &value)
{
    name = value;
    ui->productName->setText(name);
}

QString productWidget::getId() const
{
    return id;
}

void productWidget::setId(const QString &value)
{
    id = value;
    QPixmap pix (":/Productos/imgs/" + id);
    ui->productImage->setPixmap(pix);
}

float productWidget::getPrice() const
{
    return price;
}

void productWidget::setPrice(const double value)
{
    price = float (value);
    ui->productPrice->setText("$ " + QString::number(price));
}
