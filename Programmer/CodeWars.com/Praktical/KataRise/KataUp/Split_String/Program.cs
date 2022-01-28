using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;


namespace Split_String
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            PrintArr(Solution("abacffddg"));
            PrintArr(UseList.Solution("esddffs"));
        }
        
        public static string[] Solution(string str)
        {
            
           // double temp = (double)str.Length / 2; //Для работы Math.Celiling() ибо почему то str.Length / 2 не работает.
            int arrNum = (int)Math.Ceiling((double)str.Length / 2);//Закастил всё что мог, теперь работает. Округляем строго в большую сторону, 
                                                                   //для того что б получить нудное число элементов в массиве .
            string[] splitedResult = new string[arrNum];//Инициализируем массив с arrNum элементов.
            if (str.Length % 2 == 1)//Если кол-во элементов не чётное.
            {
                string new_str = str + "_"; //Прибавим строку, чтоб на конце например a имело вид a_
                int iterator = 0;//Указатель на элемент в массиве, в который записываем разделённые строки
                for (int i = 0; i < str.Length; i += 2)//Двигаем указатель по строке на 2 символа
                {
                    splitedResult[iterator] = new_str.Substring(i, 2);//В элемент номер iterator добавляем элемент строки i и i+1
                    iterator++;//Увилечение счётчика
                }
            }
            else
            {//то же самое что и выше, но не прибовляем в конец строки символ "_"
                int iterator = 0;
                for (int i = 0; i < str.Length; i += 2)
                {
                    splitedResult[iterator] = str.Substring(i, 2);
                    iterator++;
                }
            }

            return splitedResult;//Возвращяем полученный массив
        }

        public static void PrintArr(string[] arr)//Метод для распичатки результатов
        {
            foreach (var index in arr)
            {
                Console.WriteLine(index);
                Console.WriteLine();
            }
        }
    }
}