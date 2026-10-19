#include <stdio.h>
#include <assert.h>
#include "geometria.h"
#include "tests.h"

void testar_geometria(void) {
    printf("[MÓDULO] Geometria Analítica 2D/3D...\n");

    // 1. Polígono 2D
    Ponto2D verts_q[4] = {{0.0, 0.0}, {2.0, 0.0}, {2.0, 2.0}, {0.0, 2.0}};
    PoligonoIrregular2D quad = geo_criar_poligono_2d(4, verts_q);

    ASSERT_NEAR(geo_area_poligono_irregular(quad), 4.0, 1e-5);
    ASSERT_NEAR(geo_perimetro_poligono_irregular(quad), 8.0, 1e-5);

    Ponto2D centro = geo_centro_poligono_irregular(quad);
    ASSERT_NEAR(centro.x, 1.0, 1e-5);
    ASSERT_NEAR(centro.y, 1.0, 1e-5);

    // Ponto em Polígono (Ray-Casting)
    Ponto2D dentro = {1.0, 1.0};
    Ponto2D fora = {3.0, 3.0};
    assert(geo_ponto_em_poligono_irregular(dentro, quad) == 1);
    assert(geo_ponto_em_poligono_irregular(fora, quad) == 0);

    geo_liberar_poligono_2d(&quad);

    // 2. Geometria 3D
    Ponto3D p1 = {0.0, 0.0, 0.0};
    Ponto3D p2 = {1.0, 0.0, 0.0};
    Ponto3D p3 = {0.0, 1.0, 0.0};
    Plano plano = geo_criar_plano_por_tres_pontos(p1, p2, p3);

    Ponto3D p_teste = {0.0, 0.0, 5.0};
    ASSERT_NEAR(geo_distancia_ponto_plano(p_teste, plano), 5.0, 1e-5);

    // 3. Caso Limite: Polígono inválido (< 3 vértices)
    PoligonoIrregular2D invalido = geo_criar_poligono_2d(2, verts_q);
    assert(invalido.vertices == NULL && invalido.num_vertices == 0);

    printf("Aprovado: Polígonos 2D e Geometria Espacial\n");
}