// See https://aka.ms/new-console-template for more information


using Good_vs_Evil;

public class Kata
{
    //Good races
    const int Hobbits = 1,
        Elves = 3,
        Dwarves = 3,
        Eagles = 4;


    //Evil races
    const int Orcs = 1,
        Wargs = 2,
        Goblins = 2,
        Uruk_Hai = 3,
        Trolls = 5;

    //Global
    const int Man = 2,
        Wizzard = 10;

    static readonly int[] goodArmy =
    {
        1, 2, 3, 3, 4, 10
    };

    static readonly int[] evilArmy = 
    {
        1, 2, 2, 2, 3, 5, 10
    };

    public static void Main()
    {
        GoodVsEvil("1 1 1 1 1 1", "1 1 0 0 1 1");
        GoodVsEvil("1 1 1 1 1 1", "1 1 0 0 1 12");
    }
    
    public static string GoodVsEvil(string good, string evil)
    {
        //GvESimple gve = new GvESimple();
        string result;
        int goodPower = 0,
            evilPower = 0;
        
        goodPower = SumPowerArmy(SplitArmy(good));
        evilPower = SumPowerArmy(SplitArmy(evil));
        
        
        // Здесь начинаються костыли, что б вернуть начение для выполнения каты и вывести результат в IDE на ПК
        result = goodPower > evilPower ? "Battle Result: Good triumphs over Evil" :
            evilPower > goodPower ? "Battle Result: Evil eradicates all trace of Good" :
            "Battle Result: No victor on this battle field";

        Console.WriteLine(result);
        return result;
        //Console.WriteLine(gve.SumPowerAlt(good, evil));
        
        

        return "0";
    }

    static int[] SplitArmy(string army)
    {
        //var result = Array.ConvertAll(army.Split(" "), element => Convert.ToInt32(element));
        var result = StringToInt(army.Split(" "));
        return result;
    }

    static int SumPowerArmy(int [] army)
    {
        int armyPower = 0;
        if (army.Length == 6)
        {
            armyPower = PassArmy(army, goodArmy);
        }
        else if (army.Length == 7)
        {
            armyPower = PassArmy(army, evilArmy);
        }
        return armyPower;

    }

    static int PassArmy(int[] army, int[] sideArmy)
    {
        int armyPower = 0;
        int i = 0;
        foreach (var iteration in army)
        {
            armyPower += (iteration * sideArmy[i]);
            i++;
        }
        return armyPower;
    }

    static int[] StringToInt(string[] arr)
    {
        List<int> result = new List<int>();
        foreach (var iter in arr)
        {
            result.Add(Convert.ToInt32(iter));
            //result.Add(Int32.Parse(iter));
        }
        return result.ToArray();
    }
}

