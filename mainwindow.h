#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <vector>
#include "user.h"
#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

using namespace std;

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

private:
    Ui::MainWindow *ui;

    vector<User> users;
    QAction* openFileAction;
    QFile dbFile;
    QJsonArray dbArray;

    void enableLoginPB();
    void enableSingUpPB();
    void validateUser();
    void validateData();
    bool checkEmail(const QString &value);
    void saveDB();
    void loadDB();
};

#endif // MAINWINDOW_H
