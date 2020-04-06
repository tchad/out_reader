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

    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::appQuit);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::actionFileOpen);
    connect(ui->elementShowBtn, &QPushButton::clicked, [=](){
            emit setDisplay(ui->elementId->text());});
    connect(ui->elementDeleteBtn, &QPushButton::clicked, [=](){
            emit setDelete(ui->elementId->text());});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDatasetList(const QStringList &lst)
{
    mDesignListModel->setStringList(lst);
}

void MainWindow::actionFileOpen()
{
    if( mOutLoadDialog->exec() == QDialog::Accepted ) {
        emit setOpen(mOutLoadDialog->datasetName(),
                    mOutLoadDialog->datasetPath(),
                    mOutLoadDialog->datasetDesc());
    }
}
