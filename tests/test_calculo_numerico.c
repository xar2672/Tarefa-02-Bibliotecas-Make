#include <stdio.h>
#include <assert.h>
#include "calculo_numerico.h"
#include "tests.h"

static double f_raiz(double x) {
    return x * x - 4.0;
}

void testar_calculo_numerico(void) {
    printf("[MÓDULO] Cálculo Numérico...\n");

    double raiz = 0.0;
    StatusCalculo st;

    // 1. Bissecção (Caso Normal
    st = num_bisseccao(f_raiz, 0.0, 5.0, 1e-5, 100, &raiz);
    assert(st == SUCESSO);
    ASSERT_NEAR(raiz, 2.0, 1e-4);

    // 2. Bissecção (Caso de Erro: Sem troca de sinal em [3, 5])
    st = num_bisseccao(f_raiz, 3.0, 5.0, 1e-5, 100, &raiz);
    assert(st == ERRO_INTERVALO_INVALIDO);

    // 3. Newton-Raphson (Caso Normal com chute = 3.0)
    st = num_newton_raphson(f_raiz, 3.0, 1e-5, 100, &raiz);
    assert(st == SUCESSO);
    ASSERT_NEAR(raiz, 2.0, 1e-4);

    // =========================================================================
    // 4. DEMONSTRAÇÃO EXIGIDA PELO EDITAL (TESTE QUE FALHA / PASSA)
    // Se desejar simular a falha para a apresentação do trabalho, troque 0 por 1:
    #if 0
        // ESTA LINHA IRÁ FALHAR PROPOSITADAMENTE PARA DEMONSTRAÇÃO
        assert(st == ERRO_NAO_CONVERGIU); 
    #endif
    // =========================================================================

    printf("Aprovado: Bissecção e Newton-Raphson\n");
}