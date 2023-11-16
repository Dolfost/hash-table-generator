#include "mainwindow.h"
#include "ui_mainwindow.h"

int hash(QString str, int size) {
    long long hashCode = 0;
    for (long long i = 0; i < str.length(); i++) {
        hashCode += str[i].unicode() * std::pow(31, i);
    }
    return hashCode % size;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Hash table generator");
    ui->loadFactorSpinBox->setValue(1.25);

    table = new ChainHashTable<QString>(5, 1.25, hash);

    scene = new QGraphicsScene();
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    scene->setBackgroundBrush(Qt::black);
    ui->graphicsView->setScene(scene);

    table->insert("cow");
    table->insert("cat");
    table->insert("bird");
    table->insert("cockroach");
    table->insert("butterfly");
    table->insert("ant");

    refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete table;
}

void MainWindow::drawTable() {
    int sizeX = 100;
    int sizeY = 40;

    int x = 0;
    int y = 0;
    int spacing = 40;
    int verticalSpacing = 40;

    for (int i = 0; i < table->size(); i++) {
        QPen border;
        border.setColor(Qt::white);
        border.setWidth(1);

        QGraphicsEllipseItem* tableElement = new QGraphicsEllipseItem;
        tableElement->setZValue(2);
        tableElement->setRect(x, y, sizeX, sizeY);
        tableElement->setBrush(QBrush(Qt::magenta));
        tableElement->setPen(border);
        scene->addItem(tableElement);

        QGraphicsTextItem* label = new QGraphicsTextItem(QString::number(i));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setZValue(3);
        label->setPos(tableElement->boundingRect().center() - label->boundingRect().center());
        scene->addItem(label);

        if (i + 1 < table->size()) {
            QGraphicsLineItem* lineItem = new  QGraphicsLineItem(x + sizeX/2, sizeY/2, x + sizeX + spacing, sizeY/2);
            lineItem->setPen(QPen(Qt::white));
            lineItem->setZValue(1);
            scene->addItem(lineItem);
        }

        if (table->table[i] != nullptr) {
            int j = 0;
            for (LinkedListNode<QString>* temp = table->table[i]->list.head; temp != nullptr; temp = temp->next, j++) {
                y += sizeY + verticalSpacing;

                QGraphicsLineItem* lineItem = new  QGraphicsLineItem(x + sizeX/2, y - sizeY - verticalSpacing, x + sizeX/2, y);
                lineItem->setPen(QPen(Qt::white));
                lineItem->setZValue(1);
                scene->addItem(lineItem);

                QGraphicsRectItem* listItem = new QGraphicsRectItem;
                listItem->setZValue(2);
                listItem->setRect(x, y, sizeX, sizeY);
                listItem->setBrush(QBrush(Qt::green));
                if (temp == lastFound) {
                    QPen pen;
                    pen.setColor(Qt::yellow);
                    pen.setWidth(3);
                    listItem->setPen(pen);
                } else
                    listItem->setPen(QPen(Qt::white));
                lineItem->setZValue(1);
                scene->addItem(listItem);

                QGraphicsTextItem* label = new QGraphicsTextItem(temp->data);
                label->setZValue(3);
                label->setDefaultTextColor(Qt::black);
                label->setPos(listItem->boundingRect().center() - label->boundingRect().center());
                scene->addItem(label);
            }
            y = 0;
        }

        x += sizeX + spacing;
    }
}


void MainWindow::on_insertPushButton_clicked()
{
    table->insert(ui->stringLineEdit->text());
    autoRefresh();
}

void MainWindow::refresh(void) {
    scene->clear();
    drawTable();
    scene->setSceneRect(scene->itemsBoundingRect());
    ui->countLineEdit->setText(QString::number(table->count()));
    ui->sizeLineEdit->setText(QString::number(table->size()));
}

void MainWindow::autoRefresh(void) {
    if (ui->refreshAutomaticallycheckBox->isChecked())
        refresh();
}


void MainWindow::on_removePushButton_clicked()
{
    table->remove(ui->stringLineEdit->text());
    autoRefresh();
}

void MainWindow::on_createPushButton_clicked()
{
    delete table;
    table = new ChainHashTable<QString>(ui->sizeSpinBox->value(), ui->loadFactorSpinBox->value(), hash);
    autoRefresh();
}


void MainWindow::on_refreshAutomaticallycheckBox_stateChanged(int arg1)
{
    if (arg1 == true)
        refresh();
}


void MainWindow::on_searchPushButton_clicked()
{
    lastFound = table->search(ui->stringLineEdit->text());
    if (lastFound != nullptr) {
        autoRefresh();
    }
}
