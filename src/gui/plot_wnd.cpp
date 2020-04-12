#include <iostream>

#include <gui/include/plot_wnd.h>
#include "ui_plot_wnd.h"

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_renderer.h>


PlotWnd::PlotWnd(reader::DatasetAbstractSharedPtr dset, QWidget *parent) :
    QMainWindow(parent),
    ptrDataset(dset),
    ui(new Ui::PlotWnd)
{
    ui->setupUi(this);
    connect(ui->actionClose, &QAction::triggered, this, [this](){ emit sigClose(getId()); });
    connect(ui->actionExport, &QAction::triggered, this, [this](){ plotExport(); });
    connect(ui->actionDAR, &QAction::triggered, this, [this](){ printDARConsole(); });
    setAttribute(Qt::WA_DeleteOnClose);

    setPlot();
}

PlotWnd::~PlotWnd()
{
    delete ui;
}

std::uint16_t PlotWnd::getId() const
{
    return ptrDataset->Id();
}

void PlotWnd::setPlot()
{

    QwtPlot *plt = ui->qwtPlot;
    plt->setTitle( "Power vs time" );
    plt->setCanvasBackground( Qt::white );
    plt->setAxisTitle( QwtPlot::xBottom, "Time [ps]" );
    plt->setAxisTitle( QwtPlot::yLeft, "Inst. power [W]" );
    

    QwtPlotCurve *pwrCurve = new QwtPlotCurve("Power");
    QVector<QPointF> dv;
    reader::DatasetAbstract::SimpleDPoint1DListSharedPtr lst = ptrDataset->SimplePowerData();
    for (const auto& p : *lst) {
        dv.append({p.t, p.v});
    }
    pwrCurve->setSamples(dv);
    pwrCurve->attach(plt);
    //pwrCurve->setStyle(QwtPlotCurve::CurveStyle::Dots);
    pwrCurve->setStyle(QwtPlotCurve::CurveStyle::Steps);
    pwrCurve->setPen( Qt::black, 0.5 );
    //pwrCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->enableXMin( true );
    grid->enableYMin( true );
    grid->setMajorPen( Qt::black, 0, Qt::DotLine );
    grid->setMinorPen( Qt::gray, 0 , Qt::DotLine );
    grid->attach(plt);

    QwtPlotZoomer* zoomer = new QwtPlotZoomer( plt->canvas() );
    zoomer->setRubberBandPen( QColor( Qt::black ) );
    zoomer->setTrackerPen( QColor( Qt::black ) );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect3,
        Qt::RightButton );

    QwtPlotPanner *panner = new QwtPlotPanner( plt->canvas() );
    panner->setMouseButton( Qt::MidButton );

    ui->qwtPlot->replot();

}

void PlotWnd::plotExport()
{
    QwtPlotRenderer renderer;
    renderer.exportTo( ui->qwtPlot, "plot.png", QSizeF(200,100), 450 );
}

void PlotWnd::printDARConsole()
{
    std::string rep = ptrDataset->DataAnalysisReport();
    std::clog << rep;
}
