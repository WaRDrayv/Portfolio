namespace PhotoBookClass;

public class PhotoBook
{
    protected int numPages;

    // public PhotoBook()
    // {
    //     numPages = 16;
    // }

    public PhotoBook()
    {
        numPages = 16;
    }
    
    public PhotoBook(int page)
    {
        numPages = page;
    }

    public int GetNumberPages()
    {
        return numPages;
    }
}