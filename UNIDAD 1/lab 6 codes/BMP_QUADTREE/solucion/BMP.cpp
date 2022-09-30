
//
// Created by win 10 on 29/09/2022.
//

#include "BMP.h"
using namespace std;

// These functions are defined in BMP.h
bool BMP_warnings = true;

void SetBMPwarningsOff(){ BMP_warnings = false;}
void SetBMPwarningsOn(){ BMP_warnings = true;}
bool GetBMPwarningState(){return BMP_warnings;}

// These functions are defined in BMP_DataStructures.h
int Binary_Pow(int a, int b ){
    //binary exponentiation
    int res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

BMFH::BMFH(){
    bfType = 19778;
    bfReserved1 = 0;
    bfReserved2 = 0;
}
void BMFH::Switch_Endianess(){ // switch the sandiness of the data
    bfType = FlipWORD( bfType );
    bfSize = FlipDWORD( bfSize );
    bfReserved1 = FlipWORD( bfReserved1 );
    bfReserved2 = FlipWORD( bfReserved2 );
    bfOffBits = FlipDWORD( bfOffBits );
    //return;
}
BM_Info_Header::BM_Info_Header(){

    biPlanes = 1;
    biCompression = 0;
    biXPlsPerMeter = DefaultXPlsPerMeter;
    biYPlsPerMeter = DefaultYPlsPerMeter;
    biClrUsed = 0;
    biClrImportant = 0;
}
void BM_Info_Header::SwitchEndianess(){ // switch the sandiness of the data
    biSize = FlipDWORD( biSize );
    biWidth = FlipDWORD( biWidth );
    biHeight = FlipDWORD( biHeight );
    biPlanes = FlipWORD( biPlanes );
    biBitCount = FlipWORD( biBitCount );
    biCompression = FlipDWORD( biCompression );
    biSizeImage = FlipDWORD( biSizeImage );
    biXPlsPerMeter = FlipDWORD(biXPlsPerMeter );
    biYPlsPerMeter = FlipDWORD(biYPlsPerMeter );
    biClrUsed = FlipDWORD( biClrUsed );
    biClrImportant = FlipDWORD( biClrImportant );
    return;
}
void BM_Info_Header::display(){

    cout << "biSize: " << (int) biSize << endl
         << "biWidth: " << (int) biWidth << endl
         << "biHeight: " << (int) biHeight << endl
         << "biPlanes: " << (int) biPlanes << endl
         << "biBitCount: " << (int) biBitCount << endl
         << "biCompression: " << (int) biCompression << endl
         << "biSizeImage: " << (int) biSizeImage << endl
         << "biXPlsPerMeter: " << (int) biXPlsPerMeter << endl
         << "biYPlsPerMeter: " << (int) biYPlsPerMeter << endl
         << "biClrUsed: " << (int) biClrUsed << endl
         << "biClrImportant: " << (int) biClrImportant << endl << endl;
}
void BMFH::display(){
    cout << "bfType: " << (int) bfType << endl
         << "bfSize: " << (int) bfSize << endl
         << "bfReserved1: " << (int) bfReserved1 << endl
         << "bfReserved2: " << (int) bfReserved2 << endl
         << "bfOffBits: " << (int) bfOffBits << endl << endl;
}

/* These functions are defined in BMP_BMP.h */
RGBA_pixel BMP::GetPixel(int i, int j ) const{
    bool Warn = false;
    if( i >= Width ){ i = Width-1; Warn = true; }
    if( i < 0 ) { i = 0; Warn = true; }
    if( j >= Height ) { j = Height-1; Warn = true; }
    if( j < 0 ) { j = 0; Warn = true; }
    if(Warn and BMP_warnings ) {
        cout << "BMP Warning: Attempted to access non-existent pixel;" << endl
             << "                 Truncating request to fit in the range [0,"
             << Width-1 << "] x [0," << Height-1 << "]." << endl;
    }
    return Pixels[i][j];
}
bool BMP::SetPixel(int i, int j, RGBA_pixel NewPixel ){
    if (i < Width && j < Height){
        Pixels[i][j] = NewPixel;
        return true;
    }
    if (BMP_warnings) cout << "BMP Warning: Attempted to write to non-existent pixel." << endl;
    return false;
}
bool BMP::SetColor(int ColorNumber , RGBA_pixel NewColor ){
    if( BitDepth != 1 && BitDepth != 4 && BitDepth != 8 ){
        if( BMP_warnings ){
            cout << "BMP Warning: Attempted to change color table for a BMP object" << endl
                 << "                 that lacks a color table. Ignoring request." << endl;
        }
        return false;
    }
    if( !Colors ){
        if( BMP_warnings ){
            cout << "BMP Warning: Attempted to set a color, but the color table" << endl
                 << "                 is not defined. Ignoring request." << endl;
        }
        return false;
    }
    if( ColorNumber >= TellNumberOfColors() ){
        if( BMP_warnings ){
            cout << "BMP Warning: Requested color number "
                 << ColorNumber << " is outside the allowed" << endl
                 << "                 range [0," << TellNumberOfColors()-1
                 << "]. Ignoring request to set this color." << endl;
        }
        return false;
    }
    Colors[ColorNumber] = NewColor;
    return true;
}

// RGBA_pixel BMP::GetColor( int ColorNumber ) const
RGBA_pixel BMP::GetColor(int ColorNumber ){
    RGBA_pixel Output;
    Output.Red   = 255;
    Output.Green = 255;
    Output.Blue  = 255;
    Output.Alpha = 0;

    using namespace std;
    if( BitDepth != 1 and BitDepth != 4 and BitDepth != 8 ){
        if( BMP_warnings ){
            cout << "BMP Warning: Attempted to access color table for a BMP object" << endl
                 << "                 that lacks a color table. Ignoring request." << endl;
        }
        return Output;
    }
    if( !Colors ){
        if( BMP_warnings ){
            cout << "BMP Warning: Requested a color, but the color table" << endl
                 << "                 is not defined. Ignoring request." << endl;
        }
        return Output;
    }
    if( ColorNumber >= TellNumberOfColors() ){
        if( BMP_warnings ){
            cout << "BMP Warning: Requested color number "
                 << ColorNumber << " is outside the allowed" << endl
                 << "                 range [0," << TellNumberOfColors()-1
                 << "]. Ignoring request to get this color." << endl;
        }
        return Output;
    }
    Output = Colors[ColorNumber];
    return Output;
}

BMP::BMP(){
    Width = 1;
    Height = 1;
    BitDepth = 24;
    Pixels = new RGBA_pixel* [Width];
    Pixels[0] = new RGBA_pixel [Height];
    Colors = nullptr;

    XPlsPerMeter = 0;
    YPlsPerMeter = 0;

    MetaData1 = nullptr;
    SizeOfMetaData1 = 0;
    MetaData2 = nullptr;
    SizeOfMetaData2 = 0;
}

// BMP::BMP( const BMP& Input )
BMP::BMP( BMP& Input ){
    // first, make the image empty.
    Width = 1;
    Height = 1;
    BitDepth = 24;
    Pixels = new RGBA_pixel* [Width];
    Pixels[0] = new RGBA_pixel [Height];
    Colors = nullptr;
    XPlsPerMeter = 0;
    YPlsPerMeter = 0;
    MetaData1 = nullptr;
    SizeOfMetaData1 = 0;
    MetaData2 = nullptr;
    SizeOfMetaData2 = 0;

    // now, set the correct bit depth
    SetBitDepth( Input.TellBitDepth() );

    // set the correct pixel size
    SetSize( Input.TellWidth() , Input.TellHeight() );

    // set the DPI information from Input
    SetDPI( Input.TellHorizontalDPI() , Input.TellVerticalDPI() );

    // if there is a color table, get all the colors
    if( BitDepth == 1 or BitDepth == 4 or BitDepth == 8 )
        for( int k=0 ; k < TellNumberOfColors() ; ++k)
            SetColor( k, Input.GetColor( k ));

    // get all the pixels
    for( int j=0; j < Height ; ++j ){
        for( int i=0; i < Width ; ++i ){
            Pixels[i][j] = *Input(i,j);
            //Pixels[i][j] = Input.GetPixel(i,j); // *Input(i,j);
        }
    }
}

BMP::~BMP(){
    for(int i = 0; i < Width; ++i)
        delete [] Pixels[i];
    delete [] Pixels;

    if( Colors ) delete [] Colors;
    if( MetaData1 ) delete [] MetaData1;
    if( MetaData2 ) delete [] MetaData2;
}

RGBA_pixel* BMP::operator()(int i, int j){
    bool Warn = false;
    if( i >= Width ) { i = Width-1; Warn = true; }
    if( i < 0 ) { i = 0; Warn = true; }
    if( j >= Height ) { j = Height-1; Warn = true; }
    if( j < 0 ) { j = 0; Warn = true; }
    if(Warn and BMP_warnings ){
        cout << "BMP Warning: Attempted to access non-existent pixel;" << endl
             << "                 Truncating request to fit in the range [0,"
             << Width-1 << "] x [0," << Height-1 << "]." << endl;
    }
    return &(Pixels[i][j]);
}

// int BMP::TellBitDepth( void ) const
int BMP::TellBitDepth() const{ return BitDepth; }

// int BMP::TellHeight( void ) const
int BMP::TellHeight() const{ return Height; }

// int BMP::TellWidth( void ) const
int BMP::TellWidth() const{ return Width; }

// int BMP::TellNumberOfColors( void ) const
int BMP::TellNumberOfColors() const{
    int output = Binary_Pow(2, BitDepth);
    if( BitDepth == 32 ) { output = Binary_Pow(2, 24); }
    return output;
}

bool BMP::SetBitDepth( int NewDepth ){
    if( NewDepth != 1 and NewDepth != 4 and NewDepth != 8 and NewDepth != 16 and NewDepth != 24 and NewDepth != 32 ){
        if( BMP_warnings ){
            cout << "BMP Warning: User attempted to set unsupported bit depth "
                 << NewDepth << "." << endl
                 << "                 Bit depth remains unchanged at "
                 << BitDepth << "." << endl;
        }
        return false;
    }
    BitDepth = NewDepth;
    if( Colors ) delete [] Colors;
    int NumberOfColors = Binary_Pow(2, BitDepth);
    if( BitDepth == 1 or BitDepth == 4 or BitDepth == 8 )
        Colors = new RGBA_pixel [NumberOfColors];
    else
        Colors = nullptr; // no color table for 16, 24, or 32 bit images
    if( BitDepth == 1 or BitDepth == 4 or BitDepth == 8 )
        CreateStandardColorTable(); // create a standard color table
    return true;
}

bool BMP::SetSize(int NewWidth , int NewHeight ){
    if( NewWidth <= 0 or NewHeight <= 0 ){
        if( BMP_warnings ){
            cout << "BMP Warning: User attempted to set a non-positive width or height." << endl
                 << "                 Size remains unchanged at "
                 << Width << " x " << Height << "." << endl;
        }
        return false;
    }

    for(int i = 0; i < Width; ++i)
        delete [] Pixels[i];
    delete [] Pixels;

    Width = NewWidth;
    Height = NewHeight;
    Pixels = new RGBA_pixel* [ Width ];

    for(int i = 0; i < Width; ++i)
        Pixels[i] = new RGBA_pixel [ Height ]; // allocate memory for the new image

    for(int i=0 ; i < Width ; ++i){
        for(int j=0 ; j < Height ; ++j){
            Pixels[i][j].Red = 255;
            Pixels[i][j].Green = 255;
            Pixels[i][j].Blue = 255;
            Pixels[i][j].Alpha = 0;
        }
    }
    return true;
}

bool BMP::WriteToFile( const char* FileName ){ // const char* FileName
    if( !BMP_check_Data_Size() ){
        if( BMP_warnings ){
            cout << "BMP Error: Data types are wrong size!" << endl
                 << "               You may need to mess with BMP_DataTypes.h" << endl
                 << "               to fix these errors, and then recompile." << endl
                 << "               All 32-bit and 64-bit machines should be" << endl
                 << "               supported, however." << endl << endl;
        }
        return false;
    }

    FILE* fp = fopen( FileName, "wb" );
    if( fp == nullptr ){
        if( BMP_warnings )
            cout << "BMP Error: Cannot open file " << FileName << " for output." << endl;
        fclose( fp ); // just in case it opened and then failed for some reason (permissions?)
        return false;
    }

    // some preliminaries
    double dBytesPerPixel = ( (double) BitDepth ) / 8.0; // 1, 0.5, 0.25, etc.
    double dBytesPerRow = dBytesPerPixel * (Width+0.0); // exact number of bytes per row
    dBytesPerRow = ceil(dBytesPerRow); // round up to nearest byte boundary

    int BytePaddingPerRow = 4 - ( (int) (dBytesPerRow) )% 4; // number of padding bytes per row
    if( BytePaddingPerRow == 4 )
        BytePaddingPerRow = 0;

    double dActualBytesPerRow = dBytesPerRow + BytePaddingPerRow; // total bytes per row, including padding
    double dTotalPixelBytes = Height * dActualBytesPerRow; // total bytes in image

    double dPaletteSize = 0;
    if( BitDepth == 1 or BitDepth == 4 or BitDepth == 8 ) // 2, 16, or 256 colors
        dPaletteSize = Binary_Pow(2, BitDepth) * 4.0; // 4 bytes per color

    // leave some room for 16-bit masks
    if( BitDepth == 16 )
        dPaletteSize = 3*4; // 3 4-byte masks

    double dTotalFileSize = 14 + 40 + dPaletteSize + dTotalPixelBytes; // total file size in bytes

    // write the file header
    BMFH bm_file_header; // file header structure (14 bytes)
    bm_file_header.bfSize = (e_bmp_DWORD) dTotalFileSize;
    bm_file_header.bfReserved1 = 0;
    bm_file_header.bfReserved2 = 0;
    bm_file_header.bfOffBits = (e_bmp_DWORD) (14 + 40 + dPaletteSize);

    if( IsBigEndian() )
        bm_file_header.Switch_Endianess(); // switch to little endian if necessary

    fwrite((char*) &(bm_file_header.bfType) , sizeof(e_bmp_WORD) , 1 , fp ); // 2 bytes
    fwrite((char*) &(bm_file_header.bfSize) , sizeof(e_bmp_DWORD) , 1 , fp ); // 4 bytes
    fwrite((char*) &(bm_file_header.bfReserved1) , sizeof(e_bmp_WORD) , 1 , fp ); // 2 bytes
    fwrite((char*) &(bm_file_header.bfReserved2) , sizeof(e_bmp_WORD) , 1 , fp ); // 2 bytes
    fwrite((char*) &(bm_file_header.bfOffBits) , sizeof(e_bmp_DWORD) , 1 , fp ); // 4 bytes

    // write the info header
    BM_Info_Header bm_info_header; // info header structure (40 bytes)
    bm_info_header.biSize = 40;
    bm_info_header.biWidth = Width;
    bm_info_header.biHeight = Height;
    bm_info_header.biPlanes = 1;
    bm_info_header.biBitCount = BitDepth;
    bm_info_header.biCompression = 0;
    bm_info_header.biSizeImage = (e_bmp_DWORD) dTotalPixelBytes;

    if( XPlsPerMeter )
        bm_info_header.biXPlsPerMeter = XPlsPerMeter; // user specified
    else
        bm_info_header.biXPlsPerMeter = DefaultXPlsPerMeter; // default value
    if( YPlsPerMeter )
        bm_info_header.biYPlsPerMeter = YPlsPerMeter; // user specified
    else
        bm_info_header.biYPlsPerMeter = DefaultYPlsPerMeter; // default value

    bm_info_header.biClrUsed = 0; // 2^BitDepth colors used
    bm_info_header.biClrImportant = 0; // all colors are important

    // indicates that we'll be using bit fields for 16-bit files
    if( BitDepth == 16 )
        bm_info_header.biCompression = 3; // BI_BITFIELDS

    if( IsBigEndian() )
        bm_info_header.SwitchEndianess(); // switch to little endian if necessary

    fwrite((char*) &(bm_info_header.biSize) , sizeof(e_bmp_DWORD) , 1 , fp ); // 4 bytes
    fwrite((char*) &(bm_info_header.biWidth) , sizeof(e_bmp_DWORD) , 1 , fp ); // 4 bytes
    fwrite((char*) &(bm_info_header.biHeight) , sizeof(e_bmp_DWORD) , 1 , fp ); // 4 bytes
    fwrite((char*) &(bm_info_header.biPlanes) , sizeof(e_bmp_WORD) , 1 , fp ); // 2 bytes
    fwrite((char*) &(bm_info_header.biBitCount) , sizeof(e_bmp_WORD) , 1 , fp ); // 2 bytes
    fwrite((char*) &(bm_info_header.biCompression) , sizeof(e_bmp_DWORD) , 1 , fp ); // 4 bytes
    fwrite((char*) &(bm_info_header.biSizeImage) , sizeof(e_bmp_DWORD) , 1 , fp ); // 4 bytes
    fwrite((char*) &(bm_info_header.biXPlsPerMeter) , sizeof(e_bmp_DWORD) , 1 , fp ); // 4 bytes
    fwrite((char*) &(bm_info_header.biYPlsPerMeter) , sizeof(e_bmp_DWORD) , 1 , fp ); // 4 bytes
    fwrite((char*) &(bm_info_header.biClrUsed) , sizeof(e_bmp_DWORD) , 1 , fp); // 4 bytes
    fwrite((char*) &(bm_info_header.biClrImportant) , sizeof(e_bmp_DWORD) , 1 , fp); // 4 bytes

    // write the palette
    if( BitDepth == 1 or BitDepth == 4 or BitDepth == 8 ){ // 2, 16, or 256 colors
        int NumberOfColors = Binary_Pow(2, BitDepth);
        // if there is no palette, create one
        if( !Colors ){
            if( !Colors ) Colors = new RGBA_pixel [NumberOfColors]; // create a new palette
            CreateStandardColorTable();
        }

        for(int n=0 ; n < NumberOfColors ; ++n)
            fwrite( (char*) &(Colors[n]) , 4 , 1 , fp ); // 4 bytes per color
    }

    // write the pixels
    if( BitDepth != 16 ){ // 1, 4, 8, or 24 bits per pixel
        int j; // row counter
        e_bmp_BYTE* Buffer; // buffer for one row of pixels
        int BufferSize = (int) ( (Width*BitDepth)/8.0 ); // size of each row in bytes

        while( 8*BufferSize < Width*BitDepth ) { BufferSize++; } // round up to nearest byte
        while( BufferSize % 4 ) { BufferSize++; } // pad to 4-byte boundary

        Buffer = new e_bmp_BYTE [BufferSize]; // create the buffer
        for(j = 0; j < BufferSize; ++j)
            Buffer[j] = 0; // clear the buffer
        j = Height-1; // start at the bottom row

        while( j > -1 ){ // for each row
            bool Success = false;
            if( BitDepth == 32 ) { Success = Write32bitRow( Buffer, BufferSize, j ); }
            if( BitDepth == 24 ) { Success = Write24bitRow( Buffer, BufferSize, j ); }
            if( BitDepth == 8  ) { Success = Write8bitRow( Buffer, BufferSize, j ); }
            if( BitDepth == 4  ) { Success = Write4bitRow( Buffer, BufferSize, j ); }
            if( BitDepth == 1  ) { Success = Write1bitRow( Buffer, BufferSize, j ); }

            if( Success ){
                int BytesWritten = (int) fwrite( (char*) Buffer, 1, BufferSize, fp ); // write the row
                if( BytesWritten != BufferSize ) { Success = false; } // error
            }
            if( !Success ){
                if( BMP_warnings ) cout << "BMP Error: Could not write proper amount of data." << endl;
                j = -1;
            }
            j--;
        }
        delete [] Buffer;
    }

    if( BitDepth == 16 ){
        // write the bit masks
        e_bmp_WORD BlueMask = 31;    // bits 12-16
        e_bmp_WORD GreenMask = 2016; // bits 6-11
        e_bmp_WORD RedMask = 63488;  // bits 1-5
        e_bmp_WORD ZeroWORD;

        if( IsBigEndian() ) { RedMask = FlipWORD( RedMask ); } // switch to little endian if necessary
        fwrite( (char*) &RedMask , 2 , 1 , fp ); // 2 bytes
        fwrite( (char*) &ZeroWORD , 2 , 1 , fp ); // 2 bytes

        if( IsBigEndian() ) { GreenMask = FlipWORD( GreenMask ); } // switch to little endian if necessary
        fwrite( (char*) &GreenMask , 2 , 1 , fp ); // 2 bytes
        fwrite( (char*) &ZeroWORD , 2 , 1 , fp ); // 2 bytes

        if( IsBigEndian() ) { BlueMask = FlipWORD( BlueMask ); } // switch to little endian if necessary
        fwrite( (char*) &BlueMask , 2 , 1 , fp ); // 2 bytes
        fwrite( (char*) &ZeroWORD , 2 , 1 , fp ); // 2 bytes

        int DataBytes = Width*2; // 2 bytes per pixel
        int PaddingBytes = ( 4 - DataBytes % 4 ) % 4; // pad to 4-byte boundary

        // write the actual pixels
        for(int j = Height-1 ; j >= 0 ; --j){
            // write all row pixel data
            int i = 0;
            int WriteNumber = 0;
            while( WriteNumber < DataBytes ){
                e_bmp_WORD TempWORD;
                /*
                 e_bmp_WORD RedWORD = (e_bmp_WORD) ((Pixels[i][j]).Red / 8);
                e_bmp_WORD GreenWORD = (e_bmp_WORD) ((Pixels[i][j]).Green / 4);
                e_bmp_WORD BlueWORD = (e_bmp_WORD) ((Pixels[i][j]).Blue / 8);
                 */
                auto RedWORD = (e_bmp_WORD) ((Pixels[i][j]).Red / 8);
                auto GreenWORD = (e_bmp_WORD) ((Pixels[i][j]).Green / 4);
                auto BlueWORD = (e_bmp_WORD) ((Pixels[i][j]).Blue / 8);

                TempWORD = (RedWORD<<11) + (GreenWORD<<5) + BlueWORD; // 5-6-5 bit encoding
                if( IsBigEndian() ) { TempWORD = FlipWORD( TempWORD ); } // switch to little endian if necessary
                fwrite( (char*) &TempWORD , 2, 1, fp); // 2 bytes
                WriteNumber += 2; // 2 bytes per pixel
                i++; // next pixel
            }
            // write any necessary row padding
            WriteNumber = 0;
            while( WriteNumber < PaddingBytes ) {
                e_bmp_BYTE TempBYTE;
                fwrite( (char*) &TempBYTE , 1, 1, fp);
                WriteNumber++;
            }
        }

    }

    fclose(fp);
    return true;
}

bool BMP::ReadFromFile( const char* FileName ){ // read from a file
    if( !BMP_check_Data_Size()) { // check that the data sizes are correct
        if( BMP_warnings ){ // if warnings are on, print a warning
            cout << "BMP Error: Data types are wrong size!" << endl
                 << "               You may need to mess with BMP_DataTypes.h" << endl
                 << "               to fix these errors, and then recompile." << endl
                 << "               All 32-bit and 64-bit machines should be" << endl
                 << "               supported, however." << endl << endl;
        }
        return false;
    }

    FILE* fp = fopen( FileName, "rb" );
    if( fp == nullptr ) { // file does not exist
        if( BMP_warnings ) { // if warnings are on, print a warning
            cout << "BMP Error: Cannot open file "
                 << FileName << " for input." << endl;
        }
        SetBitDepth(1); // set to a default value
        SetSize(1,1); // set to a default value
        return false;
    }

    // read the file header
    BMFH bm_file_header; // bitmap file header
    bool NotCorrupted = true; // assume the file is not corrupted

    NotCorrupted &= SafeF_read((char *) &(bm_file_header.bfType), sizeof(e_bmp_WORD), 1, fp); // 2 bytes
    bool IsBitmap = false; // assume the file is not a bitmap
    if(IsBigEndian() and bm_file_header.bfType == 16973 ) IsBitmap = true; // 0x4D42
    if(!IsBigEndian() and bm_file_header.bfType == 19778 )IsBitmap = true; // 0x4D42

    if( !IsBitmap ) { // not a bitmap
        if( BMP_warnings ) { // if warnings are on, print a warning
            cout << "BMP Error: " << FileName
                 << " is not a Windows BMP file!" << endl;
        }
        fclose( fp );
        return false;
    }

    NotCorrupted &= SafeF_read((char *) &(bm_file_header.bfSize), sizeof(e_bmp_DWORD), 1, fp); // 4 bytes
    NotCorrupted &= SafeF_read((char *) &(bm_file_header.bfReserved1), sizeof(e_bmp_WORD), 1, fp); // 2 bytes
    NotCorrupted &= SafeF_read((char *) &(bm_file_header.bfReserved2), sizeof(e_bmp_WORD), 1, fp); // 2 bytes
    NotCorrupted &= SafeF_read((char *) &(bm_file_header.bfOffBits), sizeof(e_bmp_DWORD), 1, fp); // 4 bytes

    if( IsBigEndian() ) bm_file_header.Switch_Endianess(); // switch to little endian if necessary

    // read the info header
    BM_Info_Header bm_info_header; // bitmap info header
    NotCorrupted &= SafeF_read((char *) &(bm_info_header.biSize), sizeof(e_bmp_DWORD), 1, fp); // 4 bytes
    NotCorrupted &= SafeF_read((char *) &(bm_info_header.biWidth), sizeof(e_bmp_DWORD), 1, fp); // 4 bytes
    NotCorrupted &= SafeF_read((char *) &(bm_info_header.biHeight), sizeof(e_bmp_DWORD), 1, fp); // 4 bytes
    NotCorrupted &= SafeF_read((char *) &(bm_info_header.biPlanes), sizeof(e_bmp_WORD), 1, fp); // 2 bytes
    NotCorrupted &= SafeF_read((char *) &(bm_info_header.biBitCount), sizeof(e_bmp_WORD), 1, fp); // 2 bytes

    NotCorrupted &= SafeF_read((char *) &(bm_info_header.biCompression), sizeof(e_bmp_DWORD), 1, fp); // 4 bytes
    NotCorrupted &= SafeF_read((char *) &(bm_info_header.biSizeImage), sizeof(e_bmp_DWORD), 1, fp); // 4 bytes
    NotCorrupted &= SafeF_read((char *) &(bm_info_header.biXPlsPerMeter), sizeof(e_bmp_DWORD), 1, fp); // 4 bytes
    NotCorrupted &= SafeF_read((char *) &(bm_info_header.biYPlsPerMeter), sizeof(e_bmp_DWORD), 1, fp); // 4 bytes
    NotCorrupted &= SafeF_read((char *) &(bm_info_header.biClrUsed), sizeof(e_bmp_DWORD), 1, fp); // 4 bytes
    NotCorrupted &= SafeF_read((char *) &(bm_info_header.biClrImportant), sizeof(e_bmp_DWORD), 1, fp); // 4 bytes

    if( IsBigEndian()) bm_info_header.SwitchEndianess(); // switch to little endian if necessary

    // a safety catch: if any of the header information didn't read properly, abort
    // future idea: check to see if at least most is self-consistent

    if( !NotCorrupted ){ // file is corrupted
        if( BMP_warnings ) { // if warnings are on, print a warning
            cout << "BMP Error: " << FileName
                 << " is obviously corrupted." << endl;
        }
        SetSize(1,1);
        SetBitDepth(1);
        fclose(fp);
        return false;
    }

    XPlsPerMeter = bm_info_header.biXPlsPerMeter; // set the resolution
    YPlsPerMeter = bm_info_header.biYPlsPerMeter; // set the resolution

    // if bm_info_header.biCompression 1 or 2, then the file is RLE compressed
    if(bm_info_header.biCompression == 1 or bm_info_header.biCompression == 2 ) { // RLE compressed
        if( BMP_warnings ) { // if warnings are on, print a warning
            cout << "BMP Error: " << FileName << " is (RLE) compressed." << endl
                 << "               BMP does not support compression." << endl;
        }
        SetSize(1,1);
        SetBitDepth(1);
        fclose(fp);
        return false;
    }

    // if bm_info_header.biCompression > 3, then something strange is going on
    // it's probably an OS2 bitmap file.

    if(bm_info_header.biCompression > 3 ){ // OS2 bitmap
        if( BMP_warnings ) { // if warnings are on, print a warning
            cout << "BMP Error: " << FileName << " is in an unsupported format."
                 << endl
                 << "               (bm_info_header.biCompression = "
                 << bm_info_header.biCompression << ")" << endl
                 << "               The file is probably an old OS2 bitmap or corrupted."
                 << endl;
        }
        SetSize(1,1);
        SetBitDepth(1);
        fclose(fp);
        return false;
    }

    if(bm_info_header.biCompression == 3 and bm_info_header.biBitCount != 16 ) { // OS2 bitmap
        if( BMP_warnings ) { // if warnings are on, print a warning
            cout << "BMP Error: " << FileName
                 << " uses bit fields and is not a" << endl
                 << "               16-bit file. This is not supported." << endl;
        }
        SetSize(1,1);
        SetBitDepth(1);
        fclose(fp);
        return false;
    }

    // set the bit depth
    int TempBitDepth = (int) bm_info_header.biBitCount; // cast to int
    if(TempBitDepth != 1  and TempBitDepth != 4 and TempBitDepth != 8 and TempBitDepth != 16 and TempBitDepth != 24 and TempBitDepth != 32 ){
        if( BMP_warnings ) cout << "BMP Error: " << FileName << " has unrecognized bit depth." << endl; // if warnings are on, print a warning
        SetSize(1,1);
        SetBitDepth(1);
        fclose(fp);
        return false;
    }
    SetBitDepth( (int) bm_info_header.biBitCount ); // cast to int

    // set the size
    if((int) bm_info_header.biWidth <= 0 or (int) bm_info_header.biHeight <= 0 ){ // if the width or height is zero or negative
        if( BMP_warnings ){ // if warnings are on, print a warning
            cout << "BMP Error: " << FileName
                 << " has a non-positive width or height." << endl;
        }
        SetSize(1,1);
        SetBitDepth(1);
        fclose(fp);
        return false;
    }
    SetSize((int) bm_info_header.biWidth , (int) bm_info_header.biHeight ); // cast to int

    // some preliminaries
    double dBytesPerPixel = ( (double) BitDepth ) / 8.0; // bytes per pixel
    double dBytesPerRow = dBytesPerPixel * (Width+0.0); // bytes per row
    dBytesPerRow = ceil(dBytesPerRow); // round up to the nearest byte boundary

    int BytePaddingPerRow = 4 - ( (int) (dBytesPerRow) )% 4; // number of padding bytes per row
    if( BytePaddingPerRow == 4 ) BytePaddingPerRow = 0; // if divisible by 4, no padding
    { BytePaddingPerRow = 0; } // if divisible by 4, no padding

    // if < 16 bits, read the palette
    if( BitDepth < 16 ) { // read the palette
        // determine the number of colors specified in the
        // color table
        int NumberOfColorsToRead = ((int) bm_file_header.bfOffBits - 54 ) / 4; // cast to int
        // if the number of colors is larger than the number of colors allowed by the bit depth, set it to the maximum
        if(NumberOfColorsToRead > Binary_Pow(2, BitDepth) ) NumberOfColorsToRead = Binary_Pow(2, BitDepth);
        if( NumberOfColorsToRead < TellNumberOfColors() ) {
            if( BMP_warnings ){ // if warnings are on, print a warning
                cout << "BMP Warning: file " << FileName << " has an underspecified" << endl
                     << "                 color table. The table will be padded with extra" << endl
                     << "                 white (255,255,255,0) entries." << endl;
            }
        }

        for( int n=0; n < NumberOfColorsToRead ; ++n)
            SafeF_read((char *) &(Colors[n]), 4, 1, fp); // read the color table
        for(int n = NumberOfColorsToRead ; n < TellNumberOfColors() ; ++n) {
            RGBA_pixel WHITE; // create a white pixel
            WHITE.Red = 255; // set the red value
            WHITE.Green = 255;
            WHITE.Blue = 255;
            WHITE.Alpha = 0;
            SetColor( n , WHITE ); // set the color
        }
    }

    // skip blank data if bfOffBits so indicates
    int BytesToSkip = bm_file_header.bfOffBits - 54; // cast to int
    if( BitDepth < 16 ) BytesToSkip -= 4 * Binary_Pow(2, BitDepth); // subtract the size of the palette
    if( BitDepth == 16 and bm_info_header.biCompression == 3 ) BytesToSkip -= 3*4; // subtract the size of the bit masks
    if( BytesToSkip < 0 ) BytesToSkip = 0; // if negative, set to zero
    if( BytesToSkip > 0 and BitDepth != 16 ){ // if there is data to skip
        if( BMP_warnings ) { // if warnings are on, print a warning
            cout << "BMP Warning: Extra meta data detected in file " << FileName << endl
                 << "                 Data will be skipped." << endl;
        }
        e_bmp_BYTE* TempSkipBYTE; // create a temporary byte
        TempSkipBYTE = new e_bmp_BYTE [BytesToSkip]; // allocate memory
        SafeF_read((char *) TempSkipBYTE, BytesToSkip, 1, fp); // read the data
        delete [] TempSkipBYTE; // delete the temporary byte
    }

    // This code reads 1, 4, 8, 24, and 32-bpp files
    // with a more-efficient buffered technique.
    int i,j;
    if( BitDepth != 16 ) { // if not a 16-bit file
        int BufferSize = (int) ( (Width*BitDepth) / 8.0 ); // cast to int
        while( 8*BufferSize < Width*BitDepth ) BufferSize++;  // round up to nearest byte
        while( BufferSize % 4 ) BufferSize++; // pad to a 4-byte boundary
        e_bmp_BYTE* Buffer; // create a buffer
        Buffer = new e_bmp_BYTE [BufferSize];
        j= Height-1;

        while( j > -1 ){ // for each row
            int BytesRead = (int) fread( (char*) Buffer, 1, BufferSize, fp ); // cast to int
            if( BytesRead < BufferSize ){ // if the read failed
                j = -1; // this will cause the loop to exit
                if( BMP_warnings ) // if warnings are on, print a warning
                    cout << "BMP Error: Could not read proper amount of data." << endl;

            }
            else{ // read the data
                bool Success = false;
                if( BitDepth == 1  ) Success = Read1bitRow(  Buffer, BufferSize, j ); // read a 1-bit row
                if( BitDepth == 4  ) Success = Read4bitRow(  Buffer, BufferSize, j ); // read a 4-bit row
                if( BitDepth == 8  ) Success = Read8bitRow(  Buffer, BufferSize, j ); // read an 8-bit row
                if( BitDepth == 24 ) Success = Read24bitRow( Buffer, BufferSize, j ); // read a 24-bit row
                if( BitDepth == 32 ) Success = Read32bitRow( Buffer, BufferSize, j ); // read a 32-bit row
                if( !Success ){
                    if( BMP_warnings ) // if warnings are on, print a warning
                        cout << "BMP Error: Could not read enough pixel data!" << endl;
                    j = -1; // exit the loop
                }
            }
            j--; // decrement the row counter
        }
        delete [] Buffer; // delete the buffer
    }

    if( BitDepth == 16 ) { // if a 16-bit file
        int DataBytes = Width*2; // number of bytes of data
        int PaddingBytes = ( 4 - DataBytes % 4 ) % 4; // number of padding bytes

        // set the default mask
        e_bmp_WORD BlueMask = 31; // bits 12-16
        e_bmp_WORD GreenMask = 992; // bits 7-11
        e_bmp_WORD RedMask = 31744; // bits 2-6

        // read the bit fields, if necessary, to
        // override the default 5-5-5 mask
        if(bm_info_header.biCompression != 0 ) { // if the compression type is not 0
            // read the three bit masks
            e_bmp_WORD TempMaskWORD;
            e_bmp_WORD ZeroWORD;

            SafeF_read((char *) &RedMask, 2, 1, fp); // read the red mask
            if( IsBigEndian() ) RedMask = FlipWORD(RedMask);  // flip if necessary
            SafeF_read((char *) &TempMaskWORD, 2, 1, fp); // read a zero WORD

            SafeF_read((char *) &GreenMask, 2, 1, fp); // read the green mask
            if( IsBigEndian() ) GreenMask = FlipWORD(GreenMask); // flip if necessary
            SafeF_read((char *) &TempMaskWORD, 2, 1, fp); // read a zero WORD

            SafeF_read((char *) &BlueMask, 2, 1, fp); // read the blue mask
            if( IsBigEndian() ) BlueMask = FlipWORD(BlueMask); // flip if necessary
            SafeF_read((char *) &TempMaskWORD, 2, 1, fp); // read a zero WORD
        }

        // read and skip any meta data

        if( BytesToSkip > 0 ){ // if there is data to skip
            if( BMP_warnings ){ // if warnings are on, print a warning
                cout << "BMP Warning: Extra meta data detected in file "
                     << FileName << endl
                     << "                 Data will be skipped." << endl;
            }
            e_bmp_BYTE* TempSkipBYTE; // create a temporary byte
            TempSkipBYTE = new e_bmp_BYTE [BytesToSkip];
            SafeF_read((char *) TempSkipBYTE, BytesToSkip, 1, fp); // read the data
            delete [] TempSkipBYTE; // delete the temporary byte
        }

        // determine the red, green and blue shifts
        int GreenShift = 0; // number of bits to shift green
        e_bmp_WORD TempShiftWORD = GreenMask; // temporary WORD
        while( TempShiftWORD > 31 ) { TempShiftWORD = TempShiftWORD>>1; ++GreenShift; } // shift and count

        int BlueShift = 0; // number of bits to shift blue
        TempShiftWORD = BlueMask; // temporary WORD
        while( TempShiftWORD > 31 ) { TempShiftWORD = TempShiftWORD>>1; ++BlueShift; } // shift and count

        int RedShift = 0; // number of bits to shift red
        TempShiftWORD = RedMask; // temporary WORD
        while( TempShiftWORD > 31 ) { TempShiftWORD = TempShiftWORD>>1; ++RedShift; } // shift and count

        // read the actual pixels
        for( j=Height-1 ; j >= 0 ; --j ){ // for each row
            i=0;
            int ReadNumber = 0; // number of WORDs read
            while( ReadNumber < DataBytes ) { // for each WORD

                e_bmp_WORD TempWORD; // temporary WORD
                SafeF_read((char *) &TempWORD, 2, 1, fp); // read the WORD
                if( IsBigEndian() ) { TempWORD = FlipWORD(TempWORD); } // flip if necessary
                ReadNumber += 2; // increment the number of WORDs read

                e_bmp_WORD Red = RedMask & TempWORD;
                e_bmp_WORD Green = GreenMask & TempWORD;
                e_bmp_WORD Blue = BlueMask & TempWORD;

                e_bmp_BYTE BlueBYTE = (e_bmp_BYTE) 8 * (Blue >> BlueShift);
                e_bmp_BYTE GreenBYTE = (e_bmp_BYTE) 8 * (Green >> GreenShift);
                e_bmp_BYTE RedBYTE = (e_bmp_BYTE) 8 * (Red >> RedShift);

                (Pixels[i][j]).Red = RedBYTE;
                (Pixels[i][j]).Green = GreenBYTE;
                (Pixels[i][j]).Blue = BlueBYTE;
                ++i; // increment the column counter
            }
            ReadNumber = 0;
            while( ReadNumber < PaddingBytes ) { // for each padding byte
                e_bmp_BYTE TempBYTE;
                SafeF_read((char *) &TempBYTE, 1, 1, fp); // read the byte
                ReadNumber++;
            }
        }

    }

    fclose(fp);
    return true;
}

bool BMP::CreateStandardColorTable(){ // create a standard color table
    if( BitDepth != 1 and BitDepth != 4 and BitDepth != 8 ){  // if the bit depth is not 1, 4 or 8
        if( BMP_warnings ) { // if warnings are on, print a warning
            cout << "BMP Warning: Attempted to create color table at a bit" << endl
                 << "                 depth that does not require a color table." << endl
                 << "                 Ignoring request." << endl;
        }
        return false;
    }

    if( BitDepth == 1 ) { // if the bit depth is 1
        for(int i=0 ; i < 2 ; i++ )
        {
            Colors[i].Red = i*255;
            Colors[i].Green = i*255;
            Colors[i].Blue = i*255;
            Colors[i].Alpha = 0;
        }
        return true;
    }

    if( BitDepth == 4 ) { // if the bit depth is 4
        int i = 0;
        int j,k,ell; // counters
        // simplify the code for the first 8 colors
        for( ell=0 ; ell < 2 ; ++ell) {
            for( k=0 ; k < 2 ; ++k) {
                for( j=0 ; j < 2 ; ++j) {
                    Colors[i].Red = j*128;
                    Colors[i].Green = k*128;
                    Colors[i].Blue = ell*128;
                    ++i; // increment the counter
                }
            }
        }

        // simplify the code for the last 8 colors
        for( ell=0 ; ell < 2 ; ell++ )
        {
            for( k=0 ; k < 2 ; k++ )
            {
                for( j=0 ; j < 2 ; j++ )
                {
                    Colors[i].Red = j*255;
                    Colors[i].Green = k*255;
                    Colors[i].Blue = ell*255;
                    i++;
                }
            }
        }

        // overwrite the duplicate color
        i=8;
        Colors[i].Red = 192;
        Colors[i].Green = 192;
        Colors[i].Blue = 192;

        for( i=0 ; i < 16 ; i++ )
        { Colors[i].Alpha = 0; }
        return true;
    }

    if( BitDepth == 8 ) { // if the bit depth is 8
        int i=0;
        int j,k,ell; // counters

        // do an easy loop, which works for all but colors
        // 0 to 9 and 246 to 255
        for( ell=0 ; ell < 4 ; ++ell) {
            for( k=0 ; k < 8 ; ++k) {
                for( j=0; j < 8 ; ++j) {
                    Colors[i].Red = j*32;
                    Colors[i].Green = k*32;
                    Colors[i].Blue = ell*64;
                    Colors[i].Alpha = 0;
                    ++i;
                }
            }
        }

        // now redo the first 8 colors
        i=0;
        for( ell=0 ; ell < 2 ; ell++ )
        {
            for( k=0 ; k < 2 ; k++ )
            {
                for( j=0; j < 2 ; j++ )
                {
                    Colors[i].Red = j*128;
                    Colors[i].Green = k*128;
                    Colors[i].Blue = ell*128;
                    i++;
                }
            }
        }

        // overwrite colors 7, 8, 9
        i=7;
        Colors[i].Red = 192;
        Colors[i].Green = 192;
        Colors[i].Blue = 192;
        i++; // 8
        Colors[i].Red = 192;
        Colors[i].Green = 220;
        Colors[i].Blue = 192;
        i++; // 9
        Colors[i].Red = 166;
        Colors[i].Green = 202;
        Colors[i].Blue = 240;

        // overwrite colors 246 to 255
        i=246;
        Colors[i].Red = 255;
        Colors[i].Green = 251;
        Colors[i].Blue = 240;
        i++; // 247
        Colors[i].Red = 160;
        Colors[i].Green = 160;
        Colors[i].Blue = 164;
        i++; // 248
        Colors[i].Red = 128;
        Colors[i].Green = 128;
        Colors[i].Blue = 128;
        i++; // 249
        Colors[i].Red = 255;
        Colors[i].Green = 0;
        Colors[i].Blue = 0;
        i++; // 250
        Colors[i].Red = 0;
        Colors[i].Green = 255;
        Colors[i].Blue = 0;
        i++; // 251
        Colors[i].Red = 255;
        Colors[i].Green = 255;
        Colors[i].Blue = 0;
        i++; // 252
        Colors[i].Red = 0;
        Colors[i].Green = 0;
        Colors[i].Blue = 255;
        i++; // 253
        Colors[i].Red = 255;
        Colors[i].Green = 0;
        Colors[i].Blue = 255;
        i++; // 254
        Colors[i].Red = 0;
        Colors[i].Green = 255;
        Colors[i].Blue = 255;
        i++; // 255
        Colors[i].Red = 255;
        Colors[i].Green = 255;
        Colors[i].Blue = 255;

        return true;
    }
    return true;
}

bool SafeF_read(char* buffer, int size, int number, FILE* fp ){ // read a number of bytes from a file
    int ItemsRead;
    if( feof(fp) ) return false; // if the file is already at the end, return false
    ItemsRead = (int) fread( buffer , size , number , fp ); // read the data
    if( ItemsRead < number ) return false; // if the number of items read is less than the number requested, return false
    return true;
}

void BMP::SetDPI( int HorizontalDPI, int VerticalDPI ){ // set the DPI
    XPlsPerMeter = (int) (HorizontalDPI * 39.37007874015748 ); // 39.37007874015748 = 100/2.54
    YPlsPerMeter = (int) (VerticalDPI * 39.37007874015748 ); // 39.37007874015748 = 100/2.54
}

// int BMP::TellVerticalDPI( void ) const
int BMP::TellVerticalDPI(){ // return the vertical DPI
    if( !YPlsPerMeter ) YPlsPerMeter = DefaultYPlsPerMeter; // if the vertical DPI is not set, use the default
    return (int) (YPlsPerMeter / (double) 39.37007874015748 ); // 39.37007874015748 = 100/2.54
}

// int BMP::TellHorizontalDPI( void ) const
int BMP::TellHorizontalDPI(){ // return the horizontal DPI
    if( !XPlsPerMeter ) XPlsPerMeter = DefaultXPlsPerMeter; // if the horizontal DPI is not set, use the default
    return (int) (XPlsPerMeter / (double) 39.37007874015748 ); // 39.37007874015748 = 100/2.54
}

/* These functions are defined in BMP_VariousBMPutilities.h */
BMFH Get_BM_File_Header(const char* szFileNameIn ){ // get the bitmap file header
    BMFH bm_file_header;
    FILE* fp; // file pointer
    fp = fopen( szFileNameIn,"rb"); // open the file
    if( !fp  ) {
        if( BMP_warnings ) {
            cout << "BMP Error: Cannot initialize from file "
                 << szFileNameIn << "." << endl
                 << "               File cannot be opened or does not exist."
                 << endl;
        }
        bm_file_header.bfType = 0;
        return bm_file_header; // return an empty header
    }

    SafeF_read((char *) &(bm_file_header.bfType), sizeof(e_bmp_WORD), 1, fp); // read the file type
    SafeF_read((char *) &(bm_file_header.bfSize), sizeof(e_bmp_DWORD), 1, fp); // read the file size
    SafeF_read((char *) &(bm_file_header.bfReserved1), sizeof(e_bmp_WORD), 1, fp); // read the reserved word
    SafeF_read((char *) &(bm_file_header.bfReserved2), sizeof(e_bmp_WORD), 1, fp); // read the reserved word
    SafeF_read((char *) &(bm_file_header.bfOffBits), sizeof(e_bmp_DWORD), 1, fp); // read the offset

    fclose( fp ); // close the file
    if( IsBigEndian() ) bm_file_header.Switch_Endianess(); // switch the endianness if necessary
    return bm_file_header; // return the header
}

BM_Info_Header Get_BM_Info_Header(const char* szFileNameIn ){ // get the bitmap information header
    using namespace std;
    BMFH bm_file_header;  // bitmap file header
    BM_Info_Header bm_info_header; // bitmap information header

    FILE* fp;
    fp = fopen( szFileNameIn,"rb");

    if( !fp  ) {
        if( BMP_warnings ) {
            cout << "BMP Error: Cannot initialize from file "
                 << szFileNameIn << "." << endl
                 << "               File cannot be opened or does not exist."
                 << endl;
        }
        return bm_info_header;
    }

    // read the bm_file_header, i.e., first 14 bytes (just to get it out of the way);

    e_bmp_BYTE TempBYTE;
    for(int i = 14 ; i > 0 ; --i)
        SafeF_read((char *) &TempBYTE, sizeof(e_bmp_BYTE), 1, fp);

    // read the bm_info_header
    SafeF_read((char *) &(bm_info_header.biSize), sizeof(e_bmp_DWORD), 1, fp);
    SafeF_read((char *) &(bm_info_header.biWidth), sizeof(e_bmp_DWORD), 1, fp);
    SafeF_read((char *) &(bm_info_header.biHeight), sizeof(e_bmp_DWORD), 1, fp);
    SafeF_read((char *) &(bm_info_header.biPlanes), sizeof(e_bmp_WORD), 1, fp);

    SafeF_read((char *) &(bm_info_header.biBitCount), sizeof(e_bmp_WORD), 1, fp);
    SafeF_read((char *) &(bm_info_header.biCompression), sizeof(e_bmp_DWORD), 1, fp);
    SafeF_read((char *) &(bm_info_header.biSizeImage), sizeof(e_bmp_DWORD), 1, fp);
    SafeF_read((char *) &(bm_info_header.biXPlsPerMeter), sizeof(e_bmp_DWORD), 1, fp);

    SafeF_read((char *) &(bm_info_header.biYPlsPerMeter), sizeof(e_bmp_DWORD), 1, fp);
    SafeF_read((char *) &(bm_info_header.biClrUsed), sizeof(e_bmp_DWORD), 1, fp);
    SafeF_read((char *) &(bm_info_header.biClrImportant), sizeof(e_bmp_DWORD), 1, fp);

    fclose( fp );   // close the file

    if( IsBigEndian() ) bm_info_header.SwitchEndianess(); // switch the endianness if necessary
    return bm_info_header; // return the header
}

void DisplayBitmapInfo( const char* szFileNameIn ){ // display the bitmap information
    FILE* fp; // file pointer
    fp = fopen( szFileNameIn,"rb"); // open the file
    if( !fp  ) {
        if( BMP_warnings ) {
            cout << "BMP Error: Cannot initialize from file "
                 << szFileNameIn << "." << endl
                 << "               File cannot be opened or does not exist."
                 << endl;
        }
        return;
    }
    fclose( fp ); // close the file

    // don't duplicate work! Just use the functions from above!
    BMFH bm_file_header = Get_BM_File_Header(szFileNameIn); // get the bitmap file header
    BM_Info_Header bm_info_header = Get_BM_Info_Header(szFileNameIn); // get the bitmap information header

    cout << "File information for file " << szFileNameIn << ":" << endl << endl; // display the file name

    cout << "BITMAP FILE HEADER:" << endl
         << "bfType: " << bm_file_header.bfType << endl
         << "bfSize: " << bm_file_header.bfSize << endl
         << "bfReserved1: " << bm_file_header.bfReserved1 << endl
         << "bfReserved2: " << bm_file_header.bfReserved2 << endl
         << "bfOffBits: " << bm_file_header.bfOffBits << endl << endl;

    cout << "BIT MAP INFO HEADER:" << endl
         << "biSize: " << bm_info_header.biSize << endl
         << "biWidth: " << bm_info_header.biWidth << endl
         << "biHeight: " << bm_info_header.biHeight << endl
         << "biPlanes: " << bm_info_header.biPlanes << endl
         << "biBitCount: " << bm_info_header.biBitCount << endl
         << "biCompression: " << bm_info_header.biCompression << endl
         << "biSizeImage: " << bm_info_header.biSizeImage << endl
         << "biXPls_PerMeter: " << bm_info_header.biXPlsPerMeter << endl
         << "biYPls_PerMeter: " << bm_info_header.biYPlsPerMeter << endl
         << "biClrUsed: " << bm_info_header.biClrUsed << endl
         << "biClrImportant: " << bm_info_header.biClrImportant << endl << endl;
    //return;
}

int GetBitmapColorDepth( const char* szFileNameIn ){
    BM_Info_Header bm_info_header = Get_BM_Info_Header(szFileNameIn); // get the bitmap information header
    return (int) bm_info_header.biBitCount; // return the color depth
}

void PixelToPixelCopy( BMP& From, int FromX, int FromY, BMP& To, int ToX, int ToY){ // copy a pixel from one bitmap to another
    *To(ToX,ToY) = *From(FromX,FromY); // copy the pixel
    //return;
}

void PixelToPixelCopyTransparent(BMP& From, int FromX, int FromY, BMP& To, int ToX, int ToY, RGBA_pixel& Transparent ){ // copy a pixel from one bitmap to another
    // if the pixel is not transparent, copy it over to the destination
    if( From(FromX,FromY)->Red != Transparent.Red or From(FromX,FromY)->Green != Transparent.Green or From(FromX,FromY)->Blue != Transparent.Blue )
        *To(ToX,ToY) = *From(FromX,FromY);
    //return;
}

void RangedPixelToPixelCopy( BMP& From, int FromL , int FromR, int FromB, int FromT, BMP& To, int ToX, int ToY ){ // copy a range of pixels from one bitmap to another
    // make sure the conventions are followed
    if( FromB < FromT ) { int Temp = FromT; FromT = FromB; FromB = Temp; }

    // make sure that the copied regions exist in both bitmaps
    if( FromR >= From.TellWidth() ) FromR = From.TellWidth()-1;  // right
    if( FromL < 0 ) FromL = 0;  // left
    if( FromB >= From.TellHeight() ) FromB = From.TellHeight()-1; // bottom
    if( FromT < 0 ) FromT = 0;  // top
    if( ToX+(FromR-FromL) >= To.TellWidth() ) FromR = To.TellWidth()-1+FromL-ToX; // right
    if( ToY+(FromB-FromT) >= To.TellHeight() ) FromB = To.TellHeight()-1+FromT-ToY;  // bottom

    for(int j=FromT ; j <= FromB ; ++j)
        for(int i=FromL ; i <= FromR ; ++i)
            PixelToPixelCopy( From, i,j,To, ToX+(i-FromL), ToY+(j-FromT) ); // copy the pixel
    //return;
}

void RangedPixelToPixelCopyTransparent(BMP& From, int FromL , int FromR, int FromB, int FromT, BMP& To, int ToX, int ToY , RGBA_pixel& Transparent ){ // copy a range of pixels from one bitmap to another
    // make sure the conventions are followed
    if( FromB < FromT ){ int Temp = FromT; FromT = FromB; FromB = Temp; } // bottom < top

    // make sure that the copied regions exist in both bitmaps
    if( FromR >= From.TellWidth() ) FromR = From.TellWidth()-1; // right
    if( FromL < 0 ) FromL = 0;  // left
    if( FromB >= From.TellHeight() ) FromB = From.TellHeight()-1; // bottom
    if( FromT < 0 ) FromT = 0;  // top

    if( ToX+(FromR-FromL) >= To.TellWidth() ) FromR = To.TellWidth()-1+FromL-ToX; // right
    if( ToY+(FromB-FromT) >= To.TellHeight() ) FromB = To.TellHeight()-1+FromT-ToY; // bottom

    for(int j=FromT ; j <= FromB ; ++j )
        for(int i=FromL ; i <= FromR ; ++i )
            PixelToPixelCopyTransparent( From, i,j,To, ToX+(i-FromL), ToY+(j-FromT) ,Transparent); // copy the pixel
    //return;
}

bool CreateGrayscaleColorTable( BMP& InputImage ){ // create a grayscale color table
    int BitDepth = InputImage.TellBitDepth();
    if( BitDepth != 1 and BitDepth != 4 and BitDepth != 8 ) {
        if( BMP_warnings ){
            cout << "BMP Warning: Attempted to create color table at a bit" << endl
                 << "                 depth that does not require a color table." << endl
                 << "                 Ignoring request." << endl;
        }
        return false; // return false if the color table was not created
    }
    int i;
    int NumberOfColors = InputImage.TellNumberOfColors(); // get the number of colors

    e_bmp_BYTE StepSize;
    if( BitDepth != 1 ) StepSize = 255/(NumberOfColors-1); // get the step size
    else StepSize = 255;// get the step size

    for( i=0 ; i < NumberOfColors ; ++i ){ // loop through the colors  {
        e_bmp_BYTE TempBYTE = i * StepSize;
        RGBA_pixel TempColor;
        TempColor.Red = TempBYTE;
        TempColor.Green = TempBYTE;
        TempColor.Blue = TempBYTE;
        TempColor.Alpha = 0;
        InputImage.SetColor( i , TempColor ); // set the color
    }
    return true; // return true if the color table was created
}

bool BMP::Read32bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ){ // read a 32-bit row
    if( Width*4 > BufferSize ) return false; // return false if the buffer is too small
    for(int i=0 ; i < Width ; ++i ) memcpy( (char*) &(Pixels[i][Row]), (char*) Buffer+4*i, 4 ); // copy the row
    return true;
}

