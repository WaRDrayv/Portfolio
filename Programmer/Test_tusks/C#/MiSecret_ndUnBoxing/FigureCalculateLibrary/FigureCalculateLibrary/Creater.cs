using FigureCalculateLibrary.MathObjects;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static FigureCalculateLibrary.Creater;

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

        static public IGeometricShape Figure(FigureType type, int radius_a, int b = 0, int c = 0)
        {
            switch (type)
            {
                case FigureType.circle:
                    var circle = new Circle(radius_a);
                    ValidateFigure(circle);
                    return circle;
                case FigureType.triangle:
					var triangle = new Triangle(radius_a, b, c);
					ValidateFigure(triangle);
					return triangle;
				default:
                    throw new NotImplementedException();
            }
        }

	    static public Shape ValidateFigure<Shape>(Shape figure)
	    {
		    var validationContext = new ValidationContext(figure, null, null);
            var validationResult = new List<ValidationResult>();

		    if(!Validator.TryValidateObject(figure, validationContext, validationResult, true))
            {
                throw new ValidationException(validationResult);
            }

		    return figure;
	    }
    }

}
