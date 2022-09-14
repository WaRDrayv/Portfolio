namespace ClassPersonStudentAndTeacher3;

public class Person
{
    private protected int age { get; set; }

    public void Greet()
    {
        Console.WriteLine("Hello!");
    }

    public void SetAge(int age)
    {
        this.age = age;
    }
}