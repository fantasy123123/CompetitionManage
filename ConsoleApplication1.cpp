#include<iostream>
using namespace std;
#include"SpeechManager.h"
#include<ctime>
int main() {

	srand((unsigned int)time(NULL));

	SpeechManager sm;
	
	int choice = 0;

	cout << "请输入选择" << endl;
	while(1)
	{
		sm.showMenu();
		cin >> choice;

		switch (choice) {
		case 1:
			sm.start();
			break;

		case 2:
			sm.showrecord();
			break;

		case 3:
			sm.clearrecord();
			break;

		case 0:
			
			sm.exitsystem();
			break;

		default:
			system("cls");
			break;
		}
	}


	system("pause");
	return 0;
}