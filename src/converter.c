#include "bmp_handler.h"
#include "bmp_inverter.h"

int main(int argc, char* argv[])
{
    int exit_code = check_converter_parameters(argc - 1, argv);
    if(exit_code != SUCCESSFUL_EXIT_CODE)
    {
        return exit_code;
    }

    if(strcmp(argv[ARG_ALGORITHM_NAME], "--mine") == 0)
    {
        bmp_file_t input_file;
        input_file.file_name = argv[ARG_CONVERTER_INPUT_FILE_NAME];
        FILE* input_bmp = fopen(input_file.file_name, "rb");
        FILE* output_bmp = fopen(argv[ARG_CONVERTER_OUTPUT_FILE_NAME], "wb");
        exit_code = mine_invert_bmp(input_bmp, output_bmp, &input_file);
        fclose(input_bmp);
        fclose(output_bmp);
    }
    else
    {
        exit_code = qdbmp_Convert(argv[ARG_CONVERTER_INPUT_FILE_NAME], argv[ARG_CONVERTER_OUTPUT_FILE_NAME]);
    }
    return exit_code;
}
