#include "geomutil.h"
#include <QtWidgets/QApplication>

typedef QList<CguVec3> RoutePath;//����·��
struct PathProperty
{
	RoutePath Path;
	double time;
	double length;
	PathProperty(){}
	PathProperty(RoutePath x,double y,double z):Path(x),time(y),length(z){}
};

QList<PathProperty>GetPath(const CguVec3 &iStartPos,const CguVec3 &iEndPos,int maxSpeed,double searchRadius);//����ṩ3��·�����ɣ��ٶ����/ʱ�����/�������  maxSpeed km/h