bool BMP::Read24bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ){ // read a 24-bit row
    if( Width*3 > BufferSize ) return false; // return false if the buffer is too small
    for(int i=0 ; i < Width ; ++i ) memcpy( (char*) &(Pixels[i][Row]), Buffer+3*i, 3 ); // copy the row
    return true;
}

bool BMP::Read8bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ){ // read an 8-bit row
    if( Width > BufferSize ) return false; // return false if the buffer is too small
    for(int i=0 ; i < Width ; ++i ) {
        int Index = Buffer[i]; // get the index
        *( this->operator()(i,Row) )= GetColor(Index); // copy the color
    }
    return true;
}

bool BMP::Read4bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ){ // read a 4-bit row
    int Shifts[2] = {4  ,0 }; // the shifts
    int Masks[2]  = {240,15}; // the masks

    int i=0;
    int j;
    int k=0;
    if( Width > 2*BufferSize ) return false; // return false if the buffer is too small
    while( i < Width ) { // loop through the row
        j=0;
        while( j < 2 && i < Width ){ // loop through the two pixels in the byte
            int Index = (int) ( (Buffer[k]&Masks[j]) >> Shifts[j]);
            *( this->operator()(i,Row) )= GetColor(Index);
            ++i; ++j;
        }
        ++k;
    }
    return true;
}

