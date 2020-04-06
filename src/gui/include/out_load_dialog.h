#ifndef __GUI_OUT_LOAD_DIALOG__
#define __GUI_OUT_LOAD_DIALOG__

#include <QtWidgets/QDialog>
#include <QtCore/QString>

namespace Ui {
    class OutLoadDialog;
}

class OutLoadDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit OutLoadDialog(QWidget *parent = nullptr);
        ~OutLoadDialog();

        QString datasetName();
        QString datasetPath();
        QString datasetDesc();

    private:
        Ui::OutLoadDialog *ui;

    private slots:
        void fileSel();
};

#endif
