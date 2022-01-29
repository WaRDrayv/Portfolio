
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>


//----------------------------------------------------------------
// ������������
//----------------------------------------------------------------
//  ����������� ������
enum text_directions {HORIZ_DIR, VERT_DIR};

// ������������ ����� �������
enum font_names {DEFAULT_FONT, TRIPLEX_FONT, SMALL_FONT, SANS_SERIF_FONT, GOTHIC_FONT};

// ������������ ������  �����
enum line_styles{SOLID_LINE, DOTTED_LINE, CENTER_LINE, DASHED_LINE, NULL_LINE};

// ������ �����
enum line_width {NORM_WIDTH  = 1, THICK_WIDTH = 3 };

// �����
enum COLORS {BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
            DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
            LIGHTMAGENTA, YELLOW, WHITE,};

// ������������ ����� ����
enum { FULLSCREEN, FULLWINDOW, WINDOW};

//������� ��� ����������
enum fill_patterns {
    EMPTY_FILL,      // ������������ ���� ����
    SOLID_FILL,      // ������������ ���� ��������
    LINE_FILL,       // ---
    LTSLASH_FILL,    // ///
    SLASH_FILL,      // /// �������
    BKSLASH_FILL,    // "\\\" �������
    LTBKSLASH_FILL,  // "\\\"
    HATCH_FILL,      // light hatch fill
    XHATCH_FILL,     // Heavy cross hatch
    INTERLEAVE_FILL, // Interleaving line
    WIDE_DOT_FILL,   // Widely spaced dot
    CLOSE_DOT_FILL,  // Closely spaced dot
    USER_FILL        // User-defined fill
};

enum draw_message_codes {RESIZE = WM_USER, MOVETO, MOVEREL, CLEAR, CLEARPALETTE, SETBGCOLOR, SETCOLOR, PUTPIXEL,
LINE, LINEREL, LINETO, DRAWPOLY, CIRCLE, ARC, ELLIPSE, RECTANGLE, BAR, BAR3D, FILLPOLY, FILLELLIPSE, PIESLICE, SETFILLPATTERN,
SETTEXTSTYLE, OUTTEXT, OUTTEXTXY, SETFILLSTYLE, SETPALETTE, SETLINESTYLE, REPLY=65535};

struct draw_message {int p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;};

//----------------------------------------------------------------
// ���������
//----------------------------------------------------------------

// ������� ������ � ����
struct fillsettingstype { int pattern;  int color;};

// ������� ����� �����
struct linesettingstype {int linestyle; unsigned upattern; int thickness;};

// ���������� �����
struct pointtype {int x; int y ;};

// �����, ������ � ����� ����
struct arccoordstype {int x; int y; int xstart; int ystart; int xend; int yend;};

//  ������� ����������� �����
struct textsettingstype {int font; int direction; int charsize; int horiz; int  vert;};


//----------------------------------------------------------------
// ���������� �������� ������. settextstyle
LOGFONT lf  = {20, 0, 0, 0, FW_NORMAL, 0, 0, 0,
               DEFAULT_CHARSET,
               OUT_TT_ONLY_PRECIS,
               CLIP_DEFAULT_PRECIS,
               PROOF_QUALITY,
	       VARIABLE_PITCH | FF_DONTCARE, 0
              };
SIZE   size;



int color_256[256];
int color_16[16]= {RGB(  0,  0,  0),RGB(  0, 0, 255),RGB(  0,255,  0),RGB(  0,255,255),
                   RGB(255,  0,  0),RGB(255,  0,255),RGB(150, 75,  0),RGB(187,187,187),
                   RGB(128,128,128),RGB( 66,170,255),RGB(144,238,144),RGB(224,255,255),
                   RGB(255,153,153),RGB(255,119,255),RGB(255,255,  0),RGB(255,255,255)};

int color_16bk[16];
//----------------------------------------------------------------
//---------------------------------------------------------------

class Graph{
protected:
    HDC        hDC;      // ����� ��������� ����������
    HDC        hDCMem;   // ����� ��������� ������
    HBITMAP    hbitmap;  // ����� �����������
    HWND       hwnd;     // ����� ����
    HINSTANCE  hInst;    // ���������� ����������
    int        ScreenMaxX;
    int        ScreenMaxY;
    static int  nCounter;
    static int  nWidth;
    static int  nHeight;
    static char nMode;
    int         nShowMode;

public:
    Graph(const HWND&, const HINSTANCE&, int nShowMode = WINDOW);
    virtual ~Graph();

    virtual unsigned int getPixel(int, int     ) const;
    virtual int          maxWidth(             ) const {return nWidth;}
    virtual int          maxHigh (             ) const {return nHeight;}

    const HWND&      getHWND  (                   ) const;
    const HDC&       getHDC   (                   ) const;
    const HDC&       getHDCMem(                   ) const;
    const HINSTANCE& getHINST (                   ) const;
    void             flush    (                   ) const;
    };
// ---------------------------------------------------------------------
int  Graph::nCounter = 0;
int  Graph::nWidth  = 0;
int  Graph::nHeight = 0;
char Graph::nMode   = 0;

//----------------------------------------------------------------
//----------------------------------------------------------------
class WinGr:

