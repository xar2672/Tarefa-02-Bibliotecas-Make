#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "geometria.h"



PoligonoIrregular2D geo_criar_poligono_2d(int num_vertices, const Ponto2D * array_vertices) {
    PoligonoIrregular2D p;
    p.num_vertices = 0;
    p.vertices = NULL;

    if (num_vertices < 3 || array_vertices == NULL) {
        return p;
    }

    p.vertices = (Ponto2D*) malloc(num_vertices * sizeof(Ponto2D));
    if (p.vertices == NULL) {
        return p;
    }

    for (int i = 0; i < num_vertices; i++) {
        p.vertices[i] = array_vertices[i];
    }
    p.num_vertices = num_vertices;

    return p;
}

void geo_liberar_poligono_2d(PoligonoIrregular2D* p) {
    if (p != NULL && p->vertices != NULL) {
        free(p->vertices);
        p->vertices = NULL;
        p->num_vertices = 0;
    }
}


MalhaIrregular3D geo_criar_malha_3d(int num_verts, const Ponto3D* verts, int num_faces, const FaceTriangular* faces) {
    MalhaIrregular3D m;
    m.num_vertices = 0;
    m.vertices = NULL;
    m.num_faces = 0;
    m.faces = NULL;

    if (num_verts < 3 || verts == NULL ||
        num_faces < 1 || faces == NULL) {
        return m;
    }


    m.vertices = (Ponto3D*) malloc(num_verts * sizeof(Ponto3D));
    m.faces = (FaceTriangular*) malloc(num_faces * sizeof(FaceTriangular));

    if (m.vertices == NULL || m.faces == NULL) {
        free(m.vertices);
        free(m.faces);
        m.vertices = NULL;
        m.faces = NULL;
        return m;
    }

    for (int i = 0; i < num_verts; i++) {
        m.vertices[i] = verts[i];
    }
    for (int i = 0; i < num_faces; i++) {
        m.faces[i] = faces[i];
    }
   
    m.num_vertices = num_verts;
    m.num_faces = num_faces;

    return m;
}

void geo_liberar_malha_3d(MalhaIrregular3D* m) {
    if (m != NULL) {
        if (m->vertices != NULL) free(m->vertices);
        if (m->faces != NULL) free(m->faces);

        m->vertices = NULL;
        m->faces = NULL;
        m->num_vertices = 0;
        m->num_faces = 0;
    }
}



double geo_area_poligono_irregular(PoligonoIrregular2D p) {
    if (p.num_vertices < 3 || p.vertices == NULL) return 0.0;

    double soma = 0.0;
    int n = p.num_vertices;

    for (int i = 0; i < n; i++) {
        int proximo = (i + 1) % n; // Faz o loop para o primeiro vértice
        soma += (p.vertices[i].x * p.vertices[proximo].y) - (p.vertices[proximo].x * p.vertices[i].y);
    }

    return fabs(soma) / 2.0;
}

double geo_perimetro_poligono_irregular(PoligonoIrregular2D p) {
    if (p.num_vertices < 3 || p.vertices == NULL) return 0.0;

    double perimetro = 0.0;
    int n = p.num_vertices;

    for (int i = 0; i < n; i++) {
        int proximo = (i + 1) % n;
        double dx = p.vertices[proximo].x - p.vertices[i].x;
        double dy = p.vertices[proximo].y - p.vertices[i].y;
        perimetro += sqrt(dx * dx + dy * dy);
    }

    return perimetro;
}

Ponto2D geo_centro_poligono_irregular(PoligonoIrregular2D p) {
    Ponto2D c = {0.0, 0.0};
    if (p.num_vertices < 3 || p.vertices == NULL) return c;

    double area_assinada = 0.0;
    double cx = 0.0, cy = 0.0;
    int n = p.num_vertices;

    for (int i = 0; i < n; i++) {
        int proximo = (i + 1) % n;
        double termo = (p.vertices[i].x * p.vertices[proximo].y) - (p.vertices[proximo].x * p.vertices[i].y);

        area_assinada += termo;
        cx += (p.vertices[i].x + p.vertices[proximo].x) * termo;
        cy += (p.vertices[i].y + p.vertices[proximo].y) * termo;
    }

    area_assinada *= 0.5;

    if (fabs(area_assinada) < 1e-9) return c; // Evita divisão por zero

    c.x = cx / (6.0 * area_assinada);
    c.y = cy / (6.0 * area_assinada);

    return c;
}

