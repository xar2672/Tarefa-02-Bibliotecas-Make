#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "calculo.h"

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

   return (l_superior - l_inferior)/(2.0 * h);
}
void calc_gradiente(FuncaoND f, const double * ponto, int num_vars, double h, double * resultado){
    /*arranjo de todas as derivdas parcias guardadas no ponteiro resultado*/
    for (int i = 0; i < num_vars; i++) {
        resultado[i] = calc_derivada_parcial(f, ponto, num_vars, i, h);
    }
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
if (particoes_x <= 0 || particoes_y <= 0) return 0.0;

    double hx = (integral.dx.limite_superior - integral.dx.limite_inferior) / particoes_x;
    double hy = (integral.dy.limite_superior - integral.dy.limite_inferior) / particoes_y;
    double soma = 0.0;

    for (int i = 0; i < particoes_x; i++) {
        double x = integral.dx.limite_inferior + (i + 0.5) * hx;
        for (int j = 0; j < particoes_y; j++) {
            double y = integral.dy.limite_inferior + (j + 0.5) * hy;
            double vars[2] = {x, y};
            soma += integral.f(vars, 2);
        }
    }
    
    return hx * hy * soma;
}