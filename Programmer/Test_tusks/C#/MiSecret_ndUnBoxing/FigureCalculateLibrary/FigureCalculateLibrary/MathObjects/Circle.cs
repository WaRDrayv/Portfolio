using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FigureCalculateLibrary.MathObjects
{
    public class Circle : IGeometricShape
    {
        private const float _pi = 3.14f;
        private int _radius;
        [Range(1, 10000, ErrorMessage ="Радиус {0} может принимать значения от {1} до {2}.")]
        public int Radius 
        { 
            get => _radius;
            private set => _radius = value; 
        }


        public Circle (int radius)
        {
            Radius = radius;
        }

        public int GetArea() => 
            (int)(_pi * (_radius * _radius));
    }
}
