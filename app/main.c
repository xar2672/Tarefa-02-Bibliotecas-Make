#include "vetores.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

static void assert_vetor3d(Vetor3D atual, Vetor3D esperado) {
	const double tolerancia = 1e-9;
	assert(fabs(atual.x - esperado.x) < tolerancia);
	assert(fabs(atual.y - esperado.y) < tolerancia);
	assert(fabs(atual.z - esperado.z) < tolerancia);
}

int main(void) {
	const double valores[] = {1.5, -2.0, 3.25};
	VetorND vetor_nd = vec_criar_nd(3, valores);
	assert(vetor_nd.dimension == 3);
	assert(vetor_nd.components != NULL);
	for (int i = 0; i < vetor_nd.dimension; ++i) {
		assert(vetor_nd.components[i] == valores[i]);
	}
	vec_liberar_nd(&vetor_nd);
	assert(vetor_nd.dimension == 0 && vetor_nd.components == NULL);
	vec_liberar_nd(&vetor_nd);
	vec_liberar_nd(NULL);

	VetorND dimensao_invalida = vec_criar_nd(0, valores);
	VetorND componentes_nulos = vec_criar_nd(3, NULL);
	assert(dimensao_invalida.dimension == 0 && dimensao_invalida.components == NULL);
	assert(componentes_nulos.dimension == 0 && componentes_nulos.components == NULL);

	Vetor3D v1 = {1.0, 2.0, 3.0};
	Vetor3D v2 = {4.0, -5.0, 6.0};
	assert_vetor3d(vec_somar3d(v1, v2), (Vetor3D){5.0, -3.0, 9.0});
	assert_vetor3d(vec_subtrair3d(v1, v2), (Vetor3D){-3.0, 7.0, -3.0});
	assert_vetor3d(vec_multiplicar_escalar3d(v1, 2.5), (Vetor3D){2.5, 5.0, 7.5});

	Vetor3D vetor_norma = {3.0, 4.0, 12.0};
	assert(fabs(vec_modulo3d(vetor_norma) - 13.0) < 1e-9);
	Vetor3D normalizado = vec_normalizar3d(vetor_norma);
	assert(fabs(vec_modulo3d(normalizado) - 1.0) < 1e-9);
	Vetor3D vetor_nulo = {0.0, 0.0, 0.0};
	assert_vetor3d(vec_normalizar3d(vetor_nulo), vetor_nulo);

	assert(fabs(vec_produto_escalar3d(v1, v2) - 12.0) < 1e-9);
	Vetor3D produto_vetorial = vec_produto_vetorial3d(v1, v2);
	assert_vetor3d(produto_vetorial, (Vetor3D){27.0, 6.0, -13.0});
	assert(fabs(vec_produto_escalar3d(produto_vetorial, v1)) < 1e-9);
	assert(fabs(vec_produto_escalar3d(produto_vetorial, v2)) < 1e-9);

	Vetor3D eixo_x = {1.0, 0.0, 0.0};
	Vetor3D eixo_y = {0.0, 1.0, 0.0};
	Vetor3D eixo_x_oposto = {-1.0, 0.0, 0.0};
	double pi = acos(-1.0);
	assert(fabs(vec_angulo_entre_vetores3d(eixo_x, eixo_y) - pi / 2.0) < 1e-9);
	assert(fabs(vec_angulo_entre_vetores3d(eixo_x, eixo_x_oposto) - pi) < 1e-9);
	assert(vec_angulo_entre_vetores3d(vetor_nulo, eixo_x) == 0.0);

	Vetor3D origem = {3.0, 4.0, 0.0};
	Vetor3D base = {2.0, 0.0, 0.0};
	assert_vetor3d(vec_projecao3d(origem, base), (Vetor3D){3.0, 0.0, 0.0});
	assert_vetor3d(vec_projecao3d(origem, vetor_nulo), vetor_nulo);

	printf("Todos os testes de vetores passaram.\n");
	return 0;
}
