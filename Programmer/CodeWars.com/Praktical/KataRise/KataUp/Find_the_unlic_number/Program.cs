using System;

namespace Find_the_unlic_number
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            int[] test = new[] {1, 1, 1, 2, 1, 1},
                test3 = new[] {1, 2, 2, 2},
                test4 = new[] {-2, 2, 2, 2},
                test5 = new[] {11, 11, 14, 11, 11};
            double[] test2 = new[] { 0, 0, 0.55, 0, 0 };

            Console.WriteLine(Kata.GetUnique(test5));

            Console.WriteLine(LinQFind.GetUnique(test4));
            
        }
    }
}