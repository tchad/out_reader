
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

GuiMain::~GuiMain()
{
    delete mMainWnd;
}

void GuiMain::show()
{
    mMainWnd->show();
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

void GuiMain::displayById(std::uint16_t id)
{
    QMessageBox::critical(mMainWnd, "Error", "SUP.");
}

bool GuiMain::processId(const QString& id, std::uint16_t &num_id)
{
    bool ok = false;
    std::uint16_t num;

    num = id.toUInt(&ok);

    if (ok && num > 0) {
        if (mReader.GetStorage().Contains(num)) {
            num_id = num;
            ok = true;
        }
        else {
            QMessageBox::critical(mMainWnd, "Error", "Id does not exist in the storage.");
        }
    }
    else {
        QMessageBox::critical(mMainWnd, "Error", "Id must be integer dreater or equal to 1.");
    }

    return ok;
}

void GuiMain::setOpen(QString path, QString name, QString desc)
{
    mReader.LoadFile(path.toStdString(), name.toStdString(), desc.toStdString());
    refreshModel();
}

void GuiMain::setDisplay(QString id)
{
    std::uint16_t num_id;
    if (processId(id, num_id)) {
        displayById(num_id);
    }
}

void GuiMain::setDelete(QString id)
{
    std::uint16_t num_id;
    if (processId(id, num_id)) {
        mReader.GetStorage().Remove(num_id);
        refreshModel();
    }
}

