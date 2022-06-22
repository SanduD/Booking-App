#include "popupwindow.h"
#include "ui_popupwindow.h"

PopupWindow::PopupWindow(QWidget *parent,QTcpSocket* socket,QString username) :
    QDialog(parent),
    ui(new Ui::PopupWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Ask a question on forum");
    this->socket_transmis = socket;
    this->username = username;
}
PopupWindow::~PopupWindow()
{
    delete ui;
    delete socket_transmis;
}


void PopupWindow::on_Cancel_clicked()
{
    this->close();
}


void PopupWindow::on_Submit_clicked()
{
    QString question_entered = "5|" + this->username+ "|" +ui->plainTextEdit->toPlainText();

    this->socket_transmis->write(question_entered.toUtf8());
    this->socket_transmis->waitForBytesWritten();
    this->close();

}

