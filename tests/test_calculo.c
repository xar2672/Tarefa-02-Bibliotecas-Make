#include <stdio.h>
#include <assert.h>
#include "calculo.h"
#include "tests.h"

static double func_quadratica(double x) {
    return x * x;
}

static double func_2d(const double* vars, int num_vars) {
    (void)num_vars;
    return vars[0] * vars[0] + vars[1] * vars[1];
}

void testar_calculo(void) {
    printf("[MÓDULO] Cálculo Diferencial e Integral...\n");

    // 1. Derivada 1D
    double df = calc_derivada_1d(func_quadratica, 3.0, 1e-5);
    ASSERT_NEAR(df, 6.0, 1e-4);

    // 2. Gradiente: grad(f(x,y)) em (1, 2) é (2, 4)
    double ponto[2] = {1.0, 2.0};
    double grad[2] = {0.0, 0.0};
    calc_gradiente(func_2d, ponto, 2, 1e-5, grad);
    ASSERT_NEAR(grad[0], 2.0, 1e-4);
    ASSERT_NEAR(grad[1], 4.0, 1e-4);

    // 3. Integral Simples
    IntegralSimples int_1d = {func_quadratica, {0.0, 1.0}};
    double area = calc_resolver_integral_simples(int_1d, 1000);
    ASSERT_NEAR(area, 1.0 / 3.0, 1e-3);

    // 4. Integral Dupla
    IntegralDupla int_2d = {func_2d, {0.0, 1.0}, {0.0, 1.0}};
    double vol = calc_resolver_integral_dupla(int_2d, 100, 100);
    ASSERT_NEAR(vol, 2.0 / 3.0, 1e-3);

    printf("  ✓ Aprovado: Derivadas, Gradientes e Integrais 1D/2D\n");
}