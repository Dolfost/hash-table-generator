#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include"chainHashTable.hpp"

#include <QDebug>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QRandomGenerator>

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

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;

    ChainHashTable<QString>* table;

    void drawTable();
    void refresh();

};
#endif // MAINWINDOW_H
