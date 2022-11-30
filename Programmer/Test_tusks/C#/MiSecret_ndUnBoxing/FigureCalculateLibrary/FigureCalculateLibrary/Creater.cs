using FigureCalculateLibrary.MathObjects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FigureCalculateLibrary
{
    /// <summary>
    /// Фабрика
    /// </summary>
    static public class Creater 
    {
        public enum FigureType
        {
            circle,
            triangle
        }

    static public MathObjects.Figure Figure(FigureType type, int radius_a, int b = 0, int c = 0) =>
        type switch
        {
            FigureType.circle => new Circle(radius_a),
            FigureType.triangle => new Triangle (radius_a, b, c),
            _ => throw new NotImplementedException()
        };
    }
}
