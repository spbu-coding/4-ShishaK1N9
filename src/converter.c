#include "bmp_handler.h"
#include "bmp_inverter.h"
#include "bmp_validate.h"

int main(int argc, char* argv[])
{
    bmp_file_t input_file;
    input_file.file_name = argv[ARG_CONVERTER_INPUT_FILE_NAME];
    int exit_code = check_converter_parameters(argc - 1, argv);
    if(exit_code != SUCCESSFUL_EXIT_CODE)
    {
        return exit_code;
    }

    FILE* input_bmp = fopen(input_file.file_name, "rb");
    FILE* output_bmp = fopen(argv[ARG_CONVERTER_OUTPUT_FILE_NAME], "wb");

    input_file.header = malloc(BMP_HEADER_SIZE);
    input_file.info_header = malloc(BMP_INFO_HEADER_SIZE);
    read_bmp_fragment(input_file.header, BMP_HEADER_SIZE, input_bmp);
    write_bmp_fragment(input_file.header, BMP_HEADER_SIZE, output_bmp);
    //todo вставить валидацию

    read_bmp_fragment(input_file.info_header, BMP_INFO_HEADER_SIZE, input_bmp);
    write_bmp_fragment(input_file.info_header, BMP_INFO_HEADER_SIZE, output_bmp);
    //todo вставить валидацию
    if(input_file.info_header->bit_count == BMP_8_BIT_COUNT)
    {
        input_file.palette = malloc(BMP_8_PALETTE_SIZE * sizeof(word_t));
        //todo вставить валидацию
        read_bmp_fragment(input_file.palette, BMP_8_PALETTE_SIZE * sizeof(word_t), input_bmp);
        invert_bmp_8(&input_file);
        write_bmp_fragment(input_file.palette, BMP_8_PALETTE_SIZE * sizeof(word_t), output_bmp);
        free(input_file.palette);
        copy_bmp_8(input_bmp, output_bmp);
    }
    else if(input_file.info_header->bit_count == BMP_24_BIT_COUNT)
    {
        invert_bmp_24(input_bmp, output_bmp);
    }

    free(input_file.header);
    free(input_file.info_header);
    fclose(input_bmp);
    fclose(output_bmp);
    return exit_code;
}
