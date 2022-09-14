// See https://aka.ms/new-console-template for more information

using PhotoBookClass;

public class PhotoBookTest
{
    public static void Main()
    {
        var defaultPhotoBook = new PhotoBook();
        Console.WriteLine(defaultPhotoBook.GetNumberPages());

        var expandedPhotoBook = new PhotoBook(24);
        Console.WriteLine(expandedPhotoBook.GetNumberPages());

        var bigPhotoBook = new BigPhotoBook();
        Console.WriteLine(bigPhotoBook.GetNumberPages());
    }
}