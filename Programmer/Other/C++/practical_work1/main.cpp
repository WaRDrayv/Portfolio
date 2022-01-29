#define MAXCOLORTC
#include "wingraph-ts.h"
#include <stdlib.h>
#include <time.h>

//int test = 200;
int rp1 = NULL, rp2 = NULL, rs1, rs2;
struct Data
	{
		int speed, position;
	};
	
void Cp (Data *RedGoFaster) // круг слева направо
	{
		rs1 = RedGoFaster->speed;
		for (int i = 0; i < 500; i++ )
			{
				circle(100 + i, RedGoFaster->position, 50, RGB (0, 200, 0));
				delay(RedGoFaster->speed);
				circle(100 + i, RedGoFaster->position, 50, RGB (255, 255, 255));
				rp1 = 100 + i;
				
				
			}
	}
	
void Cm (Data *RedGoFaster) // круг с права налево
		{
			rs2 = RedGoFaster->speed;
			for (int i = 0; i < 500; i++)
				{
					circle(600 - i, RedGoFaster->position, 50, RGB (0, 200, 0));
					delay(RedGoFaster->speed);
					circle(600 - i, RedGoFaster->position, 50, RGB (255, 255, 255));
					rp2 = 600 - i;
					
					
				}
		}
		
void Bp (Data *RedGoFaster) // для квадратов, rectangle - это bar без закрашивания
	{
		for (int i = 0; i < 500; i++)//великая тайна, каждый раз когда запускаешь или пересобираешь, не меняя код
														//1 квадрат может перестать реагировать, а то и 2
														//ПРОВОДЯ тесты, полагаю ошибка в условии if
		{
			if (rp1 + 49 == rp2 - 49) // Теперь 1 стабильно работает, второй стабильно - нет. При чём как то не понятно.
			{
				i = 0;
//				rp1 = 0;
//				rp2 = 0;
//				rectangle (100, 100 + i, 200, 0 + i, RGB (200, 0, 0)); // красный цвет для отладки
//				delay(RedGoFaster->speed);
//				rectangle (100, 100 + i, 200, 0 + i, RGB (255, 255, 255));
			}
			else
			{
				rectangle (100, 100 + i, 200, 0 + i, RGB (0, 0, 200));
				delay(RedGoFaster->speed);
				rectangle (100, 100 + i, 200, 0 + i, RGB (255, 255, 255));
			}
			
		}
	}
	

	
void mainx ()
	{
	char buf [100]; //Видимо создали буфер на 100 значений для значений переданных из cmd/terminal
	char buf2 [100];
	char buf3 [100];
	char buf4 [100];
	HANDLE TH [3]; // HANDLE - это дескриптор для идентификации. А Дескриптор - это косвенный способ ссылки на объект, пренадлежащий ОС или Библиотеке
	
	resize(880, 880); // Установим размер окна
	outtextxy(325, 750, "Практическая Работа №1"); //выводим текст в графическом окне. Работает как outtext только по координатам x и y
	outtextxy(370, 800, "Фастовец А.Ю.");
	
	Data *RedGoFaster; //ПОЧИТАТЬ ЧТО ТУТ ПРОИСХОДИТ И ЗАЧЕМ!
	//СОЗДАДИМ ПЕРВЫЙ КРУГ
	RedGoFaster = new Data; // Инициализируем новую структуру по имени RedGoFaster типа Data
	RedGoFaster->position = 100; //Задаём значения полям в структуре 	
	if(GetEnvironmentVariable ("speed", buf, 100))// Видимо получаем через Гет данные из cmd
	{											//speed - имя переменной окружения, хмм. buf - тут указываем буфер, в который будут помещены значения, 100 - вроде как размер
		RedGoFaster->speed = atoi (buf); // atoi - конвертирует string в int, т.к. из cmd сюда прийдёт только string. Если передать не числа - будет преврящён в 0
	}
	else RedGoFaster->speed = 30; // как в методе, перестрахуемся, что б программа не сломалась
	TH [0] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Cp, (LPVOID) RedGoFaster, 0, 0);// Создаём нить через TH[0] чтоб его потом закрыть
//******************************************************************************************************************************	
	//ВТОРОЙ КРУГ
	RedGoFaster = new Data; // Видимо переинициализация той же самой структуры, заменяя прошлые значения
//	RedGoFaster->speed = 20, 
	RedGoFaster->position = 100;
	if(GetEnvironmentVariable ("speed2", buf2, 100)){
		RedGoFaster->speed = atoi (buf2);
	}
	else RedGoFaster->speed = 20;
	TH [1] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Cm, (LPVOID) RedGoFaster, 0, 0);
//******************************************************************************************************************************	
	//ПЕРВЫЙ КВАДРАТ
	RedGoFaster = new Data;
		if(GetEnvironmentVariable ("speed3", buf3, 100)){
			RedGoFaster->speed = atoi (buf3);
		}
		else RedGoFaster->speed = 20;
	TH [2] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Bp, (LPVOID) RedGoFaster, 0, 0);//А ты - молодец.
//******************************************************************************************************************************	
	//ВТОРОЙ КВАДРАТ
	RedGoFaster = new Data;
		if(GetEnvironmentVariable ("speed4", buf4, 100)){
			RedGoFaster->speed = atoi (buf4);
		}
		else RedGoFaster->speed = 10;
	TH [3] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Bp, (LPVOID) RedGoFaster, 0, 0);//Вот чё ты не возвращаешься?
	//Заметки:
	//CreateThread LPVOID 1pParametr - Принимает именно тот параметр, который указан как входные данные для функции, 
	//для того что б указать больше входных данных, нужно использовать структуру и указатель на неё как входные данные в функции
		WaitForMultipleObjects (4, TH, true, INFINITE);// Ожидаем закрытие нитей. 4 - кол-во нитей. TH - указатель на массив который содержит идентификаторы на нити.true - ждём все нити. INFINITE - не ограниченое время эжём.
		CloseHandle(TH [0]), CloseHandle(TH [1]), CloseHandle(TH [3]), CloseHandle(TH [4]);

	}
