using NUnit.Framework;

namespace UTSquare
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
            var result = SquareCalc.Square.Circle(15);
            //assert
            Assert.AreEqual(expected, result);
        }

        [Test]
        public void TriangleSquare_a23b15c10_Return54()
        {
            var result = SquareCalc.Square.Triangle(23, 15, 10);
            var expected = 54;
            Assert.AreEqual(expected, result);
        }

        [Test]
        public void CheckPronounced_a25b17c15_ReturnTrue()
        {
            var result = SquareCalc.Square.IsNotPronouncedTriangle(25, 17, 15);
            var expected = true;
            Assert.AreEqual(expected, result);
        }

        [Test]
        public void CheckPronounced_a305b15c15_ReturnFalse()
        {
            var result = SquareCalc.Square.IsNotPronouncedTriangle(305, 15, 15);
            var expected = false;
            Assert.AreEqual(expected, result);
        }

        [Test]
        public void CheckForRectangularTriangle_a25b24c7_ReturnTrue()
        {
            var result = SquareCalc.Square.IsRectangularTriangle(25, 24, 7);
            var expected = true;
            Assert.AreEqual(expected, result);
        }

        [Test]
        public void CheckForRectangularTriangle_a23b15c10_ReturnFalse()
        {
            var result = SquareCalc.Square.IsRectangularTriangle(23, 15, 10);
            var expected = false;
            Assert.AreEqual(expected, result);
        }

        [Test]
        public void FigureCircle_a15_Return706()
        {
            var result = SquareCalc.Square.Figure(15);
            var expected = 706;
            Assert.AreEqual(expected, result);
        }

        [Test]
        public void FigureTriangle_a23b15c10_Return706()
        {
            var result = SquareCalc.Square.Figure(23, 15, 10);
            var expected = 54;
            Assert.AreEqual(expected, result);
        }
    }
}