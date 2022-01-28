using System.Collections.Generic;

namespace Split_String
{
    public static class UseList
    {//Чужая реализация, тут больше используются возможности платформы и языка.
        const int PAIR_LENGTH = 2;//Длинна пар.
        public static string[] Solution(string str)
        {
            if (str.Length % PAIR_LENGTH != 0)//Если сдлинна строки по мод от длинны пар не равна нулю.
                str += '_';//+ "_" в конце строки
            List<string> listOfPairs = new List<string>(str.Length / PAIR_LENGTH);//Длинна листа равна длинне строки / длинну пар.
            for (int i = 0; i < str.Length; i += PAIR_LENGTH)
            {
                listOfPairs.Add(str.Substring(i, PAIR_LENGTH));//Добавляем в лист результаты подстроки с i по 2 элемента
            }
            return listOfPairs.ToArray();
        } 
    }
}