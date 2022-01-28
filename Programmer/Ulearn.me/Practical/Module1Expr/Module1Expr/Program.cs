using System;
using System.Threading.Channels;

namespace Expr1
{
class Program
    {
        //БАГ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //Если выбрать 1 или 2, а потом ввести неверное число (которое не выполняет действий) мы вернёмся к начальному меню выбора
        //Если потом снова войти в 1 или 2, а потом нажать 3 (выход из программы), он выйдет из программы

        static public Tuple<string, string> StringSwitchForTuple(string a, string b) //Для строк используя кортежи
        {
            string c ;
            c = a;
            a = b;
            b = c;
            return Tuple.Create(a, b);
        }
        
        
        

        static private void LoadFunc()// функция выбора действий
        {
            Console.Clear();
            Console.WriteLine("1 - Take string metod");
            Console.WriteLine("2 - Take int metod");
            //           Console.WriteLine("3 - Take var metod (Beta)");
            //           Console.WriteLine("4 - Close program");
            Console.WriteLine("3 - Close program");
            Console.WriteLine("0 - задание");
            int type = int.Parse(Console.ReadLine()); // Переменная для выбора меню
            
            switch (type)// Первый Свитч
            {
                case 1:
                    Console.Clear();
                    Console.WriteLine("Take 1 metod use Temp variable C"); //стандартный, универсальный способ
                    Console.WriteLine("Take 2 metod use Tuple"); // используем возврат более одного результата через кортежи
                    int optionString = int.Parse(Console.ReadLine());
                    switch (optionString)//Свитч для стрингов ****************************************************
                    {
                        case 1: 
                            Console.WriteLine("Choose A variable : ");
                            string a = Console.ReadLine();

                            Console.WriteLine("Choose B variable");
                            string b = Console.ReadLine();

                            string c ;
                            
                            
                            c = a;
                            a = b;
                            b = c;

                            Console.WriteLine($"Now A is equal {a}, and B is equal {b}");
                            break;
                            
                        case 2 :
                            Console.WriteLine("Enter first A, then B variable");
                            Console.WriteLine($"Result, 1st A, 2nd B{StringSwitchForTuple(Console.ReadLine(), Console.ReadLine())}");
                            break;
                        default:
                            Console.WriteLine("incorrect input, please try again... ");
                            Console.ReadLine();
                            LoadFunc();
                            break;
                    }

                    
                    break;
                case 2:
                    Console.Clear();
                    Console.WriteLine("1 - Take metod use Temp variable C"); // хотел сделать без кортежей
                    Console.WriteLine("2 - Take metod for Math manipulation (without temp)"); // без метода, без особых причин
                    int optionInt = int.Parse(Console.ReadLine());
                    switch (optionInt)// Свитч для интов **********************************************************
                    {
                        case 1:
                            Console.WriteLine("Choose A variable : ");
                            int A = int.Parse(Console.ReadLine());
                            
                            Console.WriteLine("Choose B variable");
                            int B = int.Parse(Console.ReadLine());

                            int C ;
                            
                            
                            C = A;
                            A = B;
                            B = C;

                            Console.WriteLine($"Now A is equal {A}, and B is equal {B}");
                            break;
                        case 2:
                            Console.WriteLine("Choose A variable : ");
                            int a = int.Parse(Console.ReadLine()); //дада, глупый костыль, но пака так

                            Console.WriteLine("Choose B variable");
                            int b = int.Parse(Console.ReadLine()); //Кастыыыыль хД (мб это слишком громко сказано)

                            a += b;
                            b -= a;
                            b = -b;
                            a -= b;
                            
                            Console.WriteLine($"Now A is equal {a}, and B is equal {b}");
                            
                            break;
                        case 3:
                            break;
                        default:
                            Console.WriteLine("incorrect input, please try again... ");
                            Console.ReadLine();
                            LoadFunc();
                            break;
                    }
                    break;
                case 3:
                    Console.Clear();
                    return;
                    break;
                case  0:
                    Console.Clear();
                    Console.WriteLine("Задание ");
                    Console.WriteLine("Expr1. 1 Как поменять местами значения двух переменных? 2 Можно ли это сделать без ещё одной временной переменной. 3 Стоит ли так делать?");
                    Console.WriteLine("Овет ");
                    Console.WriteLine("1 Есть несколько способов. 2 Да. 3 Нет.");
                    Console.WriteLine("Мысли ");
                    Console.WriteLine("Существует несколько способов для выполнения этой задачи. Для числовых переменных без дополнительной переменной, точно да." +
                                      " Для текста не уверен. Думаю делать так не стоит, т.к. с текстом так делать нельзя (насколько мне известно), хотя возможно я чего-то не знаю" +
                                      "но и необходимости я в этом не вижу, может конечно для этого есть специфические задачи");
                    Console.WriteLine("Описание выполнения поставленной задачи");
                    Console.WriteLine("Для того чтоб поменять местами значения двух переменных числового типа, нужно провести 4 простых математических операций:");
                    Console.WriteLine("1 - a =a + b");
                    Console.WriteLine("2 - b = b - a");
                    Console.WriteLine("3 - b = -b");
                    Console.WriteLine("4 - a = a - b");
                    Console.WriteLine("Таким способом мы можем получить 2 переменные, значения которых поменяны местами. Этот способ реализован в программе" +
                                      "по пути =>2 (Take int metod) =>2 Take metod for Math manipulation (without temp)");
                    Console.WriteLine("Так же для удобства был реализован вход в этот метод прям из этого меню, нажмите 1 для его вызова, или 2 для версии с подробным разбором. 3 для выключения.");
                    int chekExp = int.Parse(Console.ReadLine());
                    switch (chekExp)
                    {
                        case 1:
                            Console.WriteLine("Введите переменные А и В последовотельно например: введите 5, нажмите ввод, введите 10, нажмите ввод");
                            MainTaskMetod(int.Parse(Console.ReadLine()), int.Parse(Console.ReadLine()));
                            break;
                        case 2:
                            Console.Clear();
                            Console.ForegroundColor = ConsoleColor.DarkGreen;
                            Console.WriteLine("Подробный метод изменения 2-х значений между двумя переменными ");
                            Console.ResetColor();
                            Console.WriteLine("Введите переменные А и В последовотельно например: введите 5, нажмите ввод, введите 10, нажмите ввод");
                            MainTaskMetodExtra(int.Parse(Console.ReadLine()), int.Parse(Console.ReadLine()));
                            break;
                        case 3:
                            Console.Clear();
                            return;
                            break;
                        default:
                            return;
                            break;
                    }
                    
                    break;
                default:
                    Console.WriteLine("incorrect input, please try again... ");
                    Console.ReadLine();
                    LoadFunc();
                    break;
                    
            } 
        }
        
