#include <iostream>
#include <fstream>
#include<string>

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

Point_2 p[25];
int c;

int Area2Triangle(Point_2 a,Point_2 b,Point_2 c){
    return ((b.x()-a.x())*(c.y()-a.y()))-((c.x()-a.x())*(b.y()-a.y()));
}

int PolygonArea(){
    int ar=0,i=1;
    while(i!=c){
        ar+=Area2Triangle(p[0],p[i%c],p[(i+1)%c]);
        i++;
    }
    return ar;
}

int main(int argc, char **argv)
{

    ifstream iFile("input.txt",ios::in);
    QApplication app(argc, argv);


    QGraphicsScene scene;
    scene.setSceneRect(0,0, 500, 400);
    
    Point_2 pd;
    c=0;
    while(iFile>>pd){
        p[c]=pd;
        c++;
    }

    int i=0;
    while(i!=c){
        scene.addLine(QLineF(p[i%c].x(),p[i%c].y(),p[(i+1)%c].x(),p[(i+1)%c].y()));
        i++;
    }

    int Ar=PolygonArea();
    iFile.close();
    char buf[1000];
         
    snprintf(buf,sizeof buf,"Area = %d",abs(Ar)/2);
    QGraphicsTextItem *text=scene.addText(buf);
    text->setPos(50,350);

    QGraphicsView* view = new QGraphicsView(&scene);
    view->show();
    return app.exec();
}

