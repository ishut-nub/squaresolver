#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
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
        printf("Test failed \nRoots %lg %lg instead of %lg %lg \n"
               "Number of roots %d instead of %d\n\n",
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
    int j = 0;
    file = fopen("tests.txt", "r");
    if (file == NULL) {
        printf("Failed to open");
    }

    test_data tests[ROWS];

    for (j = 0; j < ROWS; j++) {
        if (fscanf(file, "%lg %lg %lg %lg %lg %d", &tests[j].compare_coeff_a, &tests[j].compare_coeff_b,
                                                   &tests[j].compare_coeff_c, &tests[j].compare_root_1,
                                                   &tests[j].compare_root_2, (int*) &tests[j].compare_root_count) != 6) {
            printf("Failed to read");
            fclose(file);
        }
    }

    int test_failed = 0;

    size_t size = sizeof(tests)/sizeof(tests[0]);

    for (long unsigned int i = 0; i < size; i++) {
        test_failed += solver_tester(&tests[i], data);
    }
    printf("\nFailed %d tests\n\n", test_failed);
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
