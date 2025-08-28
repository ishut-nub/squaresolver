#ifndef _INPUT_OUTPUT_H_
#define _INPUT_OUTPUT_H_ //TODO main.h -> kvadr.h

#include "utility.h"
#include "consts.h"
#include "solver.h"

void entry_message(void);
void exit_message(void);
void input_coeffs(equation_data *data);
void output_roots(equation_data *data);
bool do_task(const char *);

#endif /* _INPUT_OUTPUT_H_ */
