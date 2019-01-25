#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <Eigen/Geometry>
#include <iostream>
#include <vector>
#include <Eigen/Eigen>
#include <math.h>
#include <QtMath>

using namespace std;
using namespace Eigen;

/*
 * 测站系PAE与地心系坐标xyz的转换
 */

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_ToXYZ_clicked();

    void on_pushButton_ToPAE_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
