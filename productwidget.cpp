#include "productwidget.h"
#include <QString>
#include "ui_productwidget.h"

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

//Slots
void productWidget::on_addButton_clicked()
{
    emit addItem(id, ui->amountSpinBox->value());
    ui->amountSpinBox->setValue(0);
}

void productWidget::on_amountSpinBox_valueChanged(int arg1)
{
    if(arg1 > 0)
    {
        ui->addButton->setEnabled(true);
    }
    else
    {
        ui->addButton->setEnabled(false);
    }
}

//Metodos
QString productWidget::getId() const
{
    return id;
}
void productWidget::setId(const QString &value)
{
    id = value;
    QImage image;
    image.load(":/Carpeta/Productos/imgs/" + id);
    QPixmap pix = QPixmap::fromImage(image.scaled(250, 300));
    ui->productImage->setPixmap(pix);
}

QString productWidget::getName() const
{
    return name;
}
void productWidget::setName(const QString &value)
{
    name = value;
    ui->productDescription->setText(name);
}

float productWidget::getPrice() const
{
    return price;
}
void productWidget::setPrice(const double &value)
{
    price = float(value);
    ui->productPrice->setText("$" + QString::number(price));
}
