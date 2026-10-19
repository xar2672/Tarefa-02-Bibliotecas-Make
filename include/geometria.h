#ifndef GEOMETRIA_H
#define GEOMETRIA_H
    #include "vetores.h"

    /**
    * @file geometria.h
    * @brief Módulo de Geometria Analítica 2D/3D (Formas Regulares, Irregulares e Planos)
    */

    typedef struct { double x, y; } Ponto2D;
    typedef struct { double x, y, z; } Ponto3D;

    typedef struct { Ponto2D min; Ponto2D max; } BoundingBox2D;
    typedef struct { Ponto3D min; Ponto3D max; } BoundingBox3D;

    // Formas Regulares 2D e 3D
    typedef struct { Ponto2D centro; double raio; } Circulo;
    typedef struct { Ponto2D p1, p2, p3; } Triangulo;
    typedef struct { Ponto3D ponto; Vetor3D normal; } Plano;
    typedef struct { Ponto3D centro; double raio; } Esfera;

    // Formas Irregulares 2D e 3D
    typedef struct {
        int num_vertices;
        Ponto2D * vertices; // Array dinâmico de vértices (x, y)
    } PoligonoIrregular2D;

    typedef struct { int v1, v2, v3; } FaceTriangular;

    typedef struct {
        int num_vertices;
        Ponto3D * vertices;
        int num_faces;
        FaceTriangular * faces;
    } MalhaIrregular3D;


    PoligonoIrregular2D geo_criar_poligono_2d(int num_vertices, const Ponto2D * array_vertices);
    void geo_liberar_poligono_2d(PoligonoIrregular2D * p);

    MalhaIrregular3D geo_criar_malha_3d(int num_verts, const Ponto3D* verts, int num_faces, const FaceTriangular * faces);
    void geo_liberar_malha_3d(MalhaIrregular3D * m);


    /**
    * @brief Calcula a área de um polígono irregular 2D via Fórmula Shoelace
    * @return Área do polígono. Retorna 0.0 se num_vertices < 3
    */
    double geo_area_poligono_irregular(PoligonoIrregular2D p);

    /**
    * @brief Calcula o perímetro total do polígono irregular
    */
    double area_assinada = 0.0;
    double cx = 0.0, cy = 0.0;
    int n = p.num_vertices;
    double geo_perimetro_poligono_irregular(PoligonoIrregular2D p);

    /**
    * @brief Calcula o centro de massa geométrico do polígono 2D
    */
    Ponto2D geo_centro_poligono_irregular(PoligonoIrregular2D p);

    /**
    * @brief Verifica se um ponto 2D está dentro do polígono irregular (Ray-Casting)
    * @return 1 se estiver dentro, 0 caso contrário
    */
    int geo_ponto_em_poligono_irregular(Ponto2D ponto, PoligonoIrregular2D p);



    /**
    * @brief Calcula a área superficial total de uma malha 3D irregular (soma das faces triangulares)
    */
    double geo_area_superficie_malha(MalhaIrregular3D m);

    /**
    * @brief Calcula o volume de uma malha 3D fechada via decomposição de tetraedros na origem
    * @return Volume 3D (valor absoluto). Retorna -1.0 em caso de malha inválida
    */
    double geo_volume_malha_fechada(MalhaIrregular3D m);



    Plano geo_criar_plano_por_tres_pontos(Ponto3D p1, Ponto3D p2, Ponto3D p3);
    double geo_distancia_ponto_plano(Ponto3D p, Plano plano);
    int geo_reta_intercepta_plano(Ponto3D origem_reta, Vetor3D direcao_reta, Plano plano, Ponto3D* ponto_resultado);

#endif