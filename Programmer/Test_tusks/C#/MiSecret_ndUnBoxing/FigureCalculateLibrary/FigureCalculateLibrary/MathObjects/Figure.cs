using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FigureCalculateLibrary.MathObjects
{
    public class Figure
    {
        public virtual int Square()
        {
            return 0;
        }

        /// <summary>
        /// Проверка на отрицательные числа
        /// </summary>
        /// <returns>Если number отрицательна, вернёт 0</returns>
        static public int CheckingForNegative(int number) => number > 0 ? number : 0;


        //public virtual void ThisFigureIs()
        //{
        //    Console.WriteLine("Not Defined!");
        //}
    }
}
