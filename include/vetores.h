#ifndef VETORES_H
#define VETORES_H

    /**
    * @file vetores.h
    * @brief Módulo de Álgebra Linear e Operações Vetoriais em 2D, 3D e ND
    */

    // Structs de Vetores de dimensão fixa
    typedef struct { double x, y; } Vetor2D;
    typedef struct { double x, y, z; } Vetor3D;

    // Struct de Vetor N-Dimensional
    typedef struct {
        int dimension;
        double* components;
    } VetorND;



    /**
    * @brief Cria um vetor N-dimensional alocado dinamicamente
    * @param dimension Tamanho do vetor (deve ser > 0)
    * @param components Array com os valores iniciais
    * @return Struct VetorND configurada; caso em erros de alocação, dimensao = 0 e componentes = NULL
    */
    VetorND vec_criar_nd(int dimension, const double* components);

    /**
    * @brief Libera a memória alocada para um VetorND
    * @param v Ponteiro para o VetorND a ser liberado
    */
    void vec_liberar_nd(VetorND* v);



    /**
    * @brief Soma dois vetores 3D
    */
    Vetor3D vec_somar3d(Vetor3D v1, Vetor3D v2);

    /**
    * @brief Subtrai dois vetores 3D (v1 - v2)
    */
    Vetor3D vec_subtrair3d(Vetor3D v1, Vetor3D v2);

    /**
    * @brief Multiplica um Vetor 3D por um escalar
    */
    Vetor3D vec_multiplicar_escalar3d(Vetor3D v, double escalar);

    /**
    * @brief Calcula a norma/módulo (comprimento) de um Vetor 3D
    * @return Módulo do Vetor (>= 0.0)
    */
    double vec_modulo3d(Vetor3D v);

    /**
    * @brief Retorna o Vetor unitário (norma = 1.0)
    * @return Vetor normalizado. Se o vetor for nulo, retorna o próprio vetor nulo
    */
    Vetor3D vec_normalizar3d(Vetor3D v);

    /**
    * @brief Calcula o produto escalar entre dois Vetores 3D
    */
    double vec_produto_escalar3d(Vetor3D v1, Vetor3D v2);

    /**
    * @brief Calcula o produto Vetorial (v1 x v2), resultando em um vetor perpendicular aos dois
    */
    Vetor3D vec_produto_vetorial3d(Vetor3D v1, Vetor3D v2);

    /**
    * @brief Calcula o ângulo entre dois Vetores em radianos
    * @return Ângulo em radianos [0, PI]. Retorna 0.0 em caso de vetor nulo
    */
    double vec_angulo_entre_vetores3d(Vetor3D v1, Vetor3D v2);

    /**
    * @brief Projeta o vetor "v_origem" sobre o vetor "v_base"
    */
    Vetor3D vec_projecao3d(Vetor3D v_origem, Vetor3D v_base);

#endif