public Graph {
private:
    HPEN          m_hPen[17];             // ����
    HBRUSH        m_hBrush[17];           // �����
    HBRUSH        m_hPatternBrush[13];    // ������� �����
    HFONT         m_hFont;                // ������� �����
    int           m_nForeground;          // ���� ���������
    int           m_nBackground;          // ���� ����
    int           m_nFillPattern;         // ������ ����������
    int           m_nFillColor;           // ����  ����������
    int           m_nLinePattern;         // ����� �����
    int           m_nFontID;               // id ������
    int           m_nFontSize;             // ������ ������
    int           m_nFontDirection;        // ����������� ������
    arccoordstype m_arc;                   // �������� ����
    int           m_nX;                    // ���������� �
    int           m_nY;                    // ���������� y
    short         m_nUserPattern[8];
    char          m_linestyle;
    int           m_nResult;

    const int  color16(const int&) const;
    HPEN        tmp_Pen;

public:
    WinGr(const HWND&, const HINSTANCE&, int nShowMode = WINDOW);
    virtual ~WinGr();             //����������
    virtual void         putPixel(int&, int&, int&);

    void       restore        (                                         );
    void       line           (int, int, int, int, int                  );
    void       moveTo         (int, int                                 );
    void       moveRel        (int, int                                 );
    void       lineTo         (int, int, int                            );
    void       lineRel        (int, int, int                            );
    void       circle         (int, int, int, int                       );
    void       fillEllipse    (int, int, int, int, int                  );
    void       ellipse        (int, int, int, int, int                  );
    void       arc            (int, int, int, int, int, int, int,int,int);
    void       pieSlice       (int, int, int, int, int, int, int,int,int);
    void       rectangle      (int, int, int, int, int                  );
    void       bar            (int, int, int, int                       );
    void       bar3D          (int, int, int, int, int, int, int        );
    void       drawPoly       (int, int*, int                           );
    void       fillPoly       (int, int*, int                           );
    void       setForeground  (int                                      );
    void       setBackground  (int                                      );
    int        getForeground  (                                         );
    int        getBackground  (                                         );
    const int& getX           (                                         ) const;
    const int& getY           (                                         ) const;
    void       clearScreen    (                                         );
    void       setFillStyle   (const int&, const int&                   );
    void       setFillPattern (char const*, const int&                  );
    void       getFillPattern (char* const                              ) const;
    void       getFillSettings(fillsettingstype* const                  ) const;
    void       setTextStyle   (const int&, const int&, const int&       );
    void       drawText       (const int&, const int&, const char*, int );
    void       drawText       (const char*, int                         );
    void       setSize        (int,   int                               );
    void       setPalette     (int , int                                );
    void       setAllpalette  (struct palettetype*                      );
    void       clearPalette   (                                         );
    void       setLinestyle   (int                                      );

};


// ---------------------------------------------------------------------
Graph::Graph(const HWND&      hwnd,
             const HINSTANCE& hInst,
             int    nShowMode /*=WINDOW*/
             )
             :hwnd(hwnd) ,hInst(hInst),nShowMode(nShowMode)

{
    HBRUSH     hbrush;

    ScreenMaxX = ::GetSystemMetrics(SM_CXSCREEN);
    ScreenMaxY = ::GetSystemMetrics(SM_CYSCREEN);

    if (nCounter) { throw "---"; }
    nCounter++;

    nHeight  = 480;
    nWidth = 640;
    switch (nShowMode) {
        case FULLSCREEN: hDC = ::GetWindowDC(hwnd);
                         nWidth = ScreenMaxX;
                         nHeight  = ScreenMaxY;
                         ::SetWindowPos(hwnd, HWND_TOP,
                                        ScreenMaxX / 2 - nWidth / 2,
                                        ScreenMaxY / 2 - nHeight / 2,
                                        nWidth, nHeight, SWP_SHOWWINDOW );
                         break;

        case FULLWINDOW: hDC = ::GetWindowDC(hwnd);
                         ::SetWindowPos(hwnd, HWND_TOP,
                                        ScreenMaxX / 2 - nWidth / 2,
                                        ScreenMaxY / 2 - nHeight / 2,
                                        nWidth, nHeight, SWP_SHOWWINDOW );
                         break;

        default        : hDC = ::GetDC(hwnd);
                         ::SetWindowPos(hwnd, HWND_TOP,
                                        ScreenMaxX / 2 - nWidth / 2,
                                        ScreenMaxY / 2 - nHeight / 2,
                                        nWidth + 8, nHeight + 27, SWP_SHOWWINDOW );
    }
    hDCMem  = ::CreateCompatibleDC(hDC);
    hbitmap = ::CreateCompatibleBitmap(hDC, ScreenMaxX, ScreenMaxY );
    ::SelectObject(hDCMem, hbitmap);
    hbrush = (HBRUSH)::GetStockObject(WHITE_BRUSH);
    ::SelectObject(hDCMem, hbrush);
    ::PatBlt(hDCMem, 0,0, ScreenMaxX, ScreenMaxY, PATCOPY );
    ::DeleteObject(hbrush);
}

// ---------------------------------------------------------------------
// ����������
Graph::~Graph()
{
    nCounter--;
    ::ReleaseDC(hwnd, hDC);
    ::DeleteDC(hDCMem);
    ::DeleteObject(hbitmap);
}


// ��������� ���������
WinGr::WinGr(const HWND& hwnd, const HINSTANCE& hInst, int nShowMode )
                 : Graph(hwnd, hInst, nShowMode)
                 , m_nForeground(BLACK), m_nBackground(WHITE)
                 , m_nFillPattern(1)   , m_nFillColor(WHITE)
{

   // ������� ��� fillstyle.
    short nPatterns[12][8] = {
        {~0xFF, ~0xFF, ~0xFF, ~0xFF, ~0xFF, ~0xFF, ~0xFF, ~0xFF}, //SOLID_FILL
        {~0x00, ~0xFF, ~0xFF, ~0x00, ~0x00, ~0xFF, ~0xFF, ~0x00}, //LINE_FILL
        {~0x01, ~0x02, ~0x04, ~0x08, ~0x10, ~0x20, ~0x40, ~0x80}, //LTSLASH_FILL
        {~0xE1, ~0xC3, ~0x87, ~0x0F, ~0x1E, ~0x3C, ~0x78, ~0xF0}, //SLASH_FILL
        {~0xF0, ~0x78, ~0x3C, ~0x1E, ~0x0F, ~0x87, ~0xC3, ~0xE1}, //BKSLASH_FILL
        {~0x80, ~0x40, ~0x20, ~0x10, ~0x08, ~0x04, ~0x02, ~0x01}, //LTBKSLASH_FILL
        {~0x11, ~0x11, ~0x11, ~0xFF, ~0x11, ~0x11, ~0x11, ~0xFF}, //HATCH_FILL
        {~0x81, ~0x42, ~0x24, ~0x18, ~0x18, ~0x24, ~0x42, ~0x81}, //XHATCH_FILL
        {~0x55, ~0xAA, ~0x55, ~0xAA, ~0x55, ~0xAA, ~0x55, ~0xAA}, //INTERLEAVE_FILL
        {~0x00, ~0x10, ~0x00, ~0x01, ~0x00, ~0x10, ~0x00, ~0x01}, //WIDE_DOT_FILL
        {~0x44, ~0x00, ~0x11, ~0x00, ~0x44, ~0x00, ~0x11, ~0x00}, //CLOSE_DOT_FILL
        {~0x44, ~0x00, ~0x11, ~0x00, ~0x44, ~0x00, ~0x11, ~0x00}  //USER_FILL
    };

    register int i;
    m_linestyle = PS_SOLID;
    m_nFillPattern = 3;
    m_nFillColor   = 4;


    //������� ����� � �������� Bitmap.
    for (i = 1; i < 13; ++i)
        {                   //������� ��p�� ��� ������. ������, ������, planes, bitCount, ��������� �������� ����� ���
        m_hPatternBrush[i]= ::CreatePatternBrush(::CreateBitmap(8, 8, 1, 1, nPatterns[i - 1]));
        }
    m_hPatternBrush[0]  = (HBRUSH)::GetStockObject(NULL_BRUSH);

    // �������� ������� ������ � ������
    for (i = WHITE + 1; --i >= BLACK;)
        {
        m_hPen[i]   = ::CreatePen(PS_SOLID, 1, color16(i));
        m_hBrush[i] = ::CreateSolidBrush(color16(i));
        color_16bk[i] = color_16[i];
        }
    m_hPen[16]   = ::CreatePen(PS_NULL, 1, 0);
    m_hBrush[16] = (HBRUSH)::GetStockObject(NULL_BRUSH);

      for (register int i = 360; --i >= 0; ) { // Lookuptabeles initialisieren
    }
    //p����, ��p���������, ������ �� ����p���� GDI ������� ������������ ����� ����
    //��p�� p��������� ������
    ::SetBkMode(hDC, TRANSPARENT);

};


