namespace InheritanceOfObjects;

public class Student : Person
{
    public Student(string name) : base(name)
    {
        Name = name;
    }

    public void Study()
    {
        Console.WriteLine("Study");
    }
}