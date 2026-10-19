#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "vetores.h"
#include "tests.h"

void testar_vetores(void) {
    printf("[MÓDULO] Vetores...\n");

    // 1. Caso Normal: Álgebra 3D
    Vetor3D u = {1.0, 2.0, 3.0};
    Vetor3D v = {4.0, 5.0, 6.0};

    Vetor3D soma = vec_somar3d(u, v);
    assert(soma.x == 5.0 && soma.y == 7.0 && soma.z == 9.0);

    Vetor3D sub = vec_subtrair3d(v, u);
    assert(sub.x == 3.0 && sub.y == 3.0 && sub.z == 3.0);

    Vetor3D mult = vec_multiplicar_escalar3d(u, 2.0);
    assert(mult.x == 2.0 && mult.y == 4.0 && mult.z == 6.0);

    double dot = vec_produto_escalar3d(u, v);
    assert(dot == 32.0); // 1*4 + 2*5 + 3*6 = 32

    Vetor3D i = {1.0, 0.0, 0.0};
    Vetor3D j = {0.0, 1.0, 0.0};
    Vetor3D k = vec_produto_vetorial3d(i, j);
    assert(k.x == 0.0 && k.y == 0.0 && k.z == 1.0);

    double angulo = vec_angulo_entre_vetores3d(i, j);
    ASSERT_NEAR(angulo, M_PI / 2.0, 1e-5);

    // 2. Caso Limite/Inválido: Vetor N-Dimensional dinâmico
    double comps[3] = {1.0, 2.0, 3.0};
    VetorND vnd = vec_criar_nd(3, comps);
    assert(vnd.dimension == 3 && vnd.components != NULL);
    vec_liberar_nd(&vnd);
    assert(vnd.components == NULL && vnd.dimension == 0);

    // Teste com dimensão inválida
    VetorND vnd_invalido = vec_criar_nd(-1, comps);
    assert(vnd_invalido.components == NULL && vnd_invalido.dimension == 0);

    // Vetor Nulo (normalização não deve causar crash / div por zero)
    Vetor3D nulo = {0.0, 0.0, 0.0};
    Vetor3D norm_nulo = vec_normalizar3d(nulo);
    assert(norm_nulo.x == 0.0 && norm_nulo.y == 0.0 && norm_nulo.z == 0.0);

    printf("Aprovado: Vetores 3D e N-D\n");
}