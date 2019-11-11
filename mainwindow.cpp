#include "mainwindow.h"

#include <QGuiApplication>
#include <QScreen>

DWIDGET_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) : DMainWindow(parent)
{
//    resize(400,400);
    move(qApp->primaryScreen()->geometry().center() - geometry().center());
}
