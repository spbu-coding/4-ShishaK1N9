#ifndef TESTS_BMP_COMPARER_H
#define TESTS_BMP_COMPARER_H

#include "bmp_handler.h"
#include "bmp_validate.h"

static const int MAX_DIFFERENT_PIXELS = 100;

int compare_headers(bmp_header_t*, bmp_header_t*);

int palette_compare(const word_t*, const word_t*);

int compare_bmp_8_pixels(FILE*, FILE*, int, int);

int compare_bmp_24_pixels(FILE*, FILE*, int, int);

#endif //TESTS_BMP_COMPARER_H
