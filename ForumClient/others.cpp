#include "others.h"
#include "ui_others.h"

Others::Others(QWidget *parent,Client* client) :
    QWidget(parent),
    ui(new Ui::Others)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    client_mostenit = client;
}

QListWidget *Others::getListWidget()
{
    return ui->Questions_list;
}

QStackedWidget *Others::getStackedWidget()
{
    return ui->stackedWidget;
}

void Others::refresh_list()
{
    ui->Questions_list->clear();

    QString message= "3|"+client_mostenit->getTopic();
    client_mostenit->getSocket()->write(message.toUtf8());
    client_mostenit->getSocket()->waitForBytesWritten();
    client_mostenit->getSocket()->waitForReadyRead();

    QStringList dataList = client_mostenit->getLastMsg();
    for(int i=2;i<dataList.value(1).toInt()*2+1;i+=2){
       ui->Questions_list->addItem(dataList.value(i)+"|"+dataList.value(i+1));
    }

    ui->Questions_list->setCurrentRow(-1);
    ui->stackedWidget->setCurrentIndex(0);
}

void Others::refresh_list(QString question)
{
    ui->Answers_list->clear();

    //send question to server to get answers
    QString message= "4|"+question.split("|").value(1)+"|"+QString::number(ui->comboBox->currentIndex()); //protocol pentru a primi raspunsurile la intrebari
    //combobox: 0-ordinea adaugarii desc  1-ordinea adaugarii cresc  2-scor desc  3-scor cresc
    client_mostenit->getSocket()->write(message.toUtf8());
    client_mostenit->getSocket()->waitForBytesWritten();
    client_mostenit->getSocket()->waitForReadyRead();

    QStringList dataList = client_mostenit->getLastMsg();
    for(int i=2;i<dataList.value(1).toInt()*3+1;i+=3){
       ui->Answers_list->addItem(dataList.value(i)+ "|" +dataList.value(i+1)+ "|\nScore: "+dataList.value(i+2));
    }

    ui->Answers_list->setCurrentRow(-1);
    ui->stackedWidget->setCurrentIndex(2);
    //ui->comboBox->setCurrentIndex(0);
}

Others::~Others()
{
    delete ui;
}


void Others::on_NavigationButton_clicked()
{

    qDebug() <<"Current row is: "<< ui->Questions_list->currentRow();
    if(ui->Questions_list->currentRow() >= 0){
        selected_question = ui->Questions_list->currentItem()->text();
        ui->comboBox->setCurrentIndex(0);
        refresh_list(selected_question);
        qDebug() <<"Navigating: "<< selected_question;
        ui->CurrentQuestion->setPlainText(selected_question);
        ui->stackedWidget->setCurrentIndex(2);
    }
}


void Others::on_AskQuestionButton_clicked()
{
//    PopupWindow dialog(nullptr,client_mostenit->getSocket(),client_mostenit->getUsername());
//    dialog.setModal(true);
//    dialog.exec();
    submit_case = 0;
    ui->plainTextEdit->clear();
    ui->stackedWidget->setCurrentIndex(1);
}

//0 = submit question ; 1 = submit answer ; 2 = edit question ; 3 = edit answer

void Others::on_Answer_clicked()
{
    submit_case = 1;
    ui->plainTextEdit->clear();
    ui->stackedWidget->setCurrentIndex(1);
}

void Others::on_Submit_clicked()
{
    if(submit_case == 0){
        QString question_entered = "5|" + client_mostenit->getUsername()+"|"+ client_mostenit->getTopic() +"|" +ui->plainTextEdit->toPlainText();

        client_mostenit->getSocket()->write(question_entered.toUtf8());
        client_mostenit->getSocket()->waitForBytesWritten();
        client_mostenit->getSocket()->waitForReadyRead();

        refresh_list();
    }

    if(submit_case == 1){
        QString Answer_entered = "6|" + client_mostenit->getUsername()+"|" + selected_question.split("|").value(1) + "|" + ui->plainTextEdit->toPlainText();

        client_mostenit->getSocket()->write(Answer_entered.toUtf8());
        client_mostenit->getSocket()->waitForBytesWritten();
        client_mostenit->getSocket()->waitForReadyRead();

        refresh_list(selected_question);
    }

    if(submit_case == 2){
        QString only_question = selected_question.split("|").value(1);
        QString Question_to_edit = "7|" + only_question + "|" + ui->plainTextEdit->toPlainText();

        client_mostenit->getSocket()->write(Question_to_edit.toUtf8());
        client_mostenit->getSocket()->waitForBytesWritten();
        client_mostenit->getSocket()->waitForReadyRead();

        refresh_list();
    }

    if(submit_case == 3){
        QString only_answer = selected_answer.split("|").value(1);
        QString answer_to_edit = "8|" + only_answer + "|" + ui->plainTextEdit->toPlainText();

        client_mostenit->getSocket()->write(answer_to_edit.toUtf8());
        client_mostenit->getSocket()->waitForBytesWritten();
        client_mostenit->getSocket()->waitForReadyRead();

        refresh_list(selected_question);
    }
    else
    {
        qDebug() << "Ai uitat sa setezi optiunea!";
    }
    ui->plainTextEdit->clear();
    ui->Questions_list->setCurrentRow(-1);
    ui->Answers_list->setCurrentRow(-1);
}


