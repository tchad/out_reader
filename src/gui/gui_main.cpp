
#include <algorithm>

#include <QtCore/QCoreApplication>
#include <QtWidgets/QMessageBox>

#include <gui/include/gui_main.h>


GuiMain::GuiMain(reader::Reader &reader, QObject *parent) :
    QObject(parent),
    mMainWnd(new MainWindow),
    mReader(reader)
{
    connect(mMainWnd, &MainWindow::appQuit, [](){ QCoreApplication::quit(); });
    connect(mMainWnd, &MainWindow::setOpen, this, &GuiMain::setOpen);
    connect(mMainWnd, &MainWindow::setDisplay, this, &GuiMain::setDisplay);
    connect(mMainWnd, &MainWindow::setDelete, this, &GuiMain::setDelete);

    refreshModel();
}

void GuiMain::show()
{
    mMainWnd->show();
    //Test Mode
#ifdef __READER_TEST_MODE__
    setOpen("../res/power.out", "auto_tst", "tst");
    setDisplay("1");
#endif
}

void GuiMain::refreshModel()
{
    QStringList lst;
    reader::IdVectorSharedPtr ptr = mReader.GetStorage().GetIdVector();

    std::sort(ptr->begin(), ptr->end());
    QString str = "Id(%1), name(%2), path(%3), desc(%4)";

    for (auto id : *ptr) {
        reader::DatasetAbstractSharedPtr itm = mReader.GetStorage().Get(id).lock();
        QString tmp = str.arg(QString::number(id), 
                              QString::fromStdString(itm->Name()),
                              QString::fromStdString(itm->Filepath()),
                              QString::fromStdString(itm->Desc())
                );
        lst.append(tmp);
    }

    mMainWnd->setDatasetList(lst);
}

bool GuiMain::processId(const QString &id, std::uint16_t &num_id)
{
    bool ok = false;
    std::uint16_t num;

    num = id.toUShort(&ok);

    if (ok && num > 0) {
        if (mReader.GetStorage().Contains(num)) {
            num_id = num;
            ok = true;
        } else {
            QMessageBox::critical(mMainWnd, "Error", "Id does not exist in the storage.");
            ok = false;
        }
    } else {
        QMessageBox::critical(mMainWnd, "Error", "Id must be integer dreater or equal to 1.");
        ok = false;
    }

    return ok;
}

void GuiMain::setOpen(const QString &path, const QString &name, const QString &desc)
{
    reader::ParserStatus status;
    status = mReader.LoadFile(path.toStdString(), name.toStdString(), desc.toStdString());
    switch(status) {
        case reader::ParserStatus::SUCCESS:
            QMessageBox::information(mMainWnd, "Dataset load", "Loaded");
            break;
        case reader::ParserStatus::ERR_FILE_MISSING:
            QMessageBox::critical(mMainWnd, "Dataset load", "Could not open the file.");
            break;
        case reader::ParserStatus::ERR_UNSUPPORTED_VERSION:
            QMessageBox::critical(mMainWnd, "Dataset load", "Unsupperted version of the dataset.");
            break;
        case reader::ParserStatus::ERR_WRONG_FILE_CONTENT:
            QMessageBox::critical(mMainWnd, "Dataset load", "Unrecognized content of the file.");
            break;
        case reader::ParserStatus::ERR_UNKNOWN:
            QMessageBox::critical(mMainWnd, "Dataset load", "Unknown Error");
            //Obtain pointer here

            break;
    }
    refreshModel();
}

void GuiMain::setDisplay(const QString &id)
{
    std::uint16_t num_id;
    if (processId(id, num_id)) {
        plotWndOpen(num_id);
    }
}

void GuiMain::setDelete(const QString &id)
{
    std::uint16_t num_id;
    if (processId(id, num_id)) {
        if(QMessageBox::question(mMainWnd, "Delete", QString("Delete dataset ") + id) == QMessageBox::Yes) {
            mReader.GetStorage().Remove(num_id);
            refreshModel();
        }
    }
}

void GuiMain::plotWndOpen(std::uint16_t id)
{
    //Skip if window already open
    if (!mPlotWindows.contains(id)) {
        reader::DatasetAbstractSharedPtr ptr = mReader.GetStorage().Get(id).lock();
        PlotWnd *wnd = new PlotWnd(ptr);
        mPlotWindows += id;
        connect(wnd, &PlotWnd::sigClose, [this](std::uint16_t id){ mPlotWindows -= id;});
        wnd->show();
    }
}

