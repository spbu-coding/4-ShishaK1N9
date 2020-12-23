#include <string.h>

#include "bmp_validate.h"

#define error_print(...) fprintf(stderr, __VA_ARGS__)

int error(const char *error_text, int exit_code)
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

bool is_bmp_file(file_name_t file_name)
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
        return error("Input correct count of parameters.\n", UNSUCCESSFUL_EXIT_CODE);
    }

    if(is_string_in_array(parameters[ARG_ALGORITHM_NAME], ALGORITHMS_NAMES, COUNT_OF_ALGORITHMS) == UNSUCCESSFUL_EXIT_CODE)
    {
        return error("Input correct algorithm name.\n", UNSUCCESSFUL_EXIT_CODE);
    }

    if(!is_bmp_file(parameters[ARG_CONVERTER_INPUT_FILE_NAME]))
    {
        return error("Input correct input file name.\n", UNSUCCESSFUL_EXIT_CODE);
    }
    if(!is_bmp_file(parameters[ARG_CONVERTER_OUTPUT_FILE_NAME]))
    {
        return error("Input correct output file name.\n", UNSUCCESSFUL_EXIT_CODE);
    }

    if(!check_existence_input_file(parameters[ARG_CONVERTER_INPUT_FILE_NAME]))
    {
        return error("Input file doesn't exist.\n", UNSUCCESSFUL_EXIT_CODE);
    }

    return SUCCESSFUL_EXIT_CODE;
}

bool is_bmp_signature(short_word_t signature)
{
    if(signature != BMP_SIGNATURE)
    {
        return false;
    }
    return true;
}

bool check_file_size(word_t file_size)
{
    if(file_size < 0)
    {
        return false;
    }
    return true;
}

bool is_reserved_null(short_word_t first_reserved_pare, short_word_t second_reserved_pare)
{
    if(first_reserved_pare != RESERVED_VALUE || second_reserved_pare != RESERVED_VALUE)
    {
        return false;
    }
    return true;
}

bool check_image_offset(word_t image_offset)
{
    if(image_offset != BMP_8_IMAGE_OFFSET && image_offset != BMP_24_IMAGE_OFFSET)
    {
        return false;
    }
    return true;
}

int check_bmp_header(bmp_header_t *header)
{
    if(!is_bmp_signature(header->signature))
    {
        return error("BMP_file reading error: signature fault.\n", BMP_MINE_ERROR_CODE);
    }

    if(!check_file_size(header->file_size))
    {
        return error("BMP_file reading error: file size fault.\n", BMP_MINE_ERROR_CODE);
    }

    if(!is_reserved_null(header->first_reserved_pare, header->second_reserved_pare))
    {
        return error("BMP_file reading error: reserved bytes fault.\n", BMP_MINE_ERROR_CODE);
    }

    if(!check_image_offset(header->image_offset))
    {
        return error("BMP_file reading error: image offset fault.\n", BMP_MINE_ERROR_CODE);
    }
    return SUCCESSFUL_EXIT_CODE;
}

bool check_info_header_size(word_t info_header_size)
{
    if(info_header_size != BMP_INFO_HEADER_SIZE)
    {
        return false;
    }
    return true;
}

bool check_image_width(word_t width)
{
    if(width < 0)
    {
        return false;
    }
    return true;
}

bool check_image_height(word_t height)
{
    if(height < 0)
    {
        return false;
    }
    return true;
}

bool check_image_size(word_t width, word_t height, word_t image_size, short_word_t bmp_type)
{
    word_t real_width = width * (bmp_type / BYTE_LENGTH);
    if(real_width % BLOCK_SIZE != 0)
    {
        real_width = real_width + BLOCK_SIZE - real_width % BLOCK_SIZE;
    }
    if(real_width * height != image_size)
    {
        return false;
    }
    return true;
}

bool check_bmp_type(short_word_t bmp_type)
{
    if(bmp_type != BMP_8_BIT_COUNT && bmp_type != BMP_24_BIT_COUNT)
    {
        return false;
    }
    return true;
}

bool check_planes_count(short_word_t planes_count)
{
    if(planes_count != PLANES_COUNT)
    {
        return false;
    }
    return true;
}

bool check_size(word_t file_size, word_t image_size, word_t image_offset)
{
    if(file_size != image_size + image_offset)
    {
        return false;
    }
    return true;
}

int check_colors_count(int colors_count, int bmp_image_size)
{
    if(colors_count != bmp_image_size)
    {
        return error("BMP_file reading error: image size doesn't match the reality.\n", BMP_MINE_ERROR_CODE);
    }
    return SUCCESSFUL_EXIT_CODE;
}

int check_bmp_info_header(bmp_info_header_t *info_header, word_t file_size, word_t image_offset)
{
    if(!check_info_header_size(info_header->info_header_size))
    {
        return error("BMP_file reading error: info header size fault.\n", BMP_MINE_ERROR_CODE);
    }

    if(!check_image_width(info_header->image_width))
    {
        return error("BMP_file reading error: image width fault.\n", BMP_MINE_ERROR_CODE);
    }
    if(!check_image_height(info_header->image_height))
    {
        return error("BMP_file reading error: image height fault.\n", BMP_MINE_ERROR_CODE);
    }

    if(!check_bmp_type(info_header->bit_count))
    {
        return error("BMP_file reading error: bmp type fault.\n", BMP_MINE_ERROR_CODE);
    }

    if(!check_image_size(info_header->image_width, info_header->image_height,
                         info_header->image_size, info_header->bit_count))
    {
        return error("BMP_file reading error: image size fault.\n", BMP_MINE_ERROR_CODE);
    }

    if(!check_size(file_size, info_header->image_size, image_offset))
    {
        return error("BMP_file reading error: file size fault.\n", BMP_MINE_ERROR_CODE);
    }

    if(!check_planes_count(info_header->planes_count))
    {
        return error("BMP_file reading error: planes count fault.\n", BMP_MINE_ERROR_CODE);
    }
    return SUCCESSFUL_EXIT_CODE;
}
