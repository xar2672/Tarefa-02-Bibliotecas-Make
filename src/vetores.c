#include "vetores.h"

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

VetorND vec_criar_nd(int dimension, const double* components) {
	VetorND vetor = {0, NULL};

	if (dimension <= 0 || components == NULL ||
		(size_t)dimension > SIZE_MAX / sizeof(*vetor.components)) {
		return vetor;
	}

	vetor.components = malloc((size_t)dimension * sizeof(*vetor.components));
	if (vetor.components == NULL) {
		return vetor;
	}

	vetor.dimension = dimension;
	for (int i = 0; i < dimension; ++i) {
		vetor.components[i] = components[i];
	}

	return vetor;
}

void vec_liberar_nd(VetorND* v) {
	if (v == NULL) {
		return;
	}

	free(v->components);
	v->components = NULL;
	v->dimension = 0;
}

Vetor3D vec_somar3d(Vetor3D v1, Vetor3D v2) {
	Vetor3D resultado = {
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z
	};

	return resultado;
}

Vetor3D vec_subtrair3d(Vetor3D v1, Vetor3D v2) {
	Vetor3D resultado = {
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z
	};

	return resultado;
}

Vetor3D vec_multiplicar_escalar3d(Vetor3D v, double escalar) {
	Vetor3D resultado = {
		v.x * escalar,
		v.y * escalar,
		v.z * escalar
	};

	return resultado;
}

double vec_modulo3d(Vetor3D v) {
	return hypot(hypot(v.x, v.y), v.z);
}

