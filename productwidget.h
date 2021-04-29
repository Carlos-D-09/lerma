#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H

#include <QString>
#include <QWidget>

namespace Ui {
class productWidget;
}

class productWidget : public QWidget
{
    Q_OBJECT
public:
    explicit productWidget(QWidget *parent = 0);
    ~productWidget();

    QString getId() const;
    void setId(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    float getPrice() const;
    void setPrice(const double &value);

private slots:

    void on_addButton_clicked();

    void on_amountSpinBox_valueChanged(int arg1);

signals:
    void addItem(QString id, int amount);

private:
    Ui::productWidget *ui;
    QString id;
    QString name;
    float price;
};

#endif // PRODUCTWIDGET_H
