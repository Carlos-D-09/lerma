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
#include <QDateTime>

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

    void on_filters_currentIndexChanged(int index);

    void on_search_returnPressed();

    void addToChart(QString item, int amount);

private:
    Ui::MainWindow *ui;

    vector<User> users;
    vector<User>::iterator currentUser;
    vector<productWidget*> products;
    QAction* openFileAction;
    QFile dbFile;
    QJsonArray dbuArray;
    QJsonArray dbpArray;
    QJsonArray chart;
    int printingProductsFlag = 0;
    bool hideSort;

    void enableLoginPB();
    void enableSingUpPB();
    void validateUser();
    void validateData();
    bool checkEmail(const QString &value);
    void saveDB();
    void loadDB();
    void setProducts();
    void clearGrid();

    void showAllDepartments();
    void showSearchAllDepartments(const QString input);

    void showFoodDrinks();
    void showSearchFoodDrinks(const QString input);

    void showBooks();
    void showSearchBooks(const QString input);

    void showElectronics();
    void showSearchElectronics(const QString input);

    void showHomeKitchen();
    void showSearchHomeKitchen(const QString input);

    void showSportOutdoors();
    void showSearchSportOutdoors(const QString input);

    void evaluateHideSort(const int pos);
    void putErrorMessage();
    void showByPrice(const int type, const int categorie);
    void changeObjects(const int i, const int j);
    void sortProducts(const int type);
    string convertToLowerCase(string cad);
    void invalidSearch();

};

#endif // MAINWINDOW_H
