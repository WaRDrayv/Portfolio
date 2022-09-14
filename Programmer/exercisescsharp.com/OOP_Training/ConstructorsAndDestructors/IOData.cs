namespace FirstClassAndMethod_ToString;

public static class IOData
{
    public static Person[] SetPersonArray(int arrSize)
    {
        //string namePerson;
        Person[] result = new Person[arrSize];
        for (int i = 0; i < arrSize; i++)
        {
            Console.WriteLine("Enter name Person");
            //namePerson = Console.ReadLine();
            //result[i] = new Person(namePerson);
            result[i] = new Person(Console.ReadLine());

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