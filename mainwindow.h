#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include"chainHashTable.hpp"

#include <QDebug>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QCryptographicHash>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_insertPushButton_clicked();

    void on_removePushButton_clicked();

    void on_createPushButton_clicked();

    void on_refreshAutomaticallycheckBox_stateChanged(int arg1);

    void on_searchPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene = nullptr;

    ChainHashTable<QString>* table = nullptr;
    LinkedListNode<QString>* lastFound = nullptr;

    void drawTable();
    void refresh();
    void autoRefresh();

};
#endif // MAINWINDOW_H
