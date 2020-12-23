#include "bmp_comparer.h"
#include "bmp_validate.h"

int compare_headers(bmp_header_t *first_header, bmp_header_t *second_header)
{
    if(first_header->file_size != second_header->file_size)
    {
        return error("Files sizes are different.", UNSUCCESSFUL_EXIT_CODE);
    }
    return SUCCESSFUL_EXIT_CODE;
}

int palette_compare(const word_t *first_palette, const word_t *second_palette)
{
    for(int i = 0; i < BMP_8_PALETTE_SIZE; i++)
    {
        if(first_palette[i] != second_palette[i])
        {
            return error("BMP palettes are different.", UNSUCCESSFUL_EXIT_CODE);
        }
    }
    return SUCCESSFUL_EXIT_CODE;
}

int compare_bmp_8_pixels(FILE* first_bmp, FILE* second_bmp, int image_size, int image_width)
{
    int different_pixel_count = 0, pixel_count = 0;
    int *first_byte = malloc(sizeof(word_t)), *second_byte = malloc(sizeof(word_t));
    while(!feof(first_bmp) && ((*first_byte = fgetc(first_bmp)) != EOF) &&
          !feof(second_bmp) && ((*second_byte = fgetc(second_bmp)) != EOF))
    {
        if(*first_byte != *second_byte && different_pixel_count < MAX_DIFFERENT_PIXELS)
        {
            different_pixel_count++;
            error_print("%d %d\n", pixel_count % image_width, pixel_count / image_width);
        }
        pixel_count++;
    }
    free(first_byte);
    free(second_byte);
    return check_colors_count(pixel_count, image_size, UNSUCCESSFUL_EXIT_CODE);
}

int compare_bmp_24_pixels(FILE* first_bmp, FILE* second_bmp, int image_size, int image_width)
{
    int different_pixel_count = 0, pixel_count = 0;
    rgb_t *first_rgb = malloc(sizeof(byte_t) * 3), *second_rgb = malloc(sizeof(byte_t) * 3);
    while(!feof(first_bmp) && read_bmp_fragment(first_rgb, sizeof(byte_t) * 3, first_bmp) == 1 &&
          !feof(second_bmp) && read_bmp_fragment(second_rgb, sizeof(byte_t) * 3, second_bmp) == 1)
    {
        if((first_rgb->red != second_rgb->red || first_rgb->green != second_rgb->green ||
            first_rgb->blue != second_rgb->blue) && different_pixel_count < MAX_DIFFERENT_PIXELS)
        {
            different_pixel_count++;
            error_print("%d %d\n", pixel_count % image_width, pixel_count / image_width);
        }
        pixel_count++;
    }
    free(first_rgb);
    free(second_rgb);
    return check_colors_count(pixel_count * 3, image_size, UNSUCCESSFUL_EXIT_CODE);
}