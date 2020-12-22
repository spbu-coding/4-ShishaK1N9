#ifndef TESTS_BMP_INVERTER_H
#define TESTS_BMP_INVERTER_H

#define invert(word) word = ~word

void invert_bmp_8(bmp_file_t*);

void copy_bmp_8(FILE*, FILE*);

void invert_bmp_24(FILE*, FILE*);

#endif //TESTS_BMP_INVERTER_H
