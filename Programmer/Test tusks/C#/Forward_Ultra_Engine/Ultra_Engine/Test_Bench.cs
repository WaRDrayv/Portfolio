using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ultra_Engine
{
    static class Test_Bench
    {
        static public Engine_Operation engine = new Engine_Operation();
        /// <summary>
        /// Метод начала тестирования двигателя. Он отслеживает фактическую температуру двигателя, в случае превышения 
        /// температуры перегрева, остановит тестирование. Возвращает в консоль соответствующее сообщение, температуру перегрева,
        /// фактическую температуру двигателя и время, за которое произошёл нагрев.
        /// </summary>
        static public void Start_Engine_Test_Overheating()
        {
            //Engine_Operation engine = new Engine_Operation();
            int Time = 0;
            if (engine.Check_Params())
            {
                while (true)
                {
                    engine.Engine_Working();
                    Time++;//Грубо считаем чисто по условным секундам.
                    Console.WriteLine($"Vf : {engine.Vf}; Mf : {engine.Mf}; T : {engine.Teng}");
                    if (engine.Teng >= engine.Toh)
                    {
                        
                        Console.WriteLine("\nStop Test: Engine overheated.");
                        Console.WriteLine($"T(overheat) : {engine.Toh}\nT(actual) : {engine.Teng}\nTime to overheat : {Time} second");
                        engine.Vf = 0;
                        engine.Teng = engine.Tenv;

                        break;
                    }
                        
                }
            }


        }
        /// <summary>
        /// Загрузка параметров двигателя через тестовый стенд.
        /// </summary>
        static public void Engine_Load_Params(int I, int Toh, int Tenv, double Hm, double Hv, double C, int[] M, int[] V)
        {
                engine.Load_Params(I, Toh, Tenv, Hm, Hv, C, M, V);
        }

    }
}
