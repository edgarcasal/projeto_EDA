/**
 * @file funcoes.h
 * @author Edgar Casal ()
 * @version 0.1
 * @date 2025-05-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef FUNCOES_H
#define FUNCOES_H  
#include <stdbool.h>

#pragma region Estrutura de Dados
/// @brief Representa uma antena como vértice do grafo
typedef struct Vertice {
    char freq;                  //Frequência da antena (A até Z)
    int x, y;                   //Coordenadas da antena
    int visitado;               // Indica se a antena já foi visitada (0 = não visitado, 1 = visitado)
    struct Vertice* prox;       //Próximo vértice (antena) na lista
    struct Aresta* adj;         //Lista ligada de arestas (ligações)
} Vertice;

/// @brief Representa uma aresta (ligação) entre duas antenas do grafo
typedef struct Aresta { 
    int peso;                   //Distância entre coordenadas
    struct Vertice* destino;    //Antena (vértice) de destino 
    struct Aresta* prox;        //Próxima aresta na lista de adjacência
} Aresta;

/// @brief Representa o grafo, contendo a lista de antenas (vértices) e o número total de antenas
typedef struct Grafo {
    Vertice* h;                 //Apontador para o ínicio da lista de antenas
    int numVertices;            //Número total de antenas do grafo
} Grafo;

#pragma endregion

#pragma region Antenas

/// @brief Cria uma nova antena (vértice) com frequência e coordenadas dadas
/// @param freq Frequência da antena (letra entre 'A' e 'Z')
/// @param x Coordenada X da antena
/// @param y Coordenada Y da antena
/// @return Apontador para a nova antena criada (ou NULL se falhar)
Vertice* criarAntena(char freq, int x, int y);

/// @brief Insere uma nova antena na lista ligada de forma ordenada por coordenadas
/// @param h Apontador para o início da lista de antenas
/// @param nova Apontador para a nova antena a inserir
/// @return Novo início da lista de antenas
Vertice* inserirAntena(Vertice* h, Vertice* novo);

/// @brief Remove uma antena da lista ligada com base nas suas coordenadas (x, y).
/// @param h Apontador para o início da lista de antenas.
/// @param x Coordenada x da antena a remover.
/// @param y Coordenada y da antena a remover.
/// @param res Apontador para uma variável booleana que indica se a remoção foi bem-sucedida (true) ou não (false).
/// @return Devolve o novo início da lista de antenas, com a antena removida (se encontrada).
Vertice* removerAntena(Vertice* h, int x, int y, bool *res);

/// @brief Mostra todas as antenas da lista ligada no ecrã
/// @param h Apontador para o início da lista de antenas
/// @return true se existirem antenas para mostrar, false se a lista estiver vazia
bool mostrarAntenas(Vertice* h);

/// @brief Procura uma antena na lista ligada com base na frequência e coordenadas
/// @param h Lista ligada de vértices
/// @param freq Frequência a procurar
/// @param x Coordenada X
/// @param y Coordenada Y
/// @return Apontador para o vértice encontrado ou NULL se não existir
Vertice* procurarAntena(Vertice* h,char freq, int x, int y);

/// @brief Reinicia o campo 'visitado' de todos os vértices da lista ligada
/// @param h Apontador para o início da lista ligada de antenas (vértices)
/// @return true se os vértices foram reiniciados, false se a lista estiver vazia
bool resetVisitado(Vertice* h);

#pragma endregion

#pragma region Adjacências

/// @brief Cria uma nova ligação (aresta) entre dois vértices com a mesma frequência
/// @param origem Vértice de origem da ligação
/// @param destino Vértice de destino da ligação
/// @return Apontador para a nova aresta criada, ou NULL se as frequências forem diferentes ou falhar a alocação
Aresta* criarAdjacencia(Vertice* origem, Vertice* destino);

/// @brief Insere uma nova ligação (aresta) na lista de adjacências de um vértice
/// @param origem Vértice onde será inserida a ligação
/// @param novaAdjacencia Aresta a inserir na lista de adjacências
/// @return Apontador para a aresta inserida, ou NULL se a inserção falhar
Aresta* inserirAdjacencia(Vertice* origem, Aresta* novaAdjacencia);

/// @brief Mostra todas as antenas ligadas (adjacentes) a partir de um vértice (origem)
/// @param origem Apontador para o vértice cuja lista de adjacências se quer mostrar
/// @return true se existirem adjacências, false se não houver
bool mostrarAdjacencias(Vertice* origem);

/// @brief Conta quantas adjacências (arestas) tem uma dada antena
/// @param v Vértice a analisar
/// @return Número total de adjacências encontradas
int contarAdjacencias(Vertice* v);

#pragma endregion

#pragma region Percursos
/// @brief Realiza uma travessia em profundidade (DFS) a partir de uma antena
/// @param origem Apontador para o vértice onde o percurso começa
/// @return true se a travessia for realizada, false se a origem for inválida
bool depthFirstTraversal(Vertice* origem);

///bool breadthFirstTraversal(Vertice* origem);

#pragma endregion

#pragma region Ficheiros

/// @brief Cria um grafo a partir de um ficheiro de texto que representa o mapa da cidade.
///        Cada antena (letra) é transformada num vértice e inserida numa lista ligada.
/// @param nomeFicheiro Nome do ficheiro de entrada com o mapa da cidade
/// @return Apontador para o grafo criado ou NULL em caso de erro 
Grafo* criarGrafoDeFicheiro(char* nomeFicheiro);

/// @brief Grava num ficheiro binário os dados das antenas e das respetivas adjacências.
/// @param h Apontador para a lista ligada de antenas.
/// @return true se a gravação for bem sucedida, false caso contrário.
bool gravarFicheiroBinario(Vertice* h);

/// @brief Lê o ficheiro binário e reconstrói a lista de vértices com as suas adjacências
/// @param nomeFicheiro Caminho do ficheiro binário
/// @param res Apontador para flag de sucesso
/// @return Apontador para a lista reconstruída de vértices
Vertice* lerFicheiroBinario(char* nomeFicheiro, bool *res);

#pragma endregion

#endif