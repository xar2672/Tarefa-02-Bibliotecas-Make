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
        m.num_vertices = 0;
        m.num_faces = 0;
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


