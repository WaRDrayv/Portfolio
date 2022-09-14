using System;

namespace Expr4
{

    //Expr4.Найти количество чисел меньших N, которые имеют простые делители X или Y.

    class Program
    {
        

        static void Main(string[] args)
        {
            string input;
            double N, X, Y;
            Console.WriteLine("Use Only integer " +
                "numbers, all strings and characters will be set to zero");
            Console.WriteLine("Enter N");
            input = Console.ReadLine();
            bool isNumber = double.TryParse(input, out N);
            Console.WriteLine("Enter X");
            input = Console.ReadLine();
            isNumber = double.TryParse(input, out X);
            Console.WriteLine("Enter Y");
            input = Console.ReadLine();
            isNumber = double.TryParse(input, out Y);

            //Console.WriteLine("Enter N");
            //int N = Convert.ToInt32(Console.ReadLine());
            ////int N = Int32.Parse(Console.ReadLine());
            //Console.WriteLine("Enter X");
            //int X = Convert.ToInt32(Console.ReadLine());
            //Console.WriteLine("Enter Y");
            //int Y = Convert.ToInt32(Console.ReadLine());

            if (X <= 0 || Y <= 0)
            {
                Console.WriteLine("X and Y cannot be less than or equal to zero");
            }
            else
            {
            int result = (int)((N / X) + (N / Y) - (N / (X + Y)));
            Console.WriteLine($"Result is: {result} ");
            }
        }
        

        static bool IsInt(string chek)
        {
            bool result = false;
            foreach (var item in chek)
            {
                if (item <= 9 && item >= 0)
                {
                    result = true;
                }
                else
                {
                    result = false;
                    break;
                }
            }
            return result;
        }


    }
}
