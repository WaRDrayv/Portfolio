using System;
using System.Collections.Generic;

namespace Expr6
{
    // Expr6. Посчитать расстояние от точки до прямой, заданной двумя разными точками.
    class Program
    {
        static List<string> ERRORS = new List<string>();

        static void Main(string[] args)
        {
            //Console.WriteLine(PointToLineGeometry());
            Menu();
        }

        static void Menu()
        {
            int option;
            double metothResult;
            while (true)
            {
                Console.WriteLine(@"                            Menu");
                Console.WriteLine("1 - Find the distance from a point to a line given by coordinates");
                Console.WriteLine("2 - Find the distance from a point to a straight line given by a quadratic formula");
                Console.WriteLine("3 - Program info");
                Console.WriteLine("9 - Exit");

                option = InputDataNotCutChar();
                switch (option)
                {
                    case 1:
                        metothResult = PointToLineGeometry();
                        if (CheckIfThereAreErrors() == false)
                        {
                            Console.WriteLine(metothResult);
                        }
                        else
                        {
                            break;
                        }
                        Console.ReadLine();
                        break;
                    case 2:
                        metothResult = PointToLineQuadraticFormula();
                        if (CheckIfThereAreErrors() == false)
                        {
                            Console.WriteLine(metothResult);
                        }
                        else
                        {
                            break;
                        }
                        Console.ReadLine();
                        break;
                    case 3:
                        infoProgram();
                        Console.ReadLine();
                        break;
                    default:
                        break;
                }
                if (option == 9)
                {
                    break;
                }
                Console.Clear();
            }
        }

        /// <summary>
        /// Метод для определения расстояния от точки до прямой, указанной координатами
        /// </summary>
        /// <returns>Вернёт целое число</returns>
        static int PointToLineGeometry()
        {
            //int[,] coordinates = new int[30,30];
            int lineStartX, lineStartY, lineEndX, lineEndY, pointX, pointY;
            Console.WriteLine("Line format ps(x,y),pe(x,y) ");
            Console.WriteLine("Enter lineStartX coordinate");
            lineStartX = InputDataNotCutChar();
            Console.WriteLine("Enter lineStartY coordinate");
            lineStartY = InputDataNotCutChar();
            Console.WriteLine("Enter lineEndX coordinate");
            lineEndX = InputDataNotCutChar();
            Console.WriteLine("Enter lineEndY coordinate");
            lineEndY = InputDataNotCutChar();
            Console.WriteLine("Enter pointX coordinate");
            pointX = InputDataNotCutChar();
            Console.WriteLine("Enter pointY coordinate");
            pointY = InputDataNotCutChar();
            Console.WriteLine();
            
            if (pointX >= lineStartX && pointX <= lineEndX && (pointY != lineStartY || pointY != lineEndY))
            {
                return Math.Abs(pointY - ((lineStartY + lineEndY) / 2));
            }
            else if (pointY >= lineStartY && pointY <= lineEndY && (pointX != lineStartX || pointX != lineEndX))
            {
                return Math.Abs(pointX - ((lineStartX + lineEndX) / 2));
            }
            return 0;
        }

        /// <summary>
        /// Метод для определения расстояния от точки до прямой, указанной квадратичной формулой
        /// </summary>
        /// <returns>Возвращает дробное число</returns>
        static double PointToLineQuadraticFormula()
        {
            Console.WriteLine("Line format Ax+By+С=0");
            Console.WriteLine("Enter pointX coordinate");
            int pointX = InputDataNotCutChar();
            Console.WriteLine("Enter pointY coordinate");
            int pointY = InputDataNotCutChar();
            Console.WriteLine("Enter A");
            int A = InputDataNotCutChar();
            Console.WriteLine("Enter + or -");
            char AB = IsPlusOrMinus();
            Console.WriteLine("Enter B");
            int B = InputDataNotCutChar();
            Console.WriteLine("Enter + or -");
            char BC = IsPlusOrMinus();
            Console.WriteLine("Enter C");
            int C = InputDataNotCutChar();
            Console.WriteLine("");

            // Тааак не хотелось костылить, но видимо придёться...
            double result = 0;
            if (AB == '+' && BC == '+')
                result = (Math.Abs((A * pointX) + (B * pointY) + C)) / (Math.Sqrt(A * A) + (B * B));
            if (AB == '+' && BC == '-')
                result = (Math.Abs((A * pointX) + (B * pointY) - C)) / (Math.Sqrt(A * A) + (B * B));
            if (AB == '-' && BC == '+')
                result = (Math.Abs((A * pointX) - (B * pointY) + C)) / (Math.Sqrt(A * A) + (B * B));
            if (AB == '-' && BC == '-')
                result = (Math.Abs((A * pointX) - (B * pointY) - C)) / (Math.Sqrt(A * A) + (B * B));

            return result;
        }

