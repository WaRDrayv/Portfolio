#pragma once
#include "EngineOperation.h"

class TestBench
{
public:
	
	static EngineOperation engine;
	static void Start_Engine_Test_Overheating();
	static void Engine_Load_Params(int I, int Toh, int Tenv, double Hm, double Hv, double C, vector<int> M, vector<int> V);

	
};
