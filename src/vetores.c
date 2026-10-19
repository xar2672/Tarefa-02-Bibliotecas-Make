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

Vetor3D vec_normalizar3d(Vetor3D v) {
	double modulo = vec_modulo3d(v);
	if (modulo == 0.0) {
		return v;
	}

	Vetor3D normalizado = {
		v.x / modulo,
		v.y / modulo,
		v.z / modulo
	};

	return normalizado;
}

double vec_produto_escalar3d(Vetor3D v1, Vetor3D v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vetor3D vec_produto_vetorial3d(Vetor3D v1, Vetor3D v2) {
	Vetor3D resultado = {
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	};

	return resultado;
}

double vec_angulo_entre_vetores3d(Vetor3D v1, Vetor3D v2) {
	double modulo1 = vec_modulo3d(v1);
	double modulo2 = vec_modulo3d(v2);
	if (modulo1 == 0.0 || modulo2 == 0.0) {
		return 0.0;
	}

	double cosseno = (v1.x / modulo1) * (v2.x / modulo2) +
		(v1.y / modulo1) * (v2.y / modulo2) +
		(v1.z / modulo1) * (v2.z / modulo2);
	if (cosseno > 1.0) {
		cosseno = 1.0;
	} else if (cosseno < -1.0) {
		cosseno = -1.0;
	}

	return acos(cosseno);
}

Vetor3D vec_projecao3d(Vetor3D v_origem, Vetor3D v_base) {
	Vetor3D base_unitaria = vec_normalizar3d(v_base);
	double componente = vec_produto_escalar3d(v_origem, base_unitaria);

	return vec_multiplicar_escalar3d(base_unitaria, componente);
}

