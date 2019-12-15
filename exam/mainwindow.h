#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QStringListModel>
#include <vector>

#include "book.h"
#include "author.h"


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
    void on_bookList_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    std::vector<Book*> books;
    std::vector<Author*> authors;
    QStringListModel *bookModel;
    QStringListModel *authorModel;

};

#endif // MAINWINDOW_H
