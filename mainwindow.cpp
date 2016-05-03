#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTableView>
#include <QTableWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();
    connect(ui->actionCargar_Datos,SIGNAL(triggered()),this,SLOT(loadData()));
    connect(ui->actionSalir,SIGNAL(triggered()),this,SLOT(close()));
    ui->tabWidget->removeTab(1);
    ui->groupBox->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectDb()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("qtmysql");
    db.setUserName("root");
    db.setPassword("123456");
    qDebug()<<db.open();
}

void MainWindow::loadData()
{
    connectDb();
    QTableView *tableView = new QTableView;

    QSqlTableModel *model = new QSqlTableModel(this,db);
    model->setTable("datos");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("Cedula"));
    model->setHeaderData(1, Qt::Horizontal, tr("Nombre"));
    model->setHeaderData(2, Qt::Horizontal, tr("Apellido"));

    tableView->setModel(model);
    tableView->setWindowTitle("Datos");
    tableView->setObjectName("tableData");
    ui->tabWidget->addTab(new QWidget,"Datos");
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(tableView);
    ui->tabWidget->widget(1)->setLayout(layout);
    ui->tabWidget->setCurrentIndex(1);
    ui->groupBox->show();
    connect(ui->saveButton,SIGNAL(clicked(bool)),model,SLOT(submitAll()));
}



