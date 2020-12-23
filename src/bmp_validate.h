#ifndef TESTS_BMP_VALIDATE_H
#define TESTS_BMP_VALIDATE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp_handler.h"

#define size_of_array(array) sizeof(array) / sizeof(char*)

static const char *BMP_FILE_FORMAT = ".bmp";
static const char *ALGORITHMS_NAMES[] = {"--mine", "--theirs"};
static const int SUCCESSFUL_EXIT_CODE = 0, UNSUCCESSFUL_EXIT_CODE = -1, BMP_MINE_ERROR_CODE = -2;
static const int BMP_THEIR_ERROR_CODE = -3, CONVERTER_COUNT_OF_PARAMS = 3, COMPARER_COUNT_OF_PARAMS = 2;
static const int COUNT_OF_ALGORITHMS = size_of_array(ALGORITHMS_NAMES);
static const int ARG_ALGORITHM_NAME = 1, ARG_CONVERTER_INPUT_FILE_NAME = 2, ARG_CONVERTER_OUTPUT_FILE_NAME = 3;

typedef size_t array_size_t;
typedef const char** const_string_array_t;
typedef char **parameters_t, *string_t, *file_name_t;
typedef int parameters_count_t;

int error(const char*, int);

int check_converter_parameters(parameters_count_t t, parameters_t);

int check_bmp_header(bmp_header_t*, int);

int check_colors_count(int, int, int);

int check_bmp_info_header(bmp_info_header_t*, word_t, word_t, int);

#endif //TESTS_BMP_VALIDATE_H