// ----------------------------------------------------------------------
WinGr::~WinGr()
{
    for(register int i = WHITE + 2; --i >= BLACK;) {
        ::DeleteObject(m_hPen[i]);
        ::DeleteObject(m_hBrush[i]);
    }
}


// ----------------------------------------------------------------------
void WinGr::restore()
{
    m_nForeground  = BLACK;         // ���� �������
    m_nBackground  = WHITE;         // ���� ����
    m_nFillPattern = 1;             // ����� �������
    m_nFillColor   = WHITE;         // ���� �������
    SetBkMode(hDC, TRANSPARENT);

    }




// ----------------------------------------------------------------------
const int WinGr::color16(const int& nColor) const
{
    int nTemp;
    switch(nColor) {
        case  0: nTemp = RGB(0  , 0  , 0  ); break; // ������
        case  1: nTemp = RGB(0  , 0  , 255); break; // �����
        case  2: nTemp = RGB(0  , 255, 0  ); break; // �������
        case  3: nTemp = RGB(0  , 255, 255); break; // �������
        case  4: nTemp = RGB(255, 0  , 0  ); break; // �������
        case  5: nTemp = RGB(255, 0  , 255); break; // ���������
        case  6: nTemp = RGB(150, 75 , 0  ); break; // ����������
        case  7: nTemp = RGB(187, 187, 187); break; // ������-�����
        case  8: nTemp = RGB(128, 128, 128); break; // �����
        case  9: nTemp = RGB(66 , 170  , 255); break; // ������-�����

        case 10: nTemp = RGB(144, 238, 144); break; // light green
        case 11: nTemp = RGB(224, 255, 255); break; // light cyan
        case 12: nTemp = RGB(255, 153, 153); break; // light red
        case 13: nTemp = RGB(255, 119, 255); break; // light magenta

        case 14: nTemp = RGB(255, 255, 0  ); break; // ������
        case 15: nTemp = RGB(255, 255, 255); break; // �����
        default: nTemp = RGB(0  , 0  , 0  ); break;
    }
    return nTemp;
}

// ----------------------------------------------------------------------
// ���� ��������, ��������
void WinGr::setForeground(int nColor)
{
    m_nForeground = nColor;

    #ifdef MAXCOLOR16
    if (nColor < 0 || nColor >= 16)  { m_nForeground = 0; }
    #elif defined(MAXCOLOR256)
    if (nColor < 0 || nColor >= 256) { m_nForeground = 0; }
    #endif

}


// ----------------------------------------------------------------------
// ���� ����
void WinGr::setBackground(int nColor)
{
    m_nBackground = nColor;
    #ifdef MAXCOLOR16
    if (nColor < 0 || nColor >= 16)  m_nBackground = 15;
    #elif  defined(MAXCOLOR256)
    if (nColor < 0 || nColor >= 256)  m_nBackground = 255;
    #endif

}

// ----------------------------------------------------------------------
// ��������� �������
void WinGr::setPalette(int colornum, int color)
{
    colornum, color;
    #ifdef MAXCOLOR16
    if (colornum > -1 || colornum <16)  color_16[colornum] = color;
    #elif  defined(MAXCOLOR256)
    if (colornum > -1 || colornum <256) color_256[colornum] = color;
    #endif
}

// ----------------------------------------------------------------------
// ����� ��������� �����
void WinGr::setLinestyle(int num)

{
  m_linestyle = num;
}

// ----------------------------------------------------------------------
// ������� ����
int WinGr::getForeground()
{
    return m_nForeground;
}

// ----------------------------------------------------------------------
// ������� ���� ����
int WinGr::getBackground()
{
    return m_nBackground;
}

// ----------------------------------------------------------------------
// ��������� �������
void WinGr::putPixel(int& nX, int& nY, int& nZ)
{
    #ifdef MAXCOLOR16
    if (nZ < 0 || nZ > 15)  nZ=0;
    ::SetPixel(hDCMem, nX, nY, color_16[nZ]);
    #elif defined (MAXCOLOR256)
     if (nZ < 0 || nZ >= 256)  nZ=0;
    ::SetPixel(hDCMem, nX, nY, color_256[nZ]);
     #elif defined (MAXCOLORTC)
    ::SetPixel(hDCMem, nX, nY, nZ);
    #endif
}

// ----------------------------------------------------------------------
// ����������
void WinGr::circle(int nX, int nY, int nR, int color)
{
    #ifdef MAXCOLOR16
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[color]);
    #elif defined(MAXCOLOR256)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[color]);
    #elif defined(MAXCOLORTC)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, m_nForeground);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color);
    #endif

    ::SelectObject(hDCMem, tmp_Pen);
    ::Ellipse(hDCMem, nX - nR, nY - nR, nX + nR, nY + nR);
}



// ----------------------------------------------------------------------
// ������ � ����������� ������ �����.
void WinGr::pieSlice( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int color)
{

    #ifdef MAXCOLOR16
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[color]);
    ::SetTextColor(hDCMem, color_16[m_nFillColor]);
    ::SetBkColor  (hDCMem, color_16[m_nBackground]);

    #elif defined(MAXCOLOR256)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[color]);
    ::SetTextColor(hDCMem, color_256[m_nFillColor]);
    ::SetBkColor  (hDCMem, color_256[m_nBackground]);

    #elif defined(MAXCOLORTC)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, m_nForeground);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color);
    ::SetTextColor(hDCMem, m_nFillColor);
    ::SetBkColor  (hDCMem, m_nBackground);
    #endif

    ::SelectObject(hDCMem, tmp_Pen);
    ::SelectObject(hDCMem, m_hPatternBrush[m_nFillPattern]);
    ::Pie(hDCMem,   x1,  y1, x2,  y2,  x3,  y3,  x4, y4 );
}

