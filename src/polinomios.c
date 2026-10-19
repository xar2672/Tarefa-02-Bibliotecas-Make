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

Polinomio poli_somar(Polinomio p1, Polinomio p2) {
	Polinomio resultado = poli_criar_vazio();

	for (const Termo *termo = p1.inicio; termo != NULL; termo = termo->proximo) {
		poli_adicionar_termo(&resultado, termo->coeficiente, termo->expoente);
	}

	for (const Termo *termo = p2.inicio; termo != NULL; termo = termo->proximo) {
		Termo *atual = resultado.inicio;
		while (atual != NULL && atual->expoente < termo->expoente) {
			atual = atual->proximo;
		}

		if (atual != NULL && atual->expoente == termo->expoente) {
			poli_adicionar_termo(
				&resultado,
				atual->coeficiente + termo->coeficiente,
				termo->expoente
			);
		} else {
			poli_adicionar_termo(&resultado, termo->coeficiente, termo->expoente);
		}
	}

	return resultado;
}

Polinomio poli_derivada_algebrica(Polinomio p) {
	Polinomio derivada = poli_criar_vazio();

	for (const Termo *termo = p.inicio; termo != NULL; termo = termo->proximo) {
		if (termo->expoente > 0) {
			double coeficiente = termo->coeficiente * termo->expoente;
			poli_adicionar_termo(&derivada, coeficiente, termo->expoente - 1);
		}
	}

	return derivada;
}

