#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

#include "hospital.h"

/*===Console Ŭ���� ������===*/
int Console::select_menu() {//�޴� ����
	int inputMenu = 0;
	try {
		cout << "****���Ͻô� ���񽺸� �����ϼ���****" << endl;
		cout << "(1)���� ����\t\t(2)���� ���\t\t(3)���� ��ȸ\t\t(4)���� ����\t\t(5)����\n";
		cin >> inputMenu;
		cin.ignore(INT_MAX, '\n');//���ۺ���

		if (inputMenu > 4) {
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
		cout << "(1)����\t\t(2)�ܰ�\t\t(3)�Ǻΰ�\n";
		cin >> inputDept;
		cin.ignore(INT_MAX, '\n');//���ۺ���

		if (inputDept > 4) {
			throw inputDept;
		}
	}
	catch (int x) {
		cout << "WARNING! �߸��� �Է��Դϴ�!! �ٽ� �Է����ּ���~!\n";
		cin >> inputDept;
	}
	return inputDept;
}

/*=====Department Ŭ���� ������=====*/
Department::Department(int selectDept) {
	ifstream read_file;
	string readLine;//�ؽ�Ʈ���Ͽ��� ���� ������ �ؽ�Ʈ ����
	string subStr;//�κ� ���ڿ� ����
	int chkIdx = 0;

	read_file.exceptions(ifstream::failbit | ifstream::badbit);//����ó��
	read_file.open("depart.txt");//�ؽ�Ʈ���� �ҷ�����

	while (!read_file.eof()) {//���� �� ������ ���� ����
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
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			result = str.substr(i + 1);
		}
	}
	return result;
}

/*=====Hospital Ŭ���� ������=====*/
void Hospital::execute_prog() {
	selectMenu = Console::select_menu();//�޴� �Է�(1. ����, 2.��ȸ, 3.���, 4.����)
	switch (selectMenu){
	case 1: 
		selectDept = Console::select_dept();//�μ� �Է�(1~9)
		activation_reserv(selectDept);//���� Ȱ��ȭ
		break;
	}
}
void Hospital::activation_reserv(int param) {
	dc = new Doctor(param);
	dc->show_select_dept();
}
