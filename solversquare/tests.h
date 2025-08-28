#ifndef _TESTS_H_
#define _TESTS_H_

#include "utility.h"
#include "consts.h"
#include "solver.h"

int solver_tester(test_data *test, equation_data *data);
void run_test(equation_data *data);
int compare_test_roots(test_data *test, equation_data *data);

#endif /* _TESTS_H_ */
