namespace FirstClassAndMethod_ToString;

public class Person
{
    public string Name { get; set; }

    public Person()
    {
        
    }
    public Person(string name)
    {
        Name = name;
    }

    public override string ToString()
    {
        return $"Hello! My name is {Name}";
    }
}