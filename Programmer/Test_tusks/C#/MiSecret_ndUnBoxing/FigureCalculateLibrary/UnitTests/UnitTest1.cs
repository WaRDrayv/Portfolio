using FigureCalculateLibrary;
using FigureCalculateLibrary.MathObjects;
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
            var result = Creater.Figure(Creater.FigureType.circle, 15).Square();
            //assert
            //Assert.AreEqual(expected, result);
            Assert.That(expected, Is.EqualTo(result));
        }

        [Test]
        public void FigureCircle_aNegative15_Return0()
        {
            var result = Creater.Figure(Creater.FigureType.circle, -15);
            var expected = 0;
            Assert.That(expected, Is.EqualTo(result.Square()));
        }

        [Test]
        public void TriangleSquare_a23b15c10_Return54()
        {
            var result = Creater.Figure(Creater.FigureType.triangle, 23, 15, 10).Square();
            var expected = 54;
            Assert.That(expected, Is.EqualTo(result));
        }

        [Test]
        public void TriangleSquare_a23bNegative15c10_Return0()
        {
            var result = Creater.Figure(Creater.FigureType.triangle, 23, -15, 10).Square();
            var expected = 0;
            Assert.That(expected, Is.EqualTo(result));
        }

        [Test]
        public void CheckPronounced_a25b17c15_ReturnTrue()
        {
            var result = Creater.Figure(Creater.FigureType.triangle, 25, 17, 15);
            var expected = true;
            Assert.That(expected, Is.EqualTo(((Triangle)result).isPronounced));
        }

        [Test]
        public void CheckPronounced_a305b15c15_ReturnFalse()
        {
            var result = Creater.Figure(Creater.FigureType.triangle, 305, 15, 15);
            var expected = false;
            Assert.That(expected, Is.EqualTo(((Triangle)result).isPronounced));
        }

        [Test]
        public void CheckForRectangularTriangle_a25b24c7_ReturnTrue()
        {
            var result = Creater.Figure(Creater.FigureType.triangle, 25, 24, 7);
            var expected = true;
            Assert.That(expected, Is.EqualTo(((Triangle)result).isRectangular));
        }

        [Test]
        public void CheckForRectangularTriangle_a23b15c10_ReturnFalse()
        {
            var result = Creater.Figure(Creater.FigureType.triangle, 23, 15, 10);
            var expected = false;
            Assert.That(expected, Is.EqualTo(((Triangle)result).isRectangular));
        }
    }
}