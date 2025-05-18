/**
 * @file main.c
 * @author Edgar Casal ()
 * @version 0.1
 * @date 2025-05-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include "funcoes.h"

int main () {
    Grafo* grafo = NULL;
    Vertice* lista = NULL;
    bool resultado;

    // 1. Criar grafo a partir do ficheiro de texto
    printf("Carregar o grafo do ficheiro 'antenas.txt'\n");
    grafo = criarGrafoDeFicheiro("antenas.txt");
    if (grafo == NULL || grafo->h == NULL) {
        printf("Erro ao carregar grafo.\n");
        return 1;
    }

    lista = grafo->h;

    // 2. Mostrar as antenas carregadas
    printf("\n--- Antenas carregadas ---\n");
    if (!mostrarAntenas(lista)) {
        printf("Lista de antenas vazia.\n");
    }

        // 3. Criar adjacências entre antenas com a mesma frequência
    printf("\n--- Criar adjacências entre antenas ---\n");
    Vertice* v1 = lista;
    while (v1 != NULL) {
        Vertice* v2 = v1->prox;
        while (v2 != NULL) {
            Aresta* nova = criarAdjacencia(v1, v2);
            if (nova != NULL) {
                inserirAdjacencia(v1, nova);
                //printf("Adjacência criada de (%d,%d) até (%d,%d)\n", v1->x, v1->y, v2->x, v2->y);
            } 

            Aresta* nova2 = criarAdjacencia(v2, v1);
            if (nova2 != NULL) {
                inserirAdjacencia(v2, nova2);
                //printf("Adjacência criada de (%d,%d) para (%d,%d)\n", v2->x, v2->y, v1->x, v1->y);
            }

            v2 = v2->prox;
        }
        v1 = v1->prox;
    }
    printf("Adjacências criadas\n");

    // 4. Mostrar adjacências de todas as antenas
    printf("\n--- Adjacências de cada antena ---\n");
    Vertice* atual = lista;
    while (atual != NULL) {
        printf("Antena %c com as coordenadas (%d,%d) tem adjacências com:\n", atual->freq, atual->x, atual->y);
        if (!mostrarAdjacencias(atual)) {
            printf("Sem adjacências.\n");
        }
        atual = atual->prox;
    }

    // 5. DFS - Percurso em profundidade
    printf("\n--- DFS (Depth First Traversal) ---\n");
    resetVisitado(lista);
    if (!depthFirstTraversal(lista)) {
        printf("Erro: antena de origem inválida.\n");
    } else {
        printf("DFS concluído.\n");
    }

    // 6. Remover antena (por exemplo, coordenada 1,8)
    printf("\n--- Remover antena na posição (1,8) ---\n");
    lista = removerAntena(lista, 1, 8, &resultado);
    if (resultado) {
        printf("Antena removida com sucesso.\n");
    } else {
        printf("Antena não encontrada.\n");
    }

    // 7. Mostrar antenas após remoção
    printf("\n--- Lista atualizada de antenas ---\n");
    if (!mostrarAntenas(lista)) {
        printf("Lista vazia.\n");
    }


    // 8. Gravar para ficheiro binário
    printf("\n--- Gravar antenas no ficheiro binário ---\n");
    if (gravarFicheiroBinario(lista)) {
        printf("Ficheiro 'grafo.bin' criado com sucesso.\n");
    } else {
        printf("Erro ao gravar ficheiro binário.\n");
    }

    // 9. Ler novamente do ficheiro binário
    printf("\n--- Ler ficheiro binário ---\n");
    bool resLeitura = false;
    Vertice* listaLida = lerFicheiroBinario("grafo.bin", &resLeitura);

    if (resLeitura) {
        printf("Antenas lidas do ficheiro binário:\n");
        mostrarAntenas(listaLida);
    } else {
        printf("Erro ao ler do ficheiro binário.\n");
    }

    return 0;
}