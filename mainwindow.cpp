#include "mainwindow.h"
#include "ui_mainwindow.h"
//111111
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("PAE <--> XYZ");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ToXYZ_clicked()
{
    double  ae = 6378140.0;
    double  ec_2 = 0.0066946;
    double  pi = 3.1415926535897932384626433832795;
    double  we = 360.0/86164.0 ; //地球自转角速度

    double  fai = ui->doubleSpinBox_latitude->value();  //纬度;
    double  lanmuda = ui->doubleSpinBox_longitude->value(); //经度
    //double  lanmuda= ui->doubleSpinBox_latitude->value();
    //double  fai  = ui->doubleSpinBox_longitude->value();
    double  H = ui->doubleSpinBox_height->value();

    fai = fai/180.0*pi;
    lanmuda = lanmuda/180.0*pi;
    qDebug()<<"fai   lanmuda   H";
    qDebug()<<QString::number(fai,'f',6)<<QString::number(lanmuda,'f',6)<<QString::number(H,'f',6);

    double P = ui->doubleSpinBox_r->value();  //距离
    double A = ui->doubleSpinBox_a->value();  //方位
    double E = ui->doubleSpinBox_e->value();  //俯仰
    A = A/180.0*pi;
    E = E/180.0*pi;


    double N = ae/(sqrt(1.0-ec_2*sin(fai)*sin(fai)));

    Vector3d digu_M; //测站位置在地固系中的坐标为
    digu_M(0,0) = (N+H)*cos(fai)*cos(lanmuda);
    digu_M(1,0) = (N+H)*cos(fai)*sin(lanmuda);
    digu_M(2,0) = (N*(1.0-ec_2)+H)*sin(fai);

    qDebug()<<digu_M(0,0)<<endl<<digu_M(1,0)<<endl<<digu_M(2,0)<<endl;
    Vector3d station_M; //测站测量量，A，E在测站直角坐标中的分量
    station_M(0,0) = P*sin(A)*cos(E);
    station_M(1,0) = P*cos(A)*cos(E);
    station_M(2,0) = P*sin(E);

    Matrix3d M = MatrixXd::Random(3,3);//测站直角坐标系到地固系的转换矩阵
    M(0,0) = -sin(lanmuda);
    M(0,1) = -cos(lanmuda)*sin(fai);
    M(0,2) = cos(fai)*cos(lanmuda);

    M(1,0) = cos(lanmuda);
    M(1,1) = -sin(lanmuda)*sin(fai);
    M(1,2) = sin(lanmuda)*cos(fai);

    M(2,0) = 0.0;
    M(2,1) = cos(fai);
    M(2,2) = sin(fai);

    cout<<"look M: "<<M<<M.transpose();
    Vector3d xyz_M ;
    xyz_M = M*station_M + digu_M ;

    ui->doubleSpinBox_x->setValue(xyz_M(0,0));
    ui->doubleSpinBox_y->setValue(xyz_M(1,0));
    ui->doubleSpinBox_z->setValue(xyz_M(2,0));
    qDebug()<<"cal::  "<<QString::number(xyz_M(0,0),'f',6)
           <<QString::number(xyz_M(1,0),'f',6)
           <<QString::number(xyz_M(2,0),'f',6)
          <<QString::number(P,'f',6)
         <<QString::number(N,'f',6);
}

void MainWindow::on_pushButton_ToPAE_clicked()
{
    double  ae = 6378140.0;
    double  ec_2 = 0.0066946;
    double  pi = 3.1415926535897932384626433832795;
    double  we = 360.0/86164.0 ; //地球自转角速度

    double  fai = ui->doubleSpinBox_latitude->value();  //纬度;
    double  lanmuda = ui->doubleSpinBox_longitude->value(); //经度
    //double  lanmuda= ui->doubleSpinBox_latitude->value();
    //double  fai  = ui->doubleSpinBox_longitude->value();
    double  H = ui->doubleSpinBox_height->value();

    fai = fai/180.0*pi;
    lanmuda = lanmuda/180.0*pi;
    qDebug()<<"fai   lanmuda   H";
    qDebug()<<QString::number(fai,'f',6)<<QString::number(lanmuda,'f',6)<<QString::number(H,'f',6);

//    double P = ui->doubleSpinBox_r->value();  //距离
//    double A = ui->doubleSpinBox_a->value();  //方位
//    double E = ui->doubleSpinBox_e->value();  //俯仰
//    A = A/180.0*pi;
//    E = E/180.0*pi;


    double N = ae/(sqrt(1.0-ec_2*sin(fai)*sin(fai)));

    Vector3d digu_M; //测站位置在地固系中的坐标为
    digu_M(0,0) = (N+H)*cos(fai)*cos(lanmuda);
    digu_M(1,0) = (N+H)*cos(fai)*sin(lanmuda);
    digu_M(2,0) = (N*(1.0-ec_2)+H)*sin(fai);

    qDebug()<<digu_M(0,0)<<endl<<digu_M(1,0)<<endl<<digu_M(2,0)<<endl;
//    Vector3d station_M; //测站测量量，A，E在测站直角坐标中的分量
//    station_M(0,0) = P*sin(A)*cos(E);
//    station_M(1,0) = P*cos(A)*cos(E);
//    station_M(2,0) = P*sin(E);

    Matrix3d M = MatrixXd::Random(3,3);//测站直角坐标系到地固系的转换矩阵
    M(0,0) = -sin(lanmuda);
    M(0,1) = -cos(lanmuda)*sin(fai);
    M(0,2) = cos(fai)*cos(lanmuda);

    M(1,0) = cos(lanmuda);
    M(1,1) = -sin(lanmuda)*sin(fai);
    M(1,2) = sin(lanmuda)*cos(fai);

    M(2,0) = 0.0;
    M(2,1) = cos(fai);
    M(2,2) = sin(fai);

    cout<<"look M: "<<M<<M.transpose();
    Vector3d xyz_M ;
    xyz_M(0,0) = ui->doubleSpinBox_x->value();
    xyz_M(1,0) = ui->doubleSpinBox_y->value();
    xyz_M(2,0)
    //xyz_M = M*station_M + digu_M ;

//    ui->doubleSpinBox_x->setValue(xyz_M(0,0));
//    ui->doubleSpinBox_y->setValue(xyz_M(1,0));
//    ui->doubleSpinBox_z->setValue(xyz_M(2,0));
//    qDebug()<<"cal::  "<<QString::number(xyz_M(0,0),'f',6)
//           <<QString::number(xyz_M(1,0),'f',6)
//           <<QString::number(xyz_M(2,0),'f',6)
//          <<QString::number(P,'f',6)
//         <<QString::number(N,'f',6);

}
