#include "bmpimg.h"

int main() {
    FILE* fp = init_bmp();

    RGBTRIPLE pixel;

    double px[2];
    unsigned int origin[2] = {IMG_WIDTH/2 + 400, IMG_HEIGHT/2};
    _Complex double z;
    RGBTRIPLE image[IMG_HEIGHT][IMG_WIDTH];

    for (int i = 0; i < IMG_HEIGHT; i++) {
        for (int j = 0; j < IMG_WIDTH; j++) {
            px[0] = j;
            px[1] = i;
            px_to_cart(px, origin, SCALE); //changes values in px array to cartesian coordinates
            z = I*px[1]+px[0];
            //pixel = plot_px(func(z));
            //pixel = mandelbrot(z);
            image[i][j] = plot_px(mandelbrot(z));
            //fwrite(&pixel, sizeof(RGBTRIPLE), 1, fp);
        }
        //fwrite(image, IMG_WIDTH * sizeof(RGBTRIPLE), 1, fp);
        for (int k = 0; k < (4 - (IMG_WIDTH * sizeof(RGBTRIPLE)) % 4) % 4; k++) {
            //fputc(0x00, fp);

        }
    }
    fwrite(image, IMG_HEIGHT * IMG_WIDTH * sizeof(RGBTRIPLE), 1, fp);

    fclose(fp);

}