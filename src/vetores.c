#include "vetores.h"

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

