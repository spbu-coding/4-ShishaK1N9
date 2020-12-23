#ifndef TESTS_BMP_HANDLER_H
#define TESTS_BMP_HANDLER_H

#include <string.h>

#define read_bmp_fragment(fragment, fragment_size, file) fread(fragment, fragment_size, 1, file)
#define write_bmp_fragment(fragment, fragment_size, file) fwrite(fragment, fragment_size, 1, file)

static const int BMP_HEADER_SIZE = 14, BMP_INFO_HEADER_SIZE = 40, BMP_8_PALETTE_SIZE = 256, PLANES_COUNT = 1;
static const int BMP_24_BIT_COUNT = 24, BMP_8_BIT_COUNT = 8, BMP_SIGNATURE = 19778, RESERVED_VALUE = 0;
static const int BMP_24_IMAGE_OFFSET = 54, BLOCK_SIZE = 4, BMP_8_IMAGE_OFFSET = 1078, BYTE_LENGTH = 8;
static const unsigned int PALETTE_MAX = 4278190080;

typedef unsigned char byte_t;
typedef unsigned short short_word_t;
typedef unsigned int word_t;


#pragma pack(push, 1)
typedef struct
{
    short_word_t signature;
    word_t file_size;
    short_word_t first_reserved_pare;
    short_word_t second_reserved_pare;
    word_t image_offset;
} bmp_header_t;
#pragma pack(pop)

#pragma pack(push, 1)
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
#pragma pack(pop)

typedef struct
{
    char* file_name;
    bmp_header_t *header;
    bmp_info_header_t *info_header;
    word_t *palette;
} bmp_file_t;

typedef struct
{
    byte_t red;
    byte_t green;
    byte_t blue;
} rgb_t;

#endif //TESTS_BMP_HANDLER_H
