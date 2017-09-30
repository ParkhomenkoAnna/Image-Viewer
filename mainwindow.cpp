#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Image Viewer");
    ui->statusBar->addWidget(ui->label);
    wgt = new Painter();
    ui->scrollArea->setWidget(wgt);
    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    setCentralWidget(ui->scrollArea);
    ui->mainToolBar->addWidget(ui->ZoomIn);
    ui->mainToolBar->addWidget(ui->ZoomOut);
    ui->mainToolBar->addWidget(ui->Previous);
    ui->mainToolBar->addWidget(ui->Next);
}

void MainWindow::setImage(QString path, QString name)
{
    wgt->fileName = path + name;
    wgt->factor = 1.0;
    wgt->update();
    this->setWindowTitle("Image Viewer - " + name);
}

void MainWindow::on_actionOpen_triggered()
{
    OpenFile open;
    open.setWindowFlags(Qt::WindowFullscreenButtonHint);
    open.exec();
    if (!open.fname.isEmpty() && !open.fpath.isEmpty())
    {
       imagePath = open.fpath;
       imageName = open.fname;
       setImage(imagePath,imageName);
       imagesList = open.fList;
       next=imagesList.indexOf( imageName);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionZoomIn_triggered()
{
    wgt->factor = 1.11 * wgt->factor;
    wgt->update();
}

void MainWindow::on_actionZoomOut_triggered()
{;
    wgt->factor = 0.9 *wgt->factor;
    wgt->update();
}

void MainWindow::on_actionNormalSize_triggered()
{
    wgt->factor = 1.0;
    wgt->update();
}

void MainWindow::on_ZoomIn_clicked()
{
    on_actionZoomIn_triggered();
}

void MainWindow::on_ZoomOut_clicked()
{
    on_actionZoomOut_triggered();
}

void MainWindow::on_Next_clicked()
{
    if (next <= imagesList.length()-1)
        setImage(imagePath,imagesList.at(++next));
    else
        next=0;
}

void MainWindow::on_Previous_clicked()
{
    if (next > 0)
        setImage(imagePath,imagesList.at(--next));
    else
        next=imagesList.length()-1;
}
