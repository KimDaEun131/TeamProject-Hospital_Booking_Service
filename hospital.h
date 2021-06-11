#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

#ifndef __HOSPITAL__H
#define __HOPITAL__H
/*===Console Ŭ����====
  >> ����� �Է°��� �ް� ��ȯ�ϴ� �޼��� ���� --> static ����*/
class Console {
public:
	static int select_menu();//�޴� ����
	static int select_dept();//����μ� ����
	static int select_method();//���� ��� ����
	static void gotoxy(int x, int y);
};

class Department {
public:
	/*Constructor*/
	Department();//���Ͽ��� ���� �ؽ�Ʈ ���Ϳ� ����--> ��¿�
	/*Function*/
	void setDept(int selectDept);//�Է°��� ���� �ؽ�Ʈ���ϰ� ��ġ�ϴ� �μ��� Ž�� �� ��ü �ʱ�ȭ
	string extract_line(string str);//���Ͽ��� ���� �ؽ�Ʈ�� �Ϻθ� ������ ��ȯ
	void show_select_dept() { cout << deptName << "�ش�μ��� �����ϼ̽��ϴ�.\n"; }//������ �μ��� ���� �ʱ�ȭ ��� ���(TEST)
	void display_dept_list();//�μ��� ���
private:
	string deptName;//����μ� �̸� ���� ����
	vector <string>vec_deptName;//��¿�
};

class Doctor :public Department {
public:
	/*Constructor*/
	Doctor() {};
};
/*===Hospital Ŭ����===
 >> ���α׷� ���� �� Ȱ��ȭ �޼��� ����
 >> ����μ��� ���� ��ü ���� �Ҵ�*/
class Hospital {
public:
	/*Constructor*/
	Hospital() { dc = new Doctor(); }
	/*Function*/
	friend int Console::select_dept();//�μ�����-->����Ʈ ����
	void execute_prog();//��ü ���α׷� ���� �� ����
	void activation_reserv(int param);//���� Ȱ��ȭ(���� ��� �غ�ܰ�)
private:
	Doctor* dc;
	int selectMenu;//�޴�����
	int selectDept;//����μ� ����
};
#endif // !__HOSPITAL__H
