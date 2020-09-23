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

        virtual void closeEvent(QCloseEvent *event) override;

        void setDatasetList(const QStringList &lst);

    private:
        Ui::MainWindow *ui;
        OutLoadDialog *mOutLoadDialog;
        QStringListModel *mDesignListModel;

    signals:
        void appQuit();
        void setOpen(const QString &path, const QString &name, const QString &desc);
        void setDisplay(const QString &id);
        void setDelete(const QString &id);

    private slots:
        void actionFileOpen();
};


#endif

