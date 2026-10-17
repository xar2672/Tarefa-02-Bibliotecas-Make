#ifndef POLINOMIOS_H
#define POLINOMIOS_H

    /**
    * @file polinomios.h
    * @brief Módulo de Polinômios Esparsos implementado com Linked-List
    */

    // Nó da lista encadeada (guarda apenas termos com coeficientes não nulos)
    typedef struct Termo {
        double coeficiente;
        int expoente;
        struct Termo * proximo;
    } Termo;

    typedef struct {
        Termo* inicio;
    } Polinomio;


    /**
    * @brief Inicializa um polinômio vazio (0.0)
    */
    Polinomio poli_criar_vazio(void);

    /**
    * @brief Adiciona ou substitui um termo no polinômio mantendo a lista ordenada por expoente
    * @param p Ponteiro para a estrutura Polinomio
    * @param coef Coeficiente numérico. Se for 0.0, o termo é removido
    * @param exp Expoente do termo (deve ser >= 0)
    */
    void poli_adicionar_termo(Polinomio * p, double coef, int exp);

    /**
    * @brief Avalia o polinômio para um determinado valor de x: f(x)
    */
    double poli_avaliar(Polinomio p, double x);

    /**
    * @brief Soma dois polinômios esparsos e retorna um novo polinômio
    */
    Polinomio poli_somar(Polinomio p1, Polinomio p2);

    /**
    * @brief Retorna a derivada algébrica exata do polinômio
    */
    Polinomio poli_derivada_algebrica(Polinomio p);

    /**
    * @brief Libera toda a memória encadeada alocada pelo polinômio
    */
    void poli_liberar(Polinomio* p);

#endif