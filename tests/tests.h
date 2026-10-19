#ifndef TESTS_H
#define TESTS_H
#include <math.h>

#define ASSERT_NEAR(a, b, tol) assert(fabs((a) - (b)) < (tol))

void testar_vetores(void);
void testar_polinomios(void);
void testar_geometria(void);
void testar_calculo(void);
void testar_calculo_numerico(void);

#endif