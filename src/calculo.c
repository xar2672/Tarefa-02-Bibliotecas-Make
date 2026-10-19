#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "calculo.h"

    // Ponteiros para funções matemáticas genéricas
    typedef double (*Funcao1D)(double x);
    typedef double (*FuncaoND)(const double * vars, int num_vars);

    typedef struct {
        double limite_inferior;
        double limite_superior;
    } Intervalo;

    typedef struct {
        Funcao1D f;
        Intervalo dx;
    } IntegralSimples;

    typedef struct {
        FuncaoND f;
        Intervalo dx;
        Intervalo dy;
    } IntegralDupla;

    //f(x)'= [f(x+h) +f(x-h)]/2h seria a função de diferenças finitas centrada, considere 1h pequeno para a aproximação
double calc_derivada_1d(Funcao1D f, double x, double h){
    double resultado;
    resultado = (f(x+h) - f(x-h))/(2*h);
    return resultado;
}

double calc_derivada_parcial(FuncaoND f, const double * ponto, int num_vars, int var_index, double h)
{
    /*tratar do ponteiro recebido pelo array ponto*/
    double * p = (double *) malloc(num_vars * sizeof(double));
    memcpy(p, ponto, num_vars * sizeof(double));

    /*por conta da diferença de struct preferi não reultilizar a função de derivada*/

    p[var_index] = ponto[var_index] + h;
    double l_superior = f(p, num_vars);

    p[var_index] = ponto[var_index] - h;
    double l_inferior = f(p, num_vars);
    // return (f(p,num_vars) - f(p,num_vars))/(2*h); por conta da alocação dinamica e do free fui obrigado copiar os valores pra f_mais e f_menos
    free(p);

   return (l_inferior - l_superior)/(2.0*h);
}
void calc_gradiente(FuncaoND f, const double * ponto, int num_vars, double h, double * resultado){
    /*arranjo de todas as derivdas parcias guardadas no ponteiro resultado*/
    for (int i = 0; i < num_vars; i++) {
        resultado[i] = calc_derivada_parcial(f, ponto, num_vars, i, h);
    }
    return 0;
}

double calc_resolver_integral_simples(IntegralSimples integral, int particoes){
    double resultado;
    double soma = 0.0;
    double xi;

        /*h= b-a/n*/
    double h =(integral.dx.limite_superior - integral.dx.limite_inferior)/particoes;

        /*parte do somatorio*/
        
        for(particoes; particoes > 0; particoes --){
            xi= integral.dx.limite_inferior + h*particoes;
            soma+=integral.f(xi);

        }

        /*resultado da soma de rieman*/
        resultado = h*soma;
        return resultado;
}
double calc_resolver_integral_dupla(IntegralDupla integral, int particoes_x, int particoes_y){

    IntegralSimples integralsimples1;
    integralsimples1.f = integral.f;
    integralsimples1.dx = integral.dx;

    IntegralSimples integralsimples2;
    integralsimples2.f = integral.f;
    integralsimples2.dx = integral.dy;


    double dx=calc_resolver_integral_simples(integralsimples1,particoes_x);
    double dy=calc_resolver_integral_simples(integralsimples2,particoes_y);

}