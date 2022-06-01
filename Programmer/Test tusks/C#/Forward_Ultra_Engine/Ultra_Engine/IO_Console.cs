using System;

namespace Ultra_Engine
{
    class IO_Console
    {
        static void Main(string[] args) 
        {
            
            // TEST();
            //Test_Bench.Engine_Load_Params(10, 2200, 10, 0.01, 0.0001, 0.1, M, V);
            //Test_Bench.Start_Engine_Test_Overheating();
            Menu();
        }
        
        /// <summary>
        /// Метод реализует меню, в котором опции выбираются путём ввода десятичного числа.
        /// </summary>
        static private void Menu()
        {
            int I = 10,//Момент инерции двигателя (кг*м^2)
            Toh = 110,//Температура перегрева

            Tenv = 0;//Температура окружающей среды

            double Hm = 0.01,//Коэффициент зависимости скорости нагрева от крутящего момента (С^0/H*m*сек)
                   Hv = 0.0001,//Коэффициент зависимости скорости нfuhtdf от скорости вращения коленвала (С^0*сек/рад^2)
                   C = 0.1;//Коэффициент зависимости скорости охлаждения от температуры двигателя и окружающей среды (1/сек)
            int[] M = { 20, 75, 100, 105, 75, 0 },//Кусочно-линейная зависимость крутящего момента, вырабатываемого двигателем от скорости вращения коленвалом (Н*м)
                  V = { 0, 75, 150, 200, 250, 300 };//Скорость вращения коленвалом (радиан/сек)

            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine("Menu");
            Console.ResetColor();
            Console.WriteLine("1 - Start test engine in Test Bench");
            Console.WriteLine("2 - Load engine parametrs");
            Console.WriteLine("3 - Set envairment temperature");
            Console.WriteLine("4 - Load TEST parametrs (Toh = 2200)");
            Console.WriteLine("0 - Exite");

            
            char opt = char.Parse(Console.ReadLine().Substring(0, 1));
            if (char.IsDigit(opt))
            {
                switch (opt)
                {
                    case '1':
                        Console.Clear();
                        if (Test_Bench.engine.Check_Params())
                        {
                            Test_Bench.Start_Engine_Test_Overheating();
                            Console.WriteLine("\n1 - Return to Menu ");
                            Console.WriteLine("0 - Exite Program");
                            if (Console.ReadLine() == "1")
                            {
                                Console.Clear();
                                Menu();
                            }
                            else if (Console.ReadLine() == "0") return;

                        }
                        else
                        {
                            if (Test_Bench.engine.tenv_is_Set == false)//теперь мы проверяем был ли ввод температуры окружающей среды
                            {
                                Console.WriteLine("Please, set environment temperature");
                                Tenv = Protect_From_chars(Console.ReadLine());
                                Test_Bench.engine.tenv_is_Set = true;
                            }
                            Test_Bench.Engine_Load_Params(I, Toh, Tenv, Hm, Hv, C, M, V);
                            Test_Bench.Start_Engine_Test_Overheating();
                            Console.WriteLine("\n1 - Return to Menu ");
                            Console.WriteLine("0 - Exite Program");
                            if (Console.ReadLine() == "1")
                            {
                                Console.Clear();
                                Menu();
                            }
                            else if (Console.ReadLine() == "0") return;
                        }

                        break;

                    case '2':
                        if (Tenv == 0)
                        {
                            Console.WriteLine("Please, set environment temperature");
                            Tenv = Protect_From_chars(Console.ReadLine());
                            Test_Bench.engine.tenv_is_Set = true;
                            Console.Clear();
                        }
                        Test_Bench.Engine_Load_Params(I, Toh, Tenv, Hm, Hv, C, M, V);
                        Menu();
                        break;

                    case '3':
                        Console.WriteLine("Please, set environment temperature");
                        //Tenv = int.Parse(Console.ReadLine());
                        Tenv = Protect_From_chars(Console.ReadLine());
                        Test_Bench.engine.tenv_is_Set = true;
                        Test_Bench.Engine_Load_Params(I, Toh, Tenv, Hm, Hv, C, M, V);
                        Console.Clear();
                        Menu();
                        break;
                        
                    case '4':
                        Console.Clear();
                        Console.WriteLine("Please, set environment temperature");
                        Tenv = Protect_From_chars(Console.ReadLine());
                        Test_Bench.engine.tenv_is_Set = true;
                        Console.Clear();
                        Test_Bench.Engine_Load_Params(I, 2200, Tenv, Hm, Hv, C, M, V);
                        Menu();
                        break;

                    case '0':
                        Environment.Exit(0);
                        break;


                    default:
                        break;
                }
            }
            else
            {
                Console.WriteLine("Incorrect option, please, use only numbers!");
                Menu();
            }
        }
        /// <summary>
        /// Метод проверяет наличие цифр, если обнаруживает всё что не цифра - отсекает.
        /// </summary>
        /// <param name="variable">Полученные данные в метод в виде строки</param>
        /// <returns>Возвращаем только цифры</returns>
        static public int Protect_From_chars(string variable)
        {
            string result = string.Empty;
            foreach (char varif in variable)
            {
                if (char.IsDigit(varif)) result += varif;
                
            }
            if (result == string.Empty) return 0;//Без этой конструкции при вводе спецсимволом вернёт ошибку
            else if (variable.Substring(0, 1) == "-") //Костыль. Поскольку "-" не является цифрой, код выше его отсекает. Поскольку работаем
            {                                         //с строками и возвращаем число, добавим условия предварительного прибавления отрицания числу
                result = "-" + result;
                return int.Parse(result);//Вернём велеколепное отрицательное
            }
            else return int.Parse(result);// А если нет - то ок, пусть будет положительное
        }

        static public void TEST()
        {
            int[] M = { 20, 75, 100, 105, 75, 0 },//Кусочно-линейная зависимость крутящего момента, вырабатываемого двигателем от скорости вращения коленвалом (Н*м)
                  V = { 0, 75, 150, 200, 250, 300 };

            Engine_Operation engin = new Engine_Operation();
            engin.Load_Params(10, 110, 10, 0.01, 0.0001, 0.1, M, V);
            for (int i = 0; i <= 100; i++)
            {
                engin.Engine_Working();
                Console.WriteLine($"Vf : {engin.Vf}, Mf : {engin.Mf}, T : {engin.Teng}");
            }

        }

    }
}
