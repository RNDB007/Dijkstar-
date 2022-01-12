#include "dk.h"
#include "dkMain.h"
#include<iostream>
#include<cstring>
#include<queue>
#include "vector"
#include<fstream>
#include <map>
using namespace std;


typedef pair<int, int> PII;
vector<Node> allNode;
const int N =1000000; // N�ǵ����ͱ��������ֵ����Ҫ�Լ���̬ȥ�ı�
int planCount=0;//�����滮�˼��Σ�>0�β����ٶ�ȡallnode
// ϡ��ͼ���ڽӱ�����
int h[N], e[N], ne[N], idx;          //e�Ǳߵ�����,e[i]�ǵ�i���ߵ��յ㣬ne[i]�ǵ�i����ͬһ������һ���ߵ���ţ�h[i]��i�Žڵ�Ϊ�������һ���ߵ���ţ�idx������
int weight[N]; // ������Ȩ��
int dist[N];
int father[N];
bool st[N]; // ���Ϊtrue˵�����������·���Ѿ�ȷ��
vector<int> path;
int n, m;
int roadLevel[4]={80,60,45,35};

void add(int x, int y, double c)     //��ʽ��ǰ�Ǵ洢,���������ͼ������Ҫִ������add(x,y,c); add(y,x,c)��
{
	weight[idx] = c; // ���ر�Ҳ��Ҫ��������1->2��Ȩ��Ϊ2��3�ıߣ��ٱ�������1��ʱ��2�ŵ�ľ����������η������
	e[idx] = y; // �������л��кܶ�����ĵ㣬�����ڵ�����ʱ���ǻᵯ����Сֵ2+x��xΪ֮ǰȷ�������·��������
	ne[idx] = h[x]; // ���stΪtrue��������һ�ε���3+x��continue��������ִ�С�
	h[x] = idx++;
	// cout<<x<<" "<<h[x]<<"    "<<idx<<endl;
}

void dijkstra(int start,int end)   //
{

	memset(dist, 0x3f, sizeof(dist));   //����Ϊ�����
	memset(father,-1,sizeof father);
	dist[start] = 0;          //���ĸ��㿪ʼ���������ĸ�dist��Ϊ��
	priority_queue<PII, vector<PII>, greater<PII>> heap; // ����һ��С����
	// ����heap��ΪʲôҪ��pair�أ�����С�����Ǹ��ݾ������ŵģ�������һ������Ҫ�Ǿ��룬����ڴӶ����ó�����ʱ    
	// ��Ҫ֪��֪����������ĸ��㣬��Ȼ��ô�����ڽӵ��أ����Եڶ�������Ҫ��㡣 
	heap.push(make_pair(0,start)); // pair��һ�������Ǿ��룬�ڶ��������ǵ���
	while(heap.size())
	{
		PII k = heap.top(); // ȡ���ڼ���S�о�����̵ĵ�
		heap.pop();
		int ver = k.second, distance = k.first;

		if(st[ver]) continue;    //continue��ʾ��ver���·���Ѿ��ҵ�
		st[ver] = true;          //����ver�����·�����ҵ�
		if(ver==end) break;
		for(int i = h[ver]; i != -1; i = ne[i])
		{
			int j = e[i]; //e[i]������i���ߵ��յ���j�������ver
			if(dist[j] > distance + weight[i])
			{
				father[j]=ver;
				dist[j] = distance + weight[i];
				heap.push(make_pair( dist[j], j ));
			}
		}
	}
	if(dist[end] == 0x3f3f3f3f) return ;
	else {
		while(end!=-1){
			path.push_back(end);
			end=father[end];
		}
	}
}

