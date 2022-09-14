namespace Good_vs_Evil;

public class GvESimple
{
    static readonly int[] goodArmy =
    {
        1, 2, 3, 3, 4, 10
    };

    static readonly int[] evilArmy = 
    {
        1, 2, 2, 2, 3, 5, 10
    };
    
    public string SumPowerAlt(string good, string evil)
    {
        var evilQuantity = Array.ConvertAll(evil.Split(" "), element => Convert.ToInt32(element));
        var goodQuantity = Array.ConvertAll(good.Split(" "), element => Convert.ToInt32(element));
        //var goodQuantity = StringToInt(good.Split(" "));
        //var evilQuantity = StringToInt(evil.Split(" "));
        
        
        var goodArmyPower = 0;
        var evilArmyPower = 0;
        int i = 0;
        foreach (var goodTypeArmy in goodQuantity)
        {
            goodArmyPower += (goodTypeArmy * goodArmy[i]);
            i++;
        }

        i = 0;

        foreach (var evilTypeArmy in evilQuantity)
        {
            evilArmyPower += (evilTypeArmy * evilArmy[i]);
            i++;
        }

        return goodArmyPower > evilArmyPower ? "Battle Result: Good triumphs over Evil" :
            evilArmyPower > goodArmyPower ? "Battle Result: Evil eradicates all trace of Good" :
            "Battle Result: No victor on this battle field";

    }
    
    static int[] StringToInt(string[] arr)
    {
        List<int> result = new List<int>();
        foreach (var iter in arr)
        {
            //result.Add(Convert.ToInt32(iter));
            result.Add(Int32.Parse((string)iter));
        }
        return result.ToArray();
    }
    
}