void Others::on_BackToQuestions_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->Questions_list->setCurrentRow(-1);
    ui->Answers_list->setCurrentRow(-1);
    refresh_list();
}


void Others::on_EditQuestion_clicked()
{
    if(ui->Questions_list->currentRow() >= 0){
        if((client_mostenit->getUsername() == "admin" || client_mostenit->getUsername() == ui->Questions_list->currentItem()->text().split("|").value(0)) && client_mostenit->getUsername() != "GUEST"){
            submit_case = 2;
            selected_question = ui->Questions_list->currentItem()->text();
            ui->stackedWidget->setCurrentIndex(1);
        }
        else{
            QMessageBox::warning(this,"Error","Doar admin-ul sau user-ul care a pus intrebarea poate edita!");
        }
    }
}



void Others::on_EditAnswer_clicked()
{
    if(ui->Answers_list->currentRow() >= 0){
        if((client_mostenit->getUsername() == "admin" || client_mostenit->getUsername() == ui->Answers_list->currentItem()->text().split("|").value(0)) && client_mostenit->getUsername() != "GUEST"){
            submit_case = 3;
            selected_answer = ui->Answers_list->currentItem()->text();
            ui->stackedWidget->setCurrentIndex(1);
        }
        else{
            QMessageBox::warning(this,"Error","Doar admin-ul sau user-ul care a pus intrebarea poate edita!");
        }
    }
}


void Others::on_DeleteQuestion_clicked()
{
    if(ui->Questions_list->currentRow() >= 0){
        if((client_mostenit->getUsername() == "admin" || client_mostenit->getUsername() == ui->Questions_list->currentItem()->text().split("|").value(0)) && client_mostenit->getUsername() != "GUEST"){
            QString Question_to_delete = "9|" + ui->Questions_list->currentItem()->text().split("|").value(1);

            client_mostenit->getSocket()->write(Question_to_delete.toUtf8());
            client_mostenit->getSocket()->waitForBytesWritten();
            client_mostenit->getSocket()->waitForReadyRead();

            refresh_list();
        }
        else{
            QMessageBox::warning(this,"Error","Doar admin-ul sau user-ul care a pus intrebarea poate sterge!");
        }
    }
}


void Others::on_DeleteAnswer_clicked()
{
    if(ui->Answers_list->currentRow() >= 0){
        if((client_mostenit->getUsername() == "admin" || client_mostenit->getUsername() == ui->Answers_list->currentItem()->text().split("|").value(0)) && client_mostenit->getUsername() != "GUEST"){
            QString Answer_to_delete = "10|" + ui->Answers_list->currentItem()->text().split("|").value(1);

            client_mostenit->getSocket()->write(Answer_to_delete.toUtf8());
            client_mostenit->getSocket()->waitForBytesWritten();
            client_mostenit->getSocket()->waitForReadyRead();

            refresh_list(selected_question);
        }
        else{
            QMessageBox::warning(this,"Error","Doar admin-ul sau user-ul care a pus intrebarea poate sterge!");
        }
    }
}


void Others::on_UpVoteAnswer_clicked()
{
    if(ui->Answers_list->currentRow() >= 0){
        QString Answer_to_upvote = "11|" + client_mostenit->getUsername() + "|" + ui->Answers_list->currentItem()->text().split("|").value(1);
        qDebug()<<"Upvote: "<<Answer_to_upvote;
        client_mostenit->getSocket()->write(Answer_to_upvote.toUtf8());
        client_mostenit->getSocket()->waitForBytesWritten();
        client_mostenit->getSocket()->waitForReadyRead();

        refresh_list(selected_question);

    }
}


void Others::on_DownVoteAnswer_clicked()
{
    if(ui->Answers_list->currentRow() >= 0){
        QString Answer_to_downvote = "12|" + client_mostenit->getUsername() + "|" + ui->Answers_list->currentItem()->text().split("|").value(1);
        qDebug()<<"Downvote: "<<Answer_to_downvote;
        client_mostenit->getSocket()->write(Answer_to_downvote.toUtf8());
        client_mostenit->getSocket()->waitForBytesWritten();
        client_mostenit->getSocket()->waitForReadyRead();

        refresh_list(selected_question);

    }
}


void Others::on_Cancel_clicked()
{
    if(submit_case == 1 || submit_case == 3){
        refresh_list(selected_question);
        ui->Answers_list->setCurrentRow(-1);
    }
    else{
        refresh_list();
        ui->Questions_list->setCurrentRow(-1);
    }
}


void Others::on_Refresh_Questions_clicked()
{
    refresh_list();
}


void Others::on_HomePageButton_2_clicked()
{
    emit HomePage();
}


void Others::on_Refresh_Answers_clicked()
{
    refresh_list(selected_question);
}


void Others::on_LogOutButton_clicked()
{
    emit LogOut();
}


void Others::on_HomePageButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    emit HomePage();
}


void Others::on_LogOutButton_2_clicked()
{
    emit LogOut();
}



void Others::on_MyProfileFromAnswers_clicked()
{
    emit MyProfile();
}


void Others::on_MyProfileFromQuestions_clicked()
{
    emit MyProfile();
}


void Others::on_comboBox_currentIndexChanged(int index)
{
    refresh_list(selected_question);
    ui->comboBox->clearFocus();
}

