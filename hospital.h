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
};

class Department {
public:
	/*Constructor*/
	Department(int selectDept);//������ �μ��� ���� �Է°��� ������� ��ü �ʱ�ȭ
	/*Function*/
	string extract_line(string str);//���Ͽ��� ���� �ؽ�Ʈ�� �Ϻθ� ������ ��ȯ
	void show_select_dept() { cout << deptName << "�ش�μ��� �����ϼ̽��ϴ�.\n"; }//������ �μ��� ���� �ʱ�ȭ ��� ���(TEST)
private:
	string deptName;//����μ� �̸� ���� ����
};

class Doctor :public Department {
public:
	/*Constructor*/
	Doctor(int param) :Department(param) {};//��� �̴ϼȶ������� Ȱ���� baseŬ���� ������ ȣ��
};
/*===Hospital Ŭ����===
 >> ���α׷� ���� �� Ȱ��ȭ �޼��� ����
 >> ����μ��� ���� ��ü ���� �Ҵ�*/
class Hospital {
public:
	/*Function*/
	void execute_prog();//��ü ���α׷� ���� �� ����
	void activation_reserv(int param);//���� Ȱ��ȭ(���� ��� �غ�ܰ�)
private:
	Doctor* dc;
	int selectMenu;
	int selectDept;
};
#endif // !__HOSPITAL__H
