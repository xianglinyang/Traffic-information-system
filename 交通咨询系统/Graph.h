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
	string cityname;  //������е�����
	double car_start_time;//�г�����ʱ�䣨������ʱ�̣�Сʱ�ͷ��ӷֱ�洢��
	double car_arrive_time;//�г�����ʱ��
	double plane_start_time;//�ɻ�����ʱ��
	double plane_arrive_time;//�ɻ�����ʱ��
	double car_cost;//�г�����
	double plane_cost;//�ɻ�����
	EdgeNode *link;//�߽����ָ��
public:
	EdgeNode() {//�߽���ʼ����-1����û���г���ɻ�����ó���
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
	string cityname;//��������
	EdgeNode *link;//���߱�ָ��
};
class Graph {
private:
	vector<VertexNode> NodeTable;
	int VerticesNum;//��������
public:
	Graph() { VerticesNum = 0; }
	bool create_city(istream &in);//���뿼�ǵ��������ĸ�ʽ���Ի����Ƕ��˳���
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
bool Graph::create_city(istream &in) {//�ж����뼸�����У��Ƿ����ظ�
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
	if (start_city == "�������") return 'a';//�ж��������
	in >> arrive_city;
	create_time(in,start_time,arrive_time);
	in >> cost;
	for (i = 0; i < NodeTable.size(); i++) if (NodeTable[i].cityname == start_city) break;
	for (j = 0; j < NodeTable.size(); j++) if (NodeTable[j].cityname == arrive_city) break;
	if (i == NodeTable.size()&&j!=NodeTable.size()) {
		cout << "�ó�������δ������ϵͳ�У���ȷ���Ƿ����ó��У���/�񣩣�" << endl;
		in >> is_no;
		if (is_no == "��") return 'b';
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
		cout << "�õ������δ������ϵͳ�У���ȷ���Ƿ����ó��У���/�񣩣�" << endl;
		in >> is_no;
		if (is_no == "��") return 'b';
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
		cout << "�ó������к͵�����о�δ������ϵͳ�У���ȷ���Ƿ����ó��У���/�񣩣�" << endl;
		in >> is_no;
		if (is_no == "��") return 'b';
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
	if (start_city == "�������") return 'a';//�ж��������
	in >> arrive_city;
	create_time(in, start_time, arrive_time);
	in >> cost;
	for (i = 0; i < NodeTable.size(); i++) if (NodeTable[i].cityname == start_city) break;
	for (j = 0; j < NodeTable.size(); j++) if (NodeTable[j].cityname == arrive_city) break;
	if (i == NodeTable.size() && j != NodeTable.size()) {
		cout << "�ó�������δ������ϵͳ�У���ȷ���Ƿ����ó��У���/�񣩣�" << endl;
		in >> is_no;
		if (is_no == "��") return 'b';
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
		cout << "�õ������δ������ϵͳ�У���ȷ���Ƿ����ó��У���/�񣩣�" << endl;
		in >> is_no;
		if (is_no == "��") return 'b';
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
		cout << "�ó������к͵�����о�δ������ϵͳ�У���ȷ���Ƿ����ó��У���/�񣩣�" << endl;
		in >> is_no;
		if (is_no == "��") return 'b';
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
	cout << NodeTable[v].cityname << "(" << setw(2) << setfill('0') << hour << "��"
		<< setw(2) << setfill('0') << minute << ")" << "->";
	get_time(p->car_arrive_time, hour, minute);
	cout << p->cityname << "(" << setw(2) << setfill('0') << hour << "��"
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
	cout << NodeTable[v].cityname << "(" << setw(2) << setfill('0') << hour << "��"
		<< setw(2) << setfill('0') << minute << ")" << "->";
	get_time(p->plane_arrive_time, hour, minute);
	cout << p->cityname << "(" << setw(2) << setfill('0') << hour << "��"
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
	cout << "��ʡǮ��·���ǣ�";
	car_printpath(path);
	cout << "�������ˣ�" << lowest_cost;
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
	cout << "��ʡʱ���·���ǣ�";
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
	cout << "��ʡǮ��·���ǣ�";
	plane_printpath(path);
	cout << "�������ˣ�" << lowest_cost;
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
	cout << "��ʡʱ���·���ǣ�";
	plane_printpath(path);
	cout << endl;
}
void Graph::usage(istream &in,string command) {
	string city, city1;
	string start_city, arrive_city;
	string commute;
	char type;
	int i;
		/*cout << "ʹ��˵����" << endl;
		cout << "1.���루������Ϣ���Գ��н������Ӻ�ɾ������" << endl;
		cout << "2.���루�г������г���Ϣ�������Ӻ�ɾ������" << endl;
		cout << "3.���루�ɻ����Էɻ���Ϣ�������Ӻ�ɾ������" << endl;
		cout << "4.���루�����������ѳ���·��" << endl;*/
		//cout << "�����������" << endl;
		/*if (command == "������Ϣ") {
			cout << "�����루����/ɾ����������" << endl;
			in >> command;
			if (command == "����") {
				cout << "������������ƣ�" << endl;
				in >> city;
				add_Vertices(city);
				VertexNode p;
				p.cityname = city;
				VerticesNum++;
				NodeTable.push_back(p);
				cout << "����ɹ���" << endl;
			}
			else if (command == "ɾ��") {
				cout << "������������ƣ�" << endl;
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
				cout << "�ɹ�ɾ�����У�" << endl;
			}
			else {
				cout << "ָ�����" << endl;
			}
		}*/
		 if (command == "�г�") {
			cout << "�����루����/ɾ����������" << endl;
			in >> command;
			if (command == "����") {
				cout << "�밴�գ��������� ������� ����ʱ�� ����ʱ�� ��Ʊ�۸������г���Ϣ��" << endl;
				type = create_car_infomation(in);//����ȱ�ٵ�ʱ��û�еĳ��У����뱨��
				switch (type)
				{
				case'b':cout << "�����������г���Ϣ��" << endl; break;
				case'c':cout << "�Ѽ���ó������е�����ϵͳ�У������г���μ���ɹ���" << endl; break;
				case'd':cout << "�ɹ�����ð�Σ�" << endl; break;
				case'e':cout << "�Ѽ���õ�����е�����ϵͳ�У������г���μ���ɹ���" << endl; break;
				case'f':cout << "�Ѽ���ó������к͵�����е�����ϵͳ�У������г���μ���ɹ���" << endl; break;
				default:
					break;
				}
			}
			else if (command == "ɾ��") {
				cout << "�밴�գ��������� ������У������г���Ϣ��" << endl;
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
						cout << "�ɹ�ɾ���ð೵��" << endl;
						break;
					}
				}
			}
			else {
				cout << "ָ�����" << endl;
			}
		}
		else if (command == "�ɻ�") {
			cout << "�����루����/ɾ����������" << endl;
			in >> command;
			if (command == "����") {
				cout << "�밴�գ��������� ������� ����ʱ�� ����ʱ�� ��Ʊ�۸�����ɻ���Ϣ��" << endl;
				type = create_plane_infomation(in);
				switch (type)
				{
				case'b':cout << "����������ɻ���Ϣ��" << endl; break;
				case'c':cout << "�Ѽ���ó������е�����ϵͳ�У����ҷɻ��������ɹ���" << endl; break;
				case'd':cout << "�ɹ�����ú��࣡" << endl; break;
				case'e':cout << "�Ѽ���õ�����е�����ϵͳ�У����ҷɻ��������ɹ���" << endl; break;
				case'f':cout << "�Ѽ���ó������к͵�����е�����ϵͳ�У����ҷɻ��������ɹ���" << endl; break;
				default:
					break;
				}
			}
			else if (command == "ɾ��") {
				cout << "�밴�գ��������� ������У�����ɻ���Ϣ��" << endl;
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
						cout << "�ɹ�ɾ���ú��࣡" << endl;
						break;
					}
				}
			}
			else {
				cout << "ָ�����" << endl;
			}
		}
		/*else if (command == "����") {
			cout << "�밴�գ���ʼ���� �յ���� ���ž���ԭ�� ��ͨ���ߣ�����Ҫ��" << endl;
			in >> start_city >> arrive_city >> command >> commute;
			if (commute == "�г�") {
				if (command == "ʡǮ") {
					lowest_car_cost(GetVertexPos(start_city), GetVertexPos(arrive_city));
				}
				else {
					lowest_car_time(GetVertexPos(start_city), GetVertexPos(arrive_city));
				}
			}
			else {
				if (command == "ʡǮ") {
					lowest_plane_cost(GetVertexPos(start_city), GetVertexPos(arrive_city));
				}
				else {
					lowest_plane_time(GetVertexPos(start_city), GetVertexPos(arrive_city));
				}
			}

		}*/
		else cout << "ָ��������������룺" << endl;

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
	cout << "����ɹ���" << endl;
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
	cout << "�ɹ�ɾ�����У�" << endl;

}
void Graph::access(string commute,istream &in) {
	cout << "�밴�գ���ʼ���� �յ���� ���ž���ԭ������Ҫ��" << endl;
	string start_city, arrive_city, command;
	in >> start_city >> arrive_city >> command;
	if (commute == "�г�") {
		if (command == "ʡǮ") {
			lowest_car_cost(GetVertexPos(start_city),GetVertexPos(arrive_city));
		}
		else {
			lowest_car_time(GetVertexPos(start_city), GetVertexPos(arrive_city));
		}
	}
	else {
		if (command == "ʡǮ") {
			lowest_plane_cost(GetVertexPos(start_city), GetVertexPos(arrive_city));
		}
		else {
			lowest_plane_time(GetVertexPos(start_city), GetVertexPos(arrive_city));
		}
	}
}