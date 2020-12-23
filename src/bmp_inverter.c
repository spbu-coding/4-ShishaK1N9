#include "bmp_handler.h"
#include "bmp_inverter.h"
#include "qdbmp.h"


void invert_palette_bmp_8(bmp_file_t *bmp_file)
{
    for(int i = 0; i < BMP_8_PALETTE_SIZE; i++)
    {
        invert(bmp_file->palette[i]);
    }
}

int copy_bmp_8(FILE* input_file, FILE* output_file)
{
    int colors_count = 0, *byte = malloc(sizeof(word_t));
    while(!feof(input_file) && ((*byte = fgetc(input_file)) != EOF))
    {
        fputc(*byte, output_file);
        colors_count++;
    }
    free(byte);
    return colors_count;
}

int invert_bmp_8(FILE* input_file, FILE* output_file, bmp_file_t* bmp_file)
{
    bmp_file->palette = malloc(BMP_8_PALETTE_SIZE * sizeof(word_t));
    read_bmp_fragment(bmp_file->palette, BMP_8_PALETTE_SIZE * sizeof(word_t), input_file);
    invert_palette_bmp_8(bmp_file);
    write_bmp_fragment(bmp_file->palette, BMP_8_PALETTE_SIZE * sizeof(word_t), output_file);
    free(bmp_file->palette);
    return copy_bmp_8(input_file, output_file);
}

int invert_bmp_24(FILE* input_file, FILE* output_file)
{
    int colors_count = 0;
    rgb_t *rgb = malloc(sizeof(byte_t) * 3);
    while(!feof(input_file) && read_bmp_fragment(rgb, sizeof(byte_t) * 3, input_file) == 1)
    {
        invert(rgb->red);
        invert(rgb->green);
        invert(rgb->blue);
        write_bmp_fragment(rgb, sizeof(byte_t) * 3, output_file);
        colors_count +=3;
    }
    free(rgb);
    return colors_count;
}

int choose_mine_inversion(FILE* input_file, FILE* output_file, bmp_file_t* bmp_file)
{
    switch(bmp_file->info_header->bit_count)
    {
        case 8:
            return invert_bmp_8(input_file, output_file, bmp_file);
        case 24:
            return invert_bmp_24(input_file, output_file);
        default:
            return 0;
    }
}

int mine_invert_bmp(FILE* input_file, FILE* output_file, bmp_file_t* bmp_file)
{
    bmp_file->header = malloc(BMP_HEADER_SIZE);
    bmp_file->info_header = malloc(BMP_INFO_HEADER_SIZE);
    if(read_bmp_fragment(bmp_file->header, BMP_HEADER_SIZE, input_file) != 1)
    {
        free(bmp_file->header);
        free(bmp_file->info_header);
        return error("BMP header reading error.\n", BMP_MINE_ERROR_CODE);
    }
    int exit_code = check_bmp_header(bmp_file->header);
    if(exit_code == BMP_MINE_ERROR_CODE)
    {
        free(bmp_file->header);
        free(bmp_file->info_header);
        return exit_code;
    }
    write_bmp_fragment(bmp_file->header, BMP_HEADER_SIZE, output_file);

    if(read_bmp_fragment(bmp_file->info_header, BMP_INFO_HEADER_SIZE, input_file) != 1)
    {
        free(bmp_file->header);
        free(bmp_file->info_header);
        return error("BMP info header reading error.\n", BMP_MINE_ERROR_CODE);
    }
    exit_code = check_bmp_info_header(bmp_file->info_header, bmp_file->header->file_size, bmp_file->header->image_offset);
    if(exit_code == BMP_MINE_ERROR_CODE)
    {
        free(bmp_file->header);
        free(bmp_file->info_header);
        return exit_code;
    }
    write_bmp_fragment(bmp_file->info_header, BMP_INFO_HEADER_SIZE, output_file);

    exit_code = check_colors_count(choose_mine_inversion(input_file, output_file, bmp_file), bmp_file->info_header->image_size);
    if(exit_code == BMP_MINE_ERROR_CODE)
    {
        free(bmp_file->header);
        free(bmp_file->info_header);
        return exit_code;
    }
    free(bmp_file->header);
    free(bmp_file->info_header);
    return exit_code;
}


int qdbmp_Convert(file_name_t filein, file_name_t fileout)
{
    UCHAR r, g, b;
    UINT width, height;
    UINT x, y;
    BMP	*bmp = BMP_ReadFile( filein );
    BMP_CHECK_ERROR(stdout, BMP_THEIR_ERROR_CODE);

    width = BMP_GetWidth(bmp);
    height = BMP_GetHeight(bmp);

    if(bmp->Palette == NULL && BMP_GetDepth(bmp) == 24)
    {
        for(x = 0 ; x < width ; x++)
        {
            for(y = 0 ; y < height ; y++)
            {
                BMP_GetPixelRGB( bmp, x, y, &r, &g, &b );
                BMP_SetPixelRGB( bmp, x, y, 255 - r, 255 - g, 255 - b );
            }
        }
    }
    else if(BMP_GetDepth(bmp) == 8)
    {
        for(unsigned i = 0; i < 256 ; i++)
        {
            bmp->Palette[i<<2] = bmp->Palette[i<<2] ^ 0xFF;
            bmp->Palette[(i<<2)+1] = bmp->Palette[(i<<2)+1] ^ 0xFF;
            bmp->Palette[(i<<2)+2] = bmp->Palette[(i<<2)+2] ^ 0xFF;
        }
    }
    else
    {
        BMP_LAST_ERROR_CODE = BMP_FILE_NOT_SUPPORTED;
        BMP_Free(bmp);
        return error(BMP_GetErrorDescription(), BMP_THEIR_ERROR_CODE);
    }

    BMP_WriteFile( bmp, fileout );
    if(BMP_LAST_ERROR_CODE)
    {
        BMP_Free(bmp);
        return error(BMP_GetErrorDescription(), BMP_THEIR_ERROR_CODE);
    }
    BMP_Free(bmp);
    return SUCCESSFUL_EXIT_CODE;
}