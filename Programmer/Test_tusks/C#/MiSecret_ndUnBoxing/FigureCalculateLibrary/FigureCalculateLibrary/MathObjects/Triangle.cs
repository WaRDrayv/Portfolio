using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FigureCalculateLibrary.MathObjects
{
    public class Triangle : IGeometricShape
    {
        private int _a, _b, _c;
        private bool _isPronounced = false;
        private bool _isRectangular = false;

		[Range(1, 10000, ErrorMessage = "Сторона {0} может принимать значения от {1} до {2}.")]
		public int A
        {
            get => _a;
            private set => _a = value; 
        }

		[Range(1, 10000, ErrorMessage = "Сторона {0} может принимать значения от {1} до {2}.")]
		public int B
        {
            get => _b;
            private set => _b = value;
        }

		[Range(1, 10000, ErrorMessage = "Сторона {0} может принимать значения от {1} до {2}.")]
		public int C
        {
            get => _c;
            private set => _c = value;
        }

        public bool IsPronounced 
        { 
            get => _isPronounced; 
        }

        public bool IsRectangular 
        { 
            get => _isRectangular;
        }


        public Triangle(int a, int b, int c)
        {
            _a = a;
            _b = b;
            _c = c;
            _isPronounced = IsNotPronouncedTriangle(_a, _b, _c);
            _isRectangular = IsRectangularTriangle(_a, _b, _c);
        }

        /// <summary>
        /// Метод возвращяет площадь треугольника по трём сторонам
        /// используя формулу Герона
        /// </summary>
        /// <returns>
        /// Вернёт площадь треугольника.
        /// Если одна, или все стороны ниже нуля - вернёт ноль
        /// </returns>
        public int GetArea()
        {
            if (_a > 0 && _b > 0 && _c > 0) 
            {
                int p = (_a + _b + _c) / 2; // Полупериметр треугольника 
                return (int)Math.Sqrt(p * (p - _a) * (p - _b) * (p - _c));
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
