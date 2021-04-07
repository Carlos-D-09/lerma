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
    explicit productWidget(QWidget *parent = 0, QString id = "", QString name = "", float price = 0);
    ~productWidget();

    QString getId() const;
    void setId(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    float getPrice() const;
    void setPrice(const double &value);

private:
    Ui::productWidget *ui;
    QString id;
    QString name;
    float price;
};

#endif // PRODUCTWIDGET_H
