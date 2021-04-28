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
    hideSort = false;
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
            message.exec();
            ui->categories->setEnabled(true);
            QMainWindow::showMaximized();
            ui->categories->setEnabled(true);
            ui->categories->setCurrentIndex(0);
            ui->filters->setEnabled(true);
            ui->filters->setCurrentIndex(0);
            ui->search->setEnabled(true);
            /*Lo que hace es cambiar la pantalla de la aplicación, por defecto la primera
            empieza en 0, que en este caso es la pantalla de inicio de sesión
            */
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
    jsonObj["users"] = dbuArray;
    jsonObj["products"] = dbpArray;
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

    dbFile.open(QIODevice::ReadOnly); //Abro un flujo de lectura
    data = dbFile.readAll(); //Asigno a data el valor binario de la lectura del archivo
    dbFile.close(); //cierro el archivo
    jsonDoc = QJsonDocument::fromJson(data); //transformo de binario a json
    jsonObj = jsonDoc.object(); //transofrmo del docuemento a un arreglo de .json

    dbuArray = jsonObj["users"].toArray(); //hago que jsonObj en su registro users contenga el arreglo de usuarios y se lo asigna a un arreglo .json

    for (int i(0); i < dbuArray.size(); i++)
    {
        User u; //creo un objeto u de la clase User
        QJsonObject obj = dbuArray[i].toObject(); //Extraigo del arreglo .json posición i, la transformo en un objeto json y la asigno a obj
        u.setUsername(obj["name"].toString()); //De un QJsonObj conviero a un string de c++
        u.setEmail(obj["email"].toString());
        u.setPassword(obj["password"].toString());
        users.push_back(u);
    }

    dbpArray = jsonObj["products"].toArray();

    for(int i(0); i < dbpArray.size(); i++)
    {
        productWidget* p;
        QJsonObject obj = dbpArray[i].toObject();
        p = new productWidget (this);
        p->setId(obj["id"].toString());
        p->setName(obj["name"].toString());
        p->setPrice(obj["price"].toDouble());
        products.push_back(p);
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
            dbuArray.append(jsonObj);
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

void MainWindow::setProducts()
{

    for(int i(0); i < dbpArray.size(); i++)
    {
        productWidget* p;
        QJsonObject obj = dbpArray[i].toObject();
        p = new productWidget (this);
        p->setId(obj["id"].toString());
        p->setName(obj["name"].toString());
        p->setPrice(obj["price"].toDouble());
        products[i] = p;
    }
}

void MainWindow::clearGrid()
{
    QLayoutItem *item;
    while((item = ui->gridProducts->layout()->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }
    setProducts();
}

string MainWindow::convertToLowerCase(string cad)
{
    for(size_t i = 0; i < cad.size(); i++)
    {
        cad[i] = toupper(cad[i]);
    }
    return cad;
}

void MainWindow::invalidSearch()
{
    QMessageBox advice;
    advice.setText("No se encontro ningún producto con el patron deseado");
    advice.exec();
    ui->search->clear();
    if(ui->filters->currentIndex() > 0)
    {
        on_filters_currentIndexChanged(ui->filters->currentIndex());
    }
    else
    {
        on_categories_currentIndexChanged(ui->categories->currentIndex());
    }
}

void MainWindow::showAllDepartments()
{
    int x = 0, y = 0;
    for(size_t i = 0; i < products.size(); i++)
    {
        ui->gridProducts->addWidget(products[i], x, y);
        y++;
        if(y == 4)
        {
            y = 0;
            x++;
        }
    }
}

void MainWindow::showSearchAllDepartments(const QString input)
{
    int x = 0, y = 0;
    for(size_t i = 0; i < products.size(); i++)
    {
        productWidget *obj;
        obj = products[i];
        if(convertToLowerCase(obj->getName().toStdString()).find(convertToLowerCase(input.toStdString()),0) < obj->getName().toStdString().length())
        {
            ui->gridProducts->addWidget(products[i], x, y);
            y++;
            if(y == 4)
            {
                y = 0;
                x++;
            }
        }
    }
    if(x == 0 && y == 0)
    {
        invalidSearch();
    }
}

void MainWindow::showFoodDrinks()
{
    int x = 0, y = 0;
    for(size_t i = 0; i < products.size(); i++)
    {
        productWidget * obj;
        obj = products[i];
        QString id = obj->getId();
        string idString = id.toStdString();
        if(strncmp(idString.c_str(), "AB", 2) == 0)
        {
            ui->gridProducts->addWidget(obj, x, y);
            y++;
            if(y == 4)
            {
                y = 0;
                x++;
            }
        }
    }
}

void MainWindow::showSearchFoodDrinks(const QString input)
{
    int x = 0, y = 0;
    for(size_t i = 0; i < products.size(); i++)
    {
        productWidget * obj;
        obj = products[i];
        QString id = obj->getId();
        string idString = id.toStdString();
        if(strncmp(idString.c_str(), "AB", 2) == 0)
        {
            if(convertToLowerCase(obj->getName().toStdString()).find(convertToLowerCase(input.toStdString()),0) < obj->getName().toStdString().length())
            {
                ui->gridProducts->addWidget(products[i], x, y);
                y++;
                if(y == 4)
                {
                    y = 0;
                    x++;
                }
            }
        }
    }
    if(x == 0 && y == 0)
    {
        invalidSearch();
    }
}

void MainWindow::showBooks()
{
    int x = 0, y = 0;
    for(size_t i = 0; i < products.size(); i++)
    {
        productWidget * obj;
        obj = products[i];
        QString id = obj->getId();
        string idString = id.toStdString();
        if(strncmp(idString.c_str(), "L", 1) == 0)
        {
            ui->gridProducts->addWidget(obj, x, y);
            y++;
            if(y == 4)
            {
                y = 0;
                x++;
            }
        }
    }
}

void MainWindow::showSearchBooks(const QString input)
{
    int x = 0, y = 0;
    for(size_t i = 0; i < products.size(); i++)
    {
        productWidget * obj;
        obj = products[i];
        QString id = obj->getId();
        string idString = id.toStdString();
        if(strncmp(idString.c_str(), "L", 1) == 0)
        {
            if(convertToLowerCase(obj->getName().toStdString()).find(convertToLowerCase(input.toStdString()),0) < obj->getName().toStdString().length())
            {
                ui->gridProducts->addWidget(products[i], x, y);
                y++;
                if(y == 4)
                {
                    y = 0;
                    x++;
                }
            }
        }
    }
    if( x == 0 && y == 0)
    {
        invalidSearch();
    }
}

void MainWindow::showElectronics()
{
    int x = 0, y = 0;
    for(size_t i = 0; i < products.size(); i++)
    {
        productWidget * obj;
        obj = products[i];
        QString id = obj->getId();
        string idString = id.toStdString();
        if(strncmp(idString.c_str(), "E", 1) == 0)
        {
            ui->gridProducts->addWidget(obj, x, y);
            y++;
            if(y == 4)
            {
                y = 0;
                x++;
            }
        }
    }
}

void MainWindow::showSearchElectronics(const QString input)
{
    int x = 0, y = 0;
    for(size_t i = 0; i < products.size(); i++)
    {
        productWidget * obj;
        obj = products[i];
        QString id = obj->getId();
        string idString = id.toStdString();
        if(strncmp(idString.c_str(), "E", 1) == 0)
        {
            if(convertToLowerCase(obj->getName().toStdString()).find(convertToLowerCase(input.toStdString()),0) < obj->getName().toStdString().length())
            {
                ui->gridProducts->addWidget(products[i], x, y);
                y++;
                if(y == 4)
                {
                    y = 0;
                    x++;
                }
            }
        }
    }
    if(x == 0 && y == 0)
    {
        invalidSearch();
    }
}

void MainWindow::showHomeKitchen()
{
    int x = 0, y = 0;
    for(size_t i = 0; i < products.size(); i++)
    {
        productWidget * obj;
        obj = products[i];
        QString id = obj->getId();
        string idString = id.toStdString();
        if(strncmp(idString.c_str(), "HC", 2) == 0)
        {
            ui->gridProducts->addWidget(obj, x, y);
            y++;
            if(y == 4)
            {
                y = 0;
                x++;
            }
        }
    }
}

void MainWindow::showSearchHomeKitchen(const QString input)
{
    int x = 0, y = 0;
    for(size_t i = 0; i < products.size(); i++)
    {
        productWidget * obj;
        obj = products[i];
        QString id = obj->getId();
        string idString = id.toStdString();
        if(strncmp(idString.c_str(), "HC", 2) == 0)
        {
            if(convertToLowerCase(obj->getName().toStdString()).find(convertToLowerCase(input.toStdString()),0) < obj->getName().toStdString().length())
            {
                ui->gridProducts->addWidget(products[i], x, y);
                y++;
                if(y == 4)
                {
                    y = 0;
                    x++;
                }
            }
        }
    }
    if(x == 0 && y == 0)
    {
        invalidSearch();
    }
}

void MainWindow::showSportOutdoors()
{
    int x = 0, y = 0;
    for(size_t i = 0; i < products.size(); i++)
    {
        productWidget * obj;
        obj = products[i];
        QString id = obj->getId();
        string idString = id.toStdString();
        if(strncmp(idString.c_str(), "D", 1) == 0)
        {
            ui->gridProducts->addWidget(obj, x, y);
            y++;
            if(y == 4)
            {
                y = 0;
                x++;
            }
        }
    }
}

void MainWindow::showSearchSportOutdoors(const QString input)
{
    int x = 0, y = 0;
    for(size_t i = 0; i < products.size(); i++)
    {
        productWidget * obj;
        obj = products[i];
        QString id = obj->getId();
        string idString = id.toStdString();
        if(strncmp(idString.c_str(), "D", 1) == 0)
        {
            if(convertToLowerCase(obj->getName().toStdString()).find(convertToLowerCase(input.toStdString()),0) < obj->getName().toStdString().length())
            {
                ui->gridProducts->addWidget(products[i], x, y);
                y++;
                if(y == 4)
                {
                    y = 0;
                    x++;
                }
            }
        }
    }
    if(x == 0 && y == 0)
    {
        invalidSearch();
    }
}

void MainWindow::putErrorMessage()
{
    QMessageBox advice;
    advice.setIcon(QMessageBox::Warning);
    advice.setText("Something went wrong, please contact technical support");
    advice.exec();
}

void MainWindow::evaluateHideSort(const int pos)
{
    if(pos == 0)
    {
        if(hideSort == true)
        {
            ui->filters->setItemData(0,QVariant(),Qt::SizeHintRole);
            hideSort = false;
            ui->filters->setCurrentIndex(0);
        }
    }
    else if(pos == 1)
    {
        if(hideSort == false)
        {
            ui->filters->setItemData(0,QSize(0,0),Qt::SizeHintRole);
            hideSort = true;
        }
    }
    else
    {
        putErrorMessage();
    }
}

void MainWindow::changeObjects(const int i, const int j)
{
    productWidget *temp;
    temp = new productWidget(this);
    temp = products[i];
    products[i] = products[j];
    products[j] = temp;
}

//Acomoda los productos de mayor a menor
void MainWindow::sortProducts(const int type)
{
    clearGrid();
    productWidget* obj, *obj2;
    //Mayor a menor
    if(type == 1)
    {
        size_t min;
        for(size_t i = 0; i < products.size()-1; i++)
        {
            min = i;
            for(size_t j = i+1; j < products.size(); j++)
            {
                obj = new productWidget(this);
                obj = products[j];
                obj2 = new productWidget(this);
                obj2 = products[min];
                if(obj->getPrice() < obj2->getPrice())
                {
                    min = j;
                }
            }
            changeObjects(i,min);
        }
    }
    //Menor a mayor
    else if(type == 2)
    {
        size_t max;
        for(size_t i = 0; i < products.size()-1; i++)
        {
            max = i;
            for(size_t j = i+1; j < products.size(); j++)
            {
                obj = new productWidget(this);
                obj = products[j];
                obj2 = new productWidget(this);
                obj2 = products[max];
                if(obj->getPrice() > obj2->getPrice())
                {
                    max = j;
                }
            }
            changeObjects(i,max);
        }
    }
    else
    {
        putErrorMessage();
    }
}

void MainWindow::showByPrice(const int type,const int categorie)
{
    QString word = ui->search->text();
    //Se evalua si el usuario introducio previamente una cadena que desea buscar
    if(word.length() > 0)
    {
        //Si la hay, manda a llamar la señal
        on_search_returnPressed();
    }
    else
    {
        //En caso de que no haya, simplemente ordena los productos
        sortProducts(type);
        switch(categorie)
        {
            case 0:
                showAllDepartments();
                break;
            case 1:
                showFoodDrinks();
                break;
            case 2:
                showBooks();
                break;
            case 3:
                showElectronics();
                break;
            case 4:
                showHomeKitchen();
                break;
            case 5:
                showSportOutdoors();
                break;
            default:
                putErrorMessage();
                break;
        }
    }
}

void MainWindow::on_categories_currentIndexChanged(int index)
{
    switch (index)
    {
        case 0:
            ui->search->clear();
            if(cont == 0)
            {
                showAllDepartments();
                cont = 1;
            }
            else
            {
                clearGrid();
                evaluateHideSort(0);
                showAllDepartments();
            }
            break;
        case 1:
            ui->search->clear();
            clearGrid();
            evaluateHideSort(0);
            showFoodDrinks();
            break;
        case 2:
            ui->search->clear();
            clearGrid();
            evaluateHideSort(0);
            showBooks();
            break;
        case 3:
            ui->search->clear();
            clearGrid();
            evaluateHideSort(0);
            showElectronics();
            break;
        case 4:
            ui->search->clear();
            clearGrid();
            evaluateHideSort(0);
            showHomeKitchen();
            break;
        case 5:
            ui->search->clear();
            clearGrid();
            evaluateHideSort(0);
            showSportOutdoors();
            break;
        default:
            putErrorMessage();
            break;
    }
}

void MainWindow::on_filters_currentIndexChanged(int index)
{
    switch (index)
    {
        case 0:
            break;
        case 1:
            evaluateHideSort(1);
            showByPrice(index,ui->categories->currentIndex());
            break;
        case 2:
            evaluateHideSort(1);
            showByPrice(index,ui->categories->currentIndex());
            break;
        default:
            putErrorMessage();
            break;
    }
}

void MainWindow::on_search_returnPressed()
{
    clearGrid();
    int filtersIndex = ui->filters->currentIndex();
    int categorieIndex = ui->categories->currentIndex();
    if(filtersIndex > 0)
    {
        sortProducts(filtersIndex);
    }
    switch(categorieIndex)
    {
        case 0:
            showSearchAllDepartments(ui->search->text());
            break;
        case 1:
            showSearchFoodDrinks(ui->search->text());
            break;
        case 2:
            showSearchBooks(ui->search->text());
            break;
        case 3:
            showSearchElectronics(ui->search->text());
            break;
        case 4:
            showSearchHomeKitchen(ui->search->text());
            break;
        case 5:
            showSearchSportOutdoors(ui->search->text());
            break;
        default:
            putErrorMessage();
            break;
    }
}
