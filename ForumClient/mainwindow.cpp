#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->insertWidget(4,OthersTopicPage);
    ui->stackedWidget->setCurrentIndex(0);
    connect(OthersTopicPage,SIGNAL(LogOut()),this,SLOT(LogOut()));
    connect(OthersTopicPage,SIGNAL(HomePage()),this,SLOT(HomePage()));
    connect(OthersTopicPage,SIGNAL(MyProfile()),this,SLOT(MyProfile()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete client;
}

void MainWindow::LogOut()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::HomePage()
{
    ui->stackedWidget->setCurrentIndex(3);  //pagina cu lista de topicuri
}

void MainWindow::MyProfile()
{
    if(client->getUsername() != "admin" && client->getUsername() != "GUEST"){
        ui->Username_profile->setText("Username: "+client->getUsername());
        ui->stackedWidget->setCurrentIndex(5); //pagina profilului
    }else{
        QMessageBox::warning(this,"Error","Doar userii inregistrati isi pot vizualiza profilul");
    }
}

void MainWindow::on_LogInPage_LogIn_Button_clicked()
{
    QString tmp_pass = ui->LineEdit_Password->text();

    QString credentials= "1|"+ui->LineEdit_Username->text().toUtf8()+"|"+tmp_pass.toUtf8();

    client->getSocket()->write(credentials.toUtf8());
    client->getSocket()->waitForBytesWritten();
    client->getSocket()->waitForReadyRead();
    QString tmp_username = ui->LineEdit_Username->text();

    int lastRespCode = client->getLastMsg().value(1).toInt();
    qDebug() <<"\nS-a primit raspunsul la logare: " <<lastRespCode<<"\n";
    if (lastRespCode == 1){

        client->setUsername(tmp_username);
        ui->stackedWidget->setCurrentIndex(3);

    }
    else{
        QMessageBox::warning(this,"Login","Ati introdus credentiale gresite! Va rugam sa reincercati!");
    }
}


void MainWindow::on_LogInPage_Cancel_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_Home_LogIn_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_Home_SignUp_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_Home_Guest_Button_clicked()
{
    client->setUsername("Guest");
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_OtherTopics_clicked()
{
    OthersTopicPage->getListWidget()->clear();
    client->setTopic(ui->OtherTopics->text());
    QString message= "3|"+client->getTopic();
    client->getSocket()->write(message.toUtf8());
    client->getSocket()->waitForBytesWritten();
    client->getSocket()->waitForReadyRead();

    QStringList dataList = client->getLastMsg();
    for(int i=2;i<dataList.value(1).toInt()*2+1;i+=2){
        OthersTopicPage->getListWidget()->addItem(dataList.value(i)+"|"+dataList.value(i+1));
    }

    ui->stackedWidget->setCurrentIndex(4);
    OthersTopicPage->getStackedWidget()->setCurrentIndex(0);
}


void MainWindow::on_CppTopic_clicked()
{
    OthersTopicPage->getListWidget()->clear();
    client->setTopic(ui->CppTopic->text());
    QString message= "3|"+client->getTopic();
    client->getSocket()->write(message.toUtf8());
    client->getSocket()->waitForBytesWritten();
    client->getSocket()->waitForReadyRead();

    QStringList dataList = client->getLastMsg();
    for(int i=2;i<dataList.value(1).toInt()*2+1;i+=2){
        OthersTopicPage->getListWidget()->addItem(dataList.value(i)+"|"+dataList.value(i+1));
    }

    ui->stackedWidget->setCurrentIndex(4);
    OthersTopicPage->getStackedWidget()->setCurrentIndex(0);
}


void MainWindow::on_JavaTopic_clicked()
{
    OthersTopicPage->getListWidget()->clear();
    client->setTopic(ui->JavaTopic->text());
    QString message= "3|"+client->getTopic();
    client->getSocket()->write(message.toUtf8());
    client->getSocket()->waitForBytesWritten();
    client->getSocket()->waitForReadyRead();

    QStringList dataList = client->getLastMsg();
    for(int i=2;i<dataList.value(1).toInt()*2+1;i+=2){
        OthersTopicPage->getListWidget()->addItem(dataList.value(i)+"|"+dataList.value(i+1));
    }

    ui->stackedWidget->setCurrentIndex(4);
    OthersTopicPage->getStackedWidget()->setCurrentIndex(0);
}


void MainWindow::on_PythonTopic_clicked()
{
    OthersTopicPage->getListWidget()->clear();
    client->setTopic(ui->PythonTopic->text());
    QString message= "3|"+client->getTopic();
    client->getSocket()->write(message.toUtf8());
    client->getSocket()->waitForBytesWritten();
    client->getSocket()->waitForReadyRead();

    QStringList dataList = client->getLastMsg();
    for(int i=2;i<dataList.value(1).toInt()*2+1;i+=2){
        OthersTopicPage->getListWidget()->addItem(dataList.value(i)+"|"+dataList.value(i+1));
    }

    ui->stackedWidget->setCurrentIndex(4);
    OthersTopicPage->getStackedWidget()->setCurrentIndex(0);
}


void MainWindow::on_LogOutButtonFromTopics_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_SignUpCancelButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_SignUpButton_clicked()
{
    QString tmp_username = ui->lineEdit_SignUp_username->text();
    QString tmp_pass = ui->lineEdit_SignUp_password->text();
    if(tmp_pass.contains(' ') || tmp_pass.contains('|') || tmp_username.contains(' ') || tmp_username.contains('|')){
        QMessageBox::warning(this,"SignUp Password Error","User-ul sau parola nu au voie sa contina spatii sau caracterul \"|\"");
        return;
    }
    QString credentials= "2|"+tmp_username.toUtf8()+"|"+tmp_pass.toUtf8()+"|"+ui->lineEdit_SignUp_email->text().toUtf8();
    client->getSocket()->write(credentials.toUtf8());
    client->getSocket()->waitForBytesWritten();
    client->getSocket()->waitForReadyRead();


    int lastRespCode = client->getLastMsg().value(1).toInt();
    qDebug() <<"\nS-a primit raspunsul la logare: " <<lastRespCode<<"\n";
    if (lastRespCode == 1){

        client->setUsername(tmp_username);
        ui->stackedWidget->setCurrentIndex(3);

    }
    else
        if(lastRespCode == 0)
            QMessageBox::warning(this,"Register","Username-ul ales deja exista! Va rugam sa alegeti altul!");
        else
            QMessageBox::warning(this,"ERROR","S-a produs o eroare la introducerea datelor!");

}


void MainWindow::on_MyProfileButtonFromTopics_clicked()
{
    emit MyProfile();
}


void MainWindow::on_HomeFromProfile_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_LogOutButtonFromProfile_clicked()
{
    emit LogOut();
}



void MainWindow::on_EditDescription_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_EditProfile_Submit_clicked()
{
    ui->DescriptionTextBrowser->setText(ui->plainTextEdit->toPlainText());
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_EditProfile_Cancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

