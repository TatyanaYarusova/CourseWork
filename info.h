#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#pragma pack (push, 1)
typedef struct
{
	unsigned short signature;
	unsigned int filesize;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned int pixelArrOffset;
}BitmapFileHeader;

typedef struct
{
	unsigned int headerSize;
	unsigned int width;
	unsigned int height;
	unsigned short planes;
	unsigned short bitsPerPixel; // 24 bit
	unsigned int compression; // 0
	unsigned int imageSize;
	unsigned int xPixelsPerMeter;
	unsigned int yPixelsPerMeter;
	unsigned int colorsInColorTable; // 0
	unsigned int importantColorCount;
}BitmapInfoHeader;

typedef struct
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
}Rgb;

#pragma pack(pop)

typedef struct Point{
	int n; // строка
	int m; // столбец
}Point;


//Collage
void colBmp(Rgb** arr, int M, int N, BitmapFileHeader bmfh, BitmapInfoHeader bmif, char* file_out);
int collage(BitmapFileHeader bmfh, BitmapInfoHeader bmif, Rgb** arr, int argc, char **argv,int opt, int longIndex);
//Collage

//rectangle
void check_color(char* color);
void color(Rgb* elem, char* c);
void recBmp(BitmapFileHeader bmfh, BitmapInfoHeader bmif, Rgb** arr, Point left_corner, Point right_corner, int line, char* color_line, char* fill, char* color_rec, char* file_out);
int rectangle(BitmapFileHeader bmfh, BitmapInfoHeader bmif, Rgb** arr, int argc, char **argv,int opt, int longIndex);
//rectangle

//Reflection
void swap(Rgb *a, Rgb *b);
void refBmp(Rgb** arr, Point left_corner, Point right_corner, BitmapFileHeader bmfh, BitmapInfoHeader bmif, char* axis, char* file_out);
int reflection(BitmapFileHeader bmfh, BitmapInfoHeader bmif, Rgb** arr, int argc, char **argv,int opt, int longIndex);
//Reflection

//Demon
void width(Rgb** arr, int x, int y, int line, int h, int w, char* c);
void drawLine(Rgb** arr,int x1, int y1, int x2, int y2, int line, int h, int w, char* c);
void drawStar(Rgb** arr, Point center, int r, int line, char* c, int h, int w);
void drawCircle(Rgb** arr, Point center, int R, int line, int h, int w, char* c);
void starBmp(BitmapFileHeader bmfh, BitmapInfoHeader bmif, Rgb** arr, Point center, int Radius, int line, char* color, char* file_out);
int demon(BitmapFileHeader bmfh, BitmapInfoHeader bmif, Rgb** arr, int argc, char **argv,int opt, int longIndex);
//Demon

//Help
void printHelp();
void free_memory(Rgb** arr, int height);
//Help

