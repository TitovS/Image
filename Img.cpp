//
// Created by Сергей Титов on 19/05/16.
//

#include "Img.h"


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