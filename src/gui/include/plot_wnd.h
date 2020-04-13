#ifndef __GUI_PLOT_WND__
#define __GUI_PLOT_WND__

#include <cstdint>

#include <QtWidgets/QMainWindow>
#include <parser/include/dataset_abstract.h>

namespace Ui {
    class PlotWnd;
}

class PlotWnd : public QMainWindow
{
    Q_OBJECT

    public:
        explicit PlotWnd(reader::DatasetAbstractSharedPtr dset, QWidget *parent = nullptr);
        ~PlotWnd();

        virtual void closeEvent(QCloseEvent *event) override;

        std::uint16_t getId() const;

    signals:
        void sigClose(std::uint16_t id);

    private:
        void setPlot();
        void plotExport();
        void printDARConsole();

        Ui::PlotWnd *ui;
        reader::DatasetAbstractSharedPtr ptrDataset;
};

#endif

