#ifndef TESTS_BMP_INVERTER_H
#define TESTS_BMP_INVERTER_H

#include <stdio.h>
#include <stdlib.h>

#include "bmp_validate.h"

#define invert(word) word = ~word

int mine_invert_bmp(FILE*, FILE*, bmp_file_t*);

int qdbmp_Convert(file_name_t , file_name_t);

#endif //TESTS_BMP_INVERTER_H