        static void Main(string[] args)
        {
            LoadFunc();
            //return strings
            

            Console.WriteLine("Close Program, press Enter.");//работает конечно не так, как написано, но пака ладна.
                Console.ReadLine();
        }

        static void MainTaskMetod(int a, int b)
        {
            a += b;
            b -= a;
            b = -b;
            a -= b;
                            
            Console.WriteLine($"Now A is equal {a}, and B is equal {b}");
        }
        
        static void MainTaskMetodExtra(int a, int b)
        {
            Console.ForegroundColor = ConsoleColor.DarkGreen;
            Console.WriteLine($"Введены а = {a}, и b = {b}");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine("1 шаг a = a + b.");
            Console.ResetColor();
            Console.WriteLine($"a = {a} + {b}");
            a += b;
            Console.WriteLine($"a = {a}");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine("2 шаг b = b - a");
            Console.ResetColor();
            Console.WriteLine($"b = {b} - {a}");
            b -= a;
            Console.WriteLine($"b = {b}");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine("3 шаг b = -b");
            Console.ResetColor();
            Console.WriteLine($"b = -{b}");
            b = -b;
            Console.WriteLine($"b = {b}");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine("4 шаг a = a - b");
            Console.ResetColor();
            Console.WriteLine($"a = {a} - {b}");
            a -= b;
            Console.WriteLine($"a = {a}");
            Console.WriteLine();
                            
            Console.WriteLine($"Теперь a = {a}, и b = {b}. Переменные поменялись значениями");
            Console.WriteLine();
        }

    }
}
