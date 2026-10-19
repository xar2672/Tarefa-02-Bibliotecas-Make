#include "polinomios.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
	Polinomio p1 = poli_criar_vazio();
	Polinomio p2 = poli_criar_vazio();

	poli_adicionar_termo(&p1, 3.0, 2);
	poli_adicionar_termo(&p1, 2.0, 1);
	poli_adicionar_termo(&p1, 1.0, 0);

	poli_adicionar_termo(&p2, -1.0, 2);
	poli_adicionar_termo(&p2, 4.0, 1);
	poli_adicionar_termo(&p2, 5.0, 0);

	Polinomio soma = poli_somar(p1, p2);
	const Termo *termo = soma.inicio;

	assert(termo != NULL && termo->expoente == 0 && termo->coeficiente == 6.0);
	termo = termo->proximo;
	assert(termo != NULL && termo->expoente == 1 && termo->coeficiente == 6.0);
	termo = termo->proximo;
	assert(termo != NULL && termo->expoente == 2 && termo->coeficiente == 2.0);
	assert(termo->proximo == NULL);

	assert(poli_avaliar(p1, 2.0) == 17.0);
	assert(poli_avaliar(p2, 2.0) == 9.0);
	assert(poli_avaliar(soma, 2.0) == 26.0);

	Polinomio derivada = poli_derivada_algebrica(soma);
	termo = derivada.inicio;
	assert(termo != NULL && termo->expoente == 0 && termo->coeficiente == 6.0);
	termo = termo->proximo;
	assert(termo != NULL && termo->expoente == 1 && termo->coeficiente == 4.0);
	assert(termo->proximo == NULL);
	assert(poli_avaliar(derivada, 2.0) == 14.0);

	printf("Teste de soma passou: p1(2) + p2(2) = %.1f\n",
		poli_avaliar(soma, 2.0));
	printf("Teste de derivada passou: soma'(2) = %.1f\n",
		poli_avaliar(derivada, 2.0));

	poli_liberar(&p1);
	poli_liberar(&p2);
	poli_liberar(&soma);
	poli_liberar(&derivada);
	return 0;
}
