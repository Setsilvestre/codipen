#include <iostream>
#include <iomanip>
#include "Point.h"
#include "Line.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
using namespace std;

void main(){
	setprecision(8);
	vec3 u  (cos(30 * M_PI / 180)*cos(45*M_PI / 180), sin(45*M_PI / 180), sin(30*M_PI / 180)* cos(45*M_PI / 180));
	Line trayectoria;
	trayectoria.setDirectionLine(u.x,u.y,u.z);
	trayectoria.setPointLine(0, 0, 0);
	Point center;
	center.setCoord(1, 2, 1);
	Sphere esfera (center, 3);
	Plane pla;
	pla.setPlanePoint(1, 2, 1);
	pla.setPlaneNormal(-1,1,1);
	pla.setDirectFromNormal();
	pla.computeD();
	Point q, r, s;
	q.setCoord(1, 2, 1);
	r.setCoord(-1, 1, 2);
	s.setCoord(0, -1, 0);
	Triangle mytriangle(q, r, s);
	bool afterSphere=false,beforeSphere=false,afterPlane=false,beforePlane=false,afterTriangle=false,beforeTriangle=false;
	for (float i = 0; i < 10; i = i + 0.01){
		afterSphere= esfera.InsideorOut (trayectoria.pointwithAlfa(i)); 
		if (afterSphere != beforeSphere){
			cout << "La recta talla a l'esfera en: " << endl;
			cout << trayectoria.pointwithAlfa(trayectoria.intersectionwithSphere(trayectoria.pointwithAlfa(i - 0.01), trayectoria.pointwithAlfa(i), esfera.returnCenter(), esfera.returnRadius())).coord.x << endl;
			cout << trayectoria.pointwithAlfa(trayectoria.intersectionwithSphere(trayectoria.pointwithAlfa(i - 0.01), trayectoria.pointwithAlfa(i), esfera.returnCenter(), esfera.returnRadius())).coord.y << endl;
			cout << trayectoria.pointwithAlfa(trayectoria.intersectionwithSphere(trayectoria.pointwithAlfa(i - 0.01), trayectoria.pointwithAlfa(i), esfera.returnCenter(), esfera.returnRadius())).coord.z << endl;			
			cout << i << endl;
			system("pause");
		}
		beforeSphere = afterSphere;
		afterPlane = pla.changePosition(trayectoria.pointwithAlfa(i));
		if (afterPlane != beforePlane){
			cout << "La recta talla al pla en: " << endl;
			cout << pla.entryPointSegmentPlane(trayectoria.pointwithAlfa(i), trayectoria.pointwithAlfa(i - 0.01)).coord.x << endl;
			cout << pla.entryPointSegmentPlane(trayectoria.pointwithAlfa(i), trayectoria.pointwithAlfa(i - 0.01)).coord.y << endl;
			cout << pla.entryPointSegmentPlane(trayectoria.pointwithAlfa(i), trayectoria.pointwithAlfa(i - 0.01)).coord.z << endl;
			cout << i << endl;
			system("pause");
		}
		beforePlane = afterPlane;
		afterTriangle = mytriangle.InsideorOut(trayectoria.pointwithAlfa(i));
		if (afterTriangle != beforeTriangle){
			cout << "La recta talla el triangle en: " << endl;
			cout << trayectoria.pointwithAlfa(i).coord.x << endl;
			cout << trayectoria.pointwithAlfa(i).coord.y << endl;
			cout << trayectoria.pointwithAlfa(i).coord.z << endl;
			cout << i << endl;
			system("pause");
		}
		beforeTriangle = afterTriangle;
	}
}