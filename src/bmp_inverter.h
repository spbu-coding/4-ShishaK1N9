#ifndef TESTS_BMP_INVERTER_H
#define TESTS_BMP_INVERTER_H

#include <stdio.h>
#include <stdlib.h>

#define invert(word) word = ~word

int mine_invert_bmp(FILE*, FILE*, bmp_file_t*);

#endif //TESTS_BMP_INVERTER_H
