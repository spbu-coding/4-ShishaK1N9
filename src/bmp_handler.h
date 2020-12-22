#ifndef TESTS_BMP_HANDLER_H
#define TESTS_BMP_HANDLER_H

#include <strings.h>

#define read_bmp_fragment(fragment, fragment_size, file) fread(fragment, fragment_size, 1, file)
#define write_bmp_fragment(fragment, fragment_size, file) fwrite(fragment, fragment_size, 1, file)

static const int BMP_HEADER_SIZE = 14, BMP_INFO_HEADER_SIZE = 40, BMP_8_PALETTE_SIZE = 256;
static const int BMP_24_BIT_COUNT = 24, BMP_8_BIT_COUNT = 8;

typedef unsigned char byte_t;
typedef unsigned short short_word_t;
typedef unsigned int word_t;

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
    char* file_name;
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

#endif //TESTS_BMP_HANDLER_H
