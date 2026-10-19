#include <stdio.h>
#include "tests.h"

int main(void) {
    printf("--- Executando Suíte de Testes ---\n");

    testar_vetores();
    testar_polinomios();
    testar_geometria();
    testar_calculo();
    testar_calculo_numerico();

    printf("\nTodos os testes passaram com sucesso!\n");
    return 0;
}