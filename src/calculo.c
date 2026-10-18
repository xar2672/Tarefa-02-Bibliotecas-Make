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

double calc_derivada_parcial(FuncaoND f, const double * ponto, int num_vars, int var_index, double h){

}
void calc_gradiente(FuncaoND f, const double * ponto, int num_vars, double h, double * resultado){

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

}