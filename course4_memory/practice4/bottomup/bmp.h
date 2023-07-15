// BMP-related data types based on Microsoft's own

#include <stdint.h>

// Aliases for C/C++ primitive data types
// https://msdn.microsoft.com/en-us/library/cc230309.aspx
typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

// Information about the type, size, and layout of a file
// https://msdn.microsoft.com/en-us/library/dd183374(v=vs.85).aspx
typedef struct
{
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} __attribute__((__packed__))
BITMAPFILEHEADER;

// Information about the dimensions and color format
// https://msdn.microsoft.com/en-us/library/dd183376(v=vs.85).aspx
typedef struct
{
    DWORD biSize;          /**< structure size, in bytes. */
    LONG  biWidth;         /**< bitmap width in pixels. */
    LONG  biHeight;        /**< bitmap height in pixels. Negative for top-down DIBs. */
    WORD  biPlanes;        /**< number of planes for target device (must be 1). */
    WORD  biBitCount;      /**< bits per pixel. Determines pixel bits and max number of colors. */
    DWORD biCompression;   /**< compression type. Can be one of several values. */
    DWORD biSizeImage;     
    LONG  biXPelsPerMeter; 
    LONG  biYPelsPerMeter; 
    DWORD biClrUsed;       
    DWORD biClrImportant;  
} __attribute__((__packed__))
BITMAPINFOHEADER;

/**
 * The height of the bitmap, in pixels.
 * 
 * If biHeight is positive, the bitmap is a bottom-up DIB
 * and its origin is the lower-left corner.
 * If biHeight is negative, the bitmap is a top-down DIB
 * and its origin is the upper-left corner.
 * 
 * If biHeight is negative, indicating a top-down DIB,
 * biCompression must be either BI_RGB or BI_BITFIELDS.
 * Top-down DIBs cannot be compressed.
 * If biCompression is BI_JPEG or BI_PNG, the biHeight member
 * specifies the height of the decompressed JPEG or PNG image file.
 */

// Relative intensities of red, green, and blue
// https://msdn.microsoft.com/en-us/library/dd162939(v=vs.85).aspx
typedef struct
{
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;
