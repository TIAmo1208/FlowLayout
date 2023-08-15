#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

#define ITEM_WIDTH 120

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 1; i <= 6; ++i)
    {
        QString path = QString(":/Image/%1").arg(i);
        ui->widget_ImageList->addItemImage(path);
    }

    ui->widget_ImageList->resize(ui->widget_ImageList->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->widget_ImageList->resizeItemWidth(value);
}
