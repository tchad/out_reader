#include <iostream>
#include <gui/include/main_window.h>
#include "ui_main_window.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mOutLoadDialog(new OutLoadDialog(this)),
    mDesignListModel(new QStringListModel(this))
{
    ui->setupUi(this);
    ui->listView->setModel(mDesignListModel);

    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::actionFileOpen);
    connect(ui->elementShowBtn, &QPushButton::clicked, [this](){
            emit setDisplay(ui->elementId->text());});
    connect(ui->elementDeleteBtn, &QPushButton::clicked, [this](){
            emit setDelete(ui->elementId->text());});

    setAttribute(Qt::WA_DeleteOnClose);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) 
{
    emit appQuit();
    QMainWindow::closeEvent(event);

    return;
}

void MainWindow::setDatasetList(const QStringList &lst)
{
    mDesignListModel->setStringList(lst);
}

void MainWindow::actionFileOpen()
{
    if( mOutLoadDialog->exec() == QDialog::Accepted ) {
        emit setOpen(mOutLoadDialog->datasetPath(),
                     mOutLoadDialog->datasetName(),
                     mOutLoadDialog->datasetDesc());
    }
}
