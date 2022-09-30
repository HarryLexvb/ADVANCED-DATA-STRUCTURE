//
// Created by win 10 on 29/09/2022.
//

#ifndef SOLUCION_BMP_VARIOUSBMPUTILITIES_H
#define SOLUCION_BMP_VARIOUSBMPUTILITIES_H


BMFH Get_BM_File_Header(const char* szFileNameIn ); // reads the file header from a BMP file
BM_Info_Header Get_BM_Info_Header(const char* szFileNameIn ); // reads the info header from a BMP file
void DisplayBitmapInfo( const char* szFileNameIn ); // displays the info header from a BMP file
int GetBitmapColorDepth( const char* szFileNameIn ); // returns the color depth of a BMP file
void PixelToPixelCopy( BMP& From, int FromX, int FromY, BMP& To, int ToX, int ToY); // copies a pixel from one BMP to another
void PixelToPixelCopyTransparent(BMP& From, int FromX, int FromY, BMP& To, int ToX, int ToY, RGBA_pixel& Transparent ); // copies a pixel from one BMP to another, ignoring a transparent color
void RangedPixelToPixelCopy( BMP& From, int FromL , int FromR, int FromB, int FromT, BMP& To, int ToX, int ToY ); // copies a range of pixels from one BMP to another
void RangedPixelToPixelCopyTransparent(BMP& From, int FromL , int FromR, int FromB, int FromT, BMP& To, int ToX, int ToY, RGBA_pixel& Transparent ); // copies a range of pixels from one BMP to another, ignoring a transparent color
bool CreateGrayscaleColorTable( BMP& InputImage ); // creates a grayscale color table for an 8-bit BMP

bool Rescale( BMP& InputImage , char mode, int NewDimension ); // rescales an image

#endif //SOLUCION_BMP_VARIOUSBMPUTILITIES_H
