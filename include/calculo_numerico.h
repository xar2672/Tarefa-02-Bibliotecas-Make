#ifndef CALCULO_NUMERICO_H
#define CALCULO_NUMERICO_H
    #include "calculo.h"

    /**
    * @file calculo_numerico.h
    * @brief Módulo de Métodos Numéricos (Resolução de Equações e Encontro de Raízes).
    */

    typedef enum {
        SUCESSO = 0,
        ERRO_NAO_CONVERGIU = -1,
        ERRO_INTERVALO_INVALIDO = -2,
        ERRO_DERIVADA_NULA = -3
    } StatusCalculo;

    /**
    * @brief Encontra a raiz de f(x) = 0 pelo Método da Bissecção
    * @param f Função de 1 variável
    * @param a Início do intervalo
    * @param b Fim do intervalo. Deve satisfazer f(a) * f(b) < 0
    * @param tol Tolerância de erro
    * @param max_iter Número máximo de iterações permitidas
    * @param raiz_resultado Ponteiro onde o valor da raiz será gravado
    * @return StatusCalculo
    */
    StatusCalculo num_bisseccao(Funcao1D f, double a, double b, double tol, int max_iter, double* raiz_resultado);

    /**
    * @brief Encontra a raiz de f(x) = 0 pelo Método de Newton-Raphson
    * @param f Função de 1 variável
    * @param chute_inicial Estimativa inicial x0
    * @param tol Tolerância de erro
    * @param max_iter Número máximo de iterações
    * @param raiz_resultado Ponteiro onde o valor da raiz será gravado
    * @return StatusCalculo
    */
    StatusCalculo num_newton_raphson(Funcao1D f, double chute_inicial, double tol, int max_iter, double* raiz_resultado);

#endif