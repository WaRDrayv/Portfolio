using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FigureCalculateLibrary.MathObjects
{
    public class Triangle : Figure
    {
        public int a, b, c;
        public bool isPronounced = false;
        public bool isRectangular = false;

        public Triangle(int a, int b, int c)
        {
            this.a = CheckingForNegative(a);
            this.b = CheckingForNegative(b);
            this.c = CheckingForNegative(c);
            isPronounced = IsNotPronouncedTriangle(this.a, this.b, this.c);
            isRectangular = IsRectangularTriangle(this.a, this.b, this.c);
        }

        /// <summary>
        /// Метод возвращяет площадь треугольника по трём сторонам
        /// используя формулу Герона
        /// </summary>
        /// <returns>
        /// Вернёт площадь треугольника.
        /// Если одна, или все стороны ниже нуля - вернёт ноль
        /// </returns>
        public override int Square()
        {
            if (a > 0 && b > 0 && c > 0) 
            {
                int p = (a + b + c) / 2; // Полупериметр треугольника 
                return (int)Math.Sqrt(p * (p - a) * (p - b) * (p - c));
            }
            return 0;

        }

        /// <summary>
        /// Определяет является ли триугольник вырожденным, т.е. треугольником в понимании геометрии
        /// </summary>
        /// <returns>Если сумма двух любых углов больше третьего - вернёт true, в противном случае false</returns>
        static public bool IsNotPronouncedTriangle(int a, int b, int c) => a + b > c && b + c > a && a + c > b ? true : false;

        /// <summary>
        /// Определяет является ли триугольник прямоугольным. По теореме Пифогора.
        /// </summary>
        static public bool IsRectangularTriangle(int a, int b, int c)
        {
            int hypotenuse, antiliking, adjacent, result, comparable; 
            if (a > b && a > c) 
            {
                hypotenuse = a;
                adjacent = b;
                antiliking = c;
            }
            else if (b > a && b > c)
            {
                hypotenuse = b;
                adjacent = c;
                antiliking = a;
            }
            else
            {
                hypotenuse = c;
                adjacent = a;
                antiliking = b;
            }
            result = hypotenuse * hypotenuse;
            comparable = (adjacent * adjacent) + (antiliking * antiliking);

            return result == comparable ? true : false; // Если квадрат гипотенузы равен сумме квадратов прилежащего и противилежащего катетов
                                                        // значит треугольник прямоугольный, а если нет, то нет =)
        }

    }
}
