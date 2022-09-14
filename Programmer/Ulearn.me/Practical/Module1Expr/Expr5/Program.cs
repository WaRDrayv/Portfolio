using System;
using System.Collections.Generic;
namespace Expr5
{
    //Expr5. Найти количество високосных лет на отрезке [a, b] не используя циклы.
    class Program
    {
        static public List<string> ERRORS = new List<string>();
        static void Main(string[] args)
        {
            Menu(); // Вызываем меню программы
        }
        
        /// <summary>
        /// Метод для вывода меню программы
        /// </summary>
        static void Menu()
        {
            int option; // Это переменная для выбора пунктов меню
            string MethodResult; // Храним результаты работы методов
            while (true)
            {
                Console.ForegroundColor = ConsoleColor.DarkYellow; // Красивый вывод заголовка меню
                Console.WriteLine(@"      MENU      ");
                Console.ResetColor();
                Console.WriteLine("1 - Enter range data");
                Console.WriteLine("2 - Enter years");
                Console.WriteLine("3 - Programm info");
                Console.WriteLine("9 - Exite");

                option = InputDataNotCutChar(); // Выбираем пункт меню

                switch (option) // считываем наш выбор
                {
                    case 1:
                        MethodResult = LeapYearInRange(); // Вызываем метод, записываем его результат в переменную
                        if (CheckIfThereAreErrors() == false) // Проверяем, вызвал ли метод LeapYearInRange() ошибки
                        {
                            Console.WriteLine(MethodResult); //Если не вызвал, пишем результат
                        }
                        else
                        {
                            break;  // Если вызвал, метод проверки напишет что за ошибки были вызваны и снова вызовет меню
                        }
                        Console.ReadLine();
                        break;

                    case 2:
                        MethodResult = LeapYearInYears(); // Вызываем метод, записываем его результат в переменную
                        if (CheckIfThereAreErrors() == false) // Проверяем, вызвал ли метод LeapYearInRange() ошибки
                        {
                            Console.WriteLine(MethodResult); //Если не вызвал, пишем результат
                        }
                        else
                        {
                            break;  // Если вызвал, метод проверки напишет что за ошибки были вызваны и снова вызовет меню
                        }
                        Console.ReadLine();
                        break;

                    case 3:
                        InfoForProgramm();
                        Console.ReadLine();
                        break;

                    case 9:
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
        /// Метод для подсчёта количества високосных лет, при вводе произвольного диапозона лет целым числом.
        /// Он найдёт разницу между числами и подсчитает сколько в нём могло бы быть високосных лет.
        /// </summary>
        /// <returns>Строку в которой учтёт, что если был введена 1, то этот год мог быть високосным</returns>
        static string LeapYearInRange()
        {
            string result;
            Console.Clear();
            //Console.WriteLine("Enter lower range");
            Console.WriteLine("Enter number of years");
            int dataLower = InputDataNotCutChar();
            //Console.WriteLine("Enter upper range");
            //int dataUpper = InputDataNotIgnoreChar();
            
            //if (dataLower != 0 && dataUpper != 0) {
            //    if (dataLower < dataUpper)
            //    {
            //        result = $"Leap years from 1 to {(dataUpper - dataLower) / 4}";

            //    }
            //    else
            //    {
            //        ERRORS.Add("Error 03. Wrong data: Lower range cannot be greater than upper range");
            //        result = "Error";
            //    }
            //}
            if (dataLower != 0)
            {
                result = $"Leap years from 1 to {dataLower / 4}";
            }
            else
            {
                ERRORS.Add("Error 02. Wrong data: Number can't be less or equal zero (0) ");
                result = "Error";
            }
            return result;
            

        }
        /// <summary>
        /// Метод для подсчёта високосных лет от года до года. Диапазон от 0 до 4500 лет.
        /// Если стартовый год високосный - он добавится к результату
        /// </summary>
        /// <returns></returns>
        static string LeapYearInYears()
        {
            string result;
            Console.Clear();
            Console.ForegroundColor = ConsoleColor.DarkBlue;
            Console.WriteLine("You can take only range for 0 to 4500 year!");
            Console.ResetColor();
            Console.WriteLine("Enter year to start");
            int yearStart = InputDataNotCutChar();
            Console.WriteLine("Enter year to end");
            int yearEnd = InputDataNotCutChar();

            if (yearStart > 0 && yearEnd > 0 && yearEnd < 4500 && yearStart < 4499)
            {
                if (yearStart < yearEnd)
                {
                    result = @$"Number of leap years: {((yearEnd - yearStart) / 4) + (yearStart % 4 == 0 ? 1 : 0)}";
                }
                else
                {
                    ERRORS.Add("Error 03. Wrong data: Start year cannot be greater than end year");
                    result = "Error";
                }
            }
            else
            {
                ERRORS.Add("Error 04. You can take only range for 0 to 4500 year!");
                result = "Error";
            }
            return result;
        }
        /// <summary>
        /// Проверяет на корректность введённые данные. 
        /// </summary>
        /// <returns>Если введены только числа - true, будут присутствовать другие символы - false</returns>
        static bool OnlyNumber(string input)
        {
            char[] target = input.ToCharArray();
            foreach( char Char in target)
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
        /// <summary>
        /// Вывод информации по программе
        /// </summary>
        static void InfoForProgramm()
        {
            Console.Clear();
            Console.WriteLine("Задание: Expr5. Найти количество високосных лет на отрезке [a, b] не используя циклы.");
            Console.WriteLine("Разделение 2 на метода по сути было чисто для того, что б указат 2 разных формата ввода, но с очень похожим смыслом,");
            Console.WriteLine("В последствии сделал 1 способ для ввода количество лет, среди которых он считает високосные - просто делит на 4 и");
            Console.WriteLine("пишет, что предположительно от 1 до результата, подсчитаного методом");
            Console.WriteLine("2 способ предназначен для подсчёта уже диапазона лет, от года к году, считает разницу, и это число он делит на 4,");
            Console.WriteLine("сюда так же входит год, который был введён стартовым, возможно он тоже високосный, потому его тоже добавляю в формулу.");
            Console.WriteLine("Выход из меню был сделан на цифру 9, т.к. при проверке символов, при их наличии метод вернёт 0");
        }
    }
}
