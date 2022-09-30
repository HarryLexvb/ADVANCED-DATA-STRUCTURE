//
// Created by win 10 on 29/09/2022.
//

#ifndef SOLUCION_BMP_BMP_H
#define SOLUCION_BMP_BMP_H

bool SafeF_read(char* buffer, int size, int number, FILE* fp ); // reads a block of data from a file
bool BMP_check_Data_Size(); // checks the size of the data types

class BMP{
private:
    int BitDepth; // 1, 4, 8, 16, 24, or 32
    int Width; // in pixels
    int Height; // in pixels
    RGBA_pixel** Pixels; // 2D array of pixels
    RGBA_pixel* Colors; // 1D array of colors
    int XPlsPerMeter; // horizontal resolution
    int YPlsPerMeter; // vertical resolution

    e_bmp_BYTE* MetaData1; // for reading and writing
    int SizeOfMetaData1;
    e_bmp_BYTE* MetaData2;
    int SizeOfMetaData2;

    bool Read32bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ); // 32-bit
    bool Read24bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ); // 24-bit
    bool Read8bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ); // 8-bit
    bool Read4bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ); // 4-bit
    bool Read1bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ); // 1-bit

    bool Write32bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ); // 32-bit
    bool Write24bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ); // 24-bit
    bool Write8bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ); // 8-bit
    bool Write4bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ); // 4-bit
    bool Write1bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ); // 1-bit

    e_bmp_BYTE FindClosestColor(RGBA_pixel& input ); // for 1, 4, and 8-bit

public:

    [[nodiscard]] int TellBitDepth() const; // returns the bit depth
    [[nodiscard]] int TellWidth() const; // returns the width in pixels
    [[nodiscard]] int TellHeight() const; // returns the height in pixels
    [[nodiscard]] int TellNumberOfColors() const; // returns the number of colors
    void SetDPI( int HorizontalDPI, int VerticalDPI ); // sets the resolution
    int TellVerticalDPI(); // returns the vertical resolution
    int TellHorizontalDPI(); // returns the horizontal resolution

    BMP(); // default constructor
    BMP( BMP& Input ); // copy constructor
    ~BMP(); // destructor
    RGBA_pixel* operator()(int i, int j); // access a pixel

    [[nodiscard]] RGBA_pixel GetPixel(int i, int j ) const; // access a pixel
    bool SetPixel(int i, int j, RGBA_pixel NewPixel ); // set a pixel

    bool CreateStandardColorTable(); // 1, 4, and 8-bit

    bool SetSize( int NewWidth, int NewHeight ); // set the size
    bool SetBitDepth( int NewDepth ); // set the bit depth
    bool WriteToFile( const char* FileName ); // write to a file
    bool ReadFromFile( const char* FileName ); // read from a file

    RGBA_pixel GetColor(int ColorNumber ); // get a color
    bool SetColor(int ColorNumber, RGBA_pixel NewColor ); // set a color
};

#endif //SOLUCION_BMP_BMP_H