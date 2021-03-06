
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

//перевод временного интервала в секунды
long long get_time_value(char *t, int n)
{
			
	if (strcmp(t, "day") == 0)		//в зависимости от интервала n умножается
	{
		return (long long)n * 24 * 3600;	//на нужный коэффициент
	}
	else if (strcmp(t, "hour") == 0)
	{
		return (long long)n * 3600;
	}
	else if (strcmp(t, "min") == 0)
	{
		return (long long)n * 60;
	}
	else if (strcmp(t, "sec") == 0)
	{
		return (long long)n;
	}
	else
	{
		return -1;	//для неправильного интервала вернуть ошибку
	}
}

int main(int argc, char **argv)
{
	if (argc != 4)	//проверка кол-ва параметров командной строки
	{
		printf("нет аргументов\n");
		return 1;
	}
		
	if (strcmp(argv[1], "diff") == 0)	//разность времени
	{
		time_t time_1, time_2;
		struct tm tm_tmp;
		time_t now;
		time(&now);		//получить текущее время
		struct tm *timeinfo = localtime(&now);
		//первое время
		tm_tmp = *timeinfo;	//скопировать корректные занчения в tm_tmp
		if (sscanf(argv[2], "%2d:%2d:%2d", &tm_tmp.tm_hour, &tm_tmp.tm_min, &tm_tmp.tm_sec) != 3)	//парсинг времени с проверкой корректности
		{
			printf("Неверный формат time_1 \n");	//при ошибке вывести сообщение
			return 1;
		}
		if (tm_tmp.tm_hour < 0 || tm_tmp.tm_hour>23 || tm_tmp.tm_min < 0 || tm_tmp.tm_min>59 || tm_tmp.tm_sec < 0 || tm_tmp.tm_sec>59)	//проверка цифровых значений времени
		{
			printf("Неверный формат time_1 \n");	//при ошибке вывести сообщение
			return 1;
		}
		time_1 = mktime(&tm_tmp);		//создать введенное время
		//второе время
		if (sscanf(argv[3], "%2d:%2d:%2d", &tm_tmp.tm_hour, &tm_tmp.tm_min, &tm_tmp.tm_sec) != 3)	//парсинг времени с проверкой корректности
		{
			printf("Неверный формат time_2 \n");	//при ошибке вывести сообщение
			return 1;
		}
		if (tm_tmp.tm_hour < 0 || tm_tmp.tm_hour>23 || tm_tmp.tm_min < 0 || tm_tmp.tm_min>59 || tm_tmp.tm_sec < 0 || tm_tmp.tm_sec>59)	//проверка цифровых значений времени
		{
			printf("Неверный формат time_2 \n");	//при ошибке вывести сообщение
			return 1;
		}
		time_2 = mktime(&tm_tmp);		//создать введенное время
		double diff = difftime(time_1, time_2);	//вычисляем
		printf("Diff = %g\n", fabs(diff));		//и выводим разность

	}
	else if (strcmp(argv[1], "add") == 0)	//если добавление интервала к текущему времени
	{
		int n;
		if (sscanf(argv[3], "%d", &n) != 1)		//проверить чтобы последний параметр был числом
		{
			printf("Последним параметррм должно быть число\n");	//при ошибке вывести сообщение
			return 1;
		}
		long long n_sec = get_time_value(argv[2], n);		//преобразовать интервал в секунды
		if (n_sec == -1)				//при ошибке вывести сообщение
		{
			printf("Аргумент должен быть: день /час/мин/сек\n");
			return 1;
		}
		time_t now;
		time(&now);				//получить текущее время
		now += n_sec;		//прибавить к текущему времени заданный интервал
		if (now < 0)		//если получается дата до 00:00:00 1 января 1970 года
		{
			printf("Ошибка\n");	//вывести сообщение
			return 1;
		}
		struct tm *timeinfo = localtime(&now);	//получить локальное время по полученному и вывести
		printf("Результат: %02d.%02d.%04d %02d:%02d:%02d\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	}
	else if (strcmp(argv[1], "sub") == 0)
	{
		int n;
		if (sscanf(argv[3], "%d", &n) != 1)		//проверить чтобы последний параметр был числом
		{
			printf("Последним параметррм должно быть число\n");	//при ошибке вывести сообщение
			return 1;
		}
		long long n_sec = get_time_value(argv[2], n);		//преобразовать интервал в секунды
		if (n_sec == -1)				//при ошибке вывести сообщение
		{
			printf("Аргумент должен быть: день/час/мин/сек.\n");
			return 1;
		}
		time_t now;
		time(&now);				//получить текущее время
		now -= n_sec;		//вычесть из текущего времени заданный интервал
		if (now < 0)		//если получается дата до 00:00:00 1 января 1970 года
		{
			printf("Ошибка\n");	//вывести сообщение
			return 1;
		}
		struct tm *timeinfo = localtime(&now);	//получить локальное время по полученному и вывести
		printf("Результат: %02d.%02d.%04d %02d:%02d:%02d\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

	}
	else
	{	//при ошибке вывести сообщение
		printf("Неверная команда (должна быть: diff / add / sub)\n");
		return 1;
	}
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
