#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#include "hospital.h"

/*======Doctor Ŭ���� ������======*/

/* doctor ������ : �ǻ� �̸��� ���� ������ 2���� �迭 ����
  �⺻ �� : �̸�="NULL", ������ : 0��-���� 0��-Ÿ�� */
Doctor::Doctor() {
	dcName = "NULL";
	schedule[0][0] = "~~~";
	schedule[0][1] = "��";
	schedule[0][2] = "ȭ";
	schedule[0][3] = "��";
	schedule[0][4] = "��";
	schedule[0][5] = "��";

	for (int i = 1; i < 6; i++) {
		schedule[i][0] = to_string(i) + "time";
		for (int i = 1; i < 6; i++) {
			for (int j = 1; j < 6; j++) {

				schedule[i][j] = "NULL";
			}
		}
	}
}
string Doctor::getSchedule(string s) {
	string str;
	int temp = 0;
	for (int i = 1; i < DAY; i++){
		for (int j = 1; j < DATE; j++){
			if (schedule[i][j] == s) {
				temp = j;
				if (i == 1)str = "mon";
				else if (i == 2)str = "tue";
				else if (i == 3)str = "wed";
				else if (i == 4)str = "thu";
				else if (i == 5)str = "fri";
			}
		}
	}
	str = str + '-' + to_string(temp);
	return str;
}

void Doctor::setSchedule(string s, int i, int j) {
	if (schedule[i][j] == "xxxxxxxxxxxxx") {
		cout << "�����Դϴ�~!\n";
		return;
	}
	schedule[i][j] = s;
	/*try {
		schedule[i][j] = s;
		if (schedule[i][j] == "xxxxxxxxxxxxx") {
			throw 
		}
	}
	catch () {

	}*/
}
void Doctor::display_Schedule() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			cout << schedule[i][j] << "\t";
		}
		cout << endl;
	}
}

void Doctor::cancel_sche(string s) {
	string str;
	int temp = 0;
	for (int i = 1; i < DAY; i++) {
		for (int j = 1; j < DATE; j++) {
			if (schedule[i][j] == s) {
				setSchedule("============", i, j);
			}
		}
	}
}
/*======Department Ŭ���� ������======*/

void Department::loadDcList(string filename) {
	string getFile = filename;
	string str;
	ifstream read_file;
	Doctor* doc;

	read_file.open(filename);
	if (!read_file) {
		cout << "�ý��� �� ������ �ֽ��ϴ�.\n";
		exit(100);
	}
	int count = 0;   //���� �ټ���
	int i = 0;      //���� ��ü ���� ����
	int s = 1; //DAY ��� 
	while (getline(read_file, str)) {
		//�ǻ� �̸� ���� : ���Ͱ�ü �����Ͽ� ���� ���� �� �ǻ� �̸� ����
		if (count % 7 == 1) {
			doctor = new Doctor;
			doctor->setDc(str);
			v.push_back(doctor);
			i++;
		}
		else {
			//���� ���������� : ���� ������ �޾ƿ���
			//v ���� = �ǻ簴ü ���� -> pop -> temp���� -> (storage) string tokenizing --> �� ���� �Ҵ�
			if (str != "-----") {
				int j = 0;
				doc = v.at(i - 1);
				vector<string> sc = tokenizing_sc(str);
				if (s != DAY) {
					for (int t = 1; t < DATE; t++) {
						if (j != sc.size()) {
							doc->setSchedule(sc.at(j), s, t);
							j++;
						}
					}
				}
				if (s == 5)s = 0;
				s++;
			}
		}
		count++;
	}
	read_file.close();
}
vector<string> Department::tokenizing_sc(const string str) {
	vector <string> result;
	string sc;
	int chkSpace = 0;
	int idx = 0;
	for (int i = 0; i < str.size(); i++) {//���� ���ڿ��� ���̸�ŭ ���� ����
		if (str[i] == ' ') {//���� ���� ������ �� ���� ���ڿ� ���� ��ũ����¡ ���� �� �ش� ������ ��ȯ
			sc = str.substr(idx, i - idx);
			idx = i + 1;
			result.push_back(sc);
		}
	}
	sc = str.substr(idx);
	result.push_back(sc);
	return result;
}

