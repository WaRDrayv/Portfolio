namespace ClassPersonStudentAndTeacher3;

public class Student : Person
{
    public void Stady()
    {
        Console.WriteLine("I'm studying");
    }

    public void ShowAge()
    {
        Console.WriteLine($"My age is: {age} years old");
    }
}