#include <iostream>
#include <fstream>

#include <QtGui>
#include <CGAL/Qt/GraphicsViewNavigation.h>
#include <QLineF>
#include <QLabel>
#include <QApplication> 
#include <QGraphicsScene>
#include <QGraphicsView> 
#include <QGraphicsSimpleTextItem>
#include<CGAL/Cartesian.h>
#include<CGAL/Point_2.h>

using namespace std;

typedef CGAL::Cartesian<double> K;
typedef K::Point_2 Point_2;

int Area2Triangle(Point_2 a,Point_2 b,Point_2 c){
    return ((b.x()-a.x())*(c.y()-a.y()))-((c.x()-a.x())*(b.y()-a.y()));
}


int main(int argc, char **argv)
{

    ifstream iFile("input.txt",ios::in);
    Point_2 p1,p2,p3;
    QApplication app(argc, argv);


    QGraphicsScene scene;
    scene.setSceneRect(0,0, 500, 400);
    
    iFile>>p1;
    iFile>>p2;
    iFile>>p3;

    scene.addLine(QLineF(p1.x(),p1.y(),p2.x(),p2.y()));
    scene.addLine(QLineF(p1.x(),p1.y(),p3.x(),p3.y()));
    scene.addLine(QLineF(p3.x(),p3.y(),p2.x(),p2.y()));


    int Ar=Area2Triangle(p1,p2,p3);
    iFile.close();

    char buf[1000];
         
    snprintf(buf,sizeof buf,"Area = %d",abs(Ar)/2);
    QGraphicsTextItem *text=scene.addText(buf);
    text->setPos(50,350);

    QGraphicsView* view = new QGraphicsView(&scene);
    view->show();
    return app.exec();
}

