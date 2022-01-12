#include "geomutil.h"
#include <QtWidgets/QApplication>

typedef QList<CguVec3> RoutePath;//航迹路径
struct PathProperty
{
	RoutePath Path;
	double time;
	double length;
	PathProperty(){}
	PathProperty(RoutePath x,double y,double z):Path(x),time(y),length(z){}
};

QList<PathProperty>GetPath(const CguVec3 &iStartPos,const CguVec3 &iEndPos,int maxSpeed,double searchRadius);//最多提供3组路径即可，速度最快/时间最快/距离最近  maxSpeed km/h