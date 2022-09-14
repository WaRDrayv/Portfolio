namespace FirstClassAndMethod_ToString;

public static class IOData
{
    public static Person[] SetPersonArray(int arrSize)
    {

        Person[] result = new Person[arrSize];
        for (int i = 0; i < arrSize; i++)
        {
            Console.WriteLine("Enter name Person");

            result[i] = new Person() 
            {
                Name = Console.ReadLine()
            };
        }

        return result;
    }

    public static void PrintPerson(Person[] input)
    {
        foreach (var person in input)
        {
            Console.WriteLine(person.ToString());
        }
    }
}