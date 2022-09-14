// See https://aka.ms/new-console-template for more information

using InheritanceOfObjects;

public class TestInheritance
{
    public static void Main()
    {
        var testArrToTeacherAndStudents = IOData.SetPersonArray(3);
        IOData.PrintPerson(testArrToTeacherAndStudents);
    }
}