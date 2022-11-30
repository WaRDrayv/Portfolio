using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FigureCalculateLibrary.MathObjects
{
    public class Circle : Figure
    {
        const float _pi = 3.14f;
        public int radius;

        //int radius { get { return _radius; } }

        public Circle (int radius)
        {
            this.radius = CheckingForNegative(radius);          
        }

        public override int Square() => (int)(_pi * (radius * radius));
    }
}
