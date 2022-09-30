//
// Created by win 10 on 29/09/2022.
//

#ifndef SOLUCION_BMP_DATASTRUCTURES_H
#define SOLUCION_BMP_DATASTRUCTURES_H

inline double Square( double number ) { return number*number; } // for use in the distance formula
inline int IntSquare( int number ) { return number*number; }  // for use in the distance formula

#endif

int Binary_Pow(int base, int exponent ); // for use in the distance formula

#ifndef _BMP_Defined_WINGDI
#define _BMP_Defined_WINGDI

typedef unsigned char  e_bmp_BYTE; // 8 bits
typedef unsigned short e_bmp_WORD; // 16 bits
typedef unsigned int  e_bmp_DWORD; // 32 bits

#endif

#ifndef _BMP_DataStructures_h_
#define _BMP_DataStructures_h_

inline bool IsBigEndian(){ // returns true if the machine is big-endian
    short word = 0x0001; // 0x0001 is the same as 1
    // if the first byte is 0x01, then the machine is little-endian
    if((*(char *)& word) != 0x01 )  return true;  // if the first byte is not 0x01, then the machine is big-endian
    return false; // if the first byte is 0x01, then the machine is little-endian
}

inline e_bmp_WORD FlipWORD(e_bmp_WORD in ){ return ( (in >> 8) | (in << 8) ); } // swaps the bytes in a WORD
inline e_bmp_DWORD FlipDWORD(e_bmp_DWORD in ){ // swaps the bytes in a DWORD
    return ( ((in&0xFF000000)>>24) | ((in&0x000000FF)<<24) | ((in&0x00FF0000)>>8 ) | ((in&0x0000FF00)<<8 ));
}
// it's easier to use a struct than a class
// because we can read/write all four of the bytes
// at once (as we can count on them being continuous
// in memory

typedef struct RGBA_pixel { // rgba pixel (32 bits) (4 bytes) (1 DWORD) (1 e_bmp_DWORD)
    e_bmp_BYTE Blue;
    e_bmp_BYTE Green;
    e_bmp_BYTE Red;
    e_bmp_BYTE Alpha;
} RGBA_pixel;

class BMFH{ // 14 bytes
public:
    e_bmp_WORD  bfType; // 2 bytes
    e_bmp_DWORD bfSize; // 4 bytes
    e_bmp_WORD  bfReserved1; // 2 bytes
    e_bmp_WORD  bfReserved2; // 2 bytes
    e_bmp_DWORD bfOffBits; // 4 bytes

    BMFH(); // constructor
    void display(); // displays the contents of the header
    void Switch_Endianess(); // switches the endianess of the header
};

class BM_Info_Header{ // bitmaps can have different headers (DIBs) but this is the most common one (40 bytes)
public:
    e_bmp_DWORD biSize; // 4 bytes
    e_bmp_DWORD biWidth; // 4 bytes
    e_bmp_DWORD biHeight; // 4 bytes
    e_bmp_WORD  biPlanes; // 2 bytes
    e_bmp_WORD  biBitCount; // 2 bytes
    e_bmp_DWORD biCompression; // 4 bytes
    e_bmp_DWORD biSizeImage; // 4 bytes
    e_bmp_DWORD biXPlsPerMeter; // pixels per meter
    e_bmp_DWORD biYPlsPerMeter; // 40 bytes total
    e_bmp_DWORD biClrUsed; // number of colors used
    e_bmp_DWORD biClrImportant; // 40 bytes

    BM_Info_Header(); // constructor
    void display(); // displays the contents of the header
    void SwitchEndianess(); // switches the endianess of the header
};
#endif //SOLUCION_BMP_DATASTRUCTURES_H
