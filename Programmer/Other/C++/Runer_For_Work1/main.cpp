#include <iostream>
#include <stdio.h>
#include <windows.h>

//��� ���� ������ �� �������

int main(int argc, char** argv) {
	
	//HANDLE TH [3];
	
	SetEnvironmentVariable ("speed", argv[1]); // ������������� � "�������" ����� ���, ����������!
	SetEnvironmentVariable ("speed2", argv[2]);
	SetEnvironmentVariable ("speed3", argv[3]);
	SetEnvironmentVariable ("speed4", argv[4]);
	STARTUPINFO SI; // ���������� ������� ��������? �������. ��� ����� SI ���� �� ����, �� ����� ����
	ZeroMemory (&SI, sizeof SI), SI.cb = sizeof SI;// ��������� ������, &SI - ��������� �� ���� ������. ����� ������ � ������. ׸ ����� .cb?
	PROCESS_INFORMATION PI; // �� � ��� ����� ��� �������� ���� � ��������� ��������, �� PI ��� ������� (����������?) � SI ��� ������? �������...
	CreateProcess ("practical_work1.exe", 0, 0, 0, true, 0, 0, 0, &SI, &PI); // ������� ������� ��1, ���������, ����� �������� ��� ����� �����, � ��������� ��������������� � ������ ���� ��1
//	WaitForMultipleObjects (4, TH, true, INFINITE);
//	CloseHandle(TH [0]), CloseHandle(TH [1]), CloseHandle(TH [3]), CloseHandle(TH [4]);
	
	
	
	return 0;
}
