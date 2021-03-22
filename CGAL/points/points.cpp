#include<iostream>
#include<fstream>

#include<QtGui>
#include<CGAL/Qt/GraphicsViewNavigation.h>
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

    QPen pen;
    pen.setColor(Qt::red);


    while(iFile >>p){
        scene.addEllipse(p.x(),p.y(),5,5,pen,QBrush(Qt::red));
    }


    iFile.close();

    QGraphicsView* view = new QGraphicsView(&scene);
    view->show();
    return app.exec();
}

