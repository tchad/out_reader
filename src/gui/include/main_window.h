#ifndef __GUI_MAIN_WINDOW__
#define __GUI_MAIN_WINDOW__

#include <cstdint>

#include <QtCore/QStringList>
#include <QtCore/QStringListModel>
#include <QtCore/QString>
#include <QtWidgets/QMainWindow>

#include <gui/include/out_load_dialog.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        void setDatasetList(const QStringList &lst);

    private:
        Ui::MainWindow *ui;
        OutLoadDialog *mOutLoadDialog;
        QStringListModel *mDesignListModel;

    signals:
        void appQuit();
        void setOpen(QString path, QString name, QString desc);
        void setDisplay(QString id);
        void setDelete(QString id);

    private slots:
        void actionFileOpen();
};


#endif

