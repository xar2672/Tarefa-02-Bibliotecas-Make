#include "stdio.h"
#include "math.h"

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


    double quadrado(double x) { return x * x; }      
    double cubo(double x)     { return x * x * x; }  
    double seno(double x)     { return sin(x); }      
    double exponencial(double x) { return exp(x); }   

    //f(x)'= [f(x+h) +f(x-h)]/2h seria a função de diferenças finitas centrada, considere 1h pequeno para a aproximação
    double calc_derivada_1d(Funcao1D f, double x, double h){
    double resultado;
    resultado = (f(x+h) - f(x-h))/(2*h);
    return resultado;
    }
    double calc_resolver_integral_simples(IntegralSimples integral, int particoes){
    double resultado;
    double soma = 0.0;
    double xi;

        /*h= a+b/n*/
    double h =(integral.dx.limite_superior - integral.dx.limite_inferior)/particoes;

        /*parte do somatorio*/
        
        for(particoes; particoes > 0; particoes --){
            xi= integral.dx.limite_inferior + h*particoes;
            soma+=integral.f(xi);

        }
        resultado = h*soma;
        return resultado;
}
int main()
{

    double h =1e-5;
    float valor;
    valor=calc_derivada_1d (quadrado,10,h);
    printf("%.10f",valor);

    /*inicializar integral*/
    IntegralSimples I = { quadrado, {0.0, 1.0} };   // esperado: 1/3
     valor = calc_resolver_integral_simples(I, 1000);
     printf("%.10f",valor);
    return 0;
}