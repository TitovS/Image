//
// Created by Сергей Титов on 19/05/16.
//

#include "Img.h"
#include <stdio.h>
#include "string.h"


Img::Img(unsigned short BCount, int Width, int Height, unsigned char Mode) {


    BMInfoHeader.Size = 40;           // Число байтов необходимое для структуры = 40
    BMInfoHeader.Width = Width;          // Ширина точечного рисунка в пикселях
    BMInfoHeader.Height = Height;         // Высота точечного рисунка в пикселях
    BMInfoHeader.Planes = 1;         // Число плоскостей целевого устройства = 1
    BMInfoHeader.BitCount = BCount;       // Глубина цвета, число бит на точку = 0,1,4,8,16,24,32
    BMInfoHeader.Compression = 0;    // Тип сжатия = 0 для несжатого изображения
    BMInfoHeader.SizeImage = Width * Height * BMInfoHeader.BitCount;      // Размер изображения в байтах BitCount*Height*Width
    BMInfoHeader.XPelsPerMeter = 11808;  // Разрешающая способность по горизонтали
    BMInfoHeader.YPelsPerMeter = 11808;  // Разрешающая способность по вертикали
    BMInfoHeader.ColorUsed = 0;      // Число индексов используемых цветов. Если все цвета = 0
    BMInfoHeader.ColorImportant = 0; // Число необходимых цветов = 0

    if (BMInfoHeader.BitCount == 24) {

// Выделение памяти для двумерного массива размером Height*Width типа RGBTRIPLE

        Rgbtriple = new RGBTRIPLE[BMInfoHeader.Height * BMInfoHeader.Width];


// Заполнение данных изображения

        for (int i = 0; i < BMInfoHeader.Width; i++)
            for (int j = 0; j < BMInfoHeader.Height; j++) {
                Rgbtriple[i*BMInfoHeader.Width+j].Red = Mode;
                Rgbtriple[i*BMInfoHeader.Width+j].Green = Mode;
                Rgbtriple[i*BMInfoHeader.Width+j].Blue = Mode;
            }


    }

}

Img::Img(char const *fileName){

    BITMAPFILEHEADER BMFileHeader;

    FILE *f;

    char const *pchar = fileName;

    f = fopen(pchar,"rb");

    fread(&BMFileHeader,sizeof(BITMAPFILEHEADER),1,f);

    fseek(f, BMFileHeader.OffsetBits, SEEK_SET);

    fread(&BMInfoHeader,sizeof(BMInfoHeader),1,f);


    if (BMInfoHeader.BitCount == 24) {

        Rgbtriple = new RGBTRIPLE[BMInfoHeader.Height * BMInfoHeader.Width];
        fseek(f, BMInfoHeader.Size+BMFileHeader.OffsetBits, SEEK_SET);
        fread(Rgbtriple, BMInfoHeader.SizeImage, 1, f);

    }


}


Img::Img(void) {

    BMInfoHeader.Size = NULL;           // Число байтов необходимое для структуры = 40
    BMInfoHeader.Width = NULL;          // Ширина точечного рисунка в пикселях
    BMInfoHeader.Height = NULL;         // Высота точечного рисунка в пикселях
    BMInfoHeader.Planes = NULL;         // Число плоскостей целевого устройства = 1
    BMInfoHeader.BitCount = NULL;       // Глубина цвета, число бит на точку = 0,1,4,8,16,24,32
    BMInfoHeader.Compression = NULL;    // Тип сжатия = 0 для несжатого изображения
    BMInfoHeader.SizeImage = NULL;      // Размер изображения в байтах BitCount*Height*Width
    BMInfoHeader.XPelsPerMeter = NULL;  // Разрешающая способность по горизонтали
    BMInfoHeader.YPelsPerMeter = NULL;  // Разрешающая способность по вертикали
    BMInfoHeader.ColorUsed = NULL;      // Число индексов используемых цветов. Если все цвета = 0
    BMInfoHeader.ColorImportant = NULL; // Число необходимых цветов = 0


}

Img::~Img (){

    delete[] Rgbtriple;

};



Img::Img(const Img &i) {


    Img(i.BMInfoHeader.BitCount,i.BMInfoHeader.Width,i.BMInfoHeader.Height,'b');
    memcpy(Rgbtriple,i.Rgbtriple,BMInfoHeader.SizeImage);


}


Img& Img::operator=(const Img& Inp) {

    if (this == &Inp)
        return (*this);


    BMInfoHeader.Width = Inp.BMInfoHeader.Width;
    BMInfoHeader.Height = Inp.BMInfoHeader.Height;
    BMInfoHeader.BitCount = Inp.BMInfoHeader.BitCount;
    BMInfoHeader.SizeImage = Inp.BMInfoHeader.SizeImage;

    memcpy(Rgbtriple,Inp.Rgbtriple,BMInfoHeader.SizeImage);

    return (*this);

}


void Img::writeimage(char *fileName, Img image) {


    FILE * pFile;
    pFile = fopen (fileName, "rb");

    BITMAPFILEHEADER BMFileHeader;

    BMFileHeader.Type = 'BM';     // ‘BM’ 0x4D42
    BMFileHeader.Size = image.BMInfoHeader.BitCount*image.BMInfoHeader.Width*image.BMInfoHeader.Height;     // Размер файла в байтах, BitCount*Height*Width+ OffsetBits
    BMFileHeader.Reserved1 = 0;    // Зарезервирован; должен быть нуль
    BMFileHeader.Reserved2 = 54;    // Зарезервирован; должен быть нуль
    BMFileHeader.OffsetBits = 2621440;   // Смещение данных от начала файла в байтах


    fwrite (&BMFileHeader , sizeof(BITMAPFILEHEADER), 1, pFile);

    fseek(pFile, BMFileHeader.OffsetBits, SEEK_SET);

    fwrite(&BMInfoHeader,sizeof(BMInfoHeader),1,pFile);


    fseek(pFile, BMInfoHeader.Size+BMFileHeader.OffsetBits, SEEK_SET);
    fwrite(Rgbtriple, BMInfoHeader.SizeImage, 1, pFile);


    fclose (pFile);

}
int Img::loadimage(char *fileName){



};