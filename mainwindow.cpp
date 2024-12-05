#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QStandardItemModel>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //модуль тут
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Опис", "Сума", "Дата"});

     ui->tableView->setModel(model);


     connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::addTransaction);
     connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::deleteTransaction);
     ui->tableView->setSortingEnabled(true);
     ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // По кнопках працюють сиганали
}


void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::addTransaction()
{
    // Отримання даних з віджетів
    QString description = ui->lineEdit->text(); // Опис
    QString date = ui->dateEdit->date().toString("yyyy-MM-dd"); // Дата
    QString amount = QString::number(ui->doubleSpinBox->value(), 'f', 2) + " грн"; // Сума з приставкою "грн"

    // Додавання даних до таблиці
    QList<QStandardItem *> row;
    row.append(new QStandardItem(description));
    row.append(new QStandardItem(amount));
    row.append(new QStandardItem(date));
    model->appendRow(row);

    // Очищення введених даних
    ui->lineEdit->clear();
    ui->doubleSpinBox->setValue(0.0);
    ui->dateEdit->setDate(QDate::currentDate());
}

void MainWindow::deleteTransaction()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedRows();
    for (const QModelIndex &index : selected) {
        model->removeRow(index.row());
    }
}
