#include "bmp_validate.h"
#include "bmp_comparer.h"

int main(int argc, char* argv[])
{
    int exit_code = check_comparer_parameters(argc - 1, argv);
    if(exit_code == UNSUCCESSFUL_EXIT_CODE)
    {
        return exit_code;
    }

    bmp_file_t first_bmp, second_bmp;
    first_bmp.file_name = argv[ARG_FIRST_FILE_NAME];
    second_bmp.file_name = argv[ARG_SECOND_FILE_NAME];
    FILE* first_file = fopen(first_bmp.file_name, "rb");
    FILE* second_file = fopen(second_bmp.file_name, "rb");

    first_bmp.header = malloc(BMP_HEADER_SIZE);
    if(read_bmp_fragment(first_bmp.header, BMP_HEADER_SIZE, first_file) != 1)
    {
        free(first_bmp.header);
        fclose(first_file);
        fclose(second_file);
        return error("First BMP_file header reading error.\n", UNSUCCESSFUL_EXIT_CODE);
    }
    if(check_bmp_header(first_bmp.header, UNSUCCESSFUL_EXIT_CODE) == UNSUCCESSFUL_EXIT_CODE)
    {
        error_print("First file fault.\n");
        free(first_bmp.header);
        fclose(first_file);
        fclose(second_file);
        return UNSUCCESSFUL_EXIT_CODE;
    }

    second_bmp.header = malloc(BMP_HEADER_SIZE);
    if(read_bmp_fragment(second_bmp.header, BMP_HEADER_SIZE, second_file) != 1)
    {
        free(first_bmp.header);
        free(second_bmp.header);
        fclose(first_file);
        fclose(second_file);
        return error("Second BMP_file header reading error.\n", UNSUCCESSFUL_EXIT_CODE);
    }
    if(check_bmp_header(second_bmp.header, UNSUCCESSFUL_EXIT_CODE) == UNSUCCESSFUL_EXIT_CODE)
    {
        error_print("Second file fault.\n");
        free(first_bmp.header);
        free(second_bmp.header);
        fclose(first_file);
        fclose(second_file);
        return UNSUCCESSFUL_EXIT_CODE;
    }

    if(compare_headers(first_bmp.header, second_bmp.header) == UNSUCCESSFUL_EXIT_CODE)
    {
        free(first_bmp.header);
        free(second_bmp.header);
        fclose(first_file);
        fclose(second_file);
        return UNSUCCESSFUL_EXIT_CODE;
    }


    first_bmp.info_header = malloc(BMP_INFO_HEADER_SIZE);
    if(read_bmp_fragment(first_bmp.info_header, BMP_INFO_HEADER_SIZE, first_file) != 1)
    {
        free(first_bmp.header);
        free(first_bmp.info_header);
        free(second_bmp.header);
        fclose(first_file);
        fclose(second_file);
        return error("First BMP_file info header reading error.\n", UNSUCCESSFUL_EXIT_CODE);
    }
    if(check_bmp_info_header(first_bmp.info_header, first_bmp.header->file_size,
                             first_bmp.header->image_offset, UNSUCCESSFUL_EXIT_CODE) == UNSUCCESSFUL_EXIT_CODE)
    {
        error_print("First file fault.\n");
        free(first_bmp.header);
        free(first_bmp.info_header);
        free(second_bmp.header);
        fclose(first_file);
        fclose(second_file);
        return UNSUCCESSFUL_EXIT_CODE;
    }

    second_bmp.info_header = malloc(BMP_INFO_HEADER_SIZE);
    if(read_bmp_fragment(second_bmp.info_header, BMP_INFO_HEADER_SIZE, second_file) != 1)
    {
        free(first_bmp.header);
        free(first_bmp.info_header);
        free(second_bmp.header);
        free(second_bmp.info_header);
        fclose(first_file);
        fclose(second_file);
        return error("Second BMP_file info header reading error.\n", UNSUCCESSFUL_EXIT_CODE);
    }
    if(check_bmp_info_header(second_bmp.info_header, second_bmp.header->file_size,
                             second_bmp.header->image_offset, UNSUCCESSFUL_EXIT_CODE) == UNSUCCESSFUL_EXIT_CODE)
    {
        error_print("Second file fault.\n");
        free(first_bmp.header);
        free(first_bmp.info_header);
        free(second_bmp.header);
        free(second_bmp.info_header);
        fclose(first_file);
        fclose(second_file);
        return UNSUCCESSFUL_EXIT_CODE;
    }

    if(first_bmp.info_header->bit_count == BMP_8_BIT_COUNT)
    {
        first_bmp.palette = malloc(BMP_8_PALETTE_SIZE * sizeof(word_t));
        read_bmp_fragment(first_bmp.palette, BMP_8_PALETTE_SIZE * sizeof(word_t), first_file);
        second_bmp.palette = malloc(BMP_8_PALETTE_SIZE * sizeof(word_t));
        read_bmp_fragment(second_bmp.palette, BMP_8_PALETTE_SIZE * sizeof(word_t), second_file);
        exit_code = palette_compare(first_bmp.palette, second_bmp.palette);
        if(exit_code == UNSUCCESSFUL_EXIT_CODE)
        {
            free(first_bmp.palette);
            free(second_bmp.palette);
            free(first_bmp.header);
            free(first_bmp.info_header);
            free(second_bmp.header);
            free(second_bmp.info_header);
            fclose(first_file);
            fclose(second_file);
            return exit_code;
        }
        free(first_bmp.palette);
        free(second_bmp.palette);
    }

    free(first_bmp.header);
    free(first_bmp.info_header);
    free(second_bmp.header);
    free(second_bmp.info_header);
    fclose(first_file);
    fclose(second_file);
    return exit_code;
}