#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "others.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    Client *client = new Client("192.168.57.93",1234); //127.0.0.1 // 192.168.57.93
    Others *OthersTopicPage = new Others(this,client);
    //PopupWindow* popw = new PopupWindow();

    ~MainWindow();

private slots:

    void LogOut();

    void HomePage();

    void MyProfile();

    void on_LogInPage_LogIn_Button_clicked();

    void on_LogInPage_Cancel_Button_clicked();

    void on_Home_LogIn_Button_clicked();

    void on_Home_Guest_Button_clicked();

    void on_OtherTopics_clicked();

    void on_LogOutButtonFromTopics_clicked();

    void on_Home_SignUp_Button_clicked();

    void on_SignUpCancelButton_clicked();

    void on_SignUpButton_clicked();

    void on_MyProfileButtonFromTopics_clicked();

    void on_CppTopic_clicked();

    void on_JavaTopic_clicked();

    void on_PythonTopic_clicked();

    void on_HomeFromProfile_clicked();

    void on_LogOutButtonFromProfile_clicked();

    void on_EditDescription_clicked();

    void on_EditProfile_Submit_clicked();

    void on_EditProfile_Cancel_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
};
#endif // MAINWINDOW_H
