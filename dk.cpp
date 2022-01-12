#include "dk.h"
#include<fstream>
#include <iostream>
#include "string"
using namespace std;
void initnode(std::vector<Node> &allNode){

	/************************************************************************/
	/* ��ȡ3.txt���ѵ���Ϣ����vector<node > allnode                         */
	/************************************************************************/
	ifstream myfile("C:\\Users\\Li\\Desktop\\pointInfo.txt");
/*
	if (!myfile.is_open())
	{
		cout << "can not open this file" << endl;
		return ;
	}

	for (int i = 0; i < 115182; i++)
	{
		Node p;
		for (int j = 0; j < 5; j++)
		{
			switch(j){
			case 0:
				myfile>>p.objectid;
				break;
			case 1:
				myfile>>p.orig_fid;
				break;
			case 2:
				myfile>>p.x;
				break;
			case 3:
				myfile>>p.y;
			case 4:
				myfile>>p.level;
			}
		}
		allNode.push_back(p);
	}*/
	string s;
	while(getline(myfile,s)){
		Node p;
		int i=0;
		//----  //��һ������
		p.objectid=0;
		int c=10;
		while(i<s.size() && s[i]!=' '){
			p.objectid = p.objectid*c + (s[i]-'0');
			i++;
		}
		i++;
		//----   �ڶ�������
		p.orig_fid=0;
		while(i<s.size() && s[i]!=' '){
			p.orig_fid = p.orig_fid*c + (s[i]-'0');
			i++;
		}
		i++;
		//---  ������������
		p.x=0;
		
		while(i<s.size() && s[i]!='.'){
			p.x = p.x*c + (s[i]-'0');
			i++;
		}
		i++;
		double dc=0.1;
		while(i<s.size() && s[i]!=' '){
			p.x = p.x + (s[i]-'0')*dc;
			dc*=0.1;
			i++;
		}
		i++;
		//---  ���ĸ� γ��
		p.y=0;
		while(i<s.size() && s[i]!='.'){
			p.y = p.y*c + (s[i]-'0');
			i++;
		}
		i++;
		dc=0.1;
		while(i<s.size() && s[i]!=' '){
			p.y = p.y + (s[i]-'0')*dc;
			dc*=0.1;
			i++;
		}
		i++;
		//---  ����� �ȼ�
		p.level=0;
		while(i<s.size()){
			p.level = p.level*c + (s[i]-'0');
			i++;
		}
		allNode.push_back(p);
	}
	myfile.close();
}

