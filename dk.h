#ifndef DK_H
#define DK_H

#include <QtWidgets/QWidget>
#include "ui_dk.h"
#include "iostream"
#include"vector"

struct Node
{
	int objectid;     //����id
	double x;   //������
	double y;   //������
	int orig_fid;  //�ߵ�id
	int level;
};
void initnode(std::vector<Node> &allNode);
void initedge();

#endif // DK_H
