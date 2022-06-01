using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Ultra_Engine
{ 
    class Engine_Operation : IEngine
    {

        int _I, _Toh, _Tenv;
        double _Hm, _Hv, _C, _a; //_а - Ускорение, будем меняться в процессе работы двигателя 
        //1 Костыль для массивов. Инициализировали их разными, что б в случае неудачного (или отсутствия) присвоения параметров, сигнализировала ошибка о разных размерах массива.
        //int[] _M = new int[2], //Можно было сделать через лист, что б явно не указывать, и иметь возможность расширять 
        //      _V = new int[1];
        List<int> _M = new List<int>(),
                  _V = new List<int>();
        

        public double Vf,//Фактическая скорость вращения коленвала. Будет меняться во время работы
                      Mf,//Фактическая кусочно-линейная зависимость
                      Teng;//Температура двигателя

        public bool tenv_is_Set = false;




        public int Toh
        {
            get { return _Toh; }
        }

        public int Tenv
        {
            get { return _Tenv; }
        }
        /// <summary>
        /// Работа двигателя. В процессе работы изменяются скорость, ускорение и темпиратура двигателя.
        /// </summary>
        public void Engine_Working()
        {
            if (Check_Params())
            {
                Check_M_V_Ratio();
                _a = (Mf / _I); //Считаем, чему равно ускорение коленвала без нагрузки

                if (Vf < _V[_V.Count - 1]) Vf += _a; //Увеличиваем скорость коленвала на вектор ускорения (каждый тик, тики считаем на тестовом стенде)
                else Vf = _V[_V.Count - 1];

                Teng = Math.Round(Teng + (Calc_Vh() - Calc_Vc()), 2); // К t двигателя прибавим разность нагрева и охлаждения двигателя
            }

        }
        /// <summary>
        /// Метод для подсчёта скорости нагрева двигателя.
        /// </summary>
        double Calc_Vh()
        {
            return (Mf * _Hm) + (Math.Pow(Vf, 2) * _Hv);
        }

        /// <summary>
        /// Метод для подсчёта скорости охлаждения двигателя.
        /// </summary>
        double Calc_Vc()
        {
            return _C * (Tenv - Teng);
        }

        /// <summary>
        /// Метод для задания параметров двигателя. При запуске проводит проверку, если из ключевых переменных что-то равно нулю - выведет ошибку
        /// </summary>
        /// <param name="I">Момент инерции двигателя (кг*м^2)</param>
        /// <param name="Toh">Температура перегрева</param>
        /// <param name="Tenv">Температура окружающей среды</param>
        /// <param name="Hm">Коэффициент зависимости скорости нагрева от крутящего момента (С^0/H*m*сек)</param>
        /// <param name="Hv">Коэффициент зависимости скорости нагрева от скорости вращения коленвала (С^0*сек/рад^2)</param>
        /// <param name="C">Коэф. зав. с. охлаждения от температуры двигателя и окружающей среды (1/сек)</param>
        /// <param name="M">Кусочно-линейная зависимость крутящего момента, вырабатываемого двигателем от скорости вращения коленвалом (Н*м)</param>
        /// <param name="V">Скорость вращения коленвалом (радиан/сек)</param>
        public void Load_Params(int I, int Toh, int Tenv, double Hm, double Hv, double C, int[] M, int[] V)
        {
            _I = I; 
            _Toh = Toh;
            _Tenv = Tenv;
            _Hm = Hm;
            _Hv = Hv;
            _C = C;
            //2 Костыль для массивов. Делаем этот танец, т.к. Array.Copy() не работает с нуливыми массивами. Выход: Работать с листами (динамический массив)
            //_M = new int[M.Length];
            //_V = new int[V.Length];
            //Array.Copy(M, _M.ToArray(), M.Length);
            //Array.Copy(V, _V.ToArray(), V.Length);

            _M = M.ToList();
            _V = V.ToList();
            if (Check_Params())
            {
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("All parameters are set correctly!");
                Console.ResetColor();
            }

            Teng = _Tenv;//Температура двигателя равна температуре окружающей среды
            Mf = _M[0];//Этого можно было не делать, т.к. перед каждым шагом мы будем проверять Check_M_V_Ratio, и присваивать
                       //Mf = _M[i], но перестрахуюсь.
            Vf = _V[0];

        }


        /// <summary>
        /// Метод проверки отношения скорости к кусочно-линейной зависимости. В зависимости от фактической скорости, меняет зависимость.
        /// </summary>
        /// <param name="Vf">Фактическая скорость коленвала</param>
        void Check_M_V_Ratio()
        {
            for (int i = 0; i <= _M.Count - 1; i++)
            {
                if (Vf >= _V[i]) Mf = _M[i];
            }
        }

        /// <summary>
        /// Проверка корректности данных. Если всё в порядке, вернёт true. Если есть некорректные (нулевые) данные, выведет ошибку.
        /// </summary>
        /// <returns></returns>
        public bool Check_Params ()
        {
            bool intCheck = false, 
                 doubleCheck = false, 
                 arrIntCheck = false;

            Console.ForegroundColor = ConsoleColor.Red;

            if (_I != 0 && _Toh != 0 && tenv_is_Set != false ) intCheck = true;
            else
            {
                if (_I == 0) Console.WriteLine("Error! \'I\' is emty");
                if (_Toh == 0) Console.WriteLine("Error! \'Toh\' is emty");
                if (_Tenv == 0) Console.WriteLine("Error! \'Tenv\' not set");
            }

            if (_Hm != 0 && _Hv != 0 && _C != 0) doubleCheck = true;
            else
            {
                if (_Hm == 0) Console.WriteLine("Error! \'Hm\' is emty");
                if (_Hv == 0) Console.WriteLine("Error! \'Hv\' is emty");
                if (_C == 0) Console.WriteLine("Error! \'C\' is emty");
            }
            if (_M.Count != 0 && _V.Count!= 0 && _M.Count== _V.Count) arrIntCheck = true;
            else
            {
                if (_M.Count== 0) Console.WriteLine("Error! \'M\' is emty");
                if (_V.Count== 0) Console.WriteLine("Error! \'V\' is emty");
                if (_M.Count!= _V.Count) Console.WriteLine("Error! \'M\' and \'V\' is not equal");
            }

            if (intCheck == true && doubleCheck == true && arrIntCheck == true)
            {
                //Console.ForegroundColor = ConsoleColor.Green;
                //Console.WriteLine("All parameters are set correctly!");
                Console.ResetColor();
                return true;
            }
            else
            {
                //Console.ForegroundColor = ConsoleColor.Red;
                //Console.WriteLine("Check_Params is failed");
                Console.ResetColor();
                return false;
            }
            
        }


    }
}
