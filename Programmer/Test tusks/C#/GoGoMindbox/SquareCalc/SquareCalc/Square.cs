using System;

namespace SquareCalc
{
    static public class Square
    {
        //private const double pi = 3.1415926535; //Возьмём среднюю точность (между float и decimal), число ПИ до 10 знака
        private const double pi = 3.14;// Простой, нормальный ПИ

        /// <summary>
        /// Находит площадь круга по радиусу
        /// </summary>
        /// <returns>Вернёт площадь типа int</returns>
        static public int Circle(int radius) => (int)(pi * (radius * radius));

        /// <summary>
        /// Находит площадь треугольника по 3 сторонам
        /// используя формулу Герона
        /// </summary>
        /// <returns>Вернёт площадь типа int</returns>
        static public int Triangle (int a, int b, int c) { 
            int p = (a + b + c)/2; // Полупериметр треугольника
            return (int)Math.Sqrt(p * (p - a) * (p - b) * (p - c));
        }

        /// <summary>
        /// Определяет является ли треугольник прямоугольным. По теореме Пифогора.
        /// </summary>
        static public bool IsRectangularTriangle(int a, int b, int c)
        {
            //int hypotenuse = a > b && a > c ? a : b > a && b > c ? b : c; // Хотел находить углы, и по ним определять прямоугольный треугольник, но.... Теорема Пифагора рулит
            int hypotenuse, antiliking, adjacent, result, comparable; // Компилятор автоматом присвоит им нули, так что не паримся и пишем дальше на чиле.
            if (a > b && a > c) // Можно было присвоить только гипотенузу, но мы не ищем лёгких путей, только сложные и разжёванные :)
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

            return result == comparable ? true : false; // В погоне за компактностью. Если квадрат гипотенузы равен сумме квадратов прилежащего и противолежащего катетов
                                                        // значит треугольник прямоугольный, а если нет, то нет =)
        }


        /// <summary>
        /// Определяет является ли треугольник вырожденным, т.е. треугольником в понимании геометрии
        /// </summary>
        /// <returns>Если сумма двух любых углов больше третьего - вернёт true, в противном случае false</returns>
        static public bool IsNotPronouncedTriangle (int a, int b, int c)
        {
            //Немножко правил Дейкстры
            bool flag = a + b > c && b + c > a && a + c > b ? true : false;
            return flag;
        }


        /// <summary>
        /// Метод для определения площади фигур
        /// </summary>
        /// <param name="a">Радиус круга</param>
        /// <returns>Площадь круга</returns>
        static public int Figure(int a)
        {
            return Circle(a);
        }

        /// <summary>
        /// Метод для определения площади фигур
        /// </summary>
        /// <param name="a">Первая сторона</param>
        /// <param name="b">Вторая сторона</param>
        /// <param name="c">Третья сторона</param>
        /// <returns>Площадь треугольника</returns>
        static public int Figure(int a, int b, int c)
        {
            if (IsNotPronouncedTriangle(a, b, c) == true)
            {
                if (IsRectangularTriangle(a, b, c) == true)
                {
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    Console.WriteLine("Is Rectangular Triangle");
                    Console.ResetColor();
                }
                return Triangle(a, b, c);
            }
            else
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("Is not Triangle!");
                Console.ResetColor();
                return 0; // Пренебригаем законом Дейкстры, важен ли он по вашему мнению?
            }
        }
    }
}
