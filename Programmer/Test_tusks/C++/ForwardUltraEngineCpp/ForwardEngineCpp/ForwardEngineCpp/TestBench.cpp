#include "TestBench.h"


EngineOperation TestBench::engine;// ������ ���������� ���� � ������ ��� �������� ����� ��� � �����������, ��� ��� ����

/// <summary>
/// ����� ������ ������������ ���������. �� ����������� ����������� ����������� ���������, � ������ ���������� 
/// ����������� ���������, ��������� ������������. ���������� � ������� ��������������� ���������, ����������� ���������,
/// ����������� ����������� ��������� � �����, �� ������� ��������� ������.
/// </summary>
void TestBench::Start_Engine_Test_Overheating()
{
    
    //Engine_Operation engine = new Engine_Operation();
    int Time = 0;
    if (engine.Check_Params())
    {
        while (true)
        {
            engine.Engine_Working();
            Time++;//����� ������� ����� �� �������� ��������.
            cout << "Vf : " << engine.Vf << " Mf : " << engine.Mf << " T: " << engine.Teng << endl;
            if (engine.Teng >= engine.getToh())
            {

                cout << "\nStop Test: Engine overheated.";
                cout << "\nT(overheat) : " << engine.getToh() << "\nT(actual) : " << engine.Teng << "\nTime to overheat : " << Time << "second";
                engine.Vf = 0;
                engine.Teng = engine.getTenv();

                break;
            }

        }
    }


}

/// <summary>
/// �������� ���������� ��������� ����� �������� �����.
/// </summary>
void TestBench::Engine_Load_Params(int I, int Toh, int Tenv, double Hm, double Hv, double C, vector<int> M, vector<int> V)
{
    engine.Load_Params(I, Toh, Tenv, Hm, Hv, C, M, V);
}