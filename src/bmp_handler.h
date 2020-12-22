#ifndef TESTS_BMP_HANDLER_H
#define TESTS_BMP_HANDLER_H

#include <stdio.h>
#include <stdlib.h>

#define size_of_array(array) sizeof(array) / sizeof(char*)
#define read_bmp_fragment(fragment, fragment_size, file) fread(fragment, fragment_size, 1, file)
#define write_bmp_fragment(fragment, fragment_size, file) fwrite(fragment, fragment_size, 1, file)

static const char *BMP_FILE_FORMAT = ".bmp", *UTILITY_NAMES[] = {"converter", "comparer"};
static const char *ALGORITHMS_NAMES[] = {"--mine", "--theirs"};
static const int BMP_HEADER_SIZE = 14, BMP_INFO_HEADER_SIZE = 40, BMP_8_PALETTE_SIZE = 256, BMP_8_BIT_COUNT = 8;
static const int BMP_24_BIT_COUNT = 24;
static const int COUNT_OF_UTILITIES = size_of_array(UTILITY_NAMES), COUNT_OF_ALGORITHMS = size_of_array(ALGORITHMS_NAMES);

typedef char **parameters_t, *file_name_t;
typedef unsigned char byte_t;
typedef unsigned short short_word_t;
typedef unsigned int word_t;
typedef int parameters_count_t;

typedef struct
{
    short_word_t signature;
    word_t file_size;
    short_word_t first_reserved_pare;
    short_word_t second_reserved_pare;
    word_t image_offset;
} bmp_header_t;

typedef struct
{
    word_t info_header_size;
    word_t image_width;
    word_t image_height;
    short_word_t planes_count;
    short_word_t bit_count;
    word_t compression_type;
    word_t image_size;
    word_t horizontal_resolution;
    word_t vertical_resolution;
    word_t colors_used;
    word_t important_colors;
} bmp_info_header_t;

typedef struct
{
    file_name_t file_name;
    bmp_header_t *header;
    bmp_info_header_t *info_header;
    word_t *palette;
} bmp_file_t;

typedef struct
{
    word_t red;
    word_t green;
    word_t blue;
} rgb_t;

int check_parameters(parameters_count_t, parameters_t);

#endif //TESTS_BMP_HANDLER_H
