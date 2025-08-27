#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

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

void entry_message(void);
void exit_message(void);
void input_coeffs(equation_data *data);
void output_roots(equation_data *data);
bool do_task(char do_task[100]);

root_counter linear_equation(equation_data *data);
root_counter quadratic_equation(equation_data *data);
root_counter solver(equation_data *data);

int doubles_equality(double test_x, double test_y);
double find_min(double min_1, double min_2);
double find_max(double max_1, double max_2);
double check_input(char symbol);
int clear_buffer(void);

int solver_tester(test_data *test, equation_data *data);
void run_test(equation_data *data);
int compare_test_roots(test_data *test, equation_data *data);

int main(void)
{
    struct equation_data data = {.coeff_a = NAN, .coeff_b = NAN, .coeff_c = NAN,
                                 .root_1 = NAN, .root_2 = NAN, .root_count = NO_ROOTS};

    entry_message();

    if (do_task("Do tests? [y/n] ")) {
        run_test(&data);
    }

    input_coeffs(&data);

    output_roots(&data);

    while (do_task("Solve another equation? [y/n] "))
    {
        input_coeffs(&data);

        output_roots(&data);
    }

    exit_message();

    return 0;
}

void entry_message(void) {
    printf("miau\n\n");
}

void exit_message(void) {
    printf("\nCOMMIT GITHUB, LEAVE BUILDING\n");
}

void input_coeffs(equation_data *data)
{
    printf("\nYour equation will look like this: ax^2+bx+c\n\n");
    printf("Please enter coefficients\n");

    data->coeff_a = check_input('a');
    data->coeff_b = check_input('b');
    data->coeff_c = check_input('c');
    return;
}

double check_input(char symbol)
{
    bool correct_input = 1;
    double number_input = NAN;

    printf("Input %c\n", symbol);

    while (correct_input == 1)
    {
        if (scanf("%lg", &number_input)) {
            correct_input = 0;
        }
        if (clear_buffer()) {
            correct_input = 1;
        }
        if (correct_input == 1) {
            printf("Incorrect input\n"
                   "Input %c\n", symbol);
        }
    }
    return number_input;
}

bool do_task(char do_task[100])
{
    char ch = 0;
    bool correct_input = 1;

    printf("%s", do_task);

    while (correct_input == 1)
    {
        if (scanf("%c", &ch)) {
            correct_input = 0;
        }
        if (clear_buffer()) {
            correct_input = 1;
        }
        if (correct_input == 1) {
            printf("Incorrect input\n"
                   "%s", do_task);
        }
    }
    if (ch == 'y')
        return 1;

    return 0;
}

int clear_buffer(void)
{
    int buffer_clear = 0;

    while (getchar() != '\n')
        buffer_clear++;
    return buffer_clear;
}

void output_roots(equation_data *data)
{
    data->root_count = solver(data);

    switch (data->root_count)
    {
        case INF_ROOTS:
            printf("Infinite amount of solutions\n");
            break;
        case NO_ROOTS:
            printf("No solutions\n");
            break;
        case ONE_ROOT:
            printf("Equation has 1 solution, %lg\n", data->root_1);
            break;
        case TWO_ROOTS:
            printf("Equation has 2 solutions, %lg and %lg\n", data->root_1, data->root_2);
            break;
        default:
            printf("How did you even get there?\n");
            break;
    }
}

root_counter linear_equation(equation_data *data)
{
    assert(!(isnan(data->coeff_b)));
    assert(!(isnan(data->coeff_c)));

    if (doubles_equality(data->coeff_b, 0))
    {
        if (doubles_equality(data->coeff_c, 0)) {
            return INF_ROOTS;
        }
        else {
            return NO_ROOTS;
        }
    }
    data->root_1 = data->root_2 = (-data->coeff_c / data->coeff_b);
    return ONE_ROOT;
}

root_counter quadratic_equation(equation_data *data)
{
    assert(!(isnan(data->coeff_a)));
    assert(!(isnan(data->coeff_b)));
    assert(!(isnan(data->coeff_c)));

    double discriminant = data->coeff_b * data->coeff_b - 4 * data->coeff_a * data->coeff_c;
    double sqrt_discriminant = sqrt(discriminant);

    if (discriminant < 0) {
        return NO_ROOTS;
    }
    else if (doubles_equality(discriminant, 0)) {
        data->root_1 = data->root_2 = (-data->coeff_b / (2 * data->coeff_a));
        return ONE_ROOT;
    }
    data->root_1 = find_min((-data->coeff_b + sqrt_discriminant) / (2 * data->coeff_a),
                            (-data->coeff_b - sqrt_discriminant) / (2 * data->coeff_a));
    data->root_2 = find_max((-data->coeff_b + sqrt_discriminant) / (2 * data->coeff_a),
                            (-data->coeff_b - sqrt_discriminant) / (2 * data->coeff_a));
    return TWO_ROOTS;
}

root_counter solver(equation_data *data)
{
    assert(!(isnan(data->coeff_a)));
    assert(!(isnan(data->coeff_b)));
    assert(!(isnan(data->coeff_c)));
    assert(data);

    if (doubles_equality(data->coeff_a, 0)) {
        return linear_equation(data);
    }
    return quadratic_equation(data);
}

int doubles_equality(double double_a, double double_b)
{
    bool isnan_a = (isnan(double_a));
    bool isnan_b = (isnan(double_b));

    if ((!(isnan_a)) && isnan_b)
        return 1;
    if (isnan_a && (!(isnan_b)))
        return 1;
    if (isnan_a && isnan_b)
        return 1;
    return (fabs(double_a - double_b) < ACCURACY_LIMIT);
}

double find_min(double min_1, double min_2)
{
    if (!(isnan(min_1)) && (isnan(min_2)))
        return min_1;
    if (isnan(min_1) && (!(isnan(min_2))))
        return min_2;
    if (isnan(min_1) && isnan(min_2))
        return min_1;
    return fmin(min_1, min_2);
}

double find_max(double max_1, double max_2)
{
    if (!(isnan(max_1)) && (isnan(max_2)))
        return max_1;
    if (isnan(max_1) && (!(isnan(max_2))))
        return max_2;
    if (isnan(max_1) && isnan(max_2))
        return max_1;
    return fmax(max_1, max_2);
}

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
                                                   &tests[j].compare_root_2, &tests[j].compare_root_count) != 6) {
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
