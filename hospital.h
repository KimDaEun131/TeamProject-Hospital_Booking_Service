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
	static void gotoxy(int x, int y);//�ܼ�ȭ�� ��ǥ ����
	static string select_doctorName();//�ǻ� �̸� �Է�
};

class Department {
public:
	/*Constructor*/
	Department();//���Ͽ��� ���� �ؽ�Ʈ ���Ϳ� ����--> ��¿�
	/*Function*/
	void setDept(int selectDept);//�Է°��� ���� �ؽ�Ʈ���ϰ� ��ġ�ϴ� �μ��� Ž�� �� ��ü �ʱ�ȭ
	string getDept() { return deptName; }//�μ��� ��ȯ
	string tokenizing_line(const string str);//���Ͽ��� ���� �ؽ�Ʈ�� �Ϻθ� ������ ��ȯ
	void show_select_dept() { cout << deptName << "�ش�μ��� �����ϼ̽��ϴ�.\n"; }//������ �μ��� ���� �ʱ�ȭ ��� ���(TEST)
	void display_dept_list();//�μ��� ���
private:
	string deptName;//����μ� �̸� ���� ����
	vector <string>vec_deptName;//��¿�
};

class Doctor :public Department {
public:
	/*Constructor*/
	Doctor(){}
	/*Function*/
	void setDoctor(const string dp);//�� �μ��� �ش�Ǵ� �ǻ� ���� �ʱ�ȭ
	string getDoctor() { return dcName; }//�ǻ� ���� ��ȯ
	virtual string tokenizing_line(const string str);//�����Լ��� �̿��� �޼��� �������̵� Ȱ��
	string extract_line(string const& str);
	vector<string>tokenizing_doctor(string const &str);
	void display_doctorList();//������ ����μ��� �ش�Ǵ� �Ƿ��� ��� ���
	void doctorName_reserv();//�ǻ缱�� ���� ����
private:
	vector <string>vec_dcName;
	string dcName;//�ǻ� ���� ����
};
/*===Hospital Ŭ����===
 >> ���α׷� ���� �� Ȱ��ȭ �޼��� ����
 >> ����μ��� ���� ��ü ���� �Ҵ�*/
class Hospital {
public:
	/*Constructor*/
	Hospital() { dc = new Doctor(); }//��ü �����Ҵ� �ʱ�ȭ
	/*Function*/
	void execute_prog();//��ü ���α׷� ���� �� ����
	void activation_reserv(int param);//���� Ȱ��ȭ(���� ��� �غ�ܰ�)
private:
	Doctor* dc;
	int selectMenu;//�޴�����
	int selectDept;//����μ� ����
	int selectMethod;//������ ����
};
#endif // !__HOSPITAL__H
