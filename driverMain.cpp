#include <Windows.h>
#include <iostream>
using namespace std;

#include "hospital.h"

int main(void) {
	Console::gotoxy(28, 3);
	cout << " WELCOME TO SEVERANCE-HEALTHCARE\n";
	
	Console* client = new Console();
	client->execute_prog();
	system("pause");
	return 0;
}