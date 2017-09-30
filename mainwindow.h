#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <painter.h>
#include <openfile.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Painter  *wgt;
    QStringList  imagesList;
    int next;
    QString imagePath, imageName;

private slots:
    void on_actionOpen_triggered();
    void on_actionZoomIn_triggered();
    void on_actionZoomOut_triggered();
    void on_actionNormalSize_triggered();
    void on_ZoomIn_clicked();
    void on_ZoomOut_clicked();
    void on_Next_clicked();
    void on_Previous_clicked();
    void setImage(QString path, QString name);

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
