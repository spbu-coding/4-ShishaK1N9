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