// ----------------------------------------------------------------------
// ������ ���� ����������.
void WinGr::arc(int left, int top, int right, int bottom, int x1, int y1, int x2, int y2, int color)
{

    #ifdef MAXCOLOR16
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[color]);
    #elif defined(MAXCOLOR256)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[color]);
    #elif defined(MAXCOLORTC)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, m_nForeground);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color);
    #endif



    ::SetBkColor(hDCMem, color_16[WHITE]);
    ::SelectObject(hDCMem, tmp_Pen);
    ::SelectObject(hDCMem, m_hBrush[16]);
    ::Arc(hDCMem, left, top, right, bottom, x1, y1, x2, y2);
}

// ----------------------------------------------------------------------
// ����������� ������
void WinGr::fillEllipse(int nX, int nY, int nXRadius, int nYRadius, int color)
{
    #ifdef MAXCOLOR16
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[color]);
    ::SetTextColor(hDCMem, color_16[m_nFillColor]);
    ::SetBkColor(hDCMem, color_16[m_nBackground]);

    #elif defined(MAXCOLOR256)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[color]);
    ::SetTextColor(hDCMem, color_256[m_nFillColor]);
    ::SetBkColor(hDCMem, color_256[m_nBackground]);

    #elif defined(MAXCOLORTC)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, m_nForeground);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color);
    ::SetTextColor(hDCMem, m_nFillColor);
    ::SetBkColor(hDCMem, m_nBackground);
    #endif

    ::SelectObject(hDCMem, tmp_Pen);
    ::SelectObject(hDCMem, m_hPatternBrush[m_nFillPattern]);
    ::Ellipse(hDCMem, nX - nXRadius, nY - nYRadius,  nX + nXRadius, nY + nYRadius );
}

// ----------------------------------------------------------------------
// ������
void WinGr::ellipse(int nX, int nY, int nXRadius, int nYRadius, int color)
{
    #ifdef MAXCOLOR16
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[color]);
    #elif defined(MAXCOLOR256)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[color]);
    #elif defined(MAXCOLORTC)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, m_nForeground);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color);
    #endif
    ::SelectObject(hDCMem, tmp_Pen);
    ::SelectObject(hDCMem, m_hBrush[16]);
    ::Ellipse(hDCMem, nX - nXRadius, nY - nYRadius,  nX + nXRadius, nY + nYRadius );
}

// ----------------------------------------------------------------------
void WinGr::rectangle(int nLeft,  int nTop,  int nRight, int nBottom, int color)
{
    #ifdef MAXCOLOR16
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[color]);
    #elif defined(MAXCOLOR256)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[color]);
    #elif defined(MAXCOLORTC)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, m_nForeground);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color);
    #endif

    ::SetBkColor(hDCMem, color_16[WHITE]);
    ::SelectObject(hDCMem, tmp_Pen);
    ::SelectObject(hDCMem, m_hBrush[16]);
    ::Rectangle(hDCMem, nLeft, nTop, nRight, nBottom);
}

// ----------------------------------------------------------------------
void WinGr::bar3D(int nLeft,  int nTop, int nRight, int nBottom, int nDepth, int nTopFlag, int color)
{
    POINT pts[11];
    int   nDY     = (int)((sin(0.5) / cos(0.5)) * nDepth);

    pts[0].x = pts[1].x = pts[4].x = pts[7].x = nRight;
    pts[2].x = pts[3].x                       = nLeft;
    pts[5].x = pts[6].x                       = nRight + nDepth;
    pts[0].y = pts[3].y = pts[4].y            = nBottom;
    pts[1].y = pts[2].y = pts[7].y            = nTop;
    pts[5].y                                  = nBottom - nDY;
    pts[6].y                                  = nTop - nDY;
    
    if (nTopFlag) {
        pts[8].x             = nRight + nDepth;
        pts[9].x             = nLeft + nDepth;
        pts[10].x            = nLeft;
        pts[8].y  = pts[9].y = nTop - nDY;
        pts[10].y            = nTop;
    }
    bar(nLeft, nTop, nRight, nBottom);

    #ifdef MAXCOLOR16
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[color]);
    #elif defined(MAXCOLOR256)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[color]);
    #elif defined(MAXCOLORTC)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, m_nForeground);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color);
    #endif

    ::SetBkColor(hDCMem, color_16[WHITE]);
    ::SelectObject(hDCMem, tmp_Pen);
    ::Polyline(hDCMem, pts, nTopFlag ? 11 : 8);
}

// ----------------------------------------------------------------------
//   ������ ��������� �������������.
void WinGr::bar(int nLeft, int nTop, int nRight, int nBottom)
{
    RECT rect;
    rect.left   = nLeft;
    rect.right  = nRight;
    rect.top    = nTop;
    rect.bottom = nBottom;

    #ifdef MAXCOLOR16
    ::SetTextColor(hDCMem, color_16[m_nFillColor]);
    ::SetBkColor(hDCMem, color_16[m_nBackground]);
    #elif defined(MAXCOLOR256)
    ::SetTextColor(hDCMem, color_256[m_nFillColor]);
    ::SetBkColor(hDCMem, color_256[m_nBackground]);
    #elif defined(MAXCOLORTC)
    ::SetTextColor(hDCMem, m_nFillColor);
    ::SetBkColor(hDCMem, m_nBackground);
    #endif

    ::FillRect(hDCMem, &rect, m_hPatternBrush[m_nFillPattern]);
}

// ----------------------------------------------------------------------
void WinGr::line(int nX1, int nY1, int nX2, int nY2, int color)
{
    #ifdef MAXCOLOR16
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[color]);
    #elif defined(MAXCOLOR256)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[color]);
    #elif defined(MAXCOLORTC)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, m_nForeground);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color);
    #endif

    ::SelectObject(hDCMem, tmp_Pen);
    ::MoveToEx(hDCMem, nX1, nY1, NULL);
    ::LineTo(hDCMem, nX2, nY2);
}

// ----------------------------------------------------------------------
const int& WinGr::getX() const
{
    return m_nX;
}

// ----------------------------------------------------------------------
const int& WinGr::getY() const
{
    return m_nY;
}