int Department::inputDc() {
	int input;
    cout << "�� Please select the Doctor you want~!\n";
	cout << ">>";
	cin >> input;
	
	return input;
}
int Department::inputDay() {
	string input;
	int result = 0;
	cout << "�� Please select schedule~!\n";
	cout << ">>";
	cin >> input;
	
	if (input.compare("mon")==0) { result = 1;}
	else if (input.compare("tue") == 0) { result = 2;}
	else if (input.compare("wed") == 0) { result = 3;}
	else if (input.compare("thu") == 0) { result = 4;}
	else if (input.compare("fri") == 0) { result = 5;}
	
	return result;
}
int Department::inputTime() {
	int inputDept = 0;
	try {
		cout << "�� Please select the Medical Department you want~!\n";
		cout << ">>";
		cin >> inputDept;
		cin.ignore(INT_MAX, '\n');//���ۺ���

		if (inputDept > 5) {
			throw inputDept;
		}
	}
	catch (int x) {
		cout << "WARNING! �߸��� �Է��Դϴ�!! �ٽ� �Է����ּ���~!\n";
		cin >> inputDept;
	}
	return inputDept;
}
string Department::inputInfo() {
	string inputName;
	string inputId;
	string result;

	cout << "�� Please input NAME~!\n";
	cout << ">>";
	cin >> inputName;

	cout << "�� Please input ID~!\n";
	cout << ">>";
	cin >> inputId;

	result = inputName + '-'+inputId;
	return result;
}
void Department::display_dcList() {
	for (int i = 0; i < v.size(); i++){
		cout << v[i]->getDc() << endl;
	}
}
void Department::set_reservation() {//point!
	display_dcList();//���
	int day;
	int time;
	string client;

	int inputDoc = inputDc();//�ǻ��Է�
	v[inputDoc - 1]->display_Schedule();//�ǻ����

	day = inputDay();
	time = inputTime();
	client = inputInfo();

	v[inputDoc - 1]->setSchedule(client,time,day);//�ǻ����
	v[inputDoc - 1]->display_Schedule();//�ǻ����
	system("cls");//�Է� �� �Է¹��� ȭ�� ���� -->API����
}

void Department::chk_reservation() {
	string client = inputInfo();
	string s;
	for (int i = 0; i < v.size(); i++) {
		s = v[i]->getSchedule(client);
		if (s[0] != '-') {
			cout << s;
			break;
		}
	}
}

void Department::cancel_reservation() {
	string client = inputInfo();
	string s;
	for (int i = 0; i < v.size(); i++) {
		v[i]->cancel_sche(client);
	}
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
	string subFile;
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
		subFile = tokenizing_file(readLine);

		dept[idx].setDept(subDept);
		vec_dept.push_back(subDept);

		dept[idx].loadDcList(subFile);
		idx++;
	}
	read_file.close();
}
/*���� ���ڿ��� ���̸�ŭ ���� ����,
	���� ���� ������ �� ���� ���ڿ�(����μ� ��)�� ������ ��ȯ.
	---> string ��������� substr���̺귯�� Ȱ�� */
string Hospital::tokenizing_dept(string const& str) {
	string result;
	int j = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			j = i;
		}
		if (str[i] == '=') {
			result = str.substr(j+1, i-3 );
		}
	}
	return result;
}
string Hospital::tokenizing_file(string const& str) {
	string result;
	int cnt = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '=') {
			cnt++;
			if (cnt == 1) {
				result = str.substr(i+1);
			}
		}
	}
	return result;
}
void Hospital::activation_booking(int num) {
	dept[num - 1].set_reservation();
}
void Hospital::activation_chk(int num) {
	dept[num - 1].chk_reservation();
}
void Hospital::activation_cancel(int num) {
	dept[num - 1].cancel_reservation();
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
	while (1) {
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
		case 50: {//���� ���
			hp->display_deptList();
			int selectDept = Console::select_dept();// 2) ����μ� ����
			hp->activation_cancel(selectDept);
			break;
		}
		case 51: {//���� ��ȸ
			hp->display_deptList();
			int selectDept = Console::select_dept();// 2) ����μ� ����
			hp->activation_chk(selectDept);
			break;
		}
		case 52: {
			exit(100);
		}

		}
	}
}
