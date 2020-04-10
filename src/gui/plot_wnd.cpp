
#include <gui/include/plot_wnd.h>
#include "ui_plot_wnd.h"


PlotWnd::PlotWnd(reader::DatasetAbstractSharedPtr dset, QWidget *parent) :
    QMainWindow(parent),
    ptrDataset(dset),
    ui(new Ui::PlotWnd)
{
    ui->setupUi(this);
    connect(ui->actionClose, &QAction::triggered, this, [this](){ emit sigClose(getId()); });
    setAttribute(Qt::WA_DeleteOnClose);
}

PlotWnd::~PlotWnd()
{
    delete ui;
}

std::uint16_t PlotWnd::getId() const
{
    return ptrDataset->Id();
}