// ----------------------------------------------------------------------
void WinGr::moveTo(int nX, int nY)
{
    m_nX = nX;   m_nY = nY;
}

// ----------------------------------------------------------------------
void WinGr::moveRel(int nDX, int nDY)
{
    m_nX += nDX;  m_nY += nDY;
}

// ----------------------------------------------------------------------
void WinGr::lineTo(int nX, int nY, int color)
{
    #ifdef MAXCOLOR16
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[color]);
    #elif defined(MAXCOLOR256)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[color]);
    #elif defined(MAXCOLORTC)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, m_nForeground);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color);
    #endif

    ::SelectObject(hDCMem, tmp_Pen);
    ::MoveToEx(hDCMem, m_nX, m_nY, NULL);
    ::LineTo(hDCMem, nX, nY);

    m_nX = nX;
    m_nY = nY;
}

// ----------------------------------------------------------------------
void WinGr::lineRel(int nDX, int nDY, int color)
{
    #ifdef MAXCOLOR16
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[color]);
    #elif defined(MAXCOLOR256)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[color]);
    #elif defined(MAXCOLORTC)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, m_nForeground);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color);
    #endif

    ::SelectObject(hDCMem, tmp_Pen);
    ::MoveToEx(hDCMem, m_nX, m_nY, NULL);
    ::LineTo(hDCMem, m_nX + nDX, m_nY + nDY);

    m_nX += nDX;
    m_nY += nDY;
}

// ----------------------------------------------------------------------
// ������ ������ ��������������.
void WinGr::drawPoly(int nPointsQuantity, int* pnPoints, int color)
{
    #ifdef MAXCOLOR16
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[color]);
    #elif defined(MAXCOLOR256)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[color]);
    #elif defined(MAXCOLORTC)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, m_nForeground);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color);
    #endif

    ::SetBkColor(hDCMem, color_16[WHITE]);
    ::SelectObject(hDCMem, tmp_Pen);
    ::Polyline(hDCMem, (POINT*)pnPoints, nPointsQuantity);
}

// ----------------------------------------------------------------------
void WinGr::fillPoly(int nPointsQuantity, int* pnPoints, int color)
{
    #ifdef MAXCOLOR16
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_16[color]);
    ::SetTextColor(hDCMem, color_16[m_nFillColor]);
    ::SetBkColor(hDCMem, color_16[m_nBackground]);

    #elif defined(MAXCOLOR256)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[m_nForeground]);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color_256[color]);
    ::SetTextColor(hDCMem, color_256[m_nFillColor]);
    ::SetBkColor(hDCMem, color_256[m_nBackground]);

    #elif defined(MAXCOLORTC)
    if (color == -1)   tmp_Pen  = ::CreatePen(m_linestyle, 1, m_nForeground);
    else               tmp_Pen  = ::CreatePen(m_linestyle, 1, color);
    ::SetTextColor(hDCMem, color_256[m_nFillColor]);
    ::SetBkColor(hDCMem, color_256[m_nBackground]);
    #endif

    ::SelectObject(hDCMem, tmp_Pen);
    ::SelectObject(hDCMem, m_hPatternBrush[m_nFillPattern]);
    ::Polygon(hDCMem, (POINT*)pnPoints, nPointsQuantity);
}


// ----------------------------------------------------------------------
// ������� ������
void WinGr::clearScreen()
{
    m_linestyle = PS_SOLID;
    m_nForeground  = BLACK;         // ���� �������
    m_nBackground  = WHITE;         // ���� ����
    m_nFillPattern = 1;             // ����� �������
    m_nFillColor   = WHITE;         // ���� �������
    SetBkMode(hDC, TRANSPARENT);

    tmp_Pen  = ::CreatePen(5, 1, 15);
    ::SelectObject(hDCMem, tmp_Pen);
    ::SelectObject(hDCMem, m_hBrush[15]);
    ::Rectangle(hDCMem, 0, 0, nWidth, nHeight);
    m_nX = m_nY = 0;

}

// ----------------------------------------------------------------------
// ����� �������
void WinGr::clearPalette()
{
    for (int i = WHITE + 1; --i >= BLACK;)
        {
        color_16[i] = color_16bk[i];
        }
}

// ----------------------------------------------------------------------
//   ������������� ������ � ���� ����������.
void WinGr::setFillStyle(const int& nPattern, const int& nColor)
{
    m_nFillPattern = nPattern;
    m_nFillColor   = nColor;
    #ifdef MAXCOLOR16
    if (nColor < 0 || nColor >= 16)  { m_nFillColor = 0; }
    #elif defined(MAXCOLOR256)
    if (nColor < 0 || nColor >= 256) { m_nFillColor = 0; }
    #endif

}

// ----------------------------------------------------------------------
// �������� ������������ ������������� ������ ��������.
void WinGr::setFillPattern(char const* cPattern, const int&  nColor )
{
    m_nFillPattern = USER_FILL;
    m_nFillColor   = nColor;
    #ifdef MAXCOLOR16
    if (nColor < 0 || nColor >= 16)  { m_nFillColor = 0; }
    #elif defined(MAXCOLOR256)
    if (nColor < 0 || nColor >= 256) { m_nFillColor = 0; }
    #endif
    //   if (nColor < 0 || nColor >= 16)     { m_nFillColor = BLACK;   }
    for (register int i = 8; --i >=0; ) { m_nUserPattern[i] = (short)~cPattern[i]; }

    ::DeleteObject(m_hPatternBrush[USER_FILL]);
    m_hPatternBrush[USER_FILL] =  ::CreatePatternBrush(CreateBitmap(8, 8, 1, 1, m_nUserPattern));
}

// ----------------------------------------------------------------------
void WinGr::getFillPattern(char* const pc) const
{
    for (register int i = 8; --i >= 0; ) {pc[i] = (char)~m_nUserPattern[i]; }
}

// ----------------------------------------------------------------------
void WinGr::getFillSettings(fillsettingstype* const fs) const
{
    fs->pattern = m_nFillPattern; 
    fs->color   = m_nFillColor;
}

// ----------------------------------------------------------------------
void WinGr::setTextStyle(const int& nFont, const int& nDirection, const int& nCharSize)
{
    nFont;
    switch (nDirection) {
        case HORIZ_DIR: lf.lfOrientation = 0;
                        lf.lfEscapement  = 0;
                        break;
        case VERT_DIR:  lf.lfOrientation = 900;
                        lf.lfEscapement  = 900;
                        break;
        default:        lf.lfOrientation = nDirection;
                        lf.lfEscapement  = nDirection;
    };

    lf.lfHeight      = nCharSize;
    m_hFont = ::CreateFontIndirect(&lf);
    ::SelectObject(hDCMem, m_hFont);
}

