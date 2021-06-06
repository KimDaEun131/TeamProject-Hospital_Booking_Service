#include <iostream>
#include <fstream>
#include <string>
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

/*===Hospital Ŭ���� ������===*/
Hospital::Hospital() {
	test = new Test[25];//25���� ����μ� ����
	ifstream read_file;
	string readLine;//�ؽ�Ʈ ���Ͽ��� �� �پ� ���� ������ ����
	string deptName;
	int idx = 0;

	read_file.exceptions(ifstream::failbit | ifstream::badbit);//����ó��
	read_file.open("hospital.txt");//�ؽ�Ʈ���� �ҷ�����

	while (!read_file.eof()) {//���� ���� ���������� �۾� ����
		if (read_file.eof())break;//������ ������ �ߺ�üũ
		getline(read_file, readLine);
		deptName = readLine;
		test[idx].setName(deptName);// 1) ��ü �迭 �ʱ�ȭ
		vec_storage_Dept.push_back(test[idx]);// 2) �ʱ�ȭ�� ��ü�� ���Ϳ� ������� ����
		idx++;
	}
}

void Hospital::execute_prog() {
	int idx = 0;
	selectMenu = Console::select_menu();
	if (selectMenu == 1) {//�޴� �Է�
		selectDept = Console::select_dept();//���� �μ� ����
		activation_prog(selectDept);
		cout << "hello";
	}
}

void Hospital::activation_prog(int selection) {
		for (int i = 0; i < 3; i++) {//��ü ���� �μ� ���
			vec_storage_Dept[i].display();
		}

}