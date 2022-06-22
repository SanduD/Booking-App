#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class PopupWindow;
}

class PopupWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PopupWindow(QWidget *parent = nullptr,QTcpSocket* socket = nullptr,QString username = nullptr);
    ~PopupWindow();

private slots:

    void on_Cancel_clicked();

    void on_Submit_clicked();

private:
    Ui::PopupWindow *ui;
    QTcpSocket* socket_transmis;
    QString username;
};

#endif // POPUPWINDOW_H
