using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ultra_Engine
{
    interface IEngine
    {
        public void Engine_Working();
        public void Load_Params(int I, int Toh, int Tenv, double Hm, double Hv, double C, int[] M, int[] V);
    }
}
