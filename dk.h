#ifndef DK_H
#define DK_H

#include <QtWidgets/QWidget>
#include "ui_dk.h"
#include "iostream"
#include"vector"

struct Node
{
	int objectid;     //顶点id
	double x;   //横坐标
	double y;   //纵坐标
	int orig_fid;  //线的id
	int level;
};
void initnode(std::vector<Node> &allNode);
void initedge();

#endif // DK_H
