#include "TestBench.h"


EngineOperation TestBench::engine;// Помимо обьявления экза в плюсах для статиков нужно ещё и определение, так что воть

/// <summary>
/// Метод начала тестирования двигателя. Он отслеживает фактическую температуру двигателя, в случае превышения 
/// температуры перегрева, остановит тестирование. Возвращает в консоль соответствующее сообщение, температуру перегрева,
/// фактическую температуру двигателя и время, за которое произошёл нагрев.
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
            Time++;//Грубо считаем чисто по условным секундам.
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
/// Загрузка параметров двигателя через тестовый стенд.
/// </summary>
void TestBench::Engine_Load_Params(int I, int Toh, int Tenv, double Hm, double Hv, double C, vector<int> M, vector<int> V)
{
    engine.Load_Params(I, Toh, Tenv, Hm, Hv, C, M, V);
}