bool BMP::Read1bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ){ // read a 1-bit row
    int Shifts[8] = {7  ,6 ,5 ,4 ,3,2,1,0}; // the shifts
    int Masks[8]  = {128,64,32,16,8,4,2,1}; // the masks

    int i=0, k=0, j;
    if( Width > 8*BufferSize ) return false; // return false if the buffer is too small
    while( i < Width ) { // loop through the row
        j=0;
        while( j < 8 && i < Width ) { // loop through the eight pixels in the byte
            int Index = (int) ( (Buffer[k]&Masks[j]) >> Shifts[j]); // get the index
            *( this->operator()(i,Row) )= GetColor(Index); // copy the color
            ++i; ++j; // increment the counters
        }
        ++k; // increment the counter
    }
    return true; // return true if the row was read
}

bool BMP::Write32bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ){ // write a 32-bit row
    if( Width*4 > BufferSize ) return false; // return false if the buffer is too small
    for(int i=0 ; i < Width ; ++i)
        memcpy( (char*) Buffer+4*i, (char*) &(Pixels[i][Row]), 4 ); // copy the row
    return true; // return true if the row was written
}

bool BMP::Write24bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ){ // write a 24-bit row
    if( Width*3 > BufferSize ) return false; // return false if the buffer is too small
    for(int i=0 ; i < Width ; ++i )
        memcpy( (char*) Buffer+3*i,  (char*) &(Pixels[i][Row]), 3 ); // copy the row
    return true; // return true if the row was written
}

