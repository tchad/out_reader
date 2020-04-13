#ifndef __GUI__GUI_MAIN__
#define __GUI__GUI_MAIN__

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QSet>

#include <gui/include/main_window.h>
#include <gui/include/plot_wnd.h>
#include <parser/include/reader.h>

class GuiMain : public QObject
{
    Q_OBJECT

    public:
        explicit GuiMain(reader::Reader &reader, QObject *parent = nullptr);
        virtual ~GuiMain() = default;

        void show();

    private:
        void refreshModel();
        bool processId(const QString& id, std::uint16_t &num_id);

        MainWindow *mMainWnd;
        reader::Reader &mReader;

        QSet<std::uint16_t> mPlotWindows;

    private slots:
        void setOpen(QString path, QString name, QString desc);
        void setDisplay(QString id);
        void setDelete(QString id);
        void plotWndOpen(std::uint16_t id);
};

#endif

