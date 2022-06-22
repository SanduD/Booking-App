#ifndef OTHERS_H
#define OTHERS_H

#include <QWidget>
#include <QListWidget>
#include "client.h"
#include <QStackedWidget>
#include <QMessageBox>
//#include "popupwindow.h"
namespace Ui {
class Others;
}

class Others : public QWidget
{
    Q_OBJECT

private:
    QString selected_question;
    QString selected_answer;
    int submit_case = -1; //0 = submit question ; 1 = submit answer ; 2 = edit question ; 3 = edit answer

public:
    explicit Others(QWidget *parent = nullptr,Client* client = nullptr);
    Ui::Others *ui;
    QListWidget* getListWidget();
    QStackedWidget* getStackedWidget();
    Client* client_mostenit;
    void refresh_list();
    void refresh_list(QString question);
    ~Others();

signals:
    void LogOut();
    void HomePage();
    void MyProfile();

private slots:

    void on_LogOutButton_clicked();

    void on_HomePageButton_clicked();

    void on_NavigationButton_clicked();

    void on_AskQuestionButton_clicked();

    void on_Submit_clicked();

    void on_Cancel_clicked();

    void on_Refresh_Questions_clicked();

    void on_HomePageButton_2_clicked();

    void on_Refresh_Answers_clicked();

    void on_LogOutButton_2_clicked();

    void on_BackToQuestions_clicked();

    void on_MyProfileFromAnswers_clicked();

    void on_MyProfileFromQuestions_clicked();

    void on_EditQuestion_clicked();

    void on_DeleteQuestion_clicked();

    void on_Answer_clicked();

    void on_EditAnswer_clicked();

    void on_DeleteAnswer_clicked();

    void on_UpVoteAnswer_clicked();

    void on_DownVoteAnswer_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:


};

#endif // OTHERS_H
