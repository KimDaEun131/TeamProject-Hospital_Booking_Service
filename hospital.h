#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

#ifndef __HOSPITAL__H
#define __HOPITAL__H

class Doctor{
public:
	Doctor() {}
	void setDc(string dcName) { this->dcName = dcName; }
	string getDc() { return dcName; }
private:
	string dcName;
};

class Department {
public:
	Department() {}
	vector<string> tokenizing_dcList(string const& str);
	string select();
	string tokenizing_empty(string const& str);
	void setDept(string deptName) { this->deptName = deptName; }
	void inItDc(int num);
	void selectDc();
	void display_dcList();
	string getDept() { return deptName; }
private:
	Doctor* dc;
	vector<string>vec_dc;
	string deptName;
};

class Hospital{
public:
	Hospital();
	string tokenizing_dept(string const& str);
	void activation_booking(int num);
	void display_deptList();
private:
	Department* dept;
	vector<string>vec_dept;
};

class Console {
public:
	Console() { hp = new Hospital(); }
	void execute_prog();//�ý��� ����
	static int select_menu();//�޴� ����
	static int select_dept();//����μ� ����
	static int select_method();//���� ��� ����
	static void gotoxy(int x, int y);//�ܼ�ȭ�� ��ǥ ����
private:
	Hospital* hp;
};
#endif // !__HOSPITAL__H