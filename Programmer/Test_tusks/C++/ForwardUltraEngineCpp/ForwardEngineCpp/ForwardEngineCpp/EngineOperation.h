#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <string>

using namespace std;

class EngineOperation
{

private:
	int I = 0, Toh = 0, Tenv = 0;
	double Hm = 0, Hv = 0, C = 0, a = 0;
	vector<int> M,
		V;

	double Calc_Vh();
	double Calc_Vc();
	void Check_M_V_Ratio();

public:
	double Vf = 0,//Фактическая скорость вращения коленвала. Будет меняться во время работы
		Mf = 0,//Фактическая кусочно-линейная зависимость
		Teng = 0;//Температура двигателя

	bool tenv_is_Set = false;

	//EngineOperation() {
	//	I = 0;
	//	Toh = 0;
	//	Tenv = 0;
	//	Hm = 0;
	//	Hv = 0;
	//	C = 0;
	//	a = 0;
	//	Vf = 0;
	//	Mf = 0;
	//	Teng = 0;
	//	tenv_is_Set = false;
	//	M[0] = 0;
	//	V[0] = 0;
	//}

	int getToh() const { return Toh; }
	double getTenv() const { return Tenv; }
	int getI() const { return I; }
	double getHm() const { return Hm; }
	double getHv() const { return Hv; }
	double getC() const { return C; }

	void Engine_Working();
	void Load_Params(int I, int Toh, int Tenv, double Hm, double Hv, double C, vector<int> M, vector<int> V);
	bool Check_Params();
	
};

