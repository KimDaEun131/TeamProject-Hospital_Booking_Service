#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <conio.h>
#include <regex>//����ǥ����

using namespace std;

#include "hospital.h"

/*===Console Ŭ���� ������===*/
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

string Console::select_doctorName() {
	string sent;
	Console::gotoxy(34, 15); cout << "====Please enter the desired Doctor!!====\n"; 
	Console::gotoxy(37, 17); cout << ">>";
	cin >> sent;
	system("cls");//�Է� �� �Է¹��� ȭ�� ���� -->API����
	return sent;
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
	read_file.close();
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
			subStr = tokenizing_line(readLine);
			deptName = subStr;
			break;
		}
	}
	read_file.close();
}
string Department::tokenizing_line(const string str) {
	string result;
	for (int i = 0; i < str.size(); i++) {//���� ���ڿ��� ���̸�ŭ ���� ����
		if (str[i] == ' ') {//���� ���� ������ �� ���� ���ڿ� ���� ��ũ����¡ ���� �� �ش� ������ ��ȯ
			result = str.substr(i + 1);
		}
	}
	return result;
}

void Department::display_dept_list() {
	Console::gotoxy(41, 1); cout << "�ݡ� MEDICAL DEPARTMENT �ݡ�" << endl;
	for (int i = 0; i < vec_deptName.size(); i++){
		Console::gotoxy(45, (i*2)+4);
		cout << vec_deptName[i]<<endl;
	}
}

/*=====Doctor Ŭ���� ������=====*/
void Doctor::setDoctor(const string dp) {
	ifstream read_fileDoctor;
	string readLine;//�ؽ�Ʈ���Ͽ��� ���� ������ �ؽ�Ʈ ����
	string subStrDept;//�κ� ���ڿ� ����
	string subStrDc;
	string dcList;

	if (!read_fileDoctor) {//���� �б� ����ó��
		cout << "�ý��� �� ������ �ֽ��ϴ�.\n";
		exit(100);
	}
	read_fileDoctor.open("doctor.txt");//�ؽ�Ʈ���� �ҷ�����
	while (1) {
		if (read_fileDoctor.eof())break;//���ϳ� ������ ���� Ż��
		getline(read_fileDoctor, readLine);
		subStrDept=tokenizing_line(readLine);//�μ��� ����	
		subStrDc = extract_line(readLine);//'='���� ��ũ����¡�� ���ڿ� ����

		if (dp.compare(subStrDept)== 0) {//������ �μ���� �ش� �Ƿ����� ���� �μ����� �����ϸ�            
			vec_dcName = tokenizing_doctor(subStrDc);//���� ����
		}
	}
}
string Doctor::tokenizing_line( const string str) {
	string result;
	for (int i = 0; i < str.size(); i++) {//���� ���ڿ��� ���̸�ŭ ���� ����
		if (str[i] == '=') {//���� ���� ������ �� ���� ���ڿ� ���� ��ũ����¡ ���� �� �ش� ������ ��ȯ
			result = str.substr(0, i);//0��° �ε��� ���� '='���� �������� ���ڿ� ��ũ����¡
			break;
		}
	}
	return result;
}
string Doctor::extract_line(string const& str) {
	string result;
	for (int i = 0; i < str.size(); i++){
		if (str[i] == '=') {//���� ���� ������ �� ���� ���ڿ� ���� ��ũ����¡ ���� �� �ش� ������ ��ȯ
			result = str.substr(i + 1);//0��° �ε��� ���� '='���� �������� ���ڿ� ��ũ����¡
			break;
		}
	}
	return result;
}

vector <string> Doctor::tokenizing_doctor(string const& str) {
	vector <string>temp_dc_name;
	string doctor;
	int chkComma = 0;
	int idx = 0;
	for (int i = 0; i < str.size(); i++) {//��ǥ ������ ���� ���ڿ� ���� �� ���Ϳ� ����
		if (str[i] == ',') {
			doctor = str.substr(idx, i - idx);//��ǥ �������� üũ
			idx = i + 1;//�ε��� ����
			temp_dc_name.push_back(doctor);//����� ���ڿ� ���Ϳ� ����
		}
	}
	doctor = str.substr(idx);//������ �ǻ� �̸� ����--> ������ ��ǥ ���� ���ڿ��� ���� �ۿ��� ���� �۾� ����
	temp_dc_name.push_back(doctor);

	return temp_dc_name;
}
void Doctor::display_doctorList() {
	for (int i = 0; i < vec_dcName.size(); i++){
		Console::gotoxy(48, (i*2)+6);
		cout << vec_dcName[i] << endl;
	}
}
void Doctor::doctorName_reserv(){
	string temp = Console::select_doctorName();//��� �Ƿ��� �Է�
	for (int i = 0; i < vec_dcName.size(); i++){
		if (vec_dcName[i].compare(temp) == 0) {
			dcName = temp;
		}
	}
}

/*=====Hospital Ŭ���� ������=====*/
void Hospital::execute_prog() {
	selectMenu = Console::select_menu();//�޴� �Է�(1. ����, 2.��ȸ, 3.���, 4.����)
	switch (selectMenu){
	case 49: //���� ����
		dc->display_dept_list();//���� ������ ���� �μ� ���
		selectDept = Console::select_dept();//�μ� �Է�(1~9)
		dc->setDept(selectDept);//�Էµ� �μ��� �ش�Ǵ� ��ü �ʱ�ȭ
		
		selectMethod = Console::select_method();//���� ��� ����
		activation_reserv(selectMethod);//���� Ȱ��ȭ
		break;
	}
}
void Hospital::activation_reserv(int param) {//���� �غ�ܰ�

	if (selectMethod == 1) {//�ǻ� �߽� ���� ��� ����
		string department = dc->getDept();//������ �μ� ����

		dc->setDoctor(department);//������ �μ��� �ش��ϴ� �Ƿ��� �ʱ�ȭ
		Console::gotoxy(36, 4); cout <<"�ݡݡ�"<< dc->getDept() << "�Ƿ����Դϴ�!�ݡݡ�" << endl;
		dc->display_doctorList();//�Ƿ��� ��� ���
		
		dc->doctorName_reserv();//���� ����
		cout << dc->getDoctor() << "�����ϼ̽��ϴ�!";
	}
	else if (selectMethod == 2) {

	}
}