bool BMP::Write8bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ){ // write an 8-bit row
    if( Width > BufferSize ) return false; // return false if the buffer is too small
    for(int i=0 ; i < Width ; ++i )
        Buffer[i] = FindClosestColor( Pixels[i][Row] ); // find the closest color
    return true; // return true if the row was written
}

bool BMP::Write4bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ){ // write a 4-bit row
    int PositionWeights[2]  = {16,1}; // the weights for the positions
    int i=0, k=0, j; // loop counters
    if( Width > 2*BufferSize ) return false; // return false if the buffer is too small
    while( i < Width ){ // loop through the row
        j=0;
        int Index = 0;
        while( j < 2 and i < Width ){ // loop through the two pixels in the byte {
            Index += ( PositionWeights[j]* (int) FindClosestColor( Pixels[i][Row] ) );
            ++i; ++j;
        }
        Buffer[k] = (e_bmp_BYTE) Index;
        ++k; // increment the buffer index
    }
    return true; // return true if the row was written
}

bool BMP::Write1bitRow(e_bmp_BYTE* Buffer, int BufferSize, int Row ){ // write a 1-bit row
    int PositionWeights[8]  = {128,64,32,16,8,4,2,1}; // the weights for each position
    int i=0, k=0, j;
    if( Width > 8*BufferSize )  return false;
    while( i < Width ) { // loop through the row
        j=0;
        int Index = 0;
        while( j < 8 && i < Width ){ // loop through the two pixels in the byte
            Index += ( PositionWeights[j]* (int) FindClosestColor( Pixels[i][Row] ) ); // find the closest color
            ++i; ++j; // increment the counters
        }
        Buffer[k] = (e_bmp_BYTE) Index; // set the byte
        ++k; // increment the buffer index
    }
    return true; // return true if the row was written
}

