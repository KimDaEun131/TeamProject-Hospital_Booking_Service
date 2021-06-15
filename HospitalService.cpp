#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#include "hospital.h"

/*======Department Ŭ���� ������======*/

void Department::inItDc(int num) {
	ifstream read_file;
	string readLine;
	string sub;
	int idx = 0;

	read_file.open("doctor.txt");
	if (!read_file) {
		cout << "�ý��� �� ������ �ֽ��ϴ�.\n";
		exit(100);
	}

	while (!read_file.eof()) {
		if (read_file.eof()) {
			break;
		}
		getline(read_file, readLine);
		idx = readLine[0] - '0';
		sub = tokenizing_empty(readLine);
		if (idx == num) {
			vec_dc = tokenizing_dcList(sub);
		}
	}
}

string Department::tokenizing_empty(string const& str) {
	string result;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			result = str.substr(i + 1);
		}
	}
	return result;
}

vector<string>Department:: tokenizing_dcList(string const& str) {
	vector<string>v;
	string doctor;
	int chkComma = 0;
	int idx = 0;
	for (int i = 0; i < str.size(); i++){
		if (str[i] == ',') {
			doctor = str.substr(idx, i - idx);//��ǥ �������� üũ
			idx = i + 1;//�ε��� ����
			v.push_back(doctor);//����� ���ڿ� ���Ϳ� ����
		}
	}
	doctor = str.substr(idx);//������ �ǻ� �̸� ����--> ������ ��ǥ ���� ���ڿ��� ���� �ۿ��� ���� �۾� ����
	v.push_back(doctor);
	return v;
}
string Department::select() {
	string input;
    cout << "�� Please select the Doctor you want~!\n";
	cout << ">>";
	cin >> input;
	
	return input;
}
void Department::display_dcList() {
	for (int i = 0; i < vec_dc.size(); i++){
		cout << vec_dc[i] << endl;
	}
}
void Department::selectDc() {//point!
	display_dcList();//���
	dc = new Doctor();
	string doc = select();
	for (int i = 0; i < vec_dc.size(); i++) {
		if (doc.compare(vec_dc[i])) {
			dc->setDc(doc);
		}
	}
	cout << "������ �ǻ�" << dc->getDc();
}
/*======Hospital Ŭ���� ������======*/

/*9���� ����μ��� ���� ��ü �迭 ���� ����.
	�μ����� ������ �� ���� �ش�Ǵ� ��ü �ʱ�ȭ.
	---> �μ��� txt����(depart.txt)���� ��� �μ��� �о�
	��ü ��ü�� ���� �ʱ�ȭ �۾�
	---> ���� �� ��ü ����μ��� ���� ����� ���� ���� �ڷᱸ�� Ȱ��*/
Hospital::Hospital() {
	ifstream read_file;
	string readLine;
	string subDept;
	int idx = 0;
	dept = new Department[9];

	read_file.open("depart.txt");
	if (!read_file) {
		cout << "�ý��� �� ������ �ֽ��ϴ�.\n";
		exit(100);
	}
	while (!read_file.eof()) {
		getline(read_file, readLine);
		if (read_file.eof()) {
			break;
		}
		subDept = tokenizing_dept(readLine);
		dept[idx].setDept(subDept);
		vec_dept.push_back(subDept);

		idx++;
	}
	read_file.close();
}
/*���� ���ڿ��� ���̸�ŭ ���� ����,
	���� ���� ������ �� ���� ���ڿ�(����μ� ��)�� ������ ��ȯ.
	---> string ��������� substr���̺귯�� Ȱ�� */
string Hospital::tokenizing_dept(string const& str) {
	string result;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			result = str.substr(i + 1);
		}
	}
	return result;
}
void Hospital::activation_booking(int num) {
	string s = dept[num - 1].getDept();
	dept[num - 1].inItDc(num);
	dept[num - 1].selectDc();
}
/*���� �� ��ü ����μ� ���*/
void Hospital::display_deptList() {
	for (int i = 0; i < vec_dept.size(); i++) {
		cout << vec_dept[i] << endl;
	}
}
/*======Console Ŭ���� ������======*/
int Console::select_menu() {//�޴� ����
	int inputMenu = 0;
	try {
		Console::gotoxy(32, 6);  cout << "=====Please select the service you want!=====" << endl;
		Console::gotoxy(46, 8);  cout << "(1)Booking" << endl;
		Console::gotoxy(46, 10);  cout << "(2)Cancel" << endl;
		Console::gotoxy(46, 12);  cout << "(3)Check" << endl;
		Console::gotoxy(46, 14);  cout << "(4)Exit System" << endl;
		inputMenu = _getch();//getch()-->��������X Ű�� ������ ���ÿ� �� �Է�(��ȯ��:ASCII�ڵ尪)
		system("cls");//�Է� �� �Է¹��� ȭ�� ���� -->API����

		if (inputMenu > 53) {
			throw inputMenu;
		}
	}
	catch (int x) {
		cout << "WARNING! �߸��� �Է��Դϴ�!! �ٽ� �Է����ּ���~!\n";
		cin >> inputMenu;
	}
	return inputMenu;
}

int Console::select_dept() {//�μ� ����
	int inputDept = 0;
	try {
		Console::gotoxy(34, 23); cout << "�� Please select the Medical Department you want~!\n";
		Console::gotoxy(34, 24); cout << ">>";
		cin >> inputDept;
		system("cls");//�Է� �� �Է¹��� ȭ�� ���� -->API����
		cin.ignore(INT_MAX, '\n');//���ۺ���

		if (inputDept > 9) {
			throw inputDept;
		}
	}
	catch (int x) {
		cout << "WARNING! �߸��� �Է��Դϴ�!! �ٽ� �Է����ּ���~!\n";
		cin >> inputDept;
	}
	return inputDept;
}

int Console::select_method() {//�μ� ����
	int inputDept = 0;
	try {
		Console::gotoxy(34, 10); cout << "�ݡ� Please select a booking method~! �ݡ�\n";
		Console::gotoxy(46, 13); cout << "(1)�ǻ� ����\n";
		Console::gotoxy(46, 15); cout << "(2)������ ����\n";
		Console::gotoxy(46, 18); cout << ">>";
		cin >> inputDept;
		system("cls");//�Է� �� �Է¹��� ȭ�� ���� -->API����
		cin.ignore(INT_MAX, '\n');//���ۺ���

		if (inputDept > 2) {
			throw inputDept;
		}
	}
	catch (int x) {
		cout << "WARNING! �߸��� �Է��Դϴ�!! �ٽ� �Է����ּ���~!\n";
		cin >> inputDept;
	}
	return inputDept;
}
void Console::gotoxy(int x, int y) {//������ API���-->�ܼ�ȭ�� ��ǥ ����
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void Console::execute_prog() {
	//while (1) {
		int selectMenu = Console::select_menu();//1) �޴� �Է�
		switch (selectMenu) {
		case 49: {// ���� ����
			hp->display_deptList();//���� �� ��ü ����μ� ���
			int selectDept = Console::select_dept();// 2) ����μ� ����
			int selectMethod = Console::select_method();//3)������ ����
			if (selectMethod == 1) {// 3-1) �ǻ� ���� ���
				hp->activation_booking(selectDept);
			}
			else if (selectMethod == 2) {// 3-2) ������ ���� ���
				cout << "���� �̿��Ͻ� �� ���� �����Դϴ�." << endl;
			}
			break;
		}
		}
	//}
}