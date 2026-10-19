#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "calculo_numerico.h"
#include "calculo.h"

    
    StatusCalculo num_bisseccao(Funcao1D f, double a, double b, double tol, int max_iter, double* raiz_resultado){
        /* para evitar erros com a > b*/
        double tmp;

        /*swap*/
        if(a>b){tmp = a; a = b; b = tmp;}

        /*tolerancia a erros*/
        if(f == NULL){return ERRO_INTERVALO_INVALIDO;}
        if(f(a) == 0) {*raiz_resultado = a; return SUCESSO;} 
        if(f(b) ==0){*raiz_resultado = b; return SUCESSO;}
        if(f(a)*f(b) > 0){return ERRO_INTERVALO_INVALIDO;}

        /*preciso de variaveis não consigo trabalhar só em ciam da função*/
        double fa = f(a);
        /*queria fazer recursivo mas devo obedecer o max_inter*/

        while(max_iter > 0){
            max_iter--;
                /*ponto médio C*/
            double c = (a+b)/2;
            double fc = f(c);

            if (fc == 0.0 || (b - a) / 2.0 < tol) {
            *raiz_resultado = c;
            return SUCESSO;
            }

            /*significa que há pelo menos uma raiz no intervalo (a,c), caso else significa o oposto*/
            if (fa * fc <0){
                b = c;
            } else {a = c;
            fa = fc;
                }
        }
        *raiz_resultado = (a + b) / 2.0;
        return ERRO_NAO_CONVERGIU;
    }

    StatusCalculo num_newton_raphson(Funcao1D f, double chute_inicial, double tol, int max_iter, double* raiz_resultado){
        /*(Funcao1D f, double x, double h){*/
        if (f == NULL || raiz_resultado == NULL || tol <= 0.0 || max_iter <= 0){return ERRO_INTERVALO_INVALIDO;}
        double h = 1e-5;
            if(f(chute_inicial) == 0){ *raiz_resultado = chute_inicial ; return SUCESSO;}
        while(max_iter >0){
            max_iter--;
            double fx = f(chute_inicial);
            double dx = calc_derivada_1d(f, chute_inicial,h);

            if(fabs(dx)< 1e-12){
                *raiz_resultado = chute_inicial;
                return ERRO_DERIVADA_NULA;
            }
            double chute_novo = chute_inicial-fx/dx;

            if (!isfinite(chute_novo)) {               /* divergiu */
                *raiz_resultado = chute_inicial;
            return ERRO_NAO_CONVERGIU;
            }
            if (fabs(chute_novo - chute_inicial) < tol) {          /* convergiu */
                *raiz_resultado = chute_novo;
                return SUCESSO;
            }

            chute_inicial = chute_novo;
            }
            *raiz_resultado = chute_inicial;
            return ERRO_NAO_CONVERGIU;


        }