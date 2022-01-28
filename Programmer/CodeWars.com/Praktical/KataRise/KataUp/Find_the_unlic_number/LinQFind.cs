using System.Collections.Generic;
using System.Linq;

namespace Find_the_unlic_number
{
    //Эту реализацию подсмотрел у профи. Гараздо локоничнее, да и познакомился немного с LinQ 
    public class LinQFind
    {
        public static int GetUnique(IEnumerable<int> numbers)
        {
            return numbers.GroupBy(x => x).Single(x => x.Count() == 1).Key;
        }
    }
}