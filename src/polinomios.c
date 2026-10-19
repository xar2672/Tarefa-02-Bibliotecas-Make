#include "polinomios.h"

#include <math.h>
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

double poli_avaliar(Polinomio p, double x) {
	double resultado = 0.0;
	for (const Termo *termo = p.inicio; termo != NULL; termo = termo->proximo) {
		resultado += termo->coeficiente * pow(x, termo->expoente);
	}

	return resultado;
}

