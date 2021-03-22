#include <iostream>
#include <fstream>
#include <vector>

#include <QtGui>
#include <CGAL/Qt/GraphicsViewNavigation.h>
#include <QLineF>
#include <QApplication> 
#include <QGraphicsScene>
#include <QGraphicsView> 
#include <QGraphicsSimpleTextItem>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>

using namespace std;

typedef CGAL::Cartesian<double> K;
typedef K::Point_2 Point_2;

vector<pair<Point_2,Point_2>> vertx;
int nver;

int Area2Triangle(Point_2 a,Point_2 b,Point_2 c){
    return ((b.x()-a.x())*(c.y()-a.y()))-((c.x()-a.x())*(b.y()-a.y()));
}



bool Left(Point_2 a,Point_2 b,Point_2 c){
    return Area2Triangle(a,b,c)<0;
}

bool Lefton(Point_2 a,Point_2 b,Point_2 c){
    return Area2Triangle(a,b,c)<=0;
}

bool Collinear(Point_2 a,Point_2 b,Point_2 c){
    return Area2Triangle(a,b,c)==0;
}




bool Xor(bool x,bool y){
    return !x^!y;
}

bool intersectProp(Point_2 a,Point_2 b,Point_2 c,Point_2 d){
    if(Collinear(a,b,c) || Collinear(a,b,d) || Collinear(c,d,a) || Collinear(c,d,b)){
        return false;
    }

    return Xor(Left(a,b,c),Left(a,b,d)) && Xor(Left(c,d,a),Left(c,d,b));
}

bool Between(Point_2 a,Point_2 b,Point_2 c){
    if(!Collinear(a,b,c)){
        return false;
    }

    if(a.x()!=b.x()){
        return (a.x()<=c.x() && c.x()<=b.x()) || (c.x()<=a.x() && b.x()<=c.x());
    }
    else{
        return (a.y()<=c.y() && c.y()<=b.y()) || (c.y()<=a.y() && b.y()<=c.y());
    }
}


bool intersect(Point_2 a,Point_2 b,Point_2 c,Point_2 d){
    if(intersectProp(a,b,c,d)){
        return true;
    }
    else if(Between(a,b,c) || Between(a,b,d) || Between(c,d,a) || Between(c,d,b)){
        return true;
    }
    else{
        return false;
    }
}

Point_2 intersectPoints(Point_2 p1, Point_2 p2, Point_2 p3,Point_2 p4)
{
    double a1 = p2.y() - p1.y(); 
    double b1 = p1.x() - p2.x(); 
    double c1 = a1*(p1.x()) + b1*(p1.y()); 
  
    double a2 = p4.y() - p3.y(); 
    double b2 = p3.x() - p4.x(); 
    double c2 = a2*(p3.x())+ b2*(p3.y()); 
  
    double determinant = a1*b2 - a2*b1; 
  

    double x = (b2*c1 - b1*c2)/determinant; 
    double y = (a1*c2 - a2*c1)/determinant; 
    return Point_2(x, y); 
}


int main(int argc, char **argv)
{

    ifstream iFile("input.txt",ios::in);

    QApplication app(argc, argv);

    Point_2 p1,p2;
    nver=0;
    while(iFile>>p1>>p2){
        vertx.push_back(make_pair(p1,p2));
        nver++;
    }

    iFile.close();
    QGraphicsScene scene[20];

    int times=0;
    int i=1,j;
    for(auto it1=vertx.begin();it1!=vertx.end();it1++){
        j=i+1;
        for(auto it2=it1+1;it2!=vertx.end();it2++){

            scene[times].setSceneRect(0,0,400,400);
          
            scene[times].addLine(QLineF((it1)->first.x(),(it1)->first.y(), (it1)->second.x(), (it1)->second.y()));
            scene[times].addLine(QLineF((it2)->first.x(),(it2)->first.y(), (it2)->second.x(), (it2)->second.y()));

            char buf[1000];
            if(intersect((it1)->first,(it1)->second,(it2)->first,(it2)->second)){

                Point_2 in=intersectPoints((it1)->first,(it1)->second,(it2)->first,(it2)->second);

                snprintf(buf,sizeof buf,"%d - %d\n Lines intersect\nLines intersect at (%.2f , %.2f)",i,j,(float)in.x(),(float)in.y());
                QGraphicsTextItem *text=scene[times].addText(buf);
                text->setPos(50,200);
            }
            else{
         
                snprintf(buf,sizeof buf,"%d - %d\nLines do not intersect",i,j);
                QGraphicsTextItem *text=scene[times].addText(buf);
                text->setPos(50,200);
            }

            QGraphicsView* view = new QGraphicsView(scene+times);
            view->show();
            times++;j++;
        }
        i++;
    }
    return app.exec();
}