int pathPlan(int start,int end)        //�滮�����path������
{
	memset(h, -1, sizeof(h));   //��ʼ��h���飬ȫ��Ϊ-1��h[i]��ʾ��i���ڵ�Ӧ����h[i]����
	n=allNode.size();
	ifstream myfile("C:\\Users\\Li\\Desktop\\edgeInfo.txt");
	if (!myfile.is_open())
	{
		cout << "can not open this file" << endl;
		return 0;
	}
	string s;
	while(getline(myfile,s)){
		int a=0,b=0;
		int c=10;
		int i=0;
		while(i<s.size() && s[i]!=' '){
			a= a*c + (s[i]-'0');
			i++;
		}
		i++;
		while(i<s.size() && s[i]!=' '){
			b = b*c + (s[i]-'0');
			i++;
		}
		CguVec2 A(allNode[a-1].x,allNode[a-1].y);
		CguVec2 B(allNode[b-1].x,allNode[b-1].y);
		add(a,b,GetBigCircleDis_Haversine(A,B));
		add(b,a,GetBigCircleDis_Haversine(A,B));
	}
/*
	while (m--)
	{
    �ֶ�����Ļ��Ĳ���
		int x, y, c;
		scanf("%d%d%d", &x, &y, &c);
		add(x, y, c);
		add(y, x, c);
	}*/

    dijkstra(start,end);
		/* �滮��ɺ�������õ��Ĺ滮����ͱ������㣬�Ա���һ�ι滮 */
	memset(h,0,sizeof h);
	memset(e,0,sizeof e);
	memset(ne,0,sizeof ne);
	memset(weight,0,sizeof weight);
	memset(dist,0,sizeof dist);
	memset(st,0,sizeof st);
	idx=0;
	myfile.close();
	return 0;
}

