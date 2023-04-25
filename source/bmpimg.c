//
// Created by dalae on 2023-04-18.
//

#include "bmpimg.h"

void* init_bmp(){
    FILE *fp = fopen("cmplxcolor.bmp", "wb");
    if (fp == NULL) {
        printf("Could not open file for writing.\n");
        return NULL;
    }

    BITMAPFILEHEADER bfh = {0};
    bfh.bfType[0] = 'B';
    bfh.bfType[1] = 'M';
    bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + IMG_HEIGHT * IMG_WIDTH * sizeof(RGBTRIPLE);
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    BITMAPINFOHEADER bih = {0};
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = IMG_WIDTH;
    bih.biHeight = IMG_HEIGHT;
    bih.biPlanes = 1;
    bih.biBitCount = 24;

    fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fp);
    fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fp);

    return fp;
}

RGBTRIPLE plot_px(_Complex double num){
    double mag = cabs(num);
    double argz = carg(num);

    mag = -1.0/(mag + 1) + 1;

    RGBTRIPLE px;
    px.rgbtBlue = (unsigned char)(mag*(127.5*sin(argz) + 127.5)); //assign colour based on cyclic function taking in argz
    px.rgbtGreen = (unsigned char)(mag*(127.5*sin(argz + 2*M_PI/3) + 127.5));
    px.rgbtRed = (unsigned char)(mag*(127.5*sin(argz + 4*M_PI/3) + 127.5));

    return px;
}

double* px_to_cart(double px[2], unsigned int origin[2], double scale_fact){
    //origin is the pixel coordinate of the origin on the pixel map
    for (int i = 0; i < 2; ++i) {
        px[i] = (double)(px[i] - origin[i])/scale_fact;
    }
    return px;
}

RGBTRIPLE mandelbrot(_Complex double c){
    _Complex double z = 0;
    int n = 0;
    while(cabs(z) <= 2 && n < MAX_ITER){
        z = cpow(z, 2) + c;
        n++;
    }
    if(n == MAX_ITER)
        return (RGBTRIPLE){0, 0, 0};

    return (RGBTRIPLE){255 - n, 125 - n/2, 0};
}

double complex gamma_(double complex z) {
if (creal(z) < 0.5) {
        // Use reflection formula for better accuracy for small real parts
        return M_PI / (csin(M_PI * z) * gamma(1.0 - z));
    }
    
    double complex result = 1.0;
    while (creal(z) < 10.0) {
        // Incrementally multiply with terms of the product formula
        result *= z;
        z += 1.0;
    }

    // Compute the gamma function using the product formula
    result *= cexp(-z * clog(z) + z - 0.5 * clog(2.0 * M_PI / z));
    return result;
}