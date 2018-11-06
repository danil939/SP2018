﻿#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include <windows.h> 
#include <iostream>
#include <time.h>
#include <conio.h> 

using namespace std;

int main(int argc, char* argv[])// argc - колличество аргументов, argv - сколько параметров мы передали 
 {

	char pers = 0;
	time_t time1 = 0,  time2 = 0;
	time_t proverka = 0;
	


	time_t per1 = 0;
	time(&per1);

	struct tm *vr = localtime(&per1);
	
	cout << '\n' << "  Местное время: " << asctime(vr) << endl;


	
	

	if (!strcmp(argv[1], "sub") || !strcmp(argv[1], "add")) {

		if (!strcmp(argv[2], "sec") || !strcmp(argv[2], "min") || !strcmp(argv[2], "hour") || !strcmp(argv[2], "day")) {

			proverka = atoi(argv[3]);

			if (!strcmp(argv[2], "min")) proverka *= 60;
			else if (!strcmp(argv[2], "hour")) proverka *= 60 * 60;
			else if (!strcmp(argv[2], "day")) proverka *= 60 * 60 * 24;
		}

		if (!strcmp(argv[1], "sub")) {

			time(&per1);
			pers -= proverka;

		}

		else if (!strcmp(argv[1], "add")) {

			time(&per1);
			pers += proverka;

		}

		if (per1 < 0) {

			cout << '\n' << "  Местное время: " << asctime(vr) << endl;

			return -1;

		}

		if (strcmp(argv[2], "sec") != 0 && strcmp(argv[2], "min") != 0 && strcmp(argv[2], "hour") != 0 && strcmp(argv[2], "day") != 0) {
			cout << "  Error" << endl;
			_getch();
			return -1;

		}
		struct tm *vr = localtime(&per1);
		cout << "  Изменённое время: " << asctime(vr) << endl;
	}


	if (strcmp(argv[1], "sub") != 0 && strcmp(argv[1], "add") != 0 && strcmp(argv[1], "diff") != 0) {

		cout << "  Error " << endl;
		_getch();
		return -1;

	}

		if (!strcmp(argv[1], "diff")) {

			for (int i = 2; i < argc; i++) {

				int hour = 0, min = 0, sec = 0;


				if (sscanf(argv[i], "%2d:%2d:%2d", &hour, &min, &sec) != 3 || strlen(argv[i]) != 8 || argv[i][7]<'0' || argv[i][7] > '9' || hour > 23 || min > 59 || sec > 59 || hour < 0 || min < 0 || sec < 0) {
					cout << "  Неверный формат времени ') " << endl;
					return -1;
				}
				int timei = hour * 60 * 60 + min * 60 + sec;
				if (i == 2) time1 = timei;
				else time2 = timei;
			}

			per1 = abs(time1 - time2);
			cout << "  разница между 2 временами : " << per1 << endl;
			return 0;
		}
		system("pause");
		return 0;

}


