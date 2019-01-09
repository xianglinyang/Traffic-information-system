#pragma once
#include"Graph.h"
using namespace std;
//开始的界面
void guidance_greeting() {
	cout << "***您好，欢迎来到这个精心设计的交通咨询系统！***" << endl;
	cout << "**我们承诺一定为您设计最符合您要求的出行路线！**" << endl;
	cout << endl;
}
//初始建立整个系统
void guidance_create_system(istream &in,Graph &city_system_car , Graph &city_system_plane) {//界面美观问题
//城市信息
	bool istrue;
	cout << "请输入城市（Ctrl+Z完成输入）：" << endl;
	istrue = city_system_car.create_city(in);
	while (!istrue) {
		cout << "未成功建立城市信息！" << endl;
		in.clear();
		istrue = city_system_car.create_city(in);
	}
	cout << "成功建立列车城市信息！" << endl;
	in.clear();
	cout << endl;
	cout << "请输入城市（Ctrl+Z完成输入）：" << endl;
	istrue = city_system_plane.create_city(in);
	while (!istrue) {
		cout << "未成功建立城市信息！" << endl;
		in.clear();
		istrue = city_system_plane.create_city(in);
	}
	cout << "成功建立飞机城市信息！" << endl;
	in.clear();
	cout << endl;
//列车时间表
	cout << "请按照（出发城市 到达城市 出发时间 到达时间 车票价格）输入列车信息:" << endl;
	cout << "/*输入（完成输入）结束构建列车信息*/" << endl;
	char type;
	while (1) {
		type= city_system_car.create_car_infomation(in);//这里缺少到时候没有的城市，必须报错
		switch (type)
		{
		case'a':
			cout << endl; 
			cout << "完成构建列车信息！" << endl; 
			cout << endl;
			break;
		case'b':cout << "请重新输入列车信息：" << endl; break;
		case'c':cout << "已加入该出发城市到城市系统中，并且列车班次加入成功！" << endl; break;
		case'd':cout << "成功加入该班次！" << endl; break;
		case'e':cout << "已加入该到达城市到城市系统中，并且列车班次加入成功！" << endl; break;
		case'f':cout << "已加入该出发城市和到达城市到城市系统中，并且列车班次加入成功！" << endl; break;
		default:
			break;
		}
		if (type == 'a') break;
	}
//飞机航班
	cout << "请按照（出发城市 到达城市 出发时间 到达时间 机票价格）输入飞机信息:" << endl;
	cout << "/*输入（完成输入）结束构建飞机信息*/" << endl;
	while (1) {
		type = city_system_plane.create_plane_infomation(in);//这里缺少到时候没有的城市，必须报错
		switch (type)
		{
		case'a':
			cout << endl;
			cout << "完成构建飞机信息！" << endl;
			cout << endl;
			break;
		case'b':cout << "请重新输入飞机信息：" << endl; break;
		case'c':cout << "已加入该出发城市到城市系统中，并且飞机班次加入成功！" << endl; break;
		case'd':cout << "成功加入该班次！" << endl; break;
		case'e':cout << "已加入该到达城市到城市系统中，并且飞机航班加入成功！" << endl; break;
		case'f':cout << "已加入该出发城市和到达城市到城市系统中，并且飞机航班加入成功！" << endl; break;
		default:
			break;
		}
		if (type == 'a') break;
	}
	cout << "您已经成功建立城市交通系统信息！" << endl;
}
void guidance_using() {
	cout << "使用说明：" << endl;
	cout << "1.输入（城市信息）对城市进行增加和删除操作" << endl;
	cout << "2.输入（列车）对列车信息进行操作" << endl;
	cout << "3.输入（飞机）对飞机信息进行操作" << endl;
	cout << "4.输入（评估）获得最佳出行路线" << endl;
}
void usage(Graph &city_system_car, Graph &city_system_plane,istream &in) {
	string command_choose, start_city, arrive_city, command, commute;
	in >> command_choose;
	while (1) {
		if (command_choose == "列车") {
			city_system_car.usage(in,command_choose);
		}
		else if(command_choose=="飞机") city_system_plane.usage(in,command_choose);
		else if (command_choose == "城市信息") {
			cout << "请输入增加/删除：";
			in >> command_choose;
			cout << "请输入城市名称：";
			if (command_choose == "增加") {
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
		else if (command_choose == "评估") {
			cout << "请输入出行方式：";
			in >> command_choose;
			if (command_choose == "列车") {
				city_system_car.access(command_choose, cin);
			}
			else {
				city_system_plane.access(command_choose, cin);
			}
		}
		else cout << "指令错误：";
		cout << "请输入操作：" << endl;
		in >> command_choose;
	}
}