namespace InheritanceOfObjects;

public class Person
{
    protected string Name;

    public Person(string name)
    {
        Name = name;
    }


    public override string ToString()
    {
        return $"Hello! My name is {Name}";
    }
    
    ~Person() 
    {
        Name = string.Empty;
    }
}