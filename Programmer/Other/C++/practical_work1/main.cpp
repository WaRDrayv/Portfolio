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
	
void Cp (Data *RedGoFaster) // ���� ����� �������
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
	
void Cm (Data *RedGoFaster) // ���� � ����� ������
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
		
void Bp (Data *RedGoFaster) // ��� ���������, rectangle - ��� bar ��� ������������
	{
		for (int i = 0; i < 500; i++)//������� �����, ������ ��� ����� ���������� ��� �������������, �� ����� ���
														//1 ������� ����� ��������� �����������, � �� � 2
														//������� �����, ������� ������ � ������� if
		{
			if (rp1 + 49 == rp2 - 49) // ������ 1 ��������� ��������, ������ ��������� - ���. ��� ��� ��� �� �� �������.
			{
				i = 0;
//				rp1 = 0;
//				rp2 = 0;
//				rectangle (100, 100 + i, 200, 0 + i, RGB (200, 0, 0)); // ������� ���� ��� �������
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
	char buf [100]; //������ ������� ����� �� 100 �������� ��� �������� ���������� �� cmd/terminal
	char buf2 [100];
	char buf3 [100];
	char buf4 [100];
	HANDLE TH [3]; // HANDLE - ��� ���������� ��� �������������. � ���������� - ��� ��������� ������ ������ �� ������, ������������� �� ��� ����������
	
	resize(880, 880); // ��������� ������ ����
	outtextxy(325, 750, "������������ ������ �1"); //������� ����� � ����������� ����. �������� ��� outtext ������ �� ����������� x � y
	outtextxy(370, 800, "�������� �.�.");
	
	Data *RedGoFaster; //�������� ��� ��� ���������� � �����!
	//�������� ������ ����
	RedGoFaster = new Data; // �������������� ����� ��������� �� ����� RedGoFaster ���� Data
	RedGoFaster->position = 100; //����� �������� ����� � ��������� 	
	if(GetEnvironmentVariable ("speed", buf, 100))// ������ �������� ����� ��� ������ �� cmd
	{											//speed - ��� ���������� ���������, ���. buf - ��� ��������� �����, � ������� ����� �������� ��������, 100 - ����� ��� ������
		RedGoFaster->speed = atoi (buf); // atoi - ������������ string � int, �.�. �� cmd ���� ������ ������ string. ���� �������� �� ����� - ����� ��������� � 0
	}
	else RedGoFaster->speed = 30; // ��� � ������, ��������������, ��� � ��������� �� ���������
	TH [0] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Cp, (LPVOID) RedGoFaster, 0, 0);// ������ ���� ����� TH[0] ���� ��� ����� �������
//******************************************************************************************************************************	
	//������ ����
	RedGoFaster = new Data; // ������ ����������������� ��� �� ����� ���������, ������� ������� ��������
//	RedGoFaster->speed = 20, 
	RedGoFaster->position = 100;
	if(GetEnvironmentVariable ("speed2", buf2, 100)){
		RedGoFaster->speed = atoi (buf2);
	}
	else RedGoFaster->speed = 20;
	TH [1] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Cm, (LPVOID) RedGoFaster, 0, 0);
//******************************************************************************************************************************	
	//������ �������
	RedGoFaster = new Data;
		if(GetEnvironmentVariable ("speed3", buf3, 100)){
			RedGoFaster->speed = atoi (buf3);
		}
		else RedGoFaster->speed = 20;
	TH [2] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Bp, (LPVOID) RedGoFaster, 0, 0);//� �� - �������.
//******************************************************************************************************************************	
	//������ �������
	RedGoFaster = new Data;
		if(GetEnvironmentVariable ("speed4", buf4, 100)){
			RedGoFaster->speed = atoi (buf4);
		}
		else RedGoFaster->speed = 10;
	TH [3] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Bp, (LPVOID) RedGoFaster, 0, 0);//��� �� �� �� �������������?
	//�������:
	//CreateThread LPVOID 1pParametr - ��������� ������ ��� ��������, ������� ������ ��� ������� ������ ��� �������, 
	//��� ���� ��� � ������� ������ ������� ������, ����� ������������ ��������� � ��������� �� �� ��� ������� ������ � �������
		WaitForMultipleObjects (4, TH, true, INFINITE);// ������� �������� �����. 4 - ���-�� �����. TH - ��������� �� ������ ������� �������� �������������� �� ����.true - ��� ��� ����. INFINITE - �� ����������� ����� ���.
		CloseHandle(TH [0]), CloseHandle(TH [1]), CloseHandle(TH [3]), CloseHandle(TH [4]);

	}
