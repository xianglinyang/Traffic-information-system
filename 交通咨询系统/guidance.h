#pragma once
#include"Graph.h"
using namespace std;
//��ʼ�Ľ���
void guidance_greeting() {
	cout << "***���ã���ӭ�������������ƵĽ�ͨ��ѯϵͳ��***" << endl;
	cout << "**���ǳ�ŵһ��Ϊ������������Ҫ��ĳ���·�ߣ�**" << endl;
	cout << endl;
}
//��ʼ��������ϵͳ
void guidance_create_system(istream &in,Graph &city_system_car , Graph &city_system_plane) {//������������
//������Ϣ
	bool istrue;
	cout << "��������У�Ctrl+Z������룩��" << endl;
	istrue = city_system_car.create_city(in);
	while (!istrue) {
		cout << "δ�ɹ�����������Ϣ��" << endl;
		in.clear();
		istrue = city_system_car.create_city(in);
	}
	cout << "�ɹ������г�������Ϣ��" << endl;
	in.clear();
	cout << endl;
	cout << "��������У�Ctrl+Z������룩��" << endl;
	istrue = city_system_plane.create_city(in);
	while (!istrue) {
		cout << "δ�ɹ�����������Ϣ��" << endl;
		in.clear();
		istrue = city_system_plane.create_city(in);
	}
	cout << "�ɹ������ɻ�������Ϣ��" << endl;
	in.clear();
	cout << endl;
//�г�ʱ���
	cout << "�밴�գ��������� ������� ����ʱ�� ����ʱ�� ��Ʊ�۸������г���Ϣ:" << endl;
	cout << "/*���루������룩���������г���Ϣ*/" << endl;
	char type;
	while (1) {
		type= city_system_car.create_car_infomation(in);//����ȱ�ٵ�ʱ��û�еĳ��У����뱨��
		switch (type)
		{
		case'a':
			cout << endl; 
			cout << "��ɹ����г���Ϣ��" << endl; 
			cout << endl;
			break;
		case'b':cout << "�����������г���Ϣ��" << endl; break;
		case'c':cout << "�Ѽ���ó������е�����ϵͳ�У������г���μ���ɹ���" << endl; break;
		case'd':cout << "�ɹ�����ð�Σ�" << endl; break;
		case'e':cout << "�Ѽ���õ�����е�����ϵͳ�У������г���μ���ɹ���" << endl; break;
		case'f':cout << "�Ѽ���ó������к͵�����е�����ϵͳ�У������г���μ���ɹ���" << endl; break;
		default:
			break;
		}
		if (type == 'a') break;
	}
//�ɻ�����
	cout << "�밴�գ��������� ������� ����ʱ�� ����ʱ�� ��Ʊ�۸�����ɻ���Ϣ:" << endl;
	cout << "/*���루������룩���������ɻ���Ϣ*/" << endl;
	while (1) {
		type = city_system_plane.create_plane_infomation(in);//����ȱ�ٵ�ʱ��û�еĳ��У����뱨��
		switch (type)
		{
		case'a':
			cout << endl;
			cout << "��ɹ����ɻ���Ϣ��" << endl;
			cout << endl;
			break;
		case'b':cout << "����������ɻ���Ϣ��" << endl; break;
		case'c':cout << "�Ѽ���ó������е�����ϵͳ�У����ҷɻ���μ���ɹ���" << endl; break;
		case'd':cout << "�ɹ�����ð�Σ�" << endl; break;
		case'e':cout << "�Ѽ���õ�����е�����ϵͳ�У����ҷɻ��������ɹ���" << endl; break;
		case'f':cout << "�Ѽ���ó������к͵�����е�����ϵͳ�У����ҷɻ��������ɹ���" << endl; break;
		default:
			break;
		}
		if (type == 'a') break;
	}
	cout << "���Ѿ��ɹ��������н�ͨϵͳ��Ϣ��" << endl;
}
void guidance_using() {
	cout << "ʹ��˵����" << endl;
	cout << "1.���루������Ϣ���Գ��н������Ӻ�ɾ������" << endl;
	cout << "2.���루�г������г���Ϣ���в���" << endl;
	cout << "3.���루�ɻ����Էɻ���Ϣ���в���" << endl;
	cout << "4.���루�����������ѳ���·��" << endl;
}
void usage(Graph &city_system_car, Graph &city_system_plane,istream &in) {
	string command_choose, start_city, arrive_city, command, commute;
	in >> command_choose;
	while (1) {
		if (command_choose == "�г�") {
			city_system_car.usage(in,command_choose);
		}
		else if(command_choose=="�ɻ�") city_system_plane.usage(in,command_choose);
		else if (command_choose == "������Ϣ") {
			cout << "����������/ɾ����";
			in >> command_choose;
			cout << "������������ƣ�";
			if (command_choose == "����") {
				in >> command_choose;
				city_system_car.add_Vertices(command_choose);
				city_system_plane.add_Vertices(command_choose);
			}
			else {
				in >> command_choose;
				city_system_car.erase_Vertices(command_choose);
				city_system_plane.erase_Vertices(command_choose);
			}
		}
		else if (command_choose == "����") {
			cout << "��������з�ʽ��";
			in >> command_choose;
			if (command_choose == "�г�") {
				city_system_car.access(command_choose, cin);
			}
			else {
				city_system_plane.access(command_choose, cin);
			}
		}
		else cout << "ָ�����";
		cout << "�����������" << endl;
		in >> command_choose;
	}
}