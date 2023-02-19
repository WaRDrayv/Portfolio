using FigureCalculateLibrary;
using FigureCalculateLibrary.MathObjects;
using System.ComponentModel.DataAnnotations;

namespace UnitTests
{

    public class Tests
    {
        [SetUp]
        public void Setup()
        {

        }

        [Test]
        public void FindeCircleSquare_Radius15_Return706()
        {
            //arrange
            var expected = 706;
            //act
            var result = Creater.Figure(Creater.FigureType.circle, 15).GetArea();
            //assert
            //Assert.AreEqual(expected, result);
            Assert.That(expected, Is.EqualTo(result));
        }

		[Test]
		public void Circle_Radius10001_ReturnException()
		{
            var expectedErrors = new List<ValidationResult>() { new ValidationResult("Радиус Radius может принимать значения от 1 до 10000.") };
            List<ValidationResult> currentErrors = new List<ValidationResult>();
            try
            {
                Creater.Figure(Creater.FigureType.circle, 10001);
            }
            catch (ValidationException error)
            {
                currentErrors = error.ValidationResults;
            }
			
            Assert.That(expectedErrors.Select(item => item.ErrorMessage),
             Is.EqualTo(currentErrors.Select(item => item.ErrorMessage)));
		}

		[Test]
        public void TriangleSquare_a23_b15_c10_Return54()
        {
            var result = Creater.Figure(Creater.FigureType.triangle, 23, 15, 10).GetArea();
            var expected = 54;
            Assert.That(expected, Is.EqualTo(result));
        }

        [Test]
        public void TriangleSquare_a23_b10_cNegative15_ReturnException()
        {
            var expectedErrors = new List<ValidationResult>() { new ValidationResult("Сторона C может принимать значения от 1 до 10000.") };
            List<ValidationResult> currentErrors = new List<ValidationResult>();
            try
            {
                Creater.Figure(Creater.FigureType.triangle, 23, 10, -15);
            }
            catch (ValidationException error)
            {
                currentErrors= error.ValidationResults;
            }
            Assert.That(expectedErrors.Select(item => item.ErrorMessage),
             Is.EqualTo(currentErrors.Select(item => item.ErrorMessage)));
        }

        [Test]
        public void CheckPronounced_a25_b17_c15_ReturnTrue()
        {
            var result = Creater.Figure(Creater.FigureType.triangle, 25, 17, 15);
            var expected = true;
            Assert.That(expected, Is.EqualTo(((Triangle)result).IsPronounced));
        }

        [Test]
        public void CheckPronounced_a305_b15_c15_ReturnFalse()
        {
            var result = Creater.Figure(Creater.FigureType.triangle, 305, 15, 15);
            var expected = false;
            Assert.That(expected, Is.EqualTo(((Triangle)result).IsPronounced));
        }

        [Test]
        public void CheckForRectangularTriangle_a25_b24_c7_ReturnTrue()
        {
            var result = Creater.Figure(Creater.FigureType.triangle, 25, 24, 7);
            var expected = true;
            Assert.That(expected, Is.EqualTo(((Triangle)result).IsRectangular));
        }

        [Test]
        public void CheckForRectangularTriangle_a23_b15_c10_ReturnFalse()
        {
            var result = Creater.Figure(Creater.FigureType.triangle, 23, 15, 10);
            var expected = false;
            Assert.That(expected, Is.EqualTo(((Triangle)result).IsRectangular));
        }

        [Test]
		public void CircleValidationException_RadiusNegative15_ReturnExeption()
		{
            var expectedErrors = new List<ValidationResult>() { new ValidationResult("Радиус Radius может принимать значения от 1 до 10000.") };
			List<ValidationResult> currentErrors = new List<ValidationResult>();
			try
            {
                Creater.Figure(Creater.FigureType.circle, -15);
            }
            catch (ValidationException error)
            {
                currentErrors = error.ValidationResults;
            }
			
			Assert.That(currentErrors.Select(item => item.ErrorMessage),
             Is.EqualTo(expectedErrors.Select(item => item.ErrorMessage)));
		}

        [Test]
		public void TriangleValidationException_a0_bNegative15_с10_ReturnExeption()
		{
            var expectedErrors = new List<ValidationResult>(new[] { new ValidationResult("Сторона A может принимать значения от 1 до 10000."),
                                                                    new ValidationResult("Сторона B может принимать значения от 1 до 10000.")});
            List<ValidationResult> currentErrors = new List<ValidationResult>();
            try
            {
				Creater.Figure(Creater.FigureType.triangle, 0, -15, 10);
			}
            catch (ValidationException error)
            {
                currentErrors= error.ValidationResults;
            }
			Assert.That(currentErrors.Select(item => item.ErrorMessage),
             Is.EqualTo(expectedErrors.Select(item => item.ErrorMessage)));
		}
	}
}