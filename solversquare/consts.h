#ifndef _CONSTS_H_
#define _CONSTS_H_

enum root_counter
{
    INF_ROOTS = -1,
    NO_ROOTS =   0,
    ONE_ROOT =   1,
    TWO_ROOTS =  2
};

const double ACCURACY_LIMIT = 1e-15;
const int ROWS = 6;

struct test_data
{
    double compare_coeff_a, compare_coeff_b, compare_coeff_c;
    double compare_root_1, compare_root_2;
    root_counter compare_root_count;
};

struct equation_data
{
    double coeff_a, coeff_b, coeff_c;
    double root_1, root_2;
    root_counter root_count;
};

#endif /* _CONSTS_H_ */
