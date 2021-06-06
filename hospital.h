#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#ifndef __HOSPITAL__H
#define __HOSPITAL__h

/*===Department Ŭ����===
>> ����, ���, ���� �ٽ� ��� ����
>> �� �μ��� �°� �ǻ翡 ���� ��ü ����*/
class Test {
public:
	Test() { dept = ""; }
	void setName(string name) { dept = name; }
	string getName() { return dept; }
	void display() { cout << dept << endl; }
private:
	string dept;
};
/*===Hospital Ŭ����===
 >> ���α׷� ���� �� Ȱ��ȭ �޼��� ����
 >> ����μ��� ���� ��ü �迭 �ʱ�ȭ �� ���� ����*/
class Hospital {
public:
	/*Constructor & Destructor*/
	Hospital();
	~Hospital() { delete[]test; }
	/*Function*/
	void execute_prog();//���α׷� ����
	void activation_prog(int selection);//��� Ȱ��ȭ
private:
	Test* test;
	vector <Test>vec_storage_Dept;//�ʱ�ȭ�� �μ���ü�� ���Ϳ� ����
	int selectMenu;//�޴� �Է� ��ȯ�� ����
	int selectDept;//�μ� ���� �Է� ��ȯ�� ����
};
/*===Console Ŭ����====
  >> ����� �Է°��� �ް� ��ȯ�ϴ� �޼��� ���� --> static ����*/
class Console {
public:
	static int select_menu();//�޴� ����
	static int select_dept();//����μ� ����
	static int select_method();//���� ��� ����
};

#endif // !__HOSPITAL__H

