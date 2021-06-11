#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <conio.h>

using namespace std;

#include "hospital.h"

/*===Console Ŭ���� ������===*/
int Console::select_menu() {//�޴� ����
	int inputMenu = 0;
	try {
		Console::gotoxy(28, 6);  cout << "=======���Ͻô� ���񽺸� �����ϼ���!=======" << endl;
		Console::gotoxy(40, 8);  cout << "(1)���� ����" << endl;
		Console::gotoxy(40, 10);  cout << "(2)���� ���" << endl;
		Console::gotoxy(40, 12);  cout << "(3)���� ��ȸ" << endl;
		Console::gotoxy(40, 14);  cout << "(4)���� �����ϱ�" << endl;
		inputMenu = _getch();//getch()-->��������X Ű�� ������ ���ÿ� �� �Է�(��ȯ��:ASCII�ڵ尪)
		system("cls");//�Է� �� �Է¹��� ȭ�� ���� -->API����
		//cin.ignore(INT_MAX, '\n');//���ۺ���

		if (inputMenu > 53 ) {
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
		cout << "���Ͻô� ����μ��� �������ּ���~!\n";
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

void Console::gotoxy(int x, int y) {//������ API���-->�ܼ�ȭ�� ��ǥ ����
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
/*=====Department Ŭ���� ������=====*/
Department::Department() {
	fstream read_file("depart.txt");//�ؽ�Ʈ���� �ҷ�����
	string readLine;//�ؽ�Ʈ���Ͽ��� ���� ������ �ؽ�Ʈ ����

	if (!read_file) {//���� �б� ����ó��
		cout << "�ý��� �� ������ �ֽ��ϴ�.\n";
		exit(100);
	}
	while (1) {//���� �� ������ ���� ����
		if (read_file.eof())break;
		getline(read_file, readLine);
		vec_deptName.push_back(readLine);
	}
}
void Department::setDept(int selectDept) {
	ifstream read_file;
	string readLine;//�ؽ�Ʈ���Ͽ��� ���� ������ �ؽ�Ʈ ����
	string subStr;//�κ� ���ڿ� ����
	int chkIdx = 0;

	if (!read_file) {//���� �б� ����ó��
		cout << "�ý��� �� ������ �ֽ��ϴ�.\n";
		exit(100);
	}
	read_file.open("depart.txt");//�ؽ�Ʈ���� �ҷ�����
	while (1) {//���� �� ������ ���� ����
		if (read_file.eof())break;
		getline(read_file, readLine);
		chkIdx = readLine[0] - '0';// �� ���� ù ��° �ε��� ��ȣ�� ���������� ��ȯ

		if (chkIdx == selectDept) {
			subStr = extract_line(readLine);
			deptName = subStr;
			break;
		}
	}
}
string Department::extract_line(string str) {
	string result;
	for (int i = 0; i < str.size(); i++) {//���� ���ڿ��� ���̸�ŭ ���� ����
		if (str[i] == ' ') {//���� ���� ������ �� ���� ���ڿ� ���� ��ũ����¡ ���� �� �ش� ������ ��ȯ
			result = str.substr(i + 1);
		}
	}
	return result;
}

void Department::display_dept_list() {
	for (int i = 0; i < vec_deptName.size(); i++){
		//Console::gotoxy(10, 10);
		cout << vec_deptName[i]<<endl;
	}
}
/*=====Hospital Ŭ���� ������=====*/
void Hospital::execute_prog() {
	selectMenu = Console::select_menu();//�޴� �Է�(1. ����, 2.��ȸ, 3.���, 4.����)
	switch (selectMenu){
	case 49: //���� ����
		dc->display_dept_list();//���� ������ ���� �μ� ���
		selectDept = Console::select_dept();//�μ� �Է�(1~9)
		activation_reserv(selectDept);//���� Ȱ��ȭ
		break;
	}
}
void Hospital::activation_reserv(int param) {
	dc->setDept(param);//�Էµ� �μ��� �ش�Ǵ� ��ü �ʱ�ȭ
	dc->show_select_dept();

}
