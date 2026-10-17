#ifndef CALCULO_H
#define CALCULO_H

    /**
    * @file calculo.h
    * @brief Módulo de Cálculo Diferencial e Integral em 1D e N-Dimensões.
    */

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

    

    /**
    * @brief Aproxima a derivada f'(x) pelo método das diferenças finitas centradas
    * @param f Ponteiro para a função f(x)
    * @param x Ponto de avaliação
    * @param h Passo de diferenciação; h > 0
    * @return Valor aproximado da derivada
    */
    double calc_derivada_1d(Funcao1D f, double x, double h);

    /**
    * @brief Calcula a derivada parcial de uma função multivariável em relação à variável var_index
    * @param f Função N-dimensional
    * @param ponto Array contendo os valores do ponto P(x0, x1, ..., xN)
    * @param num_vars Número total de variáveis
    * @param var_index Índice da variável a ser derivada
    * @param h Passo de variação
    */
    double calc_derivada_parcial(FuncaoND f, const double * ponto, int num_vars, int var_index, double h);

    /**
    * @brief Computa o Vetor Gradiente em um determinado ponto (array de derivadas parciais)
    * @param resultado Array pré-alocado de tamanho num_vars onde o resultado será gravado
    */
    void calc_gradiente(FuncaoND f, const double * ponto, int num_vars, double h, double * resultado);

    

    /**
    * @brief Resolve uma integral simples 1D pelo Método dos Trapézios Composto
    * @param integral Struct contendo a função e o intervalo de integração
    * @param particoes Número de subdivisões (deve ser > 0)
    */
    double calc_resolver_integral_simples(IntegralSimples integral, int particoes);

    /**
    * @brief Resolve uma integral dupla sobre uma região retangular usando a Regra do Ponto Médio 2D
    */
    double calc_resolver_integral_dupla(IntegralDupla integral, int particoes_x, int particoes_y);

#endif