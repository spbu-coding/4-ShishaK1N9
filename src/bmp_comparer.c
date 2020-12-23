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