int timePathPlan(int start,int end)        //�滮�����path������
{

	memset(h, -1, sizeof(h));   //��ʼ��h���飬ȫ��Ϊ-1��h[i]��ʾ��i���ڵ�Ӧ����h[i]����
	n=allNode.size();
	ifstream myfile("C:\\Users\\Li\\Desktop\\edgeInfo.txt");
	if (!myfile.is_open())
	{
		cout << "can not open this file" << endl;
		return 0;
	}
	string s;
	while(getline(myfile,s)){
		int a=0,b=0;
		int c=10;
		int i=0;
		while(i<s.size() && s[i]!=' '){
			a= a*c + (s[i]-'0');
			i++;
		}
		i++;
		while(i<s.size() && s[i]!=' '){
			b = b*c + (s[i]-'0');
			i++;
		}
		CguVec2 A(allNode[a-1].x,allNode[a-1].y);
		CguVec2 B(allNode[b-1].x,allNode[b-1].y);
		int dist=GetBigCircleDis_Haversine(A,B);
		if(allNode[a-1].level==1) {
			add(a,b,0.69*GetBigCircleDis_Haversine(A,B));
			add(b,a,0.69*GetBigCircleDis_Haversine(A,B));
		}
		else if (allNode[a-1].level==2) {
			add(a,b,1*GetBigCircleDis_Haversine(A,B));
			add(b,a,1*GetBigCircleDis_Haversine(A,B));
		}
		else if (allNode[a-1].level==3) {
			add(a,b,1.33*GetBigCircleDis_Haversine(A,B));
			add(b,a,1.33*GetBigCircleDis_Haversine(A,B));
		}
		else{
			add(a,b,1.7*GetBigCircleDis_Haversine(A,B));
			add(b,a,1.7*GetBigCircleDis_Haversine(A,B));
		} 	
	}
/*
	while (m--)
	{
    �ֶ�����Ļ��Ĳ���
		int x, y, c;
		scanf("%d%d%d", &x, &y, &c);
		add(x, y, c);
		add(y, x, c);
	}*/

    dijkstra(start,end);
		/* �滮��ɺ�������õ��Ĺ滮����ͱ������㣬�Ա���һ�ι滮 */
	memset(h,0,sizeof h);
	memset(e,0,sizeof e);
	memset(ne,0,sizeof ne);
	memset(weight,0,sizeof weight);
	memset(dist,0,sizeof dist);
	memset(st,0,sizeof st);
	idx=0;
	return 0;
}
QList<PathProperty>GetPath(const CguVec3 &iStartPos,const CguVec3 &iEndPos,int maxSpeed,double searchRadius)//����ṩ3��·�����ɣ��ٶ����/ʱ�����/�������
{
	QList<PathProperty> finalPath;
	
	int start,end;
	int startdist=INT_MAX;
	int enddist=INT_MAX;
	if(planCount==0){
		initnode(allNode);     //���뾭γ������  allNode[i]��objectidΪi+1
		++planCount;
	}
	for(int i=0;i<allNode.size();++i){
		CguVec2 A(allNode[i].x,allNode[i].y);
		double dist1=GetBigCircleDis_Haversine(A,iStartPos);
		double dist2=GetBigCircleDis_Haversine(A,iEndPos);
		if(startdist>dist1){
			startdist=dist1;
			start=i+1;
		}
		if(enddist>dist2){
			enddist=dist2;
			end=i+1;
		}
	}
		if(startdist>searchRadius*1000||enddist>searchRadius*1000) return finalPath;

	pathPlan(start,end); //�滮��ϣ�·����path����
	RoutePath planResult;
	double sumlength=0,sumtime=0;
	for(int i=path.size()-1;i>=0;--i){
		/*��path�е���������objectid��������ǵľ�γ�Ȳ���ͬ����ô����ȫ��������Ǻ������м��objectid*/
		CguVec3 A(allNode[path[i]-1].x,allNode[path[i]-1].y,0);
		planResult.append(A);
		/*���������·�̺�ʱ��*/
		if(i>0){
			int first=i,second=i-1;  //������������

			CguVec3 AA(allNode[path[first]-1].x,allNode[path[first]-1].y,0); //��һ����
			CguVec3 BB(allNode[path[second]-1].x,allNode[path[second]-1].y,0);  //�ڶ�����
			double length=GetBigCircleDis_Haversine(AA,BB);
			sumlength+=length;  //·��
			int speed=min(maxSpeed,roadLevel[allNode[path[first]-1].level-1]);
			double time=(length)/((double)speed/3.6);
			sumtime+=time;
		}
	}
	PathProperty firstPath(planResult,sumtime,sumlength);
	finalPath.append(firstPath);


	path.clear();  //������̹滮��ɣ������path
	timePathPlan(start,end); //�滮��ϣ�·����path���У�ʱ�����
	RoutePath timePlanResult;
	double sumlength2=0,sumtime2=0;
	for(int i=path.size()-1;i>=0;--i){
		/*��path�е���������objectid��������ǵľ�γ�Ȳ���ͬ����ô����ȫ��������Ǻ������м��objectid*/
		CguVec3 A(allNode[path[i]-1].x,allNode[path[i]-1].y,0);
		timePlanResult.append(A);
		if(i>0){
			int first=i,second=i-1;  //������������
			CguVec3 AA(allNode[path[first]-1].x,allNode[path[first]-1].y,0); //��һ����
			CguVec3 BB(allNode[path[second]-1].x,allNode[path[second]-1].y,0);  //�ڶ�����
			double length2=GetBigCircleDis_Haversine(AA,BB);  //·��
			sumlength2+=length2;
			int speed2=min(maxSpeed,roadLevel[allNode[path[first]-1].level-1]);
			double time2=(length2)/((double)speed2/3.6);
			sumtime2+=time2;
		}
	}
		PathProperty secondPath(timePlanResult,sumtime2,sumlength2);
	finalPath.append(secondPath);

	path.clear();  //������̹滮��ɣ������path
	return finalPath;
}

void main(){
	CguVec3 A(104.02314742797853,30.692468414281077,0);
	CguVec3 B(104.10005172485353,30.633699793832655,0);
	GetPath(A,B,75,0.0005);

	GetPath(A,B,75,5);
}