// ----------------------------------------------------------------------
// ����� ������ � ������� �����������
void WinGr::drawText(const int& nX, const int& nY, const char* psz, int color)
{
    #ifdef MAXCOLOR16
    if (color==-1)     ::SetTextColor(hDCMem, color_16[m_nForeground]);
    else               ::SetTextColor(hDCMem, color_16[color]);
    #elif defined(MAXCOLOR256)
    if (color==-1)     ::SetTextColor(hDCMem, color_256[m_nForeground]);
    else               ::SetTextColor(hDCMem, color_256[color]);
    #elif defined(MAXCOLORTC)
    if (color==-1)     ::SetTextColor(hDCMem, m_nForeground);
    else               ::SetTextColor(hDCMem, color);
    #endif
    ::TextOut(hDCMem, nX, nY, psz, strlen(psz));
}

// ----------------------------------------------------------------------
void WinGr::drawText(const char* psz, int color)
{
    drawText(m_nX, m_nY, psz, color);
}



// ---------------------------------------------------------------------
unsigned int Graph::getPixel(int nX, int nY) const
{
    return ::GetPixel(hDCMem, nX, nY);
}

// ---------------------------------------------------------------------
const HWND& Graph::getHWND() const
{
    return hwnd;
}

// ---------------------------------------------------------------------
const HDC& Graph::getHDC() const
{
    return hDC;
}

// ---------------------------------------------------------------------
const HDC& Graph::getHDCMem() const
{
    return hDCMem;
}

// ---------------------------------------------------------------------
const HINSTANCE& Graph::getHINST() const
{
    return hInst;
}

// ---------------------------------------------------------------------
// ������� ������ ������. ����� ���� ������������ ������
 void Graph::flush() const
{
    ::BitBlt(hDC, 0, 0, ScreenMaxX, ScreenMaxY, hDCMem, 0, 0, SRCCOPY);

}

// ----------------------------------------------------------------------
// ��������� ������� ����    */
void WinGr::setSize(int nX, int nY)
{
    nWidth  = nX;
    nHeight = nY;

   ::SetWindowPos(hwnd, HWND_TOP,                 // ���������� ���� � ������� ����������
                   ScreenMaxX / 2 - nWidth / 2,   // ������� ��-�����������
                   ScreenMaxY / 2 - nHeight / 2,  // ��-���������
                   nWidth + 8,                    // ������
                   nHeight + 27,                  // ������
                   SWP_SHOWWINDOW                 // ����������
                   );
}


#define main mainx
#define TITLE "Graphics Library 2.1 Thread-Safe"

WinGr* wg;

void main();


//----------------------------------------------------------------
//  �������� �����. �������� ����.
//----------------------------------------------------------------

DWORD Th(LPVOID param) // ����� ����
{
     param;
     wg->setSize(wg->maxWidth(), wg->maxHigh());
     main();
     wg->flush();
     return 0;
}
DWORD g_nMainThreadID;


//----------------------------------------------------------------
//��������� ��������� �������� ���� ����������
//----------------------------------------------------------------
long FAR PASCAL WindowProc(HWND hWnd ,UINT message, WPARAM wParam, LPARAM lParam )
{
   register draw_message *m = (draw_message*)lParam;
   switch (message)
   {
        case RESIZE:
                         wg->setSize(wParam, lParam);
                         break;
        case MOVETO:
                         wg->moveTo(wParam, lParam);
                         break;
        case MOVEREL:
                         wg->moveRel(wParam, lParam);
                         break;
        case CLEAR:
                         wg->clearScreen();
                         break;
        case CLEARPALETTE:
                         wg->clearPalette();
                         break;
        case SETBGCOLOR:
                         wg->setBackground(wParam);
                         break;
        case SETCOLOR:
                         wg->setForeground(wParam);
                         break;
/*
        case PUTPIXEL:
                         wg->putPixel(m->p1, m->p2, m->p3);
                         delete (m);
                         break;
*/
        case LINE:
                         wg->line(m->p1, m->p2, m->p3, m->p4, m->p5);
                         PostThreadMessage(wParam, REPLY, 0, 0);
                         break;
        case LINEREL:
                         wg->lineRel(m->p1, m->p2, m->p3);
                         PostThreadMessage(wParam, REPLY, 0, 0);
                         break;
        case LINETO:
                         wg->lineTo(m->p1, m->p2, m->p3);
                         PostThreadMessage(wParam, REPLY, 0, 0);
                         break;
        case DRAWPOLY:
                         wg->drawPoly(m->p1, (int*)m->p2, m->p3);
                         PostThreadMessage(wParam, REPLY, 0, 0);
                         break;
        case CIRCLE:
                         wg->circle(m->p1, m->p2, m->p3, m->p4);
                         PostThreadMessage(wParam, REPLY, 0, 0);
                         break;
        case ARC:
                         wg->arc(m->p1, m->p2, m->p3, m->p4, m->p5, m->p6, m->p7, m->p8, m->p9);
                         PostThreadMessage(wParam, REPLY, 0, 0);
                         break;
        case ELLIPSE:
                         wg->ellipse(m->p1, m->p2, m->p3, m->p4, m->p5);
                         PostThreadMessage(wParam, REPLY, 0, 0);
                         break;
        case RECTANGLE:
                         wg->rectangle(m->p1, m->p2, m->p3, m->p4, m->p5);
                         PostThreadMessage(wParam, REPLY, 0, 0);
                         break;
        case BAR:        wg->bar(m->p1, m->p2, m->p3, m->p4);
                         PostThreadMessage(wParam, REPLY, 0, 0);
                         break;
        case BAR3D:
                         wg->bar3D(m->p1, m->p2, m->p3, m->p4, m->p5, m->p6, m->p7);
                         PostThreadMessage(wParam, REPLY, 0, 0);
                         break;
        case FILLPOLY:
                         wg->fillPoly(m->p1, (int*)m->p2, m->p3);
                         PostThreadMessage(wParam, REPLY, 0, 0);
                         break;
        case FILLELLIPSE:
                         wg->fillEllipse(m->p1, m->p2, m->p3, m->p4, m->p5);
                         PostThreadMessage(wParam, REPLY, 0, 0);
                         break;
        case PIESLICE:
                         wg->pieSlice(m->p1, m->p2, m->p3, m->p4, m->p5, m->p6, m->p7, m->p8, m->p9);
                         PostThreadMessage(wParam, REPLY, 0, 0);
                         break;
        case SETFILLSTYLE:  
                         wg->setFillStyle(wParam, lParam);
                         break;
        case SETFILLPATTERN:
                         wg->setFillPattern((const char*)wParam, lParam);
                         PostThreadMessage(wParam, REPLY, 0, 0);
        case SETTEXTSTYLE:
                         wg->setTextStyle(m->p1, m->p2, m->p3);
                         PostThreadMessage(wParam, REPLY, 0, 0);
                         break;
        case OUTTEXT:
                         wg->drawText((const char*)wParam, lParam);
                         break;
        case OUTTEXTXY:
                         wg->drawText(m->p1, m->p2, (const char*)m->p3, m->p4);
                         PostThreadMessage(wParam, REPLY, 0, 0);
                         break;
        case SETPALETTE:
                         wg->setPalette(wParam, lParam);
                         break;
        case SETLINESTYLE:
                         wg->setLinestyle(wParam);
                         break;

        case WM_PAINT:   wg->flush();
                         break;
        case WM_DESTROY: PostQuitMessage(0);
                         break;
    }
   return DefWindowProc(hWnd, message, wParam, lParam);
}


