#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<iomanip>
using namespace std;
const int Max = 50;
class Graph;
class EdgeNode {
	friend class Graph;
private:
	string cityname;  //到达城市的名称
	double car_start_time;//列车出发时间（出发的时刻，小时和分钟分别存储）
	double car_arrive_time;//列车到达时间
	double plane_start_time;//飞机出发时间
	double plane_arrive_time;//飞机到达时间
	double car_cost;//列车花费
	double plane_cost;//飞机花费
	EdgeNode *link;//边结点后继指针
public:
	EdgeNode() {//边界点初始化，-1代表没有列车或飞机到达该城市
		car_start_time = -1;
		car_arrive_time = -1;
		plane_start_time = -1;
		plane_arrive_time = -1;
		car_cost = 9999999.9;
		plane_cost = 99999999.9;
		link = NULL;
	}
	~EdgeNode(){}
};
class VertexNode {
	friend class Graph;
	friend class EdgeNode;
private:
	string cityname;//城市名称
	EdgeNode *link;//出边表指针
};
class Graph {
private:
	vector<VertexNode> NodeTable;
	int VerticesNum;//城市数量
public:
	Graph() { VerticesNum = 0; }
	bool create_city(istream &in);//必须考虑到如果输入的格式不对或者是多了城市
	char create_car_infomation(istream &in);
	char create_plane_infomation(istream &in);
	void lowest_car_cost(int v, int u);
	void lowest_car_time(int v, int u);
	void lowest_plane_cost(int v, int u);
	void lowest_plane_time(int v, int u);
	void car_printpath(int v, int u);
	void plane_printpath(int v, int u);
	int GetVertexPos(string name);
	void usage(istream &in,string command);
	void create_time(istream &in, double &i, double &j);
	void get_time(const double i, int &hour, int &minute);
	int GetFirstNeighbor(int v);
	int GetNextNeighbor(int v, int u);
	void access_car_cost(const vector<int> s, double &low, vector<int> &path);
	void access_car_time(const vector<int> s, double &low, vector<int> &path);
	void access_plane_cost(const vector<int> s, double &low, vector<int> &path);
	void access_plane_time(const vector<int> s, double &low, vector<int> &path);
	void car_printpath(const vector<int> s);
	void plane_printpath(const vector<int> s);
	void add_Vertices(string city);
	void erase_Vertices(string city);
	void access(string commute,istream &in);
};
bool Graph::create_city(istream &in) {//判断输入几个城市，是否有重复
	string city_name;
	vector<VertexNode>::size_type i;
	VertexNode p;
	while (in>>city_name) {
		for (i = 0; i < NodeTable.size(); i++) if (NodeTable[i].cityname == city_name) break;
		if (i == NodeTable.size()) {
			p.cityname = city_name;
			NodeTable.push_back(p);
			VerticesNum++;
		}
	}
	return true;
}
void Graph::create_time(istream &in, double &i, double &j) {
	char x, y;
	double a1, a2, a3, a4;
	in >> a1 >> x >> a2 >> a3 >> y >> a4;
	i = a1 + a2 / 100;
	j = a3 + a4 / 100;
}
char Graph::create_car_infomation(istream &in) {
	string start_city, arrive_city;
	double start_time, arrive_time;
	string is_no;
	vector<VertexNode>::size_type i, j;
	double cost;
	in >> start_city;
	if (start_city == "完成输入") return 'a';//判断完成输入
	in >> arrive_city;
	create_time(in,start_time,arrive_time);
	in >> cost;
	for (i = 0; i < NodeTable.size(); i++) if (NodeTable[i].cityname == start_city) break;
	for (j = 0; j < NodeTable.size(); j++) if (NodeTable[j].cityname == arrive_city) break;
	if (i == NodeTable.size()&&j!=NodeTable.size()) {
		cout << "该出发城市未出现在系统中，请确认是否加入该城市（是/否）：" << endl;
		in >> is_no;
		if (is_no == "否") return 'b';
		else {
			VertexNode q;
			q.cityname = start_city;
			VerticesNum++;
			NodeTable.push_back(q);
			EdgeNode *p;
			p = new EdgeNode;
			p->cityname = arrive_city;
			p->car_cost = cost;
			p->car_start_time = start_time;
			p->car_arrive_time = arrive_time;
			p->link = NodeTable[i].link;
			NodeTable[i].link = p;
			return 'c';
		}
	}
	if (j == NodeTable.size() && i!= NodeTable.size()) {
		cout << "该到达城市未出现在系统中，请确认是否加入该城市（是/否）：" << endl;
		in >> is_no;
		if (is_no == "否") return 'b';
		else {
			VertexNode q;
			q.cityname = arrive_city;
			VerticesNum++;
			NodeTable.push_back(q);
			EdgeNode *p;
			p = new EdgeNode;
			p->cityname = arrive_city;
			p->car_cost = cost;
			p->car_start_time = start_time;
			p->car_arrive_time = arrive_time;
			p->link = NodeTable[i].link;
			NodeTable[i].link = p;
			return 'e';
		}
	}
	if (j == NodeTable.size() && i == NodeTable.size()) {
		cout << "该出发城市和到达城市均未出现在系统中，请确认是否加入该城市（是/否）：" << endl;
		in >> is_no;
		if (is_no == "否") return 'b';
		else {
			VertexNode q;
			q.cityname = start_city;
			VerticesNum++;
			NodeTable.push_back(q);
			q.cityname = arrive_city;
			VerticesNum++;
			NodeTable.push_back(q);
			EdgeNode *p;
			p = new EdgeNode;
			p->cityname = arrive_city;
			p->car_cost = cost;
			p->car_start_time = start_time;
			p->car_arrive_time = arrive_time;
			p->link = NodeTable[i].link;
			NodeTable[i].link = p;
			return 'f';
		}
	}
	EdgeNode *p;
	p = new EdgeNode;
	p->cityname = arrive_city;
	p->car_cost = cost;
	p->car_start_time = start_time;
	p->car_arrive_time = arrive_time;
	p->link = NodeTable[i].link;
	NodeTable[i].link = p;
	return 'd';

}
char Graph::create_plane_infomation(istream &in) {
	string start_city, arrive_city;
	double start_time, arrive_time;
	string is_no;
	vector<VertexNode>::size_type i, j;
	double cost;
	in >> start_city;
	if (start_city == "完成输入") return 'a';//判断完成输入
	in >> arrive_city;
	create_time(in, start_time, arrive_time);
	in >> cost;
	for (i = 0; i < NodeTable.size(); i++) if (NodeTable[i].cityname == start_city) break;
	for (j = 0; j < NodeTable.size(); j++) if (NodeTable[j].cityname == arrive_city) break;
	if (i == NodeTable.size() && j != NodeTable.size()) {
		cout << "该出发城市未出现在系统中，请确认是否加入该城市（是/否）：" << endl;
		in >> is_no;
		if (is_no == "否") return 'b';
		else {
			VertexNode q;
			q.cityname = start_city;
			VerticesNum++;
			NodeTable.push_back(q);
			EdgeNode *p;
			p = new EdgeNode;
			p->cityname = arrive_city;
			p->plane_cost = cost;
			p->plane_start_time = start_time;
			p->plane_arrive_time = arrive_time;
			p->link = NodeTable[i].link;
			NodeTable[i].link= p;
			return 'c';
		}
	}
	if (j == NodeTable.size() && i != NodeTable.size()) {
		cout << "该到达城市未出现在系统中，请确认是否加入该城市（是/否）：" << endl;
		in >> is_no;
		if (is_no == "否") return 'b';
		else {
			VertexNode q;
			q.cityname = arrive_city;
			VerticesNum++;
			NodeTable.push_back(q);
			EdgeNode *p;
			p = new EdgeNode;
			p->cityname = arrive_city;
			p->plane_cost = cost;
			p->plane_start_time = start_time;
			p->plane_arrive_time = arrive_time;
			p->link = NodeTable[i].link;
			NodeTable[i].link= p;
			return 'e';
		}
	}
	if (j == NodeTable.size() && i == NodeTable.size()) {
		cout << "该出发城市和到达城市均未出现在系统中，请确认是否加入该城市（是/否）：" << endl;
		in >> is_no;
		if (is_no == "否") return 'b';
		else {
			VertexNode q;
			q.cityname = start_city;
			VerticesNum++;
			NodeTable.push_back(q);
			q.cityname = arrive_city;
			VerticesNum++;
			NodeTable.push_back(q);
			EdgeNode *p;
			p = new EdgeNode;
			p->cityname = arrive_city;
			p->plane_cost = cost;
			p->plane_start_time = start_time;
			p->plane_arrive_time = arrive_time;
			p->link = NodeTable[i].link;
			NodeTable[i].link = p;
			return 'f';
		}
	}
	EdgeNode *p;
	p = new EdgeNode;
	p->cityname = arrive_city;
	p->plane_cost = cost;
	p->plane_start_time = start_time;
	p->plane_arrive_time = arrive_time;
	p->link = NodeTable[i].link;
	NodeTable[i].link = p;
	return 'd';
}
int Graph::GetVertexPos(string name) {
	int i;
	for (i = 0; i < VerticesNum; i++) {
		if (NodeTable[i].cityname == name) return i;
	}
	return -1;
}
void Graph::car_printpath(int v, int u) {
	EdgeNode *p;
	p = NodeTable[v].link;
	while (1) {
		if (GetVertexPos(p->cityname) == u) break;
		p = p->link;
	}
	int hour = 0, minute = 0;
	get_time(p->car_start_time, hour, minute);
	cout << NodeTable[v].cityname << "(" << setw(2) << setfill('0') << hour << "："
		<< setw(2) << setfill('0') << minute << ")" << "->";
	get_time(p->car_arrive_time, hour, minute);
	cout << p->cityname << "(" << setw(2) << setfill('0') << hour << "："
		<< setw(2) << setfill('0') << minute << ")" << "	";
}
void Graph::plane_printpath(int v, int u) {
	EdgeNode *p;
	p = NodeTable[v].link;
	while (1) {
		if (GetVertexPos(p->cityname) == u) break;
		p = p->link;
	}
	int hour = 0, minute = 0;
	get_time(p->plane_start_time, hour, minute);
	cout << NodeTable[v].cityname << "(" << setw(2) << setfill('0') << hour << "："
		<< setw(2) << setfill('0') << minute << ")" << "->";
	get_time(p->plane_arrive_time, hour, minute);
	cout << p->cityname << "(" << setw(2) << setfill('0') << hour << "："
		<< setw(2) << setfill('0') << minute << ")" << "	";
}
void Graph::lowest_car_cost(int v, int u) {
	int *visited;
	visited = new int[Max];
	vector<int> path, s;
	for (int i = 0; i < Max; i++) visited[i] = 0;
	s.push_back(v);
	visited[v] = 1;
	int w = -1;
	double lowest_cost = 9999999;
	while (s.size()) {
		v = s.back();
		w = GetNextNeighbor(v, w);
		if (w == -1) {
			w = v;
			s.pop_back();
			visited[v] = 0;
		}
		else if (w == u) {
			s.push_back(w);
			access_car_cost(s, lowest_cost, path);
			s.pop_back();
		}
		else if(!visited[w]){
			s.push_back(w);
			visited[w] = 1;
			w = -1;
		}
	}
	cout << "最省钱的路线是：";
	car_printpath(path);
	cout << "共花费了：" << lowest_cost;
	cout << endl;
};
void Graph::lowest_car_time(int v, int u) {
	int *visited;
	visited = new int[Max];
	vector<int> path, s;
	for (int i = 0; i < Max; i++) visited[i] = 0;
	s.push_back(v);
	visited[v] = 1;
	int w = -1;
	double lowest_time = 9999999;
	while (s.size()) {
		v = s.back();
		w = GetNextNeighbor(v, w);
		if (w == -1) {
			w = v;
			s.pop_back();
			visited[v] = 0;
		}
		else if (w == u) {
			s.push_back(w);
			access_car_time(s, lowest_time, path);
			s.pop_back();
		}
		else if (!visited[w]) {
			s.push_back(w);
			visited[w] = 1;
			w = -1;
		}
	}
	cout << "最省时间的路线是：";
	car_printpath(path);
	cout << endl;
}
void Graph::lowest_plane_cost(int v, int u) {
	int *visited;
	visited = new int[Max];
	vector<int> path, s;
	for (int i = 0; i < Max; i++) visited[i] = 0;
	s.push_back(v);
	visited[v] = 1;
	int w = -1;
	double lowest_cost = 9999999;
	while (s.size()) {
		v = s.back();
		w = GetNextNeighbor(v, w);
		if (w == -1) {
			w = v;
			s.pop_back();
			visited[v] = 0;
		}
		else if (w == u) {
			s.push_back(w);
			access_plane_cost(s, lowest_cost, path);
			s.pop_back();
		}
		else if (!visited[w]) {
			s.push_back(w);
			visited[w] = 1;
			w = -1;
		}
	}
	cout << "最省钱的路线是：";
	plane_printpath(path);
	cout << "共花费了：" << lowest_cost;
	cout << endl;
}
void Graph::lowest_plane_time(int v, int u) {
	int *visited;
	visited = new int[Max];
	vector<int> path, s;
	for (int i = 0; i < Max; i++) visited[i] = 0;
	s.push_back(v);
	visited[v] = 1;
	int w = -1;
	double lowest_time = 9999999;
	while (s.size()) {
		v = s.back();
		w = GetNextNeighbor(v, w);
		if (w == -1) {
			w = v;
			s.pop_back();
			visited[v] = 0;
		}
		else if (w == u) {
			s.push_back(w);
			access_plane_time(s, lowest_time, path);
			s.pop_back();
		}
		else if (!visited[w]) {
			s.push_back(w);
			visited[w] = 1;
			w = -1;
		}
	}
	cout << "最省时间的路线是：";
	plane_printpath(path);
	cout << endl;
}
void Graph::usage(istream &in,string command) {
	string city, city1;
	string start_city, arrive_city;
	string commute;
	char type;
	int i;
		/*cout << "使用说明：" << endl;
		cout << "1.输入（城市信息）对城市进行增加和删除操作" << endl;
		cout << "2.输入（列车）对列车信息进行增加和删除操作" << endl;
		cout << "3.输入（飞机）对飞机信息进行增加和删除操作" << endl;
		cout << "4.输入（评估）获得最佳出行路线" << endl;*/
		//cout << "请输入操作：" << endl;
		/*if (command == "城市信息") {
			cout << "请输入（增加/删除）操作：" << endl;
			in >> command;
			if (command == "增加") {
				cout << "请输入城市名称：" << endl;
				in >> city;
				add_Vertices(city);
				VertexNode p;
				p.cityname = city;
				VerticesNum++;
				NodeTable.push_back(p);
				cout << "加入成功！" << endl;
			}
			else if (command == "删除") {
				cout << "请输入城市名称：" << endl;
				in >> city;
				erase_Vertices(city);
				EdgeNode *p,*q;
				vector<VertexNode>::size_type i;
				for (i = 0; i < VerticesNum; i++) {
					if (NodeTable[i].cityname == city) break;
				}
				vector<VertexNode>::iterator it = NodeTable.begin() + i;
				NodeTable.erase(it);
				VerticesNum--;
				for (i = 0; i < VerticesNum; i++) {
					p = NodeTable[i].link;
					if (p->cityname == city) {
						NodeTable[i].link = NodeTable[i].link->link;
						break;
					}
					else {
						while (p) {
							q = p;
							p = p->link;
							if (p->cityname == city) {
								q->link = p->link;
								delete p;
								break;
							}
						}
					}
				}
				cout << "成功删除城市！" << endl;
			}
			else {
				cout << "指令错误！" << endl;
			}
		}*/
		 if (command == "列车") {
			cout << "请输入（增加/删除）操作：" << endl;
			in >> command;
			if (command == "增加") {
				cout << "请按照（出发城市 到达城市 出发时间 到达时间 车票价格）输入列车信息：" << endl;
				type = create_car_infomation(in);//这里缺少到时候没有的城市，必须报错
				switch (type)
				{
				case'b':cout << "请重新输入列车信息：" << endl; break;
				case'c':cout << "已加入该出发城市到城市系统中，并且列车班次加入成功！" << endl; break;
				case'd':cout << "成功加入该班次！" << endl; break;
				case'e':cout << "已加入该到达城市到城市系统中，并且列车班次加入成功！" << endl; break;
				case'f':cout << "已加入该出发城市和到达城市到城市系统中，并且列车班次加入成功！" << endl; break;
				default:
					break;
				}
			}
			else if (command == "删除") {
				cout << "请按照（出发城市 到达城市）输入列车信息：" << endl;
				in >> city >> city1;
				for (i = 0; i < VerticesNum; i++) {
					if (NodeTable[i].cityname == city) {
						EdgeNode *p;
						p = NodeTable[i].link;
						if (p->cityname == city1) {
							NodeTable[i].link = NodeTable[i].link->link;
							delete p;
						}
						else {
							EdgeNode *q;
							while (p) {
								q = p;
								p = p->link;
								if (p->cityname == city) {
									q->link = p->link;
									delete p;
									break;
								}
							}
						}
						cout << "成功删除该班车！" << endl;
						break;
					}
				}
			}
			else {
				cout << "指令错误！" << endl;
			}
		}
		else if (command == "飞机") {
			cout << "请输入（增加/删除）操作：" << endl;
			in >> command;
			if (command == "增加") {
				cout << "请按照（出发城市 到达城市 出发时间 到达时间 机票价格）输入飞机信息：" << endl;
				type = create_plane_infomation(in);
				switch (type)
				{
				case'b':cout << "请重新输入飞机信息：" << endl; break;
				case'c':cout << "已加入该出发城市到城市系统中，并且飞机航班加入成功！" << endl; break;
				case'd':cout << "成功加入该航班！" << endl; break;
				case'e':cout << "已加入该到达城市到城市系统中，并且飞机航班加入成功！" << endl; break;
				case'f':cout << "已加入该出发城市和到达城市到城市系统中，并且飞机航班加入成功！" << endl; break;
				default:
					break;
				}
			}
			else if (command == "删除") {
				cout << "请按照（出发城市 到达城市）输入飞机信息：" << endl;
				in >> city >> city1;
				for (i = 0; i < VerticesNum; i++) {
					if (NodeTable[i].cityname == city) {
						EdgeNode *p;
						p = NodeTable[i].link;
						if (p->cityname == city1) {
							NodeTable[i].link = NodeTable[i].link->link;
							delete p;
						}
						else {
							EdgeNode *q;
							while (p) {
								q = p;
								p = p->link;
								if (p->cityname == city) {
									q->link = p->link;
									delete p;
									break;
								}
							}
						}
						cout << "成功删除该航班！" << endl;
						break;
					}
				}
			}
			else {
				cout << "指令错误！" << endl;
			}
		}
		/*else if (command == "评估") {
			cout << "请按照（起始城市 终点城市 最优决策原则 交通工具）输入要求：" << endl;
			in >> start_city >> arrive_city >> command >> commute;
			if (commute == "列车") {
				if (command == "省钱") {
					lowest_car_cost(GetVertexPos(start_city), GetVertexPos(arrive_city));
				}
				else {
					lowest_car_time(GetVertexPos(start_city), GetVertexPos(arrive_city));
				}
			}
			else {
				if (command == "省钱") {
					lowest_plane_cost(GetVertexPos(start_city), GetVertexPos(arrive_city));
				}
				else {
					lowest_plane_time(GetVertexPos(start_city), GetVertexPos(arrive_city));
				}
			}

		}*/
		else cout << "指令错误，请重新输入：" << endl;

}
void Graph::get_time(const double i, int &hour, int &minute) {
	hour = (int)i;
	minute = (i - hour) * 100;
}
int Graph::GetFirstNeighbor(int v) {
	return GetVertexPos(NodeTable[v].link->cityname);
}
int Graph::GetNextNeighbor(int v, int u) {
	EdgeNode *p;
	p = NodeTable[v].link;
	if (u == -1) return GetVertexPos(p->cityname);
	while (p) {
		if (GetVertexPos(p->cityname) == u) {
			p = p->link;
			break;
		}
		p = p->link;
	}
	if (p == NULL) return -1;
	else return GetVertexPos(p->cityname);
}
void Graph::access_car_cost(const vector<int> s, double &lowest_cost, vector<int> &path) {
	double cost = 0, time = 0;
	int i = 1, j = 2;
	EdgeNode *p;
	p = NodeTable[s[0]].link;
	time = p->car_arrive_time;
	if (time == -1)return;
	while (j < s.size()) {
		p = NodeTable[s[i]].link;
		while (p) {
			if (GetVertexPos(p->cityname) == s[j]) break;
			p = p->link;
		}
		if (time > p->car_start_time|| p->car_start_time==-1) return;
		i++; j++;
	}
	for (i=0,j = 1; j < s.size(); i++,j++) {
		p = NodeTable[s[i]].link;
		while (p) {
			if (GetVertexPos(p->cityname) == s[j]) break;
			p = p->link;
		}
		cost += p->car_cost;
	}
	if (cost < lowest_cost) {
		lowest_cost = cost;
		path.clear();
		for (i = 0; i < s.size(); i++)
			path.push_back(s[i]);
	}
}
void Graph::access_car_time(const vector<int> s, double &lowest_time, vector<int> &path) {
	double time = 0;
	int i = 1, j = 2;
	EdgeNode *p;
	p = NodeTable[s[0]].link;
	time = p->car_start_time;
	if (time == -1)return;
	time = (int)time + (time - (int)time) / 60;
	while (j < s.size()) {
		p = NodeTable[s[i]].link;
		while (p) {
			if (GetVertexPos(p->cityname) == s[j]) break;
			p = p->link;
		}
		if (time>p->car_start_time|| p->car_start_time==-1) return;
		i++; j++;
	}
	time = (int)p->car_arrive_time + (p->car_arrive_time - (int)p->car_arrive_time) / 60 - time;
	if (time < lowest_time) {
		lowest_time =time;
		path.clear();
		for (i = 0; i < s.size(); i++)
			path.push_back(s[i]);
	}
}
void Graph::access_plane_cost(const vector<int> s, double &lowest_cost, vector<int> &path) {
	double cost = 0, time = 0;
	int i = 1, j = 2;
	EdgeNode *p;
	p = NodeTable[s[0]].link;
	time = p->plane_arrive_time;
	if (time == -1)return;
	while (j < s.size()) {
		p = NodeTable[s[i]].link;
		while (p) {
			if (GetVertexPos(p->cityname) == s[j]) break;
			p = p->link;
		}
		if (time > p->plane_start_time|| p->plane_start_time==-1) return;
		i++; j++;
	}
	for (i = 0, j = 1; j < s.size(); i++, j++) {
		p = NodeTable[s[i]].link;
		while (p) {
			if (GetVertexPos(p->cityname) == s[j]) break;
			p = p->link;
		}
		cost += p->plane_cost;
	}
	if (cost < lowest_cost) {
		lowest_cost = cost;
		path.clear();
		for (i = 0; i < s.size(); i++)
			path.push_back(s[i]);
	}
}
void Graph::access_plane_time(const vector<int> s, double &lowest_time, vector<int> &path) {
	double time = 0;
	int i = 1, j = 2;
	EdgeNode *p;
	p = NodeTable[s[0]].link;
	time = p->plane_start_time;
	if (time == -1)return;
	time = (int)time + (time - (int)time) / 60;
	while (j < s.size()) {
		p = NodeTable[s[i]].link;
		while (p) {
			if (GetVertexPos(p->cityname) == s[j]) break;
			p = p->link;
		}
		if (time>p->plane_start_time|| p->plane_start_time == -1) return;
		i++; j++;
	}
	time = (int)p->plane_arrive_time + (p->plane_arrive_time - (int)p->plane_arrive_time) / 60 - time;
	if (time < lowest_time) {
		lowest_time = time;
		path.clear();
		for (i = 0; i < s.size(); i++)
			path.push_back(s[i]);
	}
}
void Graph::car_printpath(const vector<int> s) {
	int i = 0, j = 1;
	while (j < s.size()) {
		car_printpath(s[i], s[j]);
		i++;
		j++;
	}
	cout << endl;
}
void Graph::plane_printpath(const vector<int> s) {
	int i = 0, j = 1;
	while (j < s.size()) {
		plane_printpath(s[i], s[j]);
		i++;
		j++;
	}
	cout << endl;
}
void Graph::add_Vertices(string city) {
	VertexNode p;
	p.cityname = city;
	VerticesNum++;
	NodeTable.push_back(p);
	cout << "加入成功！" << endl;
}
void Graph::erase_Vertices(string city) {
	EdgeNode *p, *q;
	vector<VertexNode>::size_type i;
	for (i = 0; i < VerticesNum; i++) {
		if (NodeTable[i].cityname == city) break;
	}
	vector<VertexNode>::iterator it = NodeTable.begin() + i;
	NodeTable.erase(it);
	VerticesNum--;
	for (i = 0; i < VerticesNum; i++) {
		p = NodeTable[i].link;
		if (p->cityname == city) {
			if (NodeTable[i].link->link == NULL) NodeTable[i].link = NULL;
			else NodeTable[i].link = NodeTable[i].link->link;
			break;
		}
		else {
			while (p) {
				q = p;
				p = p->link;
				if (p->cityname == city) {
					q->link = p->link;
					delete p;
					break;
				}
			}
		}
	}
	cout << "成功删除城市！" << endl;

}
void Graph::access(string commute,istream &in) {
	cout << "请按照（起始城市 终点城市 最优决策原则）输入要求：" << endl;
	string start_city, arrive_city, command;
	in >> start_city >> arrive_city >> command;
	if (commute == "列车") {
		if (command == "省钱") {
			lowest_car_cost(GetVertexPos(start_city),GetVertexPos(arrive_city));
		}
		else {
			lowest_car_time(GetVertexPos(start_city), GetVertexPos(arrive_city));
		}
	}
	else {
		if (command == "省钱") {
			lowest_plane_cost(GetVertexPos(start_city), GetVertexPos(arrive_city));
		}
		else {
			lowest_plane_time(GetVertexPos(start_city), GetVertexPos(arrive_city));
		}
	}
}