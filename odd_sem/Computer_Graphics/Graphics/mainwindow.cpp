#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bits/stdc++.h>
#include <unistd.h>
#include <QPixmap>
#include <QImage>
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintDevice>
#include <QPoint>

#define maxHt 1800
#define maxWd 1000
#define maxVer 10000
#define fwidth 600
#define fheight 600
#define ROUND(a) ((int)(a + 0.5))

using namespace std;

const double PI = 2*acos(0.0);
int gridsize = 1;

QImage img;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->x_axis->hide();
    ui->y_axis->hide();
    img=QImage(ui->frame->width(),ui->frame->height(),QImage::Format_RGB888);
    connect(ui->frame,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_Pressed()));
    connect(ui->frame,SIGNAL(sendMousePosition(QPoint&)),this,SLOT(showMousePosition(QPoint&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::point(int x,int y, int r=255, int g=255, int b=255)
{
    if(gridsize == 1) img.setPixel(x,y,qRgb(r,g,b));
    else {
        x = (x/gridsize)*gridsize;
        y = (y/gridsize)*gridsize;
        for(int i=x+1;i <  x + gridsize;i++) {
            for(int j=y+1;j < y + gridsize;j++) {
                img.setPixel(i,j,qRgb(r,g,b));
            }
        }
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::showMousePosition(QPoint &pos)
{
    int x = (pos.x() - ui->frame->width()/2)/gridsize;
    int y = (ui->frame->height()/2 - pos.y())/gridsize;
    ui->mouse_movement->setText(" X : "+QString::number(x)+", Y : "+QString::number(y));
}

void MainWindow::Mouse_Pressed()
{
    int x = (ui->frame->x - ui->frame->width()/2)/gridsize;
    int y = (ui->frame->height()/2 - ui->frame->y)/gridsize;
    ui->mouse_pressed->setText(" X : "+QString::number(x)+", Y : "+QString::number(y));
    point(ui->frame->x,ui->frame->y);
}


void MainWindow::on_show_axes_clicked()
{

    if(ui->show_axes->isChecked())
    {
        for(int j=0;j<ui->frame->width();j+=gridsize)
        {
            point(img.width()/2,j);
        }
        for(int i=0;i<ui->frame->height();i+=gridsize)
        {
            point(i,img.height()/2);
        }
    }
    else{
        on_setgridbutton_clicked();
    }
}

void MainWindow::on_resetButton_clicked()
{
    for(int j=0;j<img.height();j++)
    {
        for(int i=0;i<img.width();i++)
        {
            img.setPixel(i,j,qRgb(0,0,0));
        }
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));

    // on_resetButton_clicked();

    gridsize=ui->gridspinbox->value();
    if(gridsize>1)
    {
        for(int i=0;i<img.width();i+=gridsize)
        {
            for(int j=0;j<img.height();j++)
            {
                img.setPixel(i,j,qRgb(163, 213, 240));
                img.setPixel(j,i,qRgb(163, 213, 240));
            }
        }
        ui->frame->setPixmap(QPixmap::fromImage(img));
    }
}

void MainWindow::on_setgridbutton_clicked()
{
    on_resetButton_clicked();
    gridsize=ui->gridspinbox->value();
    if(gridsize>1)
    {
        for(int i=0;i<img.width();i+=gridsize)
        {
            for(int j=0;j<img.height();j++)
            {
                img.setPixel(i,j,qRgb(163, 213, 240));
                img.setPixel(j,i,qRgb(163, 213, 240));
            }
        }
        ui->frame->setPixmap(QPixmap::fromImage(img));
    }
}

void MainWindow::on_set_point1_clicked()
{
    p1.setX(ui->frame->x);
    p1.setY(ui->frame->y);
}

void MainWindow::on_set_point2_clicked()
{
    p2.setX(ui->frame->x);
    p2.setY(ui->frame->y);
}


// Delay Function
void MainWindow::delay() {
    int SLEEP_ms = ui->delay->value();
    // SLEEP_ms *= 100;
    // SLEEP_ms *= 100;
    QTime dieTime= QTime::currentTime().addMSecs(SLEEP_ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


// DDA (Digital Differential Analyzer) line drawing algorithm

void MainWindow::DDAline(int r, int g, int b) {

    clock_t tStart = clock();
    double tPoint = 0.0;

    double x1 = p1.x()/gridsize;
    double y1 = p1.y()/gridsize;
    double x2 = p2.x()/gridsize;
    double y2 = p2.y()/gridsize;
    double xinc, yinc, step;
    double slope = fabs(y2-y1)/fabs(x2-x1);
    if(slope  <= 1.00) {
        xinc = 1;
        yinc = slope;
        step = fabs(x2 - x1);
    } else {
        xinc = 1/slope;
        yinc = 1;
        step = fabs(y2 - y1);
    }
    if(x1 > x2) xinc *= -1;
    if(y1 > y2) yinc *= -1;
    double x = x1*gridsize + gridsize/2;
    double y = y1*gridsize + gridsize/2;
    for(int i=0;i<=step;i++) {

        clock_t t1 = clock();
        delay();
        point(x,y,r,g,b);
        clock_t t2 = clock();

        x += xinc * gridsize;
        y += yinc * gridsize;

        tPoint += (t2-t1);
    }

    clock_t tEnd = clock();
    double tDDA = (tEnd - tStart) - tPoint;

    ui->time_elapsed_line->setText(QString::number(tDDA*1000/CLOCKS_PER_SEC));
}

void MainWindow::on_DDALine_clicked()
{
    DDAline(255,255,0);
}


// Bresenham line drawing algorithm
void swap(int &a, int &b) {
    int temp = b;
    b = a;
    a = temp;
}

void MainWindow::on_bresenhamLine_clicked()
{
    clock_t tStart = clock();
    double tPoint = 0.0;

    int x1 = p1.x()/gridsize;
    int y1 = p1.y()/gridsize;
    int x2 = p2.x()/gridsize;
    int y2 = p2.y()/gridsize;
    int dx = fabs(x2 - x1);
    int dy = fabs(y2 - y1);

    int xinc = (x1 > x2 ? -1 : 1);
    int yinc = (y1 > y2 ? -1 : 1);
    bool flag = 1;
    int x = x1*gridsize + gridsize/2;
    int y = y1*gridsize + gridsize/2;

    if(dy > dx) { // if slope > 1, then swap
        swap(dx,dy);
        swap(x,y);
        swap(xinc,yinc);
        flag = 0;
    }
    int decision = 2*dy - dx;
    int step = dx;

    for(int i=0;i<=step;i++) {

        clock_t t1 = clock();
        delay();

        if(flag) point(x,y, 253,166,93);
        else point(y,x, 253,166,93);

        clock_t t2 = clock();

        if(decision < 0) {
            x += xinc*gridsize;
            decision += 2*dy;
        } else {
            x += xinc*gridsize;
            y += yinc*gridsize;
            decision += 2*dy - 2*dx;
        }

        tPoint += (t2-t1);
    }

    clock_t tEnd = clock();
    double tBresenham = (tEnd - tStart) - tPoint;

    ui->time_elapsed_line->setText(QString::number(tBresenham*1000/CLOCKS_PER_SEC));
}


// Midpoint Circle drawing algorithm
void MainWindow::on_midpointCircle_clicked()
{
    clock_t tStart = clock();
    double tPoint = 0.0;

    int r = ui->radiusspinbox->value();
    p1.setX(ui->frame->x);
    p1.setY(ui->frame->y);
    int x0 = p1.x()/gridsize;
    int y0 = p1.y()/gridsize;
    x0 = x0*gridsize + gridsize/2;
    y0 = y0*gridsize + gridsize/2;
    int x = 0, y = r*gridsize, p = (1 - r)*gridsize;

    while(y >= x) {

        clock_t t1 = clock();

        point(x0 - x, y0 - y, 255, 255, 102);
        point(x0 + x, y0 - y, 204, 255, 153);
        point(x0 - x, y0 + y, 255, 153, 51);
        point(x0 + x, y0 + y, 255, 51, 51);
        point(x0 - y, y0 - x, 178, 102, 255);
        point(x0 + y, y0 - x, 0, 128, 255);
        point(x0 - y, y0 + x, 102, 0, 204);
        point(x0 + y, y0 + x, 255, 204, 204);

        delay();

        clock_t t2 = clock();

        x += gridsize;
        if(p < 0) {
            p += 2*x + 1;
        } else {
            p += 2*x + 1 - 2*y;
            y -= gridsize;
        }
        tPoint += (t2-t1);
    }

    clock_t tEnd = clock();
    double tBresenhamCircle = (tEnd - tStart) - tPoint;
    ui->time_elapsed_circle->setText(QString::number(tBresenhamCircle*1000/CLOCKS_PER_SEC));
}


// Bresenham Circle drawing algorithm
void MainWindow::on_bresenhamMidpointCircle_clicked()
{
    clock_t tStart = clock();
    double tPoint = 0.0;

    int r = ui->radiusspinbox->value();
    p1.setX(ui->frame->x);
    p1.setY(ui->frame->y);
    int x0 = p1.x()/gridsize;
    int y0 = p1.y()/gridsize;
    x0 = x0*gridsize + gridsize/2;
    y0 = y0*gridsize + gridsize/2;
    int x = 0, y = r*gridsize, p = (3 - 2*r)*gridsize;

    while(y >= x) {

        clock_t t1 = clock();

        point(x0 - x, y0 - y, 255, 255, 102);
        point(x0 + x, y0 - y, 204, 255, 153);
        point(x0 - x, y0 + y, 255, 153, 51);
        point(x0 + x, y0 + y, 255, 51, 51);
        point(x0 - y, y0 - x, 178, 102, 255);
        point(x0 + y, y0 - x, 0, 128, 255);
        point(x0 - y, y0 + x, 102, 0, 204);
        point(x0 + y, y0 + x, 255, 204, 204);

        delay();

        clock_t t2 = clock();

        x += gridsize;
        if(p < 0) {
            p += 4*x + 6;
        } else {
            p += 4*(x-y) + 10;
            y -= gridsize;
        }
        tPoint += (t2-t1);
    }

    clock_t tEnd = clock();
    double tBresenhamCircle = (tEnd - tStart) - tPoint;
    ui->time_elapsed_circle->setText(QString::number(tBresenhamCircle*1000/CLOCKS_PER_SEC));
}


// Polar Circle drawing algorithm
void MainWindow::on_polarCircle_clicked()
{
    clock_t tStart = clock();
    double tPoint = 0.0;

    int r = ui->radiusspinbox->value();
    p1.setX(ui->frame->x);
    p1.setY(ui->frame->y);
    int x0 = p1.x()/gridsize;
    int y0 = p1.y()/gridsize;
    x0 = x0*gridsize + gridsize/2;
    y0 = y0*gridsize + gridsize/2;
    double x=0.0, y=0.0;

    for(float theta = 0.0; theta<=(PI/4); theta += 1.0/double(r)){

        x = round(r*cos(theta)*gridsize);
        y = round(r*sin(theta)*gridsize);

        clock_t t1 = clock();

        point(x0 - x, y0 - y, 255, 255, 102);
        point(x0 + x, y0 - y, 204, 255, 153);
        point(x0 - x, y0 + y, 255, 153, 51);
        point(x0 + x, y0 + y, 255, 51, 51);
        point(x0 - y, y0 - x, 178, 102, 255);
        point(x0 + y, y0 - x, 0, 128, 255);
        point(x0 - y, y0 + x, 102, 0, 204);
        point(x0 + y, y0 + x, 255, 204, 204);

        delay();

        clock_t t2 = clock();
        tPoint += (t2-t1);
    }

    clock_t tEnd = clock();
    double tBresenhamCircle = (tEnd - tStart) - tPoint;
    ui->time_elapsed_circle->setText(QString::number(tBresenhamCircle*1000/CLOCKS_PER_SEC));
}


// Cartesian Circle drawing algorithm
void MainWindow::on_cartesianCircle_clicked()
{
    clock_t tStart = clock();
    double tPoint = 0.0;

    int r = ui->radiusspinbox->value();
    p1.setX(ui->frame->x);
    p1.setY(ui->frame->y);
    int x0 = p1.x()/gridsize;
    int y0 = p1.y()/gridsize;
    x0 = x0*gridsize + gridsize/2;
    y0 = y0*gridsize + gridsize/2;
    double x=0.0, y=0.0;

    for(float i = 0.0; i < (r/sqrt(2)); i += 1.0) {
        x = i;
        y = sqrt(r*r - x*x);
        x *= gridsize;
        y *= gridsize;

        clock_t t1 = clock();

        point(x0 - x, y0 - y, 255, 255, 102);
        point(x0 + x, y0 - y, 204, 255, 153);
        point(x0 - x, y0 + y, 255, 153, 51);
        point(x0 + x, y0 + y, 255, 51, 51);
        point(x0 - y, y0 - x, 178, 102, 255);
        point(x0 + y, y0 - x, 0, 128, 255);
        point(x0 - y, y0 + x, 102, 0, 204);
        point(x0 + y, y0 + x, 255, 204, 204);

        delay();


        clock_t t2 = clock();
        tPoint += (t2-t1);
    }

    clock_t tEnd = clock();
    double tBresenhamCircle = (tEnd - tStart) - tPoint;
    ui->time_elapsed_circle->setText(QString::number(tBresenhamCircle*1000/CLOCKS_PER_SEC));
}


// Polar Ellipse drawing algorithm
void MainWindow::on_polarEllipse_clicked()
{
    clock_t tStart = clock();
    double tPoint = 0.0;

    p1.setX(ui->frame->x);
    p1.setY(ui->frame->y);
    int rx = ui->r1spinbox->value();
    int ry = ui->r2spinbox->value();
    int x0 = p1.x()/gridsize;
    int y0 = p1.y()/gridsize;
    x0 = x0*gridsize + gridsize/2;
    y0 = y0*gridsize + gridsize/2;
    double x=0, y=0, theta = 0;

    for(int i=0; i<=90; i++){
        theta = i*PI/180;
        x = rx*cos(theta)*gridsize;
        y = ry*sin(theta)*gridsize;

        clock_t t1 = clock();

        point(x0 + x, y0 + y, 204, 0, 0);
        point(x0 - x, y0 + y, 102, 255, 255);
        point(x0 - x, y0 - y, 51, 0, 102);
        point(x0 + x, y0 - y, 255, 153, 51);

//        point(x0 + x, y0 + y);
//        point(x0 - x, y0 + y);
//        point(x0 - x, y0 - y);
//        point(x0 + x, y0 - y);

        delay();

        clock_t t2 = clock();
        tPoint += (t2-t1);
    }

    clock_t tEnd = clock();
    double tBresenhamCircle = (tEnd - tStart) - tPoint;
    ui->time_elapsed_ellipse->setText(QString::number(tBresenhamCircle*1000/CLOCKS_PER_SEC));
}


// Midpoint Ellipse drawing algorithm
void MainWindow::on_bresenhamMidpointEllipse_clicked()
{
    clock_t tStart = clock();
    double tPoint = 0.0;

    p1.setX(ui->frame->x);
    p1.setY(ui->frame->y);
    int rx = ui->r1spinbox->value();
    int ry = ui->r2spinbox->value();
    int x_centre=p1.x();
    int y_centre=p1.y();
    int k = ui->gridspinbox->value();//GridSize

    x_centre=(x_centre/k)*k+k/2;
    y_centre=(y_centre/k)*k+k/2;

    int x=0;
    int y=ry;
    int rx2=rx*rx;
    int ry2=ry*ry;
    int tworx2=2*rx2;
    int twory2=2*ry2;
    int px=0.0;
    int py=tworx2*y;

    //For first region
    int p1=ry2-rx2*ry+(0.25)*rx2; //Initial value of decision paramemter
    while(px<py)
    {
        clock_t t1 = clock();

        point(x_centre+x*k,y_centre+y*k, 204, 0, 0);
        point(x_centre-x*k,y_centre+y*k, 102, 255, 255);
        point(x_centre-x*k,y_centre-y*k, 51, 0, 102);
        point(x_centre+x*k,y_centre-y*k, 255, 153, 51);

        delay();

        clock_t t2 = clock();
        tPoint += (t2 - t1);

        x++;
        px+=twory2;
        if(p1>=0) {
            y--;
            py-=tworx2;
            p1=p1+ry2+px-py;

        }  else{
            p1=p1+ry2+px;
        }
    }

    //For second region
    p1=ry2*((double)x+0.5)*((double)x+0.5)+rx2*(y-1)*(y-1)-rx2*ry2; //Initial value of decision paramemte
    while(y>=0)
    {
        clock_t t3 = clock();

        point(x_centre+x*k,y_centre+y*k, 255, 255, 102);
        point(x_centre-x*k,y_centre+y*k, 204, 255, 153);
        point(x_centre-x*k,y_centre-y*k, 255, 204, 204);
        point(x_centre+x*k,y_centre-y*k, 0, 128, 255);

        delay();

        clock_t t4 = clock();
        tPoint += (t4 - t3);

        y--;
        py-=tworx2;
        if(p1<=0){
            x++;
            px+=twory2;
            p1=p1+rx2-py+px;

        }  else  {
            p1=p1+rx2-py;
        }
    }

    clock_t tEnd = clock();
    double tBresenhamCircle = (tEnd - tStart) - tPoint;
    ui->time_elapsed_ellipse->setText(QString::number(tBresenhamCircle*1000/CLOCKS_PER_SEC));
}


// Flood-Fill Algorithm
void MainWindow::floodfillutil(int x, int y, QRgb canvascolour, int r, int g, int b)
{
    if(x < 0 || y < 0 || x >= img.width() || y >= img.height()) return;
    if(img.pixel(x,y) != canvascolour || img.pixel(x,y) == qRgb(r,g,b)) return;
    // if(img.pixel(x,y) == qRgb(r,g,b)) return;
    else{

        point(x,y,r,g,b);
        delay();

        floodfillutil(x - gridsize, y, canvascolour, r,g,b);
        floodfillutil(x + gridsize, y, canvascolour, r,g,b);
        floodfillutil(x, y - gridsize, canvascolour, r,g,b);
        floodfillutil(x, y + gridsize, canvascolour, r,g,b);

//        floodfillutil(x - gridsize, y + gridsize, r,g,b);
//        floodfillutil(x - gridsize, y - gridsize, r,g,b);
//        floodfillutil(x + gridsize, y - gridsize, r,g,b);
//        floodfillutil(x + gridsize, y + gridsize, r,g,b);
    }
}

void MainWindow::on_floodfill_clicked()
{
    p1.setX(ui->frame->x);
    p1.setY(ui->frame->y);
    int x = p1.x()/gridsize;
    int y = p1.y()/gridsize;
    x = x*gridsize + gridsize/2;
    y = y*gridsize + gridsize/2;

    point(x,y,0,0,0);
    floodfillutil(x,y, qRgb(0,0,0), 100,0,255);
}


// Boundary-Fill Algorithm
void MainWindow::boundaryfillutil(int x, int y, QRgb edgecolour, int r, int g, int b) {

    if(x < 0 || y < 0 || x >= img.width() || y >= img.height()) return;
    if(img.pixel(x,y) == edgecolour || img.pixel(x,y) == qRgb(r,g,b)) return;
    else {

        point(x,y,r,g,b);
        delay();

        boundaryfillutil(x - gridsize, y, edgecolour,r,g,b);
        boundaryfillutil(x + gridsize, y, edgecolour,r,g,b);
        boundaryfillutil(x, y - gridsize, edgecolour,r,g,b);
        boundaryfillutil(x, y + gridsize, edgecolour,r,g,b);
    }
}

void MainWindow::on_boundaryfill_clicked()
{
    p1.setX(ui->frame->x);
    p1.setY(ui->frame->y);
    int x = p1.x()/gridsize;
    int y = p1.y()/gridsize;
    x = x*gridsize + gridsize/2;
    y = y*gridsize + gridsize/2;

    point(x,y,0,0,0);
    boundaryfillutil(x,y,qRgb(255,255,255),164,93,93);
}


// polygon drawing
std::vector<std::pair<int,int> > vertex_list;
void MainWindow::on_setvertex_clicked()
{
    vertex_list.push_back(std::make_pair((ui->frame->x/gridsize)*gridsize+gridsize/2,(ui->frame->y/gridsize)*gridsize+gridsize/2));
    int i=vertex_list.size();
    if(i>=2)
    {
        storeEdgeInTable(vertex_list[i-2].first, vertex_list[i-2].second, vertex_list[i-1].first, vertex_list[i-1].second);//storage of edges in edge table.
        p1.setX(vertex_list[i-1].first);p1.setY(vertex_list[i-1].second);
        p2.setX(vertex_list[i-2].first);p2.setY(vertex_list[i-2].second);
        on_DDALine_clicked();
    }
}

void MainWindow::on_clearvertex_clicked()
{
    vertex_list.clear();
    initEdgeTable();
}



// Scanline Filling
typedef struct edgebucket
{
    int ymax;   //max y-coordinate of edge
    float xofymin;  //x-coordinate of lowest edge point updated only in aet
    float slopeinverse;
} EdgeBucket;

typedef struct edgetabletup
{
    // the array will give the scanline number
    // The edge table (ET) with edges entries sorted
    // in increasing y and x of the lower end

    int countEdgeBucket;    //no. of edgebuckets
    EdgeBucket buckets[maxVer];
} EdgeTableTuple;

EdgeTableTuple EdgeTable[maxHt], ActiveEdgeTuple;
void MainWindow::initEdgeTable()
{
    int i;
    for (i=0; i<maxHt; i++)
    {
        EdgeTable[i].countEdgeBucket = 0;
    }

    ActiveEdgeTuple.countEdgeBucket = 0;
}

void insertionSort(EdgeTableTuple *ett)
{
    int i,j;
    EdgeBucket temp;

    for (i = 1; i < ett->countEdgeBucket; i++)
    {
        temp.ymax = ett->buckets[i].ymax;
        temp.xofymin = ett->buckets[i].xofymin;
        temp.slopeinverse = ett->buckets[i].slopeinverse;
        j = i - 1;

    while ((temp.xofymin < ett->buckets[j].xofymin) && (j >= 0))
    {
        ett->buckets[j + 1].ymax = ett->buckets[j].ymax;
        ett->buckets[j + 1].xofymin = ett->buckets[j].xofymin;
        ett->buckets[j + 1].slopeinverse = ett->buckets[j].slopeinverse;
        j = j - 1;
    }
        ett->buckets[j + 1].ymax = temp.ymax;
        ett->buckets[j + 1].xofymin = temp.xofymin;
        ett->buckets[j + 1].slopeinverse = temp.slopeinverse;
    }
}

void storeEdgeInTuple (EdgeTableTuple *receiver,int ym,int xm,float slopInv)
{
    (receiver->buckets[(receiver)->countEdgeBucket]).ymax = ym;
    (receiver->buckets[(receiver)->countEdgeBucket]).xofymin = (float)xm;
    (receiver->buckets[(receiver)->countEdgeBucket]).slopeinverse = slopInv;

    insertionSort(receiver);
    (receiver->countEdgeBucket)++;
}

void MainWindow::storeEdgeInTable (int x1,int y1, int x2, int y2)
{
    float m,minv;
    int ymaxTS,xwithyminTS, scanline;

    if (x2==x1)
    {
        minv=0.000000;
    }
    else
    {
    m = ((float)(y2-y1))/((float)(x2-x1));

    if (y2==y1)
        return;

    minv = (float)1.0/m;
    }

    if (y1>y2)
    {
        scanline=y2;
        ymaxTS=y1;
        xwithyminTS=x2;
    }
    else
    {
        scanline=y1;
        ymaxTS=y2;
        xwithyminTS=x1;
    }
    storeEdgeInTuple(&EdgeTable[scanline],ymaxTS,xwithyminTS,minv);
}

void removeEdgeByYmax(EdgeTableTuple *Tup,int yy)
{
    int i,j;
    for (i=0; i< Tup->countEdgeBucket; i++)
    {
        if (Tup->buckets[i].ymax == yy)
        {
            for ( j = i ; j < Tup->countEdgeBucket -1 ; j++ )
                {
                Tup->buckets[j].ymax =Tup->buckets[j+1].ymax;
                Tup->buckets[j].xofymin =Tup->buckets[j+1].xofymin;
                Tup->buckets[j].slopeinverse = Tup->buckets[j+1].slopeinverse;
                }
                Tup->countEdgeBucket--;
            i--;
        }
    }
}

void updatexbyslopeinv(EdgeTableTuple *Tup)
{
    int i;

    for (i=0; i<Tup->countEdgeBucket; i++)
    {
        (Tup->buckets[i]).xofymin =(Tup->buckets[i]).xofymin + (Tup->buckets[i]).slopeinverse;
    }
}

void MainWindow::on_scanlinefill_clicked()
{
    int i, j, x1, ymax1, x2, ymax2, FillFlag = 0, coordCount;

    for (i=0; i<maxHt; i++)
    {
        for (j=0; j<EdgeTable[i].countEdgeBucket; j++)
        {
            storeEdgeInTuple(&ActiveEdgeTuple,EdgeTable[i].buckets[j].
                     ymax,EdgeTable[i].buckets[j].xofymin,
                    EdgeTable[i].buckets[j].slopeinverse);
        }

        removeEdgeByYmax(&ActiveEdgeTuple, i);

        insertionSort(&ActiveEdgeTuple);

        j = 0;
        FillFlag = 0;
        coordCount = 0;
        x1 = 0;
        x2 = 0;
        ymax1 = 0;
        ymax2 = 0;
        while (j<ActiveEdgeTuple.countEdgeBucket)
        {
            if (coordCount%2==0)
            {
                x1 = (int)(ActiveEdgeTuple.buckets[j].xofymin);
                ymax1 = ActiveEdgeTuple.buckets[j].ymax;
                if (x1==x2)
                {
                    if (((x1==ymax1)&&(x2!=ymax2))||((x1!=ymax1)&&(x2==ymax2)))
                    {
                        x2 = x1;
                        ymax2 = ymax1;
                    }

                    else
                    {
                        coordCount++;
                    }
                }

                else
                {
                        coordCount++;
                }
            }
            else
            {
                x2 = (int)ActiveEdgeTuple.buckets[j].xofymin;
                ymax2 = ActiveEdgeTuple.buckets[j].ymax;

                FillFlag = 0;
                if (x1==x2)
                {
                    if (((x1==ymax1)&&(x2!=ymax2))||((x1!=ymax1)&&(x2==ymax2)))
                    {
                        x1 = x2;
                        ymax1 = ymax2;
                    }
                    else
                    {
                        coordCount++;
                        FillFlag = 1;
                    }
                }
                else
                {
                    coordCount++;
                    FillFlag = 1;
                }

            if(FillFlag)
            {
                    p1.setX(x1-1);p1.setY(i-1);
                    p2.setX(x2-1);p2.setY(i-1);
                    // on_DDALine_clicked();
                    on_bresenhamLine_clicked();
            }

        }

        j++;
    }
    updatexbyslopeinv(&ActiveEdgeTuple);
}

    vertex_list.clear();
    initEdgeTable();
}




// Translation Algorithm
void MainWindow::poly_draw(std::vector<std::pair<int,int> > vlist, int r, int g, int b) {
    for(unsigned long i=0;i<vlist.size()-1;i++)
    {
        p1.setX(vlist[i].first); p1.setY(vlist[i].second);
        p2.setX(vlist[i+1].first); p2.setY(vlist[i+1].second);
        DDAline(r,g,b);
    }
}

void mat_mult(double a[3][3], int b[3], double res[3]){
    int i,j;
    for(i=0;i<3;i++){
        res[i]=0;
        for(j=0;j<3;j++)
            res[i]+=(a[i][j]*b[j]);
    }
}

void MainWindow::on_translation_clicked()
{
    double tx = ui->xtranslate->value();
    double ty = ui->ytranslate->value();
    int k = ui->gridspinbox->value();

    std::vector<std::pair<int,int> > old_vertex = vertex_list;
    for(int i=0;i<(int)vertex_list.size();i++)
    {
        old_vertex.push_back(vertex_list[i]);
    }

    tx*=k;
    ty*=k;
    ty=-ty;
    int i,len=vertex_list.size();

    // matrix for translation
    double mat[3][3]={{1,0,tx},{0,1,ty},{0,0,1}};

    int coord[3];
    double res[3];
    for(i=0;i<len;i++)
    {
        coord[0]=vertex_list[i].first;
        coord[1]=vertex_list[i].second;
        coord[2]=1;
        mat_mult(mat,coord,res);
        vertex_list[i].first= res[0]/res[2];
        vertex_list[i].second= res[1]/res[2];
    }
    // poly_draw(old_vertex,0,0,0);
    poly_draw(old_vertex, 255,255,0);
    poly_draw(vertex_list,255, 249, 182);
}

// Rotating Algorithm
void MainWindow::on_rotation_clicked()
{
    int angle = ui->anglespinbox->value();
    gridsize = ui->gridspinbox->value();

    std::vector<std::pair<int,int> > old_vertex;
    for(int i=0;i<(int)vertex_list.size();i++)
    {
        old_vertex.push_back(vertex_list[i]);
    }

    double dang=(double)angle*M_PI/180.0;
    double sinang=sin(dang);
    double cosang=cos(dang);

    //Point about which to be rotated
    int piv_x=(ui->frame->x/gridsize)*gridsize+gridsize/2;
    int piv_y=(ui->frame->y/gridsize)*gridsize+gridsize/2;

    int i,len=vertex_list.size();

    // matrix for rotation
    double mat[3][3]={{cosang,-sinang,0},{sinang,cosang,0},{0,0,1}};
    int coord[3];
    double res[3];
    for(i=0;i<len;i++)
    {
        coord[0]=vertex_list[i].first-piv_x;
        coord[1]=piv_y-vertex_list[i].second;
        coord[2]=1;
        mat_mult(mat,coord,res);
        vertex_list[i].first=res[0]/res[2]+piv_x;
        vertex_list[i].second=piv_y-res[1]/res[2];
    }

    // poly_draw(old_vertex,0,0,0);
    poly_draw(old_vertex, 255,255,0);
    poly_draw(vertex_list,255, 249, 182);
}


// Scaling Algorithm
void MainWindow::on_scaling_clicked()
{
    double sx = ui->xscale->value();
    double sy = ui->yscale->value();
    gridsize = ui->gridspinbox->value();

    std::vector<std::pair<int,int> > old_vertex;
    for(int i=0;i<(int)vertex_list.size();i++)
    {
        old_vertex.push_back(vertex_list[i]);
    }

    //Point about which to be scaled
    int piv_x=(ui->frame->x/gridsize)*gridsize+gridsize/2;
    int piv_y=(ui->frame->y/gridsize)*gridsize+gridsize/2;

    int i,len=vertex_list.size();

    // matrix for scaling
    double mat[3][3]={{sx,0,0},{0,sy,0},{0,0,1}};
    int coord[3];
    double res[3];
    for(i=0;i<len;i++)
    {
        int* coord=(int*)malloc(3*sizeof(int));
        coord[0]=vertex_list[i].first-piv_x;
        coord[1]=piv_y-vertex_list[i].second;
        coord[2]=1;
        mat_mult(mat,coord,res);
        vertex_list[i].first=res[0]/res[2]+piv_x;
        vertex_list[i].second=piv_y-res[1]/res[2];

    }

    cout << coord;
    // poly_draw(old_vertex,0,0,0);
    poly_draw(old_vertex, 255,255,0);
    poly_draw(vertex_list,255, 249, 182);
}


// Shearing Algorithm
void MainWindow::on_shearing_clicked()
{
    double shx = ui->xshear->value();
    double shy = ui->yshear->value();
    gridsize = ui->gridspinbox->value();

    std::vector<std::pair<int,int> > old_vertex;
    for(int i=0;i<(int)vertex_list.size();i++)
    {
        old_vertex.push_back(vertex_list[i]);
    }

    //Point about which to be scaled
    int piv_x=(ui->frame->x/gridsize)*gridsize+gridsize/2;
    int piv_y=(ui->frame->y/gridsize)*gridsize+gridsize/2;

    int i,len=vertex_list.size();

    // matrix for shearing
    double mat[3][3]={{1,shx,0},{shy,1,0},{0,0,1}};
    int coord[3];
    double res[3];
    for(i=0;i<len;i++)
    {
        coord[0]=vertex_list[i].first-piv_x;
        coord[1]=piv_y-vertex_list[i].second;
        coord[2]=1;
        mat_mult(mat,coord,res);
        vertex_list[i].first=res[0]/res[2]+piv_x;
        vertex_list[i].second=piv_y-res[1]/res[2];
    }
    // poly_draw(old_vertex,0,0,0);
    poly_draw(old_vertex, 255,255,0);
    poly_draw(vertex_list,255, 249, 182);
}


// Reflection Algorithm
void MainWindow::on_reflection_clicked()
{
    int i,len=vertex_list.size();

    double dx=p1.x()-p2.x();
    double dy=p1.y()-p2.y();

    double a=-dy;
    double b=dx;
    double c=p1.x()*dy-p1.y()*dx;

    for(i=0;i<len;i++)
    {
        int x1=vertex_list[i].first;
        int y1=vertex_list[i].second;

        vertex_list[i].first=(int)((double)x1-(double)(2*a*(a*x1+b*y1+c))/(double)((a*a+b*b)));
        vertex_list[i].second=(int)((double)y1-(double)(2*b*(a*x1+b*y1+c))/(double)((a*a+b*b)));
    }
    poly_draw(vertex_list,255,255,255);
}



// ----------------------------------------------CLIPPING-----------------------------------------------
int clipper_points[4][2];
void MainWindow::on_setcorner1_clicked()
{
    cp1.setX((ui->frame->x/gridsize)*gridsize+gridsize/2);
    cp1.setY((ui->frame->y/gridsize)*gridsize+gridsize/2);
}

void MainWindow::on_setcorner2_clicked()
{
    cp2.setX((ui->frame->x/gridsize)*gridsize+gridsize/2);
    cp2.setY((ui->frame->y/gridsize)*gridsize+gridsize/2);

    clipper_points[0][0]=cp1.x();
    clipper_points[0][1]=cp1.y();
    clipper_points[1][0]=cp1.x();
    clipper_points[1][1]=cp2.y();
    clipper_points[2][0]=cp2.x();
    clipper_points[2][1]=cp2.y();
    clipper_points[3][0]=cp2.x();
    clipper_points[3][1]=cp1.y();

    draw_Window();
}

void MainWindow::draw_Window()
{
    p1.setX(clipper_points[0][0]);
    p1.setY(clipper_points[0][1]);
    p2.setX(clipper_points[1][0]);
    p2.setY(clipper_points[1][1]);
    DDAline(0,255,255);

    p1.setX(clipper_points[1][0]);
    p1.setY(clipper_points[1][1]);
    p2.setX(clipper_points[2][0]);
    p2.setY(clipper_points[2][1]);
    DDAline(0,255,255);

    p1.setX(clipper_points[2][0]);
    p1.setY(clipper_points[2][1]);
    p2.setX(clipper_points[3][0]);
    p2.setY(clipper_points[3][1]);
    DDAline(0,255,255);

    p1.setX(clipper_points[3][0]);
    p1.setY(clipper_points[3][1]);
    p2.setX(clipper_points[0][0]);
    p2.setY(clipper_points[0][1]);
    DDAline(0,255,255);
}


// ************************** LINE CLIPPING ********************************

// Cohen-Sutherland Line-Clipping Algorithm
// Defining region codes
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Function to compute region code for a point(x, y)
int MainWindow::computeCode(int xa, int ya)
{
    int x_min=cp1.x(),x_max=cp2.x(),y_min=cp1.y(),y_max=cp2.y();

    // initialized as being inside
        int code = INSIDE;
        if (xa < x_min)       // to the left of rectangle
            code |= LEFT;
        else if (xa > x_max)  // to the right of rectangle
            code |= RIGHT;
        if (ya < y_min)       // below the rectangle
            code |= BOTTOM;
        else if (ya > y_max)  // above the rectangle
            code |= TOP;

        return code;
}

// Implementing Cohen-Sutherland algorithm
// Clipping a line from P1 = (x2, y2) to P2 = (x2, y2)
void MainWindow::cohenSutherlandClip(int x1, int y1, int x2, int y2)
{
    int x_min=clipper_points[0][0],x_max=clipper_points[2][0],y_min=clipper_points[0][1],y_max=clipper_points[2][1];
    // Compute region codes for P1, P2
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

    // Initialize line as outside the rectangular window
    bool accept = false;

    while (true)
    {
        if ((code1 == 0) && (code2 == 0))
        {
            // If both endpoints lie within rectangle
            accept = true;
            break;
        }
        else if (code1 & code2)
        {
            // If both endpoints are outside rectangle,
            // in same region
            break;
        }
        else
        {
            // Some segment of line lies within the
            // rectangle
            int code_out;
            int x, y;

            // At least one endpoint is outside the
            // rectangle, pick it.
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            // Find intersection point;
            // using formulas y = y1 + slope * (x - x1),
            // x = x1 + (1 / slope) * (y - y1)
            if (code_out & TOP)
            {
                // point is above the clip rectangle
                x = x1 + (int)((double)(x2 - x1) *(double)(y_max - y1) /(double)(y2 - y1));
                y = y_max;
            }
            else if (code_out & BOTTOM)
            {
                // point is below the rectangle
                x = x1 + (int)((double)(x2 - x1) * (double)(y_min - y1) / (double)(y2 - y1));
                y = y_min;
            }
            else if (code_out & RIGHT)
            {
                // point is to the right of rectangle
                y = y1 + (int)((double)(y2 - y1) * (double)(x_max - x1) / (double)(x2 - x1));
                x = x_max;
            }
            else if (code_out & LEFT)
            {
                // point is to the left of rectangle
                y = y1 + (int)((double)(y2 - y1) * (double)(x_min - x1) / (double)(x2 - x1));
                x = x_min;
            }

            // Now intersection point x,y is found
            // We replace point outside rectangle
            // by intersection point
            if (code_out == code1)
            {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }
    if (accept)
    {
        //If accepted
        //Just reset and draw the boundary and the line
        //Reset the screen and draw the grid

        p1.setX(x1);
        p1.setY(y1);

        p2.setX(x2);
        p2.setY(y2);

        DDAline(255,255,0);
        draw_Window();
    }
    else
    {
        //If not accepted
        //Just reset and draw the boundary
        //Reset the screen and draw the grid
        draw_Window();
    }

}

void MainWindow::on_cohenSutherland_clicked()
{
    DDAline(0,0,0);
    // DDAline(100,100,100);
    cohenSutherlandClip(p1.x(),p1.y(),p2.x(),p2.y());
}



// Liang-Barsky Line Clipping Algorithm
bool MainWindow :: testandsetliangbarsky(float p, float q, float* u1, float* u2)
{
    float r ;
    bool retval = true;
    if(p < 0){
        r = q/p;
        if(r>*u2)retval = false;
        else if(r>*u1) *u1 = r;
    }else if(p>0){
            r = q/p;
            if(r<*u1)retval=false;
            else if(r<*u2) *u2 = r;
    }else if(q<0) retval = false;
    return retval;
}

bool MainWindow :: liangBarskyClip(QPair<int, int>* p1, QPair<int, int>* p2, QPair<int, int> min, QPair<int, int> max)
{
    float u1 = 0.0, u2 = 1.0, dx = p2->first - p1->first, dy = p2->second - p1->second;
    if(testandsetliangbarsky(-dx,p1->first-min.first,&u1,&u2))
        if(testandsetliangbarsky(dx,max.first-p1->first,&u1,&u2))
            if(testandsetliangbarsky(-dy,p1->second-min.second,&u1,&u2))
                if(testandsetliangbarsky(dy,max.second-p1->second,&u1,&u2)){
                    if(u2<1){
                        p2->first = p1->first + u2*dx;
                        p2->second = p1->second + u2*dy;
                    }
                    if(u1>0){
                        p1->first += u1*dx;
                        p1->second += u1*dy;
                    }
                    return true;

                }
    return false;
}

void MainWindow :: on_liangBarsky_clicked()
{
    DDAline(0,0,0);
    QPair<int, int> point1, point2, minP, maxP;
    point1 = QPair<int,int>(p1.x(), p1.y());
    point2 = QPair<int,int>(p2.x(), p2.y());
    minP = QPair<int,int>(cp1.x(), cp1.y());
    maxP = QPair<int,int>(cp2.x(), cp2.y());

    if (liangBarskyClip(&point1, &point2, minP, maxP))
    {
        p1.setX(point1.first);
        p1.setY(point1.second);
        p2.setX(point2.first);
        p2.setY(point2.second);
        DDAline(255,255,0);
    }
    draw_Window();
}




// *********************** POLYGON CLIPPING *************************************

/* Sutherland-Hodgemann Polygon Clipping Algorithm */
// Returns x-value of point of intersectipn of two lines
int MainWindow::x_intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4)
{
    y1=ui->frame->height()-y1+1;
    y2=ui->frame->height()-y2+1;
    y3=ui->frame->height()-y3+1;
    y4=ui->frame->height()-y4+1;
    int num = (x1*y2 - y1*x2) * (x3-x4) -
              (x1-x2) * (x3*y4 - y3*x4);
    int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    int retx=num/den;
    return retx;
}

// Returns y-value of point of intersectipn of two lines
int MainWindow:: y_intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4)
{
    y1=ui->frame->height()-y1+1;
    y2=ui->frame->height()-y2+1;
    y3=ui->frame->height()-y3+1;
    y4=ui->frame->height()-y4+1;
    int num = (x1*y2 - y1*x2) * (y3-y4) -
              (y1-y2) * (x3*y4 - y3*x4);
    int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    int rety= (ui->frame->height()-num/den+1);
    return rety;
}

// This functions clips all the edges w.r.t one clip edge of clipping area
void MainWindow::clip(int x1, int y1, int x2, int y2)
{
    int poly_size=vertex_list.size()-1;
    int new_poly_size = 0;

    vector<pair<int,int> > new_points;

    // (ix,iy),(kx,ky) are the co-ordinate values of the points
    for (int i = 0; i < poly_size; i++)
    {
        // i and k form a line in polygon
        int k = (i+1) % poly_size;
        int ix = vertex_list[i].first, iy = vertex_list[i].second;
        int kx = vertex_list[k].first, ky = vertex_list[k].second;

        // Calculating position of first and second point

        int i_pos,k_pos;
        if(x2==x1 && ix>x1) i_pos=1;
        else if(x2==x1 && ix<x1) i_pos=-1;
        else if(y2==y1 && iy<y1) i_pos=1;
        else i_pos=-1;

        if(x2==x1 && kx>x1) k_pos=1;
        else if(x2==x1 && kx<x1) k_pos=-1;
        else if(y2==y1 && ky<y1) k_pos=1;
        else k_pos=-1;

        if(y1>y2||x1>x2)
        {
            i_pos=(-1)*i_pos;
            k_pos=(-1)*k_pos;
        }

        // Case 1 : When both points are inside
        if (i_pos >= 0  && k_pos >= 0)
        {
            //Only second point is added
            new_points.push_back(make_pair(kx,ky));
            new_poly_size++;
        }

        // Case 2: When only first point is outside
        else if (i_pos < 0  && k_pos >= 0)
        {
            // Point of intersection with edge and the second point is added

            new_points.push_back(make_pair(x_intersect(x1,y1, x2, y2, ix, iy, kx, ky),y_intersect(x1,y1, x2, y2, ix, iy, kx, ky)));
            new_poly_size++;

            new_points.push_back(make_pair(kx,ky));
            new_poly_size++;
        }

        // Case 3: When only second point is outside
        else if (i_pos >= 0  && k_pos < 0)
        {
            //Only point of intersection with edge is added

            new_points.push_back(make_pair(x_intersect(x1,y1, x2, y2, ix, iy, kx, ky),y_intersect(x1,y1, x2, y2, ix, iy, kx, ky)));
            new_poly_size++;
        }

        // Case 4: When both points are outside
        else
        {
            //No points are added
        }
    }

    // Copying new points into original array and changing the no. of vertices
    // poly_size = new_poly_size;
    vertex_list.clear();
    for (int i = 0; i < int(new_points.size()); i++)
    {
        vertex_list.push_back(new_points[i]);
    }
    vertex_list.push_back(new_points[0]);
}

// Implements Sutherland–Hodgman algorithm
void MainWindow::suthHodgClip()
{
    vector<pair<int,int> > old_vertex;
    for(int i=0;i<int(vertex_list.size());i++)
    {
        old_vertex.push_back(vertex_list[i]);
    }
    int clipper_size=4;
    //i and k are two consecutive indexes
    for (int i=0; i<clipper_size; i++)
    {
        int k = (i+1) % clipper_size;

        // We pass the current array of vertices, it's size and the end points of the selected clipper line
        clip(clipper_points[i][0],
             clipper_points[i][1],
             clipper_points[k][0],
             clipper_points[k][1]);
    }

    poly_draw(old_vertex,0,0,0);
    draw_Window();
    poly_draw(vertex_list,255,0,0);
}
void MainWindow::on_sutherlandHodgeman_clicked()
{
    suthHodgClip();
}





/* Weiler-Atherton Polygon Clipping Algorithm */
QPoint MainWindow::intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4)
{
    y1=ui->frame->height()-y1+1;
    y2=ui->frame->height()-y2+1;
    y3=ui->frame->height()-y3+1;
    y4=ui->frame->height()-y4+1;

    int num1 = (x1*y2 - y1*x2) * (x3-x4) -(x1-x2) * (x3*y4 - y3*x4);
    int den1 = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    int retx=num1/den1;

    int num2 = (x1*y2 - y1*x2) * (y3-y4) -(y1-y2) * (x3*y4 - y3*x4);
    int den2 = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    int rety= (ui->frame->height()-num2/den2+1);

    return QPoint(retx,rety);
}

void MainWindow::WAclipCacher(int x1, int y1, int x2, int y2)
{
    vector<QPoint> polygon(this->poly_vertex_list.begin(),this->poly_vertex_list.end());
    int poly_size = polygon.size() - 1;

    this->clipping_poly_list.push_back(qMakePair(QPoint(x1,y1),"vertex"));
    vector<QPair<QPoint, QString>> store;
    int sign = x1 == x2 ? y2 - y1 : x2 - x1;
    bool flag = x1 == x2 ? false : true;

    // i and k are two consecutive indexes
    // (ix,iy),(kx,ky) are the co-ordinate values of the points
    for (int i = 0; i < poly_size; i++)
    {
        // i and k form a line in polygon
        int k = (i+1) % poly_size;
        int ix = polygon[i].x(), iy = polygon[i].y();
        int kx = polygon[k].x(), ky = polygon[k].y();
        int index = findIntersection(true, qMakePair(polygon[k], "vertex"));
        auto it = this->clipped_poly_list.begin() + index;
//        it = (it == this->clipped_poly_list.begin()) ? it = this->clipped_poly_list.end() : it-1;
        // Calculating position of first and second point

        int i_pos,k_pos;
        if(x2==x1 && ix>x1) i_pos=1;
        else if(x2==x1 && ix<x1) i_pos=-1;
        else if(y2==y1 && iy<y1) i_pos=1;
        else i_pos=-1;

        if(x2==x1 && kx>x1) k_pos=1;
        else if(x2==x1 && kx<x1) k_pos=-1;
        else if(y2==y1 && ky<y1) k_pos=1;
        else k_pos=-1;

        if(y1>y2||x1>x2)
        {
            i_pos=(-1)*i_pos;
            k_pos=(-1)*k_pos;
        }

        // Case 1 : When both points are inside
        if (i_pos >= 0  && k_pos >= 0)
        {
            // No intersection points are added
        }

        // Case 2: When only first point is outside
        else if (i_pos < 0  && k_pos >= 0)
        {
            // Point of intersection with edge and the second point is added
            QPoint intPoint = intersect(x1,y1, x2, y2, ix, iy, kx, ky);
            it = this->clipped_poly_list.insert(it, qMakePair(intPoint, "entry"));
            it++;
            auto it1 = this->clipping_poly_list.begin() + findCorrPos(sign, flag, store, qMakePair(intPoint, "entry"));
            it1 = this->clipping_poly_list.insert(it1,qMakePair(intPoint, "entry"));
        }

        // Case 3: When only second point is outside
        else if (i_pos >= 0  && k_pos < 0)
        {
            //Only point of intersection with edge is added
            QPoint intPoint = intersect(x1,y1, x2, y2, ix, iy, kx, ky);
            it = this->clipped_poly_list.insert(it, qMakePair(intPoint, "exit"));
            it++;
            auto it1 = this->clipping_poly_list.begin() + findCorrPos(sign, flag, store, qMakePair(intPoint, "exit"));
            it1 = this->clipping_poly_list.insert(it1,qMakePair(intPoint, "exit"));
        }

        // Case 4: When both points are outside
        else
        {
            //No intersection points are added
        }
    }
    this->clipping_poly_list.insert(this->clipping_poly_list.end(), store.begin(),store.end());
}

void MainWindow::WAclip()
{
    int i=0;
    int clliped_poly_size=this->clipped_poly_list.size(), clliping_poly_size=this->clipping_poly_list.size();
    for(auto &&point : this->clipped_poly_list) {
        if(point.second=="entry") {
            qDebug() << point.first.x() << point.first.y() << point.second;
            vector<QPoint> new_poly;
            new_poly.push_back(point.first);
            int j=i;
            while(true) {
                j = (j+1) % clliped_poly_size;
                auto newPoint = this->clipped_poly_list[j];
                if(newPoint.second!="exit"){
                    qDebug() << newPoint.first.x() << newPoint.first.y() << newPoint.second;
                    new_poly.push_back(newPoint.first);
                }
                else {
                    int index = findIntersection(false, newPoint);
                    while(true) {
                        auto newPoint1 = this->clipping_poly_list[index];
                        qDebug() << newPoint1.first.x() << newPoint1.first.y() << newPoint1.second;
                        index = (index+1) % clliping_poly_size;
                        new_poly.push_back(newPoint1.first);
                        if(point==newPoint1) break;
                    }
                    break;
                }
            }
            this->poly_list.push_back(new_poly);
        }
        ++i;
    }
}

int MainWindow::findCorrPos(int sign, bool xy, vector<QPair<QPoint, QString> > &vec, QPair<QPoint, QString> intPoint)
{
    int i=0;
    if(xy) {
        for (auto && point : vec) {
            if(sign * point.first.x() > sign * intPoint.first.x()) return i;
            ++i;
        }
    }
    else {
        for (auto && point : vec) {
            if(sign * point.first.y() > sign * intPoint.first.y()) return i;
            ++i;
        }
    }
    return i;
}

int MainWindow::findIntersection(bool flag, QPair<QPoint, QString> intPoint)
{
    int i=0;
    if(flag) {
        for (auto && point : this->clipped_poly_list) {
            if(point == intPoint) return i;
            ++i;
        }
    }
    else {
        for (auto && point : this->clipping_poly_list) {
            if(point == intPoint) return i;
            ++i;
        }
    }
    return -1;
}

/*
void MainWindow::on_weilerAtherton_clicked()
{
    vector<QPoint> old_polygon(this->poly_vertex_list.begin(),this->poly_vertex_list.end());

    this->poly_list.clear();
    this->clipped_poly_list.clear();
    this->clipping_poly_list.clear();

    int x_min=this->clipping_window.topLeft().x(),
            x_max=this->clipping_window.bottomRight().x(),
            y_max=this->clipping_window.topLeft().y(),
            y_min=this->clipping_window.bottomRight().y();

    for(auto &&vertex: this->poly_vertex_list) {
        this->clipped_poly_list.push_back(qMakePair(vertex,"vertex"));
    }
    this->clipped_poly_list.pop_back();

    qDebug() << "\n";
    for(auto && poly: clipped_poly_list) {
        qDebug() << poly.first.x() << poly.first.y() << poly.second;
    }

    WAclipCacher(x_min,y_max,x_min,y_min); //Left
    if(this->poly_vertex_list.size()>0)
        WAclipCacher(x_min,y_min,x_max,y_min); //Bottom
    if(this->poly_vertex_list.size()>1)
        WAclipCacher(x_max,y_min,x_max,y_max); //Right
    if(this->poly_vertex_list.size()>1)
        WAclipCacher(x_max,y_max,x_min,y_max); //Top

    rotate(clipped_poly_list.begin(), clipped_poly_list.begin()+1, clipped_poly_list.end());

    qDebug() << "\n";
    for(auto && poly: clipped_poly_list) {
        qDebug() << poly.first.x() << poly.first.y() << poly.second;
    }
    qDebug() << "\n";
    for(auto && poly: clipping_poly_list) {
        qDebug() << poly.first.x() << poly.first.y() << poly.second;
    }
    qDebug() << "\n";

    WAclip();

    this->on_show_grid_clicked();
    this->draw_window();


    this->line_colours[1] = this->clip_colour;
    for(auto && poly: poly_list) {
        this->poly_vertex_list = poly;
        this->drawPolygon();
    }

    this->poly_vertex_list = old_polygon;
}
*/
