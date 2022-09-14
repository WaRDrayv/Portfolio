using InheritanceOfObjects;

namespace InheritanceOfObjects;

public static class IOData
{
    public static Person[] SetPersonArray(int arrSize)
    {

        Person[] result = new Person[arrSize];
        for (int i = 0; i < arrSize; i++)
        {
            if (i == 0)
            {
                Console.WriteLine("Enter Teacher name");
                result[i] = new Teacher(Console.ReadLine());
            }
            else
            {
                Console.WriteLine("Enter Student name");
                result[i] = new Student(Console.ReadLine());
            }
        }
        Console.WriteLine();
        return result;
    }

    public static void PrintPerson(Person[] input)
    {
        //Type whoAreYou;
        foreach (var person in input)
        {
            //Console.WriteLine(person.ToString());
            //whoAreYou = typeof(person);
            //var loc = person.GetType().ToString(); //Способ получить тип в формате Пространство_имён.Название_класса
            //if (person.GetType() == typeof(Student) ) // Легче, проверяем тип с типом студент (Ещё есть person == typeof(Student))
            if (person is Student) // Ещё легче, проверка является ли человек студентом
            {
                ((Student)person).Study();
            }
            else
            {
                ((Teacher)person).Explain();
            }
            //Console.WriteLine();
        }
    }
}