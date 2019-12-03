#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QListWidgetItem>

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
    void on_actionNew_chat_triggered();

    void on_sendingButton_clicked();

    void on_sendPhotoButton_clicked();

    void on_chatLists_currentRowChanged(int currentRow);

private:
    Ui::MainWindow *ui;

    QVector<QVector<QListWidgetItem> > chats;

    void setNewMsgList(int row);
    void addToChatHistory(QListWidgetItem  item, int row);

};

#endif // MAINWINDOW_H