e_bmp_BYTE BMP::FindClosestColor(RGBA_pixel& input ){
    int i=0;
    int NumberOfColors = TellNumberOfColors(); // get the number of colors
    e_bmp_BYTE BestI = 0; // the best index
    int BestMatch = 999999; // the best match

    while( i < NumberOfColors ) { // loop through all the colors
        RGBA_pixel Attempt = GetColor(i ); // get the color
        int TempMatch = IntSquare( (int) Attempt.Red - (int) input.Red )
                        + IntSquare( (int) Attempt.Green - (int) input.Green )
                        + IntSquare( (int) Attempt.Blue - (int) input.Blue ); // find the distance
        if( TempMatch < BestMatch ) BestI = (e_bmp_BYTE) i; BestMatch = TempMatch; if(BestMatch == 0 ) break;
        if( BestMatch < 1 )i = NumberOfColors; // if the best match is perfect, stop
        ++i; // increment the counter
    }
    return BestI; // return the index of the best match
}

bool BMP_check_Data_Size(){
    bool ReturnValue = true;
    if(sizeof( e_bmp_BYTE ) != 1 ) { // check the size of the data types
        if( BMP_warnings ){ // if the user wants warnings
            cout << "BMP Error: e_bmp_BYTE has the wrong size ("
                 << sizeof( e_bmp_BYTE ) << " bytes)," << endl
                 << "               Compared to the expected 1 byte value" << endl;
        }
        ReturnValue = false; // return false if there is a problem
    }
    if(sizeof( e_bmp_WORD ) != 2 ) { // check the size of the data types
        if( BMP_warnings ) { // if the user wants warnings
            cout << "BMP Error: e_bmp_WORD has the wrong size ("
                 << sizeof( e_bmp_WORD ) << " bytes)," << endl
                 << "               Compared to the expected 2 byte value" << endl;
        }
        ReturnValue = false; // return false if the size is wrong
    }
    if(sizeof( e_bmp_DWORD ) != 4 ){ // this is the most common error
        if( BMP_warnings ){ // so we check for it first
            cout << "BMP Error: e_bmp_DWORD has the wrong size ("
                 << sizeof( e_bmp_DWORD ) << " bytes)," << endl
                 << "               Compared to the expected 4 byte value" << endl;
        }
        ReturnValue = false; // and we return false
    }
    return ReturnValue; // if we get here, everything is OK
}