//----------------------------------------------------------------
// ������� ����
//----------------------------------------------------------------
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR  lpCmdLine,  int  nShowCmd )
{
    hPrevInstance, lpCmdLine;
    HWND      hwnd;   // ������������� �������� ���� ����������
    WNDCLASS  wc;     // ��������� ��� ����������� ������ ����
    MSG       msg;    // ��������� ��� ������ � �����������

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WindowProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = "Menu_one";
    wc.lpszClassName = "NAME";

    //������������ �����
    if (!RegisterClass(&wc)) {return 0; };


    //������� ������� ���� ����������
    hwnd = CreateWindow("NAME",               // ��� ������ ����
                        TITLE,                // ��������� ����
                        WS_OVERLAPPEDWINDOW,  // ����� ����
                        CW_USEDEFAULT,        //�-�� � ������������ ��-���������
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        HWND_DESKTOP,          // ������������� ������������� ����
                        NULL,                  // ������������� ����
                        hInstance,             // ������������� ����������
                        NULL                   // ��� ���������
                       );


    wg = new WinGr(hwnd, hInstance, WINDOW);

    CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Th, (LPVOID)hwnd, 0,&g_nMainThreadID);

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    // ��������� ���� ��������� ���������
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}


// ----------------------------------------------------------------------
// �������� � �������������
void delay(unsigned int mlsec)
{
    PostMessage (wg->getHWND(), WM_PAINT, 0, 0);
    Sleep(mlsec);
}


// ----------------------------------------------------------------------
// ��������� �������� �������� ����
void resize (int nX, int nY)
{
    PostMessage (wg->getHWND(), RESIZE, nX, nY);
}


// ----------------------------------------------------------------------
//  ����. ������
int getmaxx()
{
    return wg->maxWidth();
}

// ----------------------------------------------------------------------
//  ����. ������
int getmaxy()
{
    return wg->maxHigh();
}


// ----------------------------------------------------------------------
//  �������� ��������� � �, y
void moveto(int x, int y)
{
    PostMessage (wg->getHWND(), MOVETO, x, y);
}


// ----------------------------------------------------------------------
// �������� ��������� �� x, y �� ��� ������� �������.
void moverel(int dx, int dy)
{
    PostMessage (wg->getHWND(), MOVEREL, dx, dy);
}

// ----------------------------------------------------------------------
// �������� ���������� �
int getx()
{
    return wg->getX();
}

// ----------------------------------------------------------------------
// �������� ���������� �
int gety()
{
    return wg->getY();
}


// ----------------------------------------------------------------------
// ������� ������
void clear()
{
    PostMessage (wg->getHWND(), CLEAR, 0, 0);
}

// ----------------------------------------------------------------------
// ����� �������
void clearpalette()
{
    PostMessage (wg->getHWND(), CLEARPALETTE, 0, 0);
}

// ----------------------------------------------------------------------
// ���������� ���� ����
void setbgcolor(int color)
{
    PostMessage (wg->getHWND(), SETBGCOLOR, color, 0);
}

// ----------------------------------------------------------------------
// �������� ���� ����
int getbgcolor()
{
    return wg->getBackground();
}

// ----------------------------------------------------------------------
// ���������� ���� ���������
void setcolor(int color)
{
    PostMessage (wg->getHWND(), SETCOLOR, color, 0);
}

// ----------------------------------------------------------------------
// �������� ������� ����
int getcolor()
{
    return wg->getForeground();
}


// ----------------------------------------------------------------------
// ���������� �������
void putpixel(int x,int y, int z)
{
    wg->putPixel(x, y, z);
}

// ----------------------------------------------------------------------
// ����� ����� ����� �������. ��������� �� ���������!
void line(int x1, int y1, int x2, int y2, int color = -1)
{
    register draw_message m;
	MSG R;
	m.p1 = x1, m.p2 = y1, m.p3 = x2, m.p4 = y2, m.p5 = color;
    PostMessage (wg->getHWND(), LINE, GetCurrentThreadId(), (LPARAM)&m);
    GetMessage (&R, 0, REPLY, REPLY);
}


// ----------------------------------------------------------------------
// ����� �� �������� ��������� � ����� x, y
void linerel(int dx, int dy, int color = -1)
{
    register draw_message m;
	MSG R;
	m.p1 = dx, m.p2 = dy, m.p3 = color;
    PostMessage (wg->getHWND(), LINEREL, GetCurrentThreadId(), (LPARAM)&m);
    GetMessage (&R, 0, REPLY, REPLY);
}

// ----------------------------------------------------------------------
void lineto(int x, int y, int color = -1)
{
    register draw_message m;
	MSG R;
	m.p1 = x, m.p2 = y, m.p3 = color;
    PostMessage (wg->getHWND(), LINETO, GetCurrentThreadId(), (LPARAM)&m);
    GetMessage (&R, 0, REPLY, REPLY);
}

// ----------------------------------------------------------------------
//  �������������
void drawpoly(int numpoints, int* polypoints, int color = -1)
{
    register draw_message m;
	MSG R;
	m.p1 = numpoints, m.p2 = (int)polypoints, m.p3 = color;
    PostMessage (wg->getHWND(), DRAWPOLY, GetCurrentThreadId(), (LPARAM)&m);
    GetMessage (&R, 0, REPLY, REPLY);
}

