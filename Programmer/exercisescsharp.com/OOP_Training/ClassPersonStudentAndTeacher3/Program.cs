// See https://aka.ms/new-console-template for more information

using ClassPersonStudentAndTeacher3;

public class StudentProfessorTest
{
    public static void Main()
    {
        var testPerson = new Person();
        testPerson.Greet();

        var testStudent = new Student();
        testStudent.SetAge(21);
        testStudent.Greet();
        testStudent.ShowAge();
        testStudent.Stady();

        var testProfessor = new Professor();
        testProfessor.SetAge(35);
        testProfessor.Greet();
        testProfessor.Explain();
    }
}