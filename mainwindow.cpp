#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    openFileAction = new QAction ("&Open Database", this);

    //Detecta cuando haya una señal, sus argumentos son: quien emite la señal, cual es la señal, quien responde, con que le responde
    connect(openFileAction, SIGNAL(triggered()),this, SLOT(openFile()));
    ui->menuBar->addMenu("&File")->addAction(openFileAction);

    /*
     * Que se genere el archivo .json
        dbFile.setFileName("lerma.json");
        dbFile.open(QIODevice::WriteOnly);
        dbFile.close();
    */
}

MainWindow::~MainWindow()
{
    saveDB();
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

//Busca si el usuario que se ingreso ya esta registrado para iniciar sesión
void MainWindow::validateUser()
{
    QMessageBox message;
    vector<User>::iterator it; //iterador
    QString user = ui->usernameLE->text();
    QString password = ui->passwordLE->text();

    it = find_if(users.begin(), users.end(), [&user](User u) -> bool
    {
        return u.getUsername() == user;
    }
        );
    //Si el iterador termina al final es que no hay ningun usuario registrado con ese nombre
    if (it == users.end())
    {
        message.setText("Invalid credentials");
        message.setIcon(QMessageBox::Warning);
        message.exec();

        ui->usernameLE->clear();
        ui->passwordLE->clear();
    }
    //En caso contrario paso a evaluar si hay coincidencia en la contraseña
    else
    {
        it = find_if(users.begin(), users.end(), [&password](User u) -> bool
        {
            return u.getPassword() == password;
        }
            );
        if(it == users.end())
        {
            message.setText("Incorrect password, please try again");
            message.setIcon(QMessageBox::Warning);
            message.exec();

            ui->passwordLE->clear();
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
}

//Metodo para corroborar la dirección de correo electronico
bool MainWindow::checkEmail(const QString &value)
{
    bool result = true; //Variable que voy a retornar
    char a = 64, b = 46; //Caracteres @ y . en código ascii
    if(value.contains(a) && value.contains(b)) //Evaluo si contiene un @ y .
    {
        int cont = 0; //cont es la variable que llevara el conteo de cuantas veces aparece el @
        int pos1 = 0, pos2 = 0; //pos1 es la posición donde se encontro el ultimo '@' y pos2 donde se encontro el ultimo '.'
        int letters = 0; //contador para saber si hay caracteres antes del @
        for (int x = 0; x < value.size(); x++)
        {
            if(value[x] != a && cont == 0)
            {
                if(value[x] == b)
                {
                    pos2 = x;
                    letters++;
                }
                else
                {
                    letters++;
                }
            }
            else if(value[x] == a)
            {
                pos1 = x;
                cont++;
            }
            else if (value[x] == b)
            {
                pos2 = x;
            }
        }
        if(letters == 0) //En caso de que no haya nada escrito antes del @
        {
            result = false;
        }
        else if(cont > 1) //En caso de que haya dos @
        {
            result = false;
        }
        else if(pos1 > pos2) //En caso de que no haya un . despues del @
        {
            result = false;
        }
        else if(pos1 + 1 == pos2) //En caso de que el @ y el . esten juntos
        {
            result = false;
        }
        else //Para evaluar que no haya caracteres especiales dentro del correo
        {
            for (int c = 32; c < 129; c++)
            {
                char x = c;
                if(c < 42)
                {
                    if(value.contains(x) == true)
                    {
                        result = false;
                        break;
                    }
                }
                else if(c == 44 || c == 58 || c == 59 || c == 60 || c == 62 || c == 91 || c == 92 || c == 93 || c == 96 || c == 124 || c == 128)
                {
                    if(value.contains(x) == true)
                    {
                        result = false;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        result = false;
    }

    return result;
}

void MainWindow::saveDB()
{
    QJsonObject jsonObj;
    QJsonDocument jsonDoc;
    jsonObj["users"] = dbArray;
    jsonDoc = QJsonDocument(jsonObj);

    dbFile.open(QIODevice::WriteOnly);
    dbFile.write(jsonDoc.toJson());
    dbFile.close();
}

void MainWindow::loadDB()
{
    QJsonObject jsonObj;
    QJsonDocument jsonDoc;
    QByteArray data;

    dbFile.open(QIODevice::ReadOnly);
    data = dbFile.readAll();
    dbFile.close();
    jsonDoc = QJsonDocument::fromJson(data);
    jsonObj = jsonDoc.object();
    dbArray = jsonObj["users"].toArray();

    for (int i(0); i < dbArray.size(); i++)
    {
        User u;
        QJsonObject obj = dbArray[i].toObject();
        u.setUsername(obj["name"].toString());
        u.setEmail(obj["email"].toString());
        u.setPassword(obj["password"].toString());
        users.push_back(u);
    }
}

//Metodo para identificar repeticiones de datos al momento de crear un nuevo usuaio
void MainWindow::validateData()
{
    QMessageBox message;
    QString user = ui->newUserLE->text();
    QString email = ui->emailLE->text();
    //Si el email introducidio es valido
    if(checkEmail(email) == true)
    {
        //Busca que no haya un nombre de usuario o email en el vector users
        vector <User> :: iterator it; //iterador para la función find if
        it = find_if(users.begin(),users.end(),[&user, &email](User u) -> bool
        {
            return (u.getUsername() == user || u.getEmail() == email);
        }
            );

        //Si no lo hay, registra el usuario sin problema
        if(it == users.end())
        {
            QJsonObject jsonObj;
            User u;
            u.setUsername(ui->newUserLE->text());
            u.setEmail(ui->emailLE->text());
            u.setPassword(ui->newPasswordLE->text());

            users.push_back(u);
            message.setText("New user created");
            message.exec();
            ui->newUserLE->clear();
            ui->newPasswordLE->clear();
            ui->emailLE->clear();

            //Se agrega al final del arreglo json el usuario registrado
            jsonObj["name"] = u.getUsername();
            jsonObj["email"] = u.getEmail();
            jsonObj["password"] = u.getPassword();
            dbArray.append(jsonObj);
        }
        else
        {
            User u = *it;

            //En caso que se este tratando de registrar un usuario ya creado
            if(u.getUsername() == user && u.getEmail() == email)
            {
                message.setText("This user is already registred");
                message.setIcon(QMessageBox::Warning);
                message.exec();
                ui->newUserLE->clear();
                ui->newPasswordLE->clear();
                ui->emailLE->clear();

            }

            //En caso de que se quiera usar un nombre de usuario ya registrado
            else if (u.getUsername() == user)
            {
                message.setText("please try another username this has already been registered");
                message.setIcon(QMessageBox::Warning);
                message.exec();
                ui->newUserLE->clear();
            }

            //En caso de que se quiera usar un correo electronico ya registrado
            else if(u.getEmail() == email)
            {
                message.setText("please try another email this has already been registered");
                message.setIcon(QMessageBox::Warning);
                message.exec();
                ui->emailLE->clear();
            }
        }
    }

    //En caso de que la dirección de correo electronico no sea valida
    else
    {
        message.setText("Invalid email adress");
        message.setIcon(QMessageBox::Warning);
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

//Accion cuando se presiona el boton signUpPB
void MainWindow::on_signUpPB_clicked()
{
    validateData();
}

void MainWindow::on_loginPB_clicked()
{
    validateUser();
}

void MainWindow::openFile()
{
    QString name;
    //Busca el archivo dentro del sistema de archivos, recibe como argumentos:
    //el widget, la leyenda que aparecera, donde se empieza la busqueda
    //("" para que se busque en la carpeta contenedora del ejecutable),cual es el filtro que se aplica
    name = QFileDialog::getOpenFileName(this,"Select Database","","JSON files (*.json)");

    if (name.length() > 0)
    {
        dbFile.setFileName(name);
        ui->loginGB->setEnabled(true);
        ui->signUpGB->setEnabled(true);
        loadDB();
    }
}
