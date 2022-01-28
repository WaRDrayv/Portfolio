using System;
using System.Threading.Channels;

namespace Expr2
{
    class Program
    {
        //Expr2. Задается натуральное трехзначное число (гарантируется, что трехзначное). Развернуть
        //его, т.е. получить трехзначное число, записанное теми же цифрами в обратном порядке


        static void LoadFunc()
        {
            
            //int number = 842;//debug solution
            //Console.Clear();
            Console.WriteLine("Enter a three-digit number. 100 <= number <= 999");
            int number = int.Parse(Console.ReadLine());
            if (number >= 100 & number <= 999)
            {
                int right, mid, left;
                
                right = number % 100 % 10; // Получаем правую часть, в дебаг числе (842) это 2
                mid = (number % 100 - right) / 10; // Получим среднюю в дебаге 4
                left = (number - mid - right) / 100; // Получим левую, в дебаге 8
                Console.WriteLine($"Revers number is : {right}{mid}{left}"); // Перевернём число обратно, меняя левую и правую, в дебаге 248
                
                Console.WriteLine();
                Console.WriteLine("Repeat? y/n");
                string repeat = Console.ReadLine();
                switch (repeat)
                {
                    case "y":
                        Console.Clear();
                        LoadFunc();
                        break;
                    case "n":
                        return;
                    default:
                        break;
                }
            }
            else
            {
                Console.WriteLine("incorrect number. 100 <= number <= 999");
                LoadFunc();
            }
            
        }
        
        static void Main(string[] args)
        {
            Console.WriteLine("Expr2. Задается натуральное трёхзначное число (гарантируется, что трехзначное). Развернуть " +
                              "его, т.е. получить трехзначное число, записанное теми же цифрами в обратном порядке");
            LoadFunc();
            //Console.ReadKey();
        }
    }
}
