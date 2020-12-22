#include <strings.h>

#include "bmp_validate.h"
#include "bmp_handler.h"

#define error_print(...) fprintf(stderr, __VA_ARGS__)

int error(char *error_text, int exit_code)
{
    error_print("%s\n", error_text);
    return exit_code;
}

bool check_converter_count_of_parameters(parameters_count_t parameters_count)
{
    if(parameters_count == CONVERTER_COUNT_OF_PARAMS)
    {
        return true;
    }
    return false;
}

bool is_bmp_file(char* file_name)
{
    unsigned int index = 0;
    for(unsigned int i = 0; i < strlen(file_name); i++)
    {
        if(file_name[i] == BMP_FILE_FORMAT[index])
        {
            index++;
        }
    }
    if(index == strlen(BMP_FILE_FORMAT))
    {
        return true;
    }
    return false;
}

bool check_existence_input_file(file_name_t file_name)
{
    FILE* input_file = fopen(file_name, "rb");
    if(input_file == NULL)
    {
        return false;
    }
    fclose(input_file);
    return true;
}

int is_string_in_array(string_t string, const_string_array_t string_array, array_size_t array_size)
{
    for(array_size_t i = 0; i < array_size; i++)
    {
        if(strcmp(string, string_array[i]) == 0)
        {
            return i;
        }
    }
    return UNSUCCESSFUL_EXIT_CODE;
}

int check_converter_parameters(parameters_count_t parameters_count, parameters_t parameters)
{
    if(!check_converter_count_of_parameters(parameters_count))
    {
        return error("Input correct count of parameters.", UNSUCCESSFUL_EXIT_CODE);
    }

    if(is_string_in_array(parameters[ARG_ALGORITHM_NAME], ALGORITHMS_NAMES, COUNT_OF_ALGORITHMS))
    {
        return error("Input correct algorithm name.", UNSUCCESSFUL_EXIT_CODE);
    }

    if(!is_bmp_file(parameters[ARG_CONVERTER_INPUT_FILE_NAME]))
    {
        return error("Input correct input file name", UNSUCCESSFUL_EXIT_CODE);
    }
    if(!is_bmp_file(parameters[ARG_CONVERTER_OUTPUT_FILE_NAME]))
    {
        return error("Input correct output file name", UNSUCCESSFUL_EXIT_CODE);
    }

    if(!check_existence_input_file(parameters[ARG_CONVERTER_INPUT_FILE_NAME]))
    {
        return error("Input file doesn't exist.", UNSUCCESSFUL_EXIT_CODE);
    }
}


//todo проверить первые два байта на сигнартуру BM
//todo отловить ошибку размера файла(02-05 / 1 строчка)
//todo отловить ошибку зарезервированных бит(должны быть пустыми, 06-09 / 1 строчка)
//todo отловить ошибку смещения изображения(54 для 24bit и 1078 для 8bit, 0A-0D / 1 строчка)
//todo отловить ошибку с длиной заголовка?(стандартная длина 40, 0E-01 / 1-2 строчки)

//todo отловить ошибку с шириной изображения(02-05 / 2 строчка)
//todo отловить ошибку с высотой изображения(06-09 / 2 строчка)
//todo проверить размер изображения с высота * ширина
//todo отловить ошибку с кол-вом плоскостей(по стандарту 1, 0A-0B / 2 строчка)
//todo отловить ошибку со стандратом bmp(8 или 24, 0С-0В / 2 строчка)

//todo отловить ошибку размера изображения в размере файла(размер файла минус смещение, 02-05 / 3 строчка)
//todo какое-то смещение(06-09 / 3 строчка)
//todo отловить ошибку с числом используемых цветов(максимум 0, 0E-01 / 3-4 строчка)

//todo проверить байты на наличие в палитре?

