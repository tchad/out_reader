#ifndef __GUI__GUI_MAIN__
#define __GUI__GUI_MAIN__

#include <QtCore/QObject>

#include <gui/include/main_window.h>
#include <parser/include/reader.h>

class GuiMain : public QObject
{
    Q_OBJECT

    public:
        explicit GuiMain(reader::Reader &reader, QObject *parent = nullptr);
        ~GuiMain();

        void show();

    private:
        void refreshModel();
        void displayById(std::uint16_t id);
        bool processId(const QString& id, std::uint16_t &num_id);

        MainWindow *mMainWnd;
        reader::Reader &mReader;

    private slots:
        void setOpen(QString path, QString name, QString desc);
        void setDisplay(QString id);
        void setDelete(QString id);
};

#endif

