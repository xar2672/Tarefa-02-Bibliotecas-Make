#include "polinomios.h"

#include <stddef.h>
#include <stdlib.h>

Polinomio poli_criar_vazio(void) {
	Polinomio polinomio = {NULL};
	return polinomio;
}

void poli_adicionar_termo(Polinomio *p, double coef, int exp) {
	if (p == NULL || exp < 0) {
		return;
	}

	Termo **atual = &p->inicio;
	while (*atual != NULL && (*atual)->expoente < exp) {
		atual = &(*atual)->proximo;
	}

	if (*atual != NULL && (*atual)->expoente == exp) {
		if (coef == 0.0) {
			Termo *removido = *atual;
			*atual = removido->proximo;
			free(removido);
		} else {
			(*atual)->coeficiente = coef;
		}
		return;
	}

	if (coef == 0.0) {
		return;
	}

	Termo *novo = malloc(sizeof(*novo));
	if (novo == NULL) {
		return;
	}

	novo->coeficiente = coef;
	novo->expoente = exp;
	novo->proximo = *atual;
	*atual = novo;
}
