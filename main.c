#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// clang-format off
static int GX[3][3] = {
    {-1, 0, 1}, 
    {-2, 0, 2}, 
    {-1, 0, 1}
};

static int GY[3][3] = {
    {1 ,  2,  1}, 
    {0 ,  0,  0}, 
    {-1, -2, -1}
};


static int ROWS[3] = {
    -1, 0, 1
};

static int COLS[3][3] = {
    { -1, 0, 1 }, { -1, 0, 1 }, { -1, 0, 1 }
};
// clang-format on

int get_array_index(int row, int col, int width, int height, int channels) { return (row * width + col) * channels; }

int main() {
    char *image_name = "mountains.png";

    int height, width, channels;
    stbi_uc *img_data = stbi_load(image_name, &width, &height, &channels, 0);

    if (img_data == NULL) {
        printf("Failed to load image '%s'\n", image_name);
        return -1;
    }

    printf("Image: '%s', height: %d, width: %d, channels: %d\n", image_name, height, width, channels);

    static int target_img_channels = 3;

    uint8_t *new_pixels = calloc(width * height * target_img_channels, 1);

    if (new_pixels == NULL) {
        printf("malloc failed. Buy more ram\n");
        return -1;
    }

    for (int irow = 0; irow < height; irow++) {
        for (int icol = 0; icol < width; icol++) {
            if (irow == 0 || irow == height - 1 || icol == 0 || icol == width - 1) {
                continue;
            }

            int gx = 0;
            int gy = 0;

            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    int actual_row = irow + ROWS[x];
                    int actual_col = icol + COLS[x][y];

                    int img_index = get_array_index(actual_row, actual_col, width, height, channels);

                    gx += GX[x][y] * img_data[img_index];
                    gy += GY[x][y] * img_data[img_index];
                }
            }

            int new_pixels_idx = get_array_index(irow, icol, width, height, target_img_channels);
            int value = abs(gx) + abs(gy);

            new_pixels[new_pixels_idx] = value;
            new_pixels[new_pixels_idx + 1] = value;
            new_pixels[new_pixels_idx + 2] = value;
        }
    }

    stbi_write_png("output.png", width, height, target_img_channels, new_pixels, 0);

    return 0;
}
