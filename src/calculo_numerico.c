#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "calculo_numerico.h"
#include "calculo.h"

    StatusCalculo num_bisseccao(Funcao1D f, double a, double b, double tol, int max_iter, double* raiz_resultado){
        /*ponto médio*/
        /*fazer tolerancia a erros para B*/
        if(f(a) == 0 || f(b) ==0){
            *raiz_resultado = 0;
            return SUCESSO;
        }
            else if(f(a)*f(b) > 0){
            printf("valores invalidos");
            return ERRO_INTERVALO_INVALIDO;
            }
        
        /*queria fazer recursivo mas devo obedecer o max_inter*/
        while(max_iter > 0){
            max_iter--;
            double c = (a+b)/2;
            double fc = f(c);

            if (fc == 0.0 || (b - a) / 2.0 < tol) {
            *raiz_resultado = c;
            return SUCESSO;
            }

            /*significa que há pelo menos uma raiz no intervalo (a,c), caso else significa o oposto*/
            if (f(a)*f(c)<0){
                b = c;
            } else a = c;
        }
        *raiz_resultado = (a + b) / 2.0;
        return ERRO_NAO_CONVERGIU;
    }

    StatusCalculo num_newton_raphson(Funcao1D f, double chute_inicial, double tol, int max_iter, double* raiz_resultado){

    }