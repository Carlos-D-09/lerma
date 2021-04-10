#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class productWidget;
}

class productWidget : public QWidget
{
    Q_OBJECT

public:
    explicit productWidget(QWidget *parent = 0);
    ~productWidget();


    QString getName() const;
    void setName(const QString &value);

    QString getId() const;
    void setId(const QString &value);

    float getPrice() const;
    void setPrice(const double value);

private:
    Ui::productWidget *ui;
    QString name;
    QString id;
    float price;

};

#endif // PRODUCTWIDGET_H