// Algoritmo de Ray-Casting
int geo_ponto_em_poligono_irregular(Ponto2D ponto, PoligonoIrregular2D p) {
    if (p.num_vertices < 3 || p.vertices == NULL) return 0;

    int dentro = 0;
    int n = p.num_vertices;

    for (int i = 0, j = n - 1; i < n; j = i++) {
        if (((p.vertices[i].y > ponto.y) != (p.vertices[j].y > ponto.y)) &&
            (ponto.x < (p.vertices[j].x - p.vertices[i].x) * (ponto.y - p.vertices[i].y) / 
                       (p.vertices[j].y - p.vertices[i].y) + p.vertices[i].x)) {
            dentro = !dentro;
        }
    }

    return dentro;
}



// Calcula a área da superfície somando a área de cada face triangular
double geo_area_superficie_malha(MalhaIrregular3D m) {
    if (m.num_faces < 1 || m.vertices == NULL || m.faces == NULL) return 0.0;

    double area_total = 0.0;

    for (int i = 0; i < m.num_faces; i++) {
        Ponto3D p1 = m.vertices[m.faces[i].v1];
        Ponto3D p2 = m.vertices[m.faces[i].v2];
        Ponto3D p3 = m.vertices[m.faces[i].v3];

        // Vetores das arestas do triângulo
        Vetor3D v1 = {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
        Vetor3D v2 = {p3.x - p1.x, p3.y - p1.y, p3.z - p1.z};

        // Produto vetorial para achar o vetor normal da face
        Vetor3D cruzado = vec_produto_vetorial3d(v1, v2);

        // A área de um triângulo no espaço 3D é metade do módulo do produto vetorial
        area_total += 0.5 * vec_modulo3d(cruzado);
    }

    return area_total;
}

// Volume via Soma dos Volumes Orientados de Tetraedros com a Origem (0,0,0)
double geo_volume_malha_fechada(MalhaIrregular3D m) {
    if (m.num_faces < 1 || m.vertices == NULL || m.faces == NULL) return -1.0;

    double volume_total = 0.0;

    for (int i = 0; i < m.num_faces; i++) {
        Ponto3D p1 = m.vertices[m.faces[i].v1];
        Ponto3D p2 = m.vertices[m.faces[i].v2];
        Ponto3D p3 = m.vertices[m.faces[i].v3];

        Vetor3D v1 = {p1.x, p1.y, p1.z};
        Vetor3D v2 = {p2.x, p2.y, p2.z};
        Vetor3D v3 = {p3.x, p3.y, p3.z};

        // Volume do tetraedro formado pelos 3 pontos e a origem: 1/6 * (v1 . (v2 x v3))
        Vetor3D v2_x_v3 = vec_produto_vetorial3d(v2, v3);
        double vol_tetraedro = vec_produto_escalar3d(v1, v2_x_v3) / 6.0;

        volume_total += vol_tetraedro;
    }

    return fabs(volume_total);
}


Plano geo_criar_plano_por_tres_pontos(Ponto3D p1, Ponto3D p2, Ponto3D p3) {
    Plano plano;
    plano.ponto = p1;

    Vetor3D v1 = {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
    Vetor3D v2 = {p3.x - p1.x, p3.y - p1.y, p3.z - p1.z};

    Vetor3D normal_nao_normalizado = vec_produto_vetorial3d(v1, v2);
    plano.normal = vec_normalizar3d(normal_nao_normalizado);

    return plano;
}

double geo_distancia_ponto_plano(Ponto3D p, Plano plano) {
    Vetor3D v_ponto_ao_plano = {p.x - plano.ponto.x, p.y - plano.ponto.y, p.z - plano.ponto.z};
    
    // Projeção do vetor ponto-ao-plano na normal do plano
    double dist = vec_produto_escalar3d(v_ponto_ao_plano, plano.normal);
    return fabs(dist);
}

int geo_reta_intercepta_plano(Ponto3D origem_reta, Vetor3D direcao_reta, Plano plano, Ponto3D* ponto_resultado) {
    double produto_denominador = vec_produto_escalar3d(direcao_reta, plano.normal);

    // Se a direção da reta for perpendicular à normal do plano, a reta é paralela ao plano
    if (fabs(produto_denominador) < 1e-9) {
        return 0; // Não há interseção única
    }

    Vetor3D v_origem_ao_plano = {plano.ponto.x - origem_reta.x, plano.ponto.y - origem_reta.y, plano.ponto.z - origem_reta.z};
    double t = vec_produto_escalar3d(v_origem_ao_plano, plano.normal) / produto_denominador;

    if (ponto_resultado != NULL) {
        ponto_resultado->x = origem_reta.x + t * direcao_reta.x;
        ponto_resultado->y = origem_reta.y + t * direcao_reta.y;
        ponto_resultado->z = origem_reta.z + t * direcao_reta.z;
    }

    return 1;
}