// ----------------------------------------------------------------------
// ����������
void circle(int x, int y, int radius, int color = -1)
{
    register draw_message m;
	MSG R;
	m.p1 = x, m.p2 = y, m.p3 = radius, m.p4 = color;
    PostMessage (wg->getHWND(), CIRCLE, GetCurrentThreadId(), (LPARAM)&m);
    GetMessage (&R, 0, REPLY, REPLY);
}

// ----------------------------------------------------------------------
// ����
void arc(int left, int top, int right, int bottom, int x1, int y1, int x2, int y2, int color = -1)
{
    register draw_message m;
	MSG R;
	m.p1 = left, m.p2 = top, m.p3 = right, m.p4 = bottom, m.p5 = x1, m.p6 = y1, m.p7 = x2, m.p8 = y2, m.p9 = color;
    PostMessage (wg->getHWND(), ARC, GetCurrentThreadId(), (LPARAM)&m);
    GetMessage (&R, 0, REPLY, REPLY);
}

// ----------------------------------------------------------------------
// �����
void ellipse(int x, int y, int xradius, int yradius, int color = -1)
{
    register draw_message m;
	MSG R;
	m.p1 = x, m.p2 = y, m.p3 = xradius, m.p4 = yradius, m.p5 = color;
    PostMessage (wg->getHWND(), ELLIPSE, GetCurrentThreadId(), (LPARAM)&m);
    GetMessage (&R, 0, REPLY, REPLY);
}


// ----------------------------------------------------------------------
//  ����������� �������������
void bar(int left, int top, int right, int bottom)
{
    register draw_message m;
	MSG R;
	m.p1 = left, m.p2 = top, m.p3 = right, m.p4 = bottom;
    PostMessage (wg->getHWND(), BAR, GetCurrentThreadId(), (LPARAM)&m);
    GetMessage (&R, 0, REPLY, REPLY);
}

// ----------------------------------------------------------------------
// �������������
void rectangle(int left, int top, int right, int bottom, int color = -1)
{
    register draw_message m;
	MSG R;
	m.p1 = left, m.p2 = top, m.p3 = right, m.p4 = bottom, m.p5 = color;
    PostMessage (wg->getHWND(), RECTANGLE, GetCurrentThreadId(), (LPARAM)&m);
    GetMessage (&R, 0, REPLY, REPLY);
}

// ----------------------------------------------------------------------
// ���������� �������
void bar3d(int left, int top, int right, int bottom, int depth, int topflag, int color = -1)
{
    register draw_message m;
	MSG R;
	m.p1 = left, m.p2 = top, m.p3 = right, m.p4 = bottom, m.p5 = depth, m.p6 = topflag, m.p7 = color;
    PostMessage (wg->getHWND(), BAR3D, GetCurrentThreadId(), (LPARAM)&m);
    GetMessage (&R, 0, REPLY, REPLY);
}

// ----------------------------------------------------------------------
//  ����������� �������������
void fillpoly(int numpoints, int* polypoints, int color = -1)
{
    register draw_message m;
	MSG R;
	m.p1 = numpoints, m.p2 = (int)polypoints, m.p3 = color;
    PostMessage (wg->getHWND(), FILLPOLY, GetCurrentThreadId(), (LPARAM)&m);
    GetMessage (&R, 0, REPLY, REPLY);
}

// ----------------------------------------------------------------------
// ����������� ������
void fillellipse(int x, int y, int xradius, int yradius, int color = -1)
{
    register draw_message m;
	MSG R;
	m.p1 = x, m.p2 = y, m.p3 = xradius, m.p4 = yradius, m.p5 = color;
    PostMessage (wg->getHWND(), FILLELLIPSE, GetCurrentThreadId(), (LPARAM)&m);
    GetMessage (&R, 0, REPLY, REPLY);
}

// ----------------------------------------------------------------------
//  ����������� ������ �����
void pieslice(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int color)
{
    register draw_message m;
	MSG R;
	m.p1 = x1, m.p2 = y1, m.p3 = x2, m.p4 = y2, m.p5 = x3, m.p6 = y3, m.p7 = x4, m.p8 = y4, m.p9 = color;
    PostMessage (wg->getHWND(), PIESLICE, GetCurrentThreadId(), (LPARAM)&m);
    GetMessage (&R, 0, REPLY, REPLY);
}



// ----------------------------------------------------------------------
// ������������� ������� ����  �  ������ ����������.
void setfillstyle(int pattern, int color)
{
    PostMessage (wg->getHWND(), SETFILLSTYLE, pattern, color);
}

// ----------------------------------------------------------------------
//  ������ ��������
void setfillpattern(const char *upattern, int color)
{
    PostMessage (wg->getHWND(), SETFILLPATTERN, (WPARAM)upattern, color);
}

// ----------------------------------------------------------------------
// �������� ���������� � ������� ������� � ����� ����������
void getfillsettings(struct fillsettingstype* fillinfo)
{
    wg->getFillSettings(fillinfo);
}

// ----------------------------------------------------------------------
//  �������� ������ ����������
void getfillpattern(char* pattern)
{
    wg->getFillPattern(pattern);
}

// ----------------------------------------------------------------------
// ������� �������������� ������ ��� ������������ ������
void settextstyle(int font, int direction, int charsize)
{
    register draw_message m;
	MSG R;
	m.p1 = font, m.p2 = direction, m.p3 = charsize;
    PostMessage (wg->getHWND(), SETTEXTSTYLE, GetCurrentThreadId(), (LPARAM)&m);
    GetMessage (&R, 0, REPLY, REPLY);
}


// ----------------------------------------------------------------------
// ����� ������ �� �����
void outtext(char* textstring, int color = -1)
{
    PostMessage (wg->getHWND(), OUTTEXT, (WPARAM)textstring, color);
}

// ----------------------------------------------------------------------
// ����� ������ ������� � ����� �, y
void outtextxy(int x, int y, const char* textstring, int color = -1)
{
    register draw_message m;
	MSG R;
	m.p1 = x, m.p2 = y, m.p3 = (int)textstring, m.p4 = color;
    PostMessage (wg->getHWND(), OUTTEXTXY, GetCurrentThreadId(), (LPARAM)&m);
    GetMessage (&R, 0, REPLY, REPLY);
}


// ----------------------------------------------------------------------
// ��������� �������
void setpalette(int colornum, int color)
{
    PostMessage (wg->getHWND(), SETPALETTE, colornum, color);
}

// ----------------------------------------------------------------------
// ��������� ����� ��������� �����
void setlinestyle(int num)
{
    PostMessage (wg->getHWND(), SETLINESTYLE, num, 0);
}




