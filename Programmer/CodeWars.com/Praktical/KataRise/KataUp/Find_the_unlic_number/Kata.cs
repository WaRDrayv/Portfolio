using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

namespace Find_the_unlic_number
{
    public class Kata
    {
        public static int GetUnique(IEnumerable<int> numbers)
        {
            IEnumerator entryNumbers = numbers.GetEnumerator();//Получаем Енумираторы
            entryNumbers.MoveNext();//Двигаем "каретку" на элемент, в данном случае на первый
            int unic = (int)entryNumbers.Current;//Присваиваем текущее значение. Сейчас это 1 элемент колекции
            int temp = 0;//Переменная пара для уник
            int unicCount = 0, tempCount = 0;//Счётчикки для подсчёта повторений аналогичного значения для уник и темп
            while (entryNumbers.MoveNext())//Цикл, двигает указатель на элемент, и работает, пака есть куда двигать (пака условие true)
            {
                //Смысл в том, что мы подситываем количество совпадений в уник или темп, и там где меньше, то и возвращяем. 
                if (unic != (int) entryNumbers.Current)
                {
                    temp = (int) entryNumbers.Current;
                    tempCount++;
                }
                else
                {
                    unicCount++;
                }
            }
            int result = unicCount > tempCount ? temp : unic;
            return result ;
        }
        
    }
}
