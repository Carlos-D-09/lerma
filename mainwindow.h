#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <vector>
#include <QVector>
#include "user.h"
#include "productwidget.h"
#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <iomanip>
#include <QMainWindow>
#include <QMessageBox>
#include <vector>
#include <QVector>
#include <user.h>
#include "productwidget.h"
#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <string>

using namespace std;

class productWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_usernameLE_textChanged(const QString &arg1);

    void on_passwordLE_textChanged(const QString &arg1);

    void on_newUserLE_textChanged(const QString &arg1);

    void on_emailLE_textChanged(const QString &arg1);

    void on_newPasswordLE_textChanged(const QString &arg1);

    void on_signUpPB_clicked();

    void on_loginPB_clicked();

    void openFile();

    void on_categories_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    vector<User> users;
    vector<productWidget*> products;
    vector<productWidget*> products_aux;
    QAction* openFileAction;
    QFile dbFile;
    QJsonArray dbuArray;
    QJsonArray dbpArray;
    productWidget *productInfo;

    void enableLoginPB();
    void enableSingUpPB();
    void validateUser();
    void validateData();
    bool checkEmail(const QString &value);
    void saveDB();
    void loadDB();
    void setProducts();
    void clearGrid();
    void showAllDepartments(int cont = 0);
    void showFoodDrinks();
    void showBooks();
    void showElectronics();
    void showHomeKitchen();
    void showSportOutdoors();
};

#endif // MAINWINDOW_H
