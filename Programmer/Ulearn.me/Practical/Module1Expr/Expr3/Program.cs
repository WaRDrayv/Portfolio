namespace Expr3
{
    internal class Program
    {
        /*
         Expr3. Задано время Н часов (ровно). Вычислить угол в градусах между часовой и минутной
         стрелками. Например, 5 часов -> 150 градусов, 20 часов -> 120 градусов. Не использовать
         циклы.
         */
        const int hourMinetDistanse = 30;
        
        
        
        public static void Main(string[] args)
        {
            Test();
        }

        public static void Test()
        {
            for (int i = 0; i <= 24; i++)
                System.Console.WriteLine(DistanceBetweenArrows(i));

            System.Console.WriteLine("Programm is done!");
            System.Console.ReadKey();
        }

        public static int DistanceBetweenArrows(int hour)
        {
            int result = 0,
                negative = 0;

            if (hour >= 1 && hour <= 6 || hour >= 13 && hour <= 18)
            {
                result = (hour % 12) * hourMinetDistanse;
            }
            else if (hour >= 7 && hour <= 11 || hour >= 19 && hour <= 23)
            {
                negative = (hour % 6);
                result = ((hour % 12) - (negative * 2)) * hourMinetDistanse;
            }
            else if (hour == 12 || hour == 24 || hour == 0)
            {
                result = 0;
            }

            return result;
        }
    }
}