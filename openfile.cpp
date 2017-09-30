#include "openfile.h"
#include "ui_openfile.h"
#include <QWidget>
#include <QDialog>
#include <QFileSystemModel>
#include <QDebug>

OpenFile::OpenFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenFile)
{
    ui->setupUi(this);
    this->setWindowTitle("Открыть изображение");

    lDir = new QFileSystemModel(this);
    lDir->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    lDir->setRootPath("~/");
    ui->listView->setModel(lDir);
    QModelIndex idx = lDir->index("~/");
    ui->listView->setRootIndex(idx);
}

OpenFile::~OpenFile()
{
    delete ui;
}
void OpenFile::on_listView_clicked(const QModelIndex &index)
{
    fname = lDir->filePath(index);
    tDir = new QFileSystemModel(this);
    tDir->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
    tDir->setRootPath(fname);
    QModelIndex idx1 = tDir->index(fname);
    ui->treeView->setModel(tDir);
    ui->treeView->setRootIndex(idx1);

}

void OpenFile::on_treeView_clicked(const QModelIndex &index)
{
    QRegExp exp("([a-zA-Z0-9_ \\:\\-\\.\\C\\)\\+ ])+([a-zA-Z0-9_ \\:\\-\\.\\C\\)\\+ ])?\\.(JPG|png|jpg|gif|jpeg)");
    dir = new QDir();
    tDir->filePath(index);
    QString name = tDir->fileInfo(index).fileName();
    if (tDir->isDir(index))
    {
        ui->treeView->setModel(tDir);
        ui->treeView->setRootIndex(index);
    }
    if (exp.exactMatch(name))
    {
        fname = name;
        fpath=tDir->filePath(index).remove(fname);
        ui->label->setText(name);
        int size = (tDir->fileInfo(index).size()/1024);
        if ( (size/1024) < 1)
         {   ui->label_2->setText(QString::number(size)+"Kb");

        }
        else
        {
            size/=1024;
            ui->label_2->setText(QString::number(size)+"Mb");
        }
     QImage img(fpath+"/"+fname);
     QImage img2 = img.scaled(200,200, Qt::KeepAspectRatio);
     QPalette* pal = new QPalette();
     pal->setBrush(ui->widget->backgroundRole(), QBrush(img2));
     ui->widget->setPalette(*pal);

     ui->widget->setAutoFillBackground(true);
     ui->widget->setFixedSize(img2.width(), img2.height());
     dir->setPath(fpath);
     fList = dir->entryList();
    }
}

void OpenFile::on_open_clicked()
{
    if (!fname.isEmpty())
        close();
}

void OpenFile::on_treeView_doubleClicked(const QModelIndex &index)
{
    if (!fname.isEmpty())
        close();
}
