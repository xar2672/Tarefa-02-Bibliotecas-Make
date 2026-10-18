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
