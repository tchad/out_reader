#ifndef __GUI__GUI_MAIN__
#define __GUI__GUI_MAIN__

#include <QtCore/QObject>
#include <QtCore/QList>

#include <gui/include/main_window.h>
#include <gui/include/plot_wnd.h>
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
        bool processId(const QString& id, std::uint16_t &num_id);
        int getPlotWndIdxById(std::uint16_t id) const;

        MainWindow *mMainWnd;
        reader::Reader &mReader;
        QList<PlotWnd*> mPlotWindows;

    private slots:
        void setOpen(QString path, QString name, QString desc);
        void setDisplay(QString id);
        void setDelete(QString id);
        void plotWndOpen(std::uint16_t id);
        void plotWndClose(std::uint16_t id);
};

#endif

