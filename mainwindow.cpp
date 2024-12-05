#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QStandardItemModel>
#include <QDate>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

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

     loadTransactions();


}

MainWindow::~MainWindow()
{
    saveTransactions();
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

// тут все для збергання
void MainWindow::loadTransactions()
{
    QFile file("finans.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Помилка", "Не вдалося відкрити файл finans.csv для читання.");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if (fields.size() == 3) { // Перевірка на правильність формату
            QList<QStandardItem *> row;
            row.append(new QStandardItem(fields[0])); // Опис
            row.append(new QStandardItem(fields[1])); // Сума
            row.append(new QStandardItem(fields[2])); // Дата
            model->appendRow(row);
        }
    }

    file.close();
}

void MainWindow::saveTransactions()
{
    QFile file("finans.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Помилка", "Не вдалося відкрити файл finans.csv для запису.");
        return;
    }

    QTextStream out(&file);
    for (int row = 0; row < model->rowCount(); ++row) {
        QStringList fields;
        fields.append(model->item(row, 0)->text()); // Опис
        fields.append(model->item(row, 1)->text()); // Сума
        fields.append(model->item(row, 2)->text()); // Дата
        out << fields.join(',') << "\n";
    }

    file.close();
}

