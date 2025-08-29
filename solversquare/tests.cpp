#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include "tests.h"

int solver_tester(test_data *test, equation_data *data)
{
    data->coeff_a = test->compare_coeff_a;
    data->coeff_b = test->compare_coeff_b;
    data->coeff_c = test->compare_coeff_c;

    assert(!(isnan(data->coeff_a)));
    assert(!(isnan(data->coeff_b)));
    assert(!(isnan(data->coeff_c)));

    data->root_count = solver(data);

    if (!(compare_test_roots(test, data) && (data->root_count == test->compare_root_count)))
    {
        printf("\033[1;31mTest failed \n\033[1;35mRoots\033[1;0m \033[1;31m%lg %lg\033[1;0m \033[1;35minstead of\033[1;0m \033[1;32m%lg %lg\033[1;0m \n"
               "\033[1;36mNumber of roots \033[1;31m%d\033[1;0m \033[1;36minstead of\033[1;0m \033[1;32m%d\033[1;0m\n\n",
               data->root_1, data->root_2, test->compare_root_1, test->compare_root_2,
               data->root_count, test->compare_root_count);
        return 1;
    }
    else
        return 0;
}

void run_test(equation_data *data)
{
    FILE *file;
    file = fopen("tests.txt", "r");

    if (file == NULL) {
        printf("\033[1;31mFailed to open\033[1;0m");
    }

    char ch = 0;
    long unsigned int row_count = 0;

    while (fscanf(file, "%c", &ch) == 1 && ch != EOF)
    {
        if (ch == '\n') {
            row_count++;
        }
    }

    rewind(file);

    struct test_data* tests;
    tests = (struct test_data*) calloc(row_count, sizeof(test_data));

    for (long unsigned int j = 0; j < row_count; j++) {
        if (fscanf(file, "%lg %lg %lg %lg %lg %d", &tests[j].compare_coeff_a, &tests[j].compare_coeff_b,
                                                   &tests[j].compare_coeff_c, &tests[j].compare_root_1,
                                                   &tests[j].compare_root_2, (int*) &tests[j].compare_root_count) != 6) {
            printf("\033[1;31mFailed to read\033[1;0m");

            fclose(file);
        }
    }

    fclose(file);

    int test_failed = 0;

    for (long unsigned int i = 0; i < row_count; i++) {
        test_failed += solver_tester(&tests[i], data);
    }
    printf("\n\033[1;31mFailed\033[1;0m \033[1;37m%d tests\033[1;0m\n\n", test_failed);

    free(tests);

    return;
}

int compare_test_roots(test_data *test, equation_data *data)
{
    double min_root = NAN;
    double max_root = NAN;
    double min_compare_root = NAN;
    double max_compare_root = NAN;

    min_root = find_min(data->root_1, data->root_2);
    max_root = find_max(data->root_1, data->root_2);
    min_compare_root = find_min(test->compare_root_1, test->compare_root_2);
    max_compare_root = find_max(test->compare_root_1, test->compare_root_2);

    if (doubles_equality(min_root, min_compare_root) && doubles_equality(max_root, max_compare_root))
        return 1;

    return 0;
}
