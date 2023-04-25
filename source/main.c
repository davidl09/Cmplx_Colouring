#include "bmpimg.h"

int main() {
    FILE* fp = init_bmp();

    double px[2];
    unsigned int origin[2] = {IMG_WIDTH/2, IMG_HEIGHT/2};
    _Complex double z;
    RGBTRIPLE** image = malloc(IMG_HEIGHT * IMG_WIDTH * sizeof(RGBTRIPLE));

    for (int i = 0; i < IMG_HEIGHT; i++) {
        image[i] = malloc(IMG_WIDTH * sizeof(RGBTRIPLE));
        for (int j = 0; j < IMG_WIDTH; j++) {
            px[0] = j;
            px[1] = i;
            px_to_cart(px, origin, SCALE); //changes values in px array to cartesian coordinates
            z = I*px[1]+px[0];
            image[i][j] = plot_px(func(z));
        }
        fwrite(image[i], IMG_WIDTH * sizeof(RGBTRIPLE), 1, fp);
        for (unsigned int k = 0; k < (4 - (IMG_WIDTH * sizeof(RGBTRIPLE)) % 4) % 4; k++) {
            fputc(0x00, fp);
        }
    }
    free(image);
    fclose(fp);
}