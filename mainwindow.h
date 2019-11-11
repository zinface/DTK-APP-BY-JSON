#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>

class MainWindow : public Dtk::Widget::DMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MAINWINDOW_H
