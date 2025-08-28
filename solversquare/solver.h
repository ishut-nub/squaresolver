#ifndef _SOLVER_H_
#define _SOLVER_H_

#include "utility.h"
#include "consts.h"

root_counter linear_equation(equation_data *data);
root_counter quadratic_equation(equation_data *data);
root_counter solver(equation_data *data);

#endif /* _SOLVER_H_ */
