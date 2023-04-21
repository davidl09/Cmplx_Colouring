#include "bmpimg.h"

int main() {
    FILE* fp = init_bmp();

    RGBTRIPLE pixel;

    double px[2];
    unsigned int origin[2] = {IMG_WIDTH/2, IMG_HEIGHT/2};
    //unsigned int origin[2] = {0, 0};
    _Complex double z;

    for (int i = 0; i < IMG_HEIGHT; i++) {
        for (int j = 0; j < IMG_WIDTH; j++) {
            px[0] = j;
            px[1] = i;
            px_to_cart(px, origin, SCALE); //changes values in px array to cartesian coordinates
            z = I*px[1]+px[0];
            pixel = plot_px(func(z));
            fwrite(&pixel, sizeof(RGBTRIPLE), 1, fp);
        }
        for (int k = 0; k < (4 - (IMG_WIDTH * sizeof(RGBTRIPLE)) % 4) % 4; k++) {
            fputc(0x00, fp);
        }
    }

    fclose(fp);
/*
    printf("Applying the mandelbrot sequence\n");
    double real;
    double img;
    _Complex double cmplx;

    while(1){
        printf("Enter the real component of the c constant for the mandelbrot iteration\n");
        scanf("%lf", &real);
        printf("Enter the imaginary component\n");
        scanf("%lf", &img);
        cmplx = I*img + real;
        printf("You have entered the following complex number: %f + %fi\n", creal(cmplx), cimag(cmplx));
        printf("(%f + %fi)^2 = %f + %fi\n", creal(cmplx), cimag(cmplx), creal(cpow(cmplx, 2)), cimag(cpow(cmplx, 2)));
    }
     */
}