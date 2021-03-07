#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Habilitar el boton login push Botton
void MainWindow::enableLoginPB()
{
    if(ui->usernameLE->text().length() > 0 &&
            ui->passwordLE->text().length()>0)
    {
        ui->loginPB->setEnabled(true);
    }
    else
    {
        ui->loginPB->setEnabled(false);
    }
}

//Habilitar el boton login push Botton
void MainWindow::enableSingUpPB()
{
    if(ui->newUserLE->text().length() > 0 &&
            ui->emailLE->text().length() > 0 &&
            ui->newPasswordLE->text().length() > 0)
    {
        ui->signUpPB->setEnabled(true);
    }
    else
    {
        ui->signUpPB->setEnabled(false);
    }

}

//Busca si el usuario que se ingreso ya esta registrado para iniciar sesion
void MainWindow::validateUser()
{
    QMessageBox message;
    vector<User>::iterator it; //iterador
    QString user = ui->usernameLE->text();
    QString password = ui->passwordLE->text();

    it = find_if(users.begin(), users.end(), [&user, &password](User u) -> bool
    {
        return u.getUsername() == user && u.getPassword() == password;
    }
        );
    if (it == users.end())
    {
        message.setText("Invalid credentials");
        message.setIcon(QMessageBox::Warning);
        //message.layout();
        message.exec();
    }
    else
    {
        message.setText("Welcome to LERMA " + user);
        ui->viewSW->setCurrentIndex(1);
        /*Lo que hace es cambiar la pantalla de la aplicación, por defecto la primera
        empieza en 0, que en este caso es la pantalla de inicio de sesión
        */
        message.exec();
    }
}

//viewSW (verStackedWidget)Son todos de slots

void MainWindow::on_usernameLE_textChanged(const QString &arg1)
{
    /*cada vez que haya un cambio de texto en la casilla de usernameLE
    llamo al metodo para ver si se activa o no el boton de login*/
    Q_UNUSED(arg1);
    enableLoginPB();
}

void MainWindow::on_passwordLE_textChanged(const QString &arg1)
{
    Q_UNUSED (arg1);
    enableLoginPB();
}

void MainWindow::on_newUserLE_textChanged(const QString &arg1)
{
    Q_UNUSED (arg1);
    enableSingUpPB();
}

void MainWindow::on_emailLE_textChanged(const QString &arg1)
{
    Q_UNUSED (arg1);
    enableSingUpPB();
}

void MainWindow::on_newPasswordLE_textChanged(const QString &arg1)
{
    Q_UNUSED (arg1);
    enableSingUpPB();
}

void MainWindow::on_signUpPB_clicked()
{
    QMessageBox message;
    User u;
    u.setUsername(ui->newUserLE->text());
    u.setEmail(ui->emailLE->text());
    u.setPassword(ui->newPasswordLE->text());

    users.push_back(u);

    message.setText("New user created");
    message.exec();

    ui->newUserLE->clear();
    ui->emailLE->clear();
    ui->newPasswordLE->clear();

}

void MainWindow::on_loginPB_clicked()
{
    validateUser();
    ui->usernameLE->clear();
    ui->passwordLE->clear();
}
