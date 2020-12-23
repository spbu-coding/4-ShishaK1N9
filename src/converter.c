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
    exit_code = mine_invert_bmp(input_bmp, output_bmp, &input_file);

    fclose(input_bmp);
    fclose(output_bmp);
    return exit_code;
}
