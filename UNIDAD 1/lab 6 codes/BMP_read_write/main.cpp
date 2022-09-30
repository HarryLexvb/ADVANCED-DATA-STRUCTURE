#include <iostream>

using namespace std;

typedef struct bmpFileHeader
{
    //2 bytes de identificación
    uint32_t size;        // Tamaño del archivo
    uint16_t reserve1;       // Reservado
    uint16_t reserve2;       // Reservado
    uint32_t offset;      // Offset hasta hasta los datos de imagen
} bmpFileHeader;

typedef struct bmpInfoHeader
{
    uint32_t header_size;      /* Tamaño de la cabecera */
    uint32_t width;       /* Ancho */
    uint32_t height;      /* Alto */
    uint16_t plans;          /* Planos de color (Siempre 1) */
    uint16_t bpp;             /* bits por pixel */
    uint32_t compress;        /* compresión */
    uint32_t img_size;     /* tamaño de los datos de imagen */
    uint32_t bpmx;        /* Resolución X en bits por metro */
    uint32_t bpmy;        /* Resolución Y en bits por metro */
    uint32_t colors;      /* colors used en la paleta */
    uint32_t imxt_colors;      /* Colores importantes. 0 si son todos */
} bmpInfoHeader;

unsigned char *LoadBMP(char *filename, bmpInfoHeader *bInfoHeader);
void DisplayInfo(bmpInfoHeader *info);
void TextDisplay(bmpInfoHeader *info, const unsigned char *img);
void writeBMP(char *filename, bmpInfoHeader *bInfoHeader, unsigned char *img);
void Negative(bmpInfoHeader *info, unsigned char *img);

int main(){
    bmpInfoHeader info;
    unsigned char *img;

    img=LoadBMP((char *)R"(C:\Users\win 10\Documents\CLION\BMP_read_write\test.bmp)", &info);
    DisplayInfo(&info);
    TextDisplay(&info, img);
    Negative(&info, img);
    writeBMP((char *)R"(C:\Users\win 10\Documents\CLION\BMP_read_write\output_test5.bmp)", &info, img);
    free(img);
    system("pause");
}
void TextDisplay(bmpInfoHeader *info, const unsigned char *img)
{
    int x, y;
    /* Reducimos la resolución vertical y horizontal para que la imagen entre en pantalla */
    static const int reductionX=6, reductionY=4;
    /* Si la componente supera el limit, el color se marcará como 1. */
    static const int limit=90; // limite
    /* Asignamos caracteres a los colors en pantalla */
    static unsigned char colors[9]=" bgfrRGB";
    int r,g,b;

    /* Dibujamos la imagen */
    for(y=0; y<info->height; y+=reductionY)
    {
        for(x=0; x<info->width; x+=reductionX)
        {
            /* Obtenemos el color de la imagen */
            b=img[(x+y*info->width)*3];
            g=img[(x+y*info->width)*3+1];
            r=img[(x+y*info->width)*3+2];

            /* Calculamos el color de la imagen */
            int color=0;
            if(r > limit) color+=4;
            if(g > limit) color+=2;
            if(b > limit) color+=1;

            /* Mostramos el color */
            cout << colors[color];
        }
        cout << endl;
    }
}
unsigned char *LoadBMP(char *filename, bmpInfoHeader *bInfoHeader)
{

    FILE *f;
    bmpFileHeader header;     /* cabecera */
    unsigned char *img_data;   /* datos de imagen */
    uint16_t type;        /* 2 bytes identificativos */

    f=fopen (filename, "r");
    if (!f)
        return nullptr;        /* Si no podemos leer, no hay imagen*/

    /* Leemos los dos primeros bytes */
    fread(&type, sizeof(uint16_t), 1, f);
    if (type !=0x4D42)        /* Comprobamos el formato */
    {
        fclose(f);
        return nullptr;
    }

    /* Leemos la cabecera de fichero completa */
    fread(&header, sizeof(bmpFileHeader), 1, f);

    /* Leemos la cabecera de información completa */
    fread(bInfoHeader, sizeof(bmpInfoHeader), 1, f);

    /* Reservamos memoria para la imagen, ¿cuánta?
       Tanto como indique img_size */
    img_data=(unsigned char*)malloc(bInfoHeader->img_size);

    /* Nos situamos en el sitio donde empiezan los datos de imagen,
     nos lo indica el offset de la cabecera de fichero*/
    //fseek(f, header.offset, SEEK_SET);
    fseek(f, 54, SEEK_SET);

    /* Leemos los datos de imagen, tantos bytes como img_size */
    fread(img_data, bInfoHeader->img_size, 1, f);

    /* Cerramos */
    fclose(f);

    /* Devolvemos la imagen */
    return img_data;
}
void DisplayInfo(bmpInfoHeader *info)
{
    cout << "Header size: " << info->header_size << endl;
    cout << "Width: " << info->width << endl;
    cout << "Height: " << info->height << endl;
    cout << "Planes: " << info->plans << endl;
    cout << "BPP: " << info->bpp << endl;
    cout << "Compression: " << info->compress << endl;
    cout << "Image size: " << info->img_size << endl;
    cout << "Horizontal resolution: " << info->bpmx << endl;
    cout << "Vertical resolution: " << info->bpmy << endl;
    cout << "Colors in palette: " << info->colors << endl;
    cout << "Important colors: " << info->imxt_colors << endl;
}
void writeBMP(char *filename, bmpInfoHeader *bInfoHeader, unsigned char *img){
    FILE *f;
    bmpFileHeader header;     /* cabecera */
    uint16_t type;        /* 2 bytes identificativos */

    f=fopen (filename, "w");
    if (!f)
        return;        /* Si no podemos leer, no hay imagen*/

    /* Escribimos los dos primeros bytes */
    type = 0x4D42;
    fwrite(&type, sizeof(uint16_t), 1, f);

    /* Escribimos la cabecera de fichero completa */
    fwrite(&header, sizeof(bmpFileHeader), 1, f);

    /* Escribimos la cabecera de información completa */
    fwrite(bInfoHeader, sizeof(bmpInfoHeader), 1, f);

    /* Nos situamos en el sitio donde empiezan los datos de imagen,
     nos lo indica el offset de la cabecera de fichero*/
    //fseek(f, header.offset, SEEK_SET);
    fseek(f, 54, SEEK_SET); //54

    /* Escribimos los datos de imagen, tantos bytes como img_size */
    fwrite(img, bInfoHeader->img_size, 1, f);

    /* Cerramos */
    fclose(f);
}
void Negative(bmpInfoHeader *info, unsigned char *img)
{
    int x, y;
    int r,g,b;

    for(y=0; y<info->height; y++)
    {
        for(x=0; x<info->width; x++)
        {
            /* Obtenemos el color de la imagen */
            b=img[(x+y*info->width)*3];
            g=img[(x+y*info->width)*3+1];
            r=img[(x+y*info->width)*3+2];

            /* Calculamos el color de la imagen */
            r=255-r;
            g=255-g;
            b=255-b;

            /* Mostramos el color */
            img[(x+y*info->width)*3] = r;
            img[(x+y*info->width)*3+1] = g;
            img[(x+y*info->width)*3+2] = b;
        }
    }
}