bool Rescale( BMP& InputImage , char mode, int NewDimension ){ // mode = 'w' or 'h' or 'b' (both)
    int CapMode = toupper( mode ); // make sure it's upper case
    BMP OldImage( InputImage ); // make a copy of the input image

    if( CapMode != 'P' and CapMode != 'W' and CapMode != 'H' and CapMode != 'F' ) {
        if( BMP_warnings ){
            char ErrorMessage [1024]; // 1024 is a safe size
            sprintf( ErrorMessage, "BMP Error: Unknown rescale mode %c requested\n" , mode );
            cout << ErrorMessage;
        }
        return false;
    }

    int NewWidth  =0;
    int NewHeight =0;

    int OldWidth = OldImage.TellWidth(); // get the old dimensions
    int OldHeight= OldImage.TellHeight(); // these are ints

    if( CapMode == 'P' ){
        NewWidth = (int) floor( OldWidth * NewDimension / 100.0 ); // percent
        NewHeight = (int) floor( OldHeight * NewDimension / 100.0 ); // percent
    }
    if( CapMode == 'F' ){
        if( OldWidth > OldHeight ) CapMode = 'W'; // landscape
        else CapMode = 'H'; // portrait
    }

    if( CapMode == 'W' ){
        double percent = (double) NewDimension / (double) OldWidth; // percent
        NewWidth = NewDimension;    // new width
        NewHeight = (int) floor( OldHeight * percent ); // new height
    }
    if( CapMode == 'H' ){
        double percent = (double) NewDimension / (double) OldHeight; // 1.5
        NewHeight = NewDimension; // 100
        NewWidth = (int) floor( OldWidth * percent ); // 150
    }

    if( NewWidth < 1 ) NewWidth = 1; // sanity check
    if( NewHeight < 1 ) NewHeight = 1; // sanity check

    InputImage.SetSize( NewWidth, NewHeight ); // this clears the image
    InputImage.SetBitDepth( 24 ); // always 24-bit

    int I,J;
    double ThetaI,ThetaJ;

    for( int j=0; j < NewHeight-1 ; ++j ){
        ThetaJ = (double)(j*(OldHeight-1.0))
                 /(double)(NewHeight-1.0);
        J	= (int) floor( ThetaJ );
        ThetaJ -= J; // ThetaJ is now the fractional part of ThetaJ
        for( int i=0; i < NewWidth-1 ; ++i ){
            ThetaI = (double)(i*(OldWidth-1.0))
                     /(double)(NewWidth-1.0);
            I = (int) floor( ThetaI );
            ThetaI -= I;

            InputImage(i,j)->Red = (e_bmp_BYTE)
                    ( (1.0-ThetaI-ThetaJ+ThetaI*ThetaJ)*(OldImage(I,J)->Red)
                      +(ThetaI-ThetaI*ThetaJ)*(OldImage(I+1,J)->Red)
                      +(ThetaJ-ThetaI*ThetaJ)*(OldImage(I,J+1)->Red)
                      +(ThetaI*ThetaJ)*(OldImage(I+1,J+1)->Red) );
            InputImage(i,j)->Green = (e_bmp_BYTE)
                    ( (1.0-ThetaI-ThetaJ+ThetaI*ThetaJ)*OldImage(I,J)->Green
                      +(ThetaI-ThetaI*ThetaJ)*OldImage(I+1,J)->Green
                      +(ThetaJ-ThetaI*ThetaJ)*OldImage(I,J+1)->Green
                      +(ThetaI*ThetaJ)*OldImage(I+1,J+1)->Green );
            InputImage(i,j)->Blue = (e_bmp_BYTE)
                    ( (1.0-ThetaI-ThetaJ+ThetaI*ThetaJ)*OldImage(I,J)->Blue
                      +(ThetaI-ThetaI*ThetaJ)*OldImage(I+1,J)->Blue
                      +(ThetaJ-ThetaI*ThetaJ)*OldImage(I,J+1)->Blue
                      +(ThetaI*ThetaJ)*OldImage(I+1,J+1)->Blue );
        }
        InputImage(NewWidth-1,j)->Red = (e_bmp_BYTE)
                ( (1.0-ThetaJ)*(OldImage(OldWidth-1,J)->Red)
                  + ThetaJ*(OldImage(OldWidth-1,J+1)->Red) );
        InputImage(NewWidth-1,j)->Green = (e_bmp_BYTE)
                ( (1.0-ThetaJ)*(OldImage(OldWidth-1,J)->Green)
                  + ThetaJ*(OldImage(OldWidth-1,J+1)->Green) );
        InputImage(NewWidth-1,j)->Blue = (e_bmp_BYTE)
                ( (1.0-ThetaJ)*(OldImage(OldWidth-1,J)->Blue)
                  + ThetaJ*(OldImage(OldWidth-1,J+1)->Blue) );
    }

    for( int i=0 ; i < NewWidth-1 ; ++i ){
        ThetaI = (double)(i*(OldWidth-1.0))
                 /(double)(NewWidth-1.0); // ThetaI = 0.0;
        I = (int) floor( ThetaI ); // I is the integer part of ThetaI
        ThetaI -= I;
        InputImage(i,NewHeight-1)->Red = (e_bmp_BYTE)
                ( (1.0-ThetaI)*(OldImage(I,OldHeight-1)->Red)
                  + ThetaI*(OldImage(I,OldHeight-1)->Red) ); // I+1
        InputImage(i,NewHeight-1)->Green = (e_bmp_BYTE)
                ( (1.0-ThetaI)*(OldImage(I,OldHeight-1)->Green)
                  + ThetaI*(OldImage(I,OldHeight-1)->Green) ); // I+1
        InputImage(i,NewHeight-1)->Blue = (e_bmp_BYTE)
                ( (1.0-ThetaI)*(OldImage(I,OldHeight-1)->Blue)
                  + ThetaI*(OldImage(I,OldHeight-1)->Blue) ); // I+1
    }

    *InputImage(NewWidth-1,NewHeight-1) = *OldImage(OldWidth-1,OldHeight-1); // copy the last pixel
    return true; // success
}
