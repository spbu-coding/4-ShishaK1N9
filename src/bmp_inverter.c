#include "bmp_handler.h"
#include "bmp_inverter.h"

void invert_bmp_8(bmp_file_t *bmp_file)
{
    for(int i = 0; i < BMP_8_PALETTE_SIZE; i++)
    {
        invert(bmp_file->palette[i]);
    }
}

void copy_bmp_8(FILE* input_file, FILE* output_file)
{
    while(!feof(input_file))
    {
        short_word_t byte = fgetc(input_file);
        fputc(byte, output_file);
    }
}

void invert_bmp_24(FILE* input_file, FILE* output_file)
{
    rgb_t *rgb = malloc(sizeof(word_t) * 3);
    while(!feof(input_file))
    {
        read_bmp_fragment(rgb, sizeof(word_t) * 3, input_file);
        invert(rgb->red);
        invert(rgb->green);
        invert(rgb->blue);
        write_bmp_fragment(rgb, sizeof(word_t) * 3, output_file);
    }
    free(rgb);
}