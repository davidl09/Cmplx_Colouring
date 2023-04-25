//
// Created by dalae on 2023-04-18.
//

#ifndef MANDELBROT_BMPIMG_H
#define MANDELBROT_BMPIMG_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define IMG_WIDTH 10000
#define IMG_HEIGHT 10000
#define MAX_ITER 255
#define func(z) ccos(z) * cexp(cpow(z, 3))
//(I * carg(z) * cabs(z) * exp((cpow(z, 3) + cpow(z, z))))
//(((cpow(z, 2) - 1)*cpow(z - 2 - I, 2))/(cpow(z, 2) + 2 + 2*I))
//(0.4*cpow((z), 5) + 3 * cpow(z, 3) - cpow(z, 2) + 5*z)/(cpow(I*z, 5))
//csin(3*carg(cexp(I *  (cabs(z) - carg(z))))) * cexp(I *  (cabs(z) - carg(z))) //spiral
//(0.4*cpow((z), 5) + 3 * cpow(z, 3) - cpow(z, 2) + 5*z)
//z*cexp(I * 2 * carg(z))
//cpow(M_E, I*carg(z))
//cos(cimag(z))+I*csin((creal(z))) //grid
//cpow(z, 2) + 1
//cpow(M_E, ccos(z))
//(((cpow(z, 2) - 1)*cpow(z - 2 - I, 2))/(cpow(z, 2) + 2 + 2*I))
#define SCALE 4000

;
#pragma pack(push, 1)
typedef struct {
    unsigned char bfType[2];
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
    unsigned int biSize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
} BITMAPINFOHEADER;

typedef struct {
    unsigned char rgbtBlue;
    unsigned char rgbtGreen;
    unsigned char rgbtRed;
} RGBTRIPLE;

#pragma pack(pop)
void* init_bmp();
RGBTRIPLE plot_px(_Complex double num);
double* px_to_cart(double px[2], unsigned int origin[2], double scale_fact);
RGBTRIPLE mandelbrot(_Complex double c);
_Complex double integral(void* func, double a, double b, double dx);
_Complex double zeta(_Complex double z);
_Complex double gamma_(_Complex double z);

#endif //MANDELBROT_BMPIMG_H
