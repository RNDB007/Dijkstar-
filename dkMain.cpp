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
const int N =1000000; // N是点数和边数的最大值，需要自己动态去改变
int planCount=0;//计数规划了几次，>0次不用再读取allnode
// 稀疏图用邻接表来存
int h[N], e[N], ne[N], idx;          //e是边的数组,e[i]是第i条边的终点，ne[i]是第i条边同一起点的上一条边的序号，h[i]是i号节点为起点的最后一条边的序号，idx计数用
int weight[N]; // 用来存权重
int dist[N];
int father[N];
bool st[N]; // 如果为true说明这个点的最短路径已经确定
vector<int> path;
int n, m;
int roadLevel[4]={80,60,45,35};

void add(int x, int y, double c)     //链式向前星存储,如果是无向图，则需要执行两次add(x,y,c); add(y,x,c)。
{
	weight[idx] = c; // 有重边也不要紧，假设1->2有权重为2和3的边，再遍历到点1的时候2号点的距离会更新两次放入堆中
	e[idx] = y; // 这样堆中会有很多冗余的点，但是在弹出的时候还是会弹出最小值2+x（x为之前确定的最短路径），并
	ne[idx] = h[x]; // 标记st为true，所以下一次弹出3+x会continue不会向下执行。
	h[x] = idx++;
	// cout<<x<<" "<<h[x]<<"    "<<idx<<endl;
}

void dijkstra(int start,int end)   //
{

	memset(dist, 0x3f, sizeof(dist));   //设置为无穷大
	memset(father,-1,sizeof father);
	dist[start] = 0;          //从哪个点开始，就设置哪个dist不为空
	priority_queue<PII, vector<PII>, greater<PII>> heap; // 定义一个小根堆
	// 这里heap中为什么要存pair呢，首先小根堆是根据距离来排的，所以有一个变量要是距离，其次在从堆中拿出来的时    
	// 候要知道知道这个点是哪个点，不然怎么更新邻接点呢？所以第二个变量要存点。 
	heap.push(make_pair(0,start)); // pair第一个参数是距离，第二个参数是点编号
	while(heap.size())
	{
		PII k = heap.top(); // 取不在集合S中距离最短的点
		heap.pop();
		int ver = k.second, distance = k.first;

		if(st[ver]) continue;    //continue表示该ver最短路径已经找到
		st[ver] = true;          //到达ver的最短路径已找到
		if(ver==end) break;
		for(int i = h[ver]; i != -1; i = ne[i])
		{
			int j = e[i]; //e[i]表明第i条边的终点是j，起点是ver
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

int pathPlan(int start,int end)        //规划结果在path数组中
{
	memset(h, -1, sizeof(h));   //初始化h数组，全置为-1，h[i]表示第i个节点应该找h[i]条边
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
    手动输入的话的操作
		int x, y, c;
		scanf("%d%d%d", &x, &y, &c);
		add(x, y, c);
		add(y, x, c);
	}*/

    dijkstra(start,end);
		/* 规划完成后把所有用到的规划数组和变量清零，以便下一次规划 */
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

int timePathPlan(int start,int end)        //规划结果在path数组中
{

	memset(h, -1, sizeof(h));   //初始化h数组，全置为-1，h[i]表示第i个节点应该找h[i]条边
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
    手动输入的话的操作
		int x, y, c;
		scanf("%d%d%d", &x, &y, &c);
		add(x, y, c);
		add(y, x, c);
	}*/

    dijkstra(start,end);
		/* 规划完成后把所有用到的规划数组和变量清零，以便下一次规划 */
	memset(h,0,sizeof h);
	memset(e,0,sizeof e);
	memset(ne,0,sizeof ne);
	memset(weight,0,sizeof weight);
	memset(dist,0,sizeof dist);
	memset(st,0,sizeof st);
	idx=0;
	return 0;
}
QList<PathProperty>GetPath(const CguVec3 &iStartPos,const CguVec3 &iEndPos,int maxSpeed,double searchRadius)//最多提供3组路径即可，速度最快/时间最快/距离最近
{
	QList<PathProperty> finalPath;
	
	int start,end;
	int startdist=INT_MAX;
	int enddist=INT_MAX;
	if(planCount==0){
		initnode(allNode);     //读入经纬度数据  allNode[i]的objectid为i+1
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

	pathPlan(start,end); //规划完毕，路径在path当中
	RoutePath planResult;
	double sumlength=0,sumtime=0;
	for(int i=path.size()-1;i>=0;--i){
		/*在path中的连续两个objectid，如果他们的经纬度不相同，那么必须全部输出他们和他们中间的objectid*/
		CguVec3 A(allNode[path[i]-1].x,allNode[path[i]-1].y,0);
		planResult.append(A);
		/*在这里计算路程和时间*/
		if(i>0){
			int first=i,second=i-1;  //连续的两个点

			CguVec3 AA(allNode[path[first]-1].x,allNode[path[first]-1].y,0); //第一个点
			CguVec3 BB(allNode[path[second]-1].x,allNode[path[second]-1].y,0);  //第二个点
			double length=GetBigCircleDis_Haversine(AA,BB);
			sumlength+=length;  //路程
			int speed=min(maxSpeed,roadLevel[allNode[path[first]-1].level-1]);
			double time=(length)/((double)speed/3.6);
			sumtime+=time;
		}
	}
	PathProperty firstPath(planResult,sumtime,sumlength);
	finalPath.append(firstPath);


	path.clear();  //距离最短规划完成，先清空path
	timePathPlan(start,end); //规划完毕，路径在path当中，时间最短
	RoutePath timePlanResult;
	double sumlength2=0,sumtime2=0;
	for(int i=path.size()-1;i>=0;--i){
		/*在path中的连续两个objectid，如果他们的经纬度不相同，那么必须全部输出他们和他们中间的objectid*/
		CguVec3 A(allNode[path[i]-1].x,allNode[path[i]-1].y,0);
		timePlanResult.append(A);
		if(i>0){
			int first=i,second=i-1;  //连续的两个点
			CguVec3 AA(allNode[path[first]-1].x,allNode[path[first]-1].y,0); //第一个点
			CguVec3 BB(allNode[path[second]-1].x,allNode[path[second]-1].y,0);  //第二个点
			double length2=GetBigCircleDis_Haversine(AA,BB);  //路程
			sumlength2+=length2;
			int speed2=min(maxSpeed,roadLevel[allNode[path[first]-1].level-1]);
			double time2=(length2)/((double)speed2/3.6);
			sumtime2+=time2;
		}
	}
		PathProperty secondPath(timePlanResult,sumtime2,sumlength2);
	finalPath.append(secondPath);

	path.clear();  //距离最短规划完成，先清空path
	return finalPath;
}

void main(){
	CguVec3 A(104.02314742797853,30.692468414281077,0);
	CguVec3 B(104.10005172485353,30.633699793832655,0);
	GetPath(A,B,75,0.0005);

	GetPath(A,B,75,5);
}
