#include <iostream>
#include <stdio.h>
#include <windows.h>

//Тут ваще многое не понятно

int main(int argc, char** argv) {
	
	//HANDLE TH [3];
	
	SetEnvironmentVariable ("speed", argv[1]); // Устанавливаем в "очередь" забыл что, почтитаьть!
	SetEnvironmentVariable ("speed2", argv[2]);
	SetEnvironmentVariable ("speed3", argv[3]);
	SetEnvironmentVariable ("speed4", argv[4]);
	STARTUPINFO SI; // Определить оконный терминал? непонял. Что такое SI тоже не ясно, не нашёл инфы
	ZeroMemory (&SI, sizeof SI), SI.cb = sizeof SI;// Освободим память, &SI - указатель на блок памяти. Потом размер в байтах. Чё такое .cb?
	PROCESS_INFORMATION PI; // Ну я так понял что собирает инфу о созданном процессе, мб PI это Процесс (информейшн?) а SI это Систем? Загадка...
	CreateProcess ("practical_work1.exe", 0, 0, 0, true, 0, 0, 0, &SI, &PI); // Создали процесс ПР1, интересно, можно обойтись без этого файла, и запускать непосредственно с СетЕнв файл ПР1
//	WaitForMultipleObjects (4, TH, true, INFINITE);
//	CloseHandle(TH [0]), CloseHandle(TH [1]), CloseHandle(TH [3]), CloseHandle(TH [4]);
	
	
	
	return 0;
}
