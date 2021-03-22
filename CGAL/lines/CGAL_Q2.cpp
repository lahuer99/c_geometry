#include<iostream>
#include<fstream>

#include<QtGui>
#include<CGAL/Qt/GraphicsViewNavigation.h>
#include<QLineF>
#include<QApplication> 
#include<QGraphicsScene>
#include<QGraphicsView> 
#include<QPen>
#include<CGAL/Cartesian.h>
#include<CGAL/Point_2.h>

typedef CGAL::Cartesian<double> K;
typedef K::Point_2 Point_2;

using namespace std;

int main(int argc, char **argv)
{

    ifstream iFile("input.txt",ios::in);

    Point_2 p;
    QApplication app(argc, argv);


    QGraphicsScene scene;
    scene.setSceneRect(0,0, 500, 400);


    Point_2 p1,p2;
    while(iFile >>p1>>p2){
        scene.addLine(QLineF(p1.x(),p1.y(),p2.x(),p2.y()));
    }


    iFile.close();

    QGraphicsView* view = new QGraphicsView(&scene);
    view->show();
    return app.exec();
}

