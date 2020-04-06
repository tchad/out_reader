#include <gui/include/out_load_dialog.h>
#include "ui_out_load_dialog.h"

#include <QtWidgets/QFileDialog>

#include <iostream>

OutLoadDialog::OutLoadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OutLoadDialog)
{
    ui->setupUi(this);

    connect(ui->fileSelectBtn, &QToolButton::clicked, this, &OutLoadDialog::fileSel);
}

OutLoadDialog::~OutLoadDialog()
{
    delete ui;
}

QString OutLoadDialog::datasetName()
{
    return ui->datasetName->text();
}

QString OutLoadDialog::datasetPath()
{
    return ui->datasetPath->text();
}

QString OutLoadDialog::datasetDesc()
{
    return ui->datasetDesc->toPlainText();
}

void OutLoadDialog::fileSel()
{
    QString path = QFileDialog::getOpenFileName(this, "Open dataset", "", "Output files *.out");

    if(!path.isEmpty()) {
        ui->datasetPath->setText(path);
    }


}