        /// <summary>
        /// Метод определяет, является символ + или -, если нет, пишет ошибку
        /// </summary>
        /// <returns>Вернёт +, -, или ' ' пробел, в случае неверных данных</returns>
        static char IsPlusOrMinus()
        {
            string input = Console.ReadLine();
            char result = input[0];
            // Вариант хороший, но я хочу писать ошибку
            //return result == '+' || result == '-' ? result : ' ';
            if (result == '+' || result == '-')
            {
                return result;
            }
            ERRORS.Add("Error 02. Wrong data: Only plus and minus can be entered");
            return ' ';
        }
        /// <summary>
        /// Проверяет на корректность введённые данные. 
        /// </summary>
        /// <returns>Если введены только числа - true, будут присутствовать другие символы - false</returns>
        static bool OnlyNumber(string input)
        {
            char[] target = input.ToCharArray();
            foreach (char Char in target)
            {
                if (char.IsDigit(Char) == false)
                {
                    ERRORS.Add("Error 01. Wrong data: Characters found in input, use integers only");
                    return false;
                }
            }
            return true;
        }
        /// <summary>
        /// Метод для ввода данных с проверкой.
        /// </summary>
        /// <returns>Если будут обнаружены любые символы кроме чисел - вернёт 0, иначе вернёт число.</returns>
        static int InputDataNotCutChar()
        {
            bool isNumber;
            string input;
            int data;
            input = Console.ReadLine();
            if (OnlyNumber(input) == false)
            {
                return 0;
            }
            isNumber = Int32.TryParse(input, out data);
            return data;
        }

        /// <summary>
        /// Метод для вывода ошибок
        /// </summary>
        static void PrintError()
        {
            Console.ForegroundColor = ConsoleColor.Red;
            foreach (var Error in ERRORS)
            {
                Console.WriteLine(Error);
            }
            Console.ResetColor();
            ERRORS.Clear();
        }
        /// <summary>
        /// Проверка, есть ли записи в список ошибок
        /// </summary>
        /// <returns></returns>
        static bool CheckIfThereAreErrors()
        {
            if (ERRORS.Count != 0)
            {
                PrintError();
                Console.ReadLine();
                return true;
            }
            else
            {
                return false;
            }
        }

        static void infoProgram()
        {
            Console.Clear();
            Console.WriteLine("Традиционно 2 варианта.");
            Console.WriteLine("1 Способ принимает данные в формате координат, для точки, и двух точек формирующих прямую.");
            Console.WriteLine("вычитая расстояние от точки до плоскости прямой, берёт результат по модулю");
            Console.WriteLine("ВНИМАНИЕ! пака корректно не считает расстояния до прямой расположеной диагонально (считает только перпендикулярные осям)");
            Console.WriteLine("2 Способ принимает данные в формате координат для точки и квадратного уравнения для прямой");
            Console.WriteLine("Расстояние от точки до прямой считает по формуле:");
            Console.WriteLine("|Ax+By+C|\n" +
                              "—————————— = 0\n" +
                              "√(a^2+b^2)");
            Console.WriteLine("Значение переменных, и знаки в квадратичной формуле вводяться отдельно, и могут быть только \'+\' и \'-\'");
        }
    }
}
