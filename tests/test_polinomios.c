#include <stdio.h>
#include <assert.h>
#include "polinomios.h"
#include "tests.h"

void testar_polinomios(void) {
    printf("[MÓDULO] Polinômios Esparsos...\n");

    Polinomio p1 = poli_criar_vazio();
    poli_adicionar_termo(&p1, 1.0, 0);
    poli_adicionar_termo(&p1, 2.0, 1);
    poli_adicionar_termo(&p1, 3.0, 2);

    double val = poli_avaliar(p1, 2.0);
    ASSERT_NEAR(val, 17.0, 1e-5);

    Polinomio p2 = poli_criar_vazio();
    poli_adicionar_termo(&p2, -2.0, 1);
    poli_adicionar_termo(&p2, 4.0, 3);

    Polinomio p3 = poli_somar(p1, p2);
    ASSERT_NEAR(poli_avaliar(p3, 2.0), 45.0, 1e-5);

    Polinomio dp1 = poli_derivada_algebrica(p1);
    ASSERT_NEAR(poli_avaliar(dp1, 2.0), 14.0, 1e-5);

    // Caso Limite: remoção automática de termo ao definir coef 0.0
    poli_adicionar_termo(&p1, 0.0, 2);
    ASSERT_NEAR(poli_avaliar(p1, 2.0), 5.0, 1e-5);

    poli_liberar(&p1);
    poli_liberar(&p2);
    poli_liberar(&p3);
    poli_liberar(&dp1);

    printf("Aprovado: Polinômios\n");
}