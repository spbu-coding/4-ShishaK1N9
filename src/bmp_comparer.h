#ifndef TESTS_BMP_COMPARER_H
#define TESTS_BMP_COMPARER_H

#include "bmp_handler.h"
#include "bmp_validate.h"

int compare_headers(bmp_header_t*, bmp_header_t*);

int palette_compare(const word_t*, const word_t*);

#endif //TESTS_BMP_COMPARER_H
