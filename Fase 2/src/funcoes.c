/**
 * @file funcoes.c
 * @author Edgar Casal ()
 * @version 0.1
 * @date 2025-05-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "funcoes.h"
#include "malloc.h"

#pragma region Funções de Antenas
/// @brief Cria uma nova antena com os dados fornecidos
/// @param freq Frequência da antena (carácter entre 'A' e 'Z')
/// @param x Coordenada X da antena
/// @param y Coordenada Y da antena
/// @return Devolve um apontador para a nova antena criada, ou NULL se a alocação falhar
Vertice* criarAntena(char freq, int x, int y){
    Vertice* nova;

    // Aloca memória para a nova antena 
    nova = (Vertice*)malloc(sizeof(Vertice));

    //Verifica se o espaço foi alocado corretamente
    if (!nova) {
        return NULL;
    }

    // Preenche os campos da nova antena com os dados fornecidos
    nova->freq = freq;
    nova->x = x;
    nova->y = y;
    // Inicializa os ponteiros da lista ligada e adjacências como NULL
    nova->prox= NULL;
    nova->adj= NULL;
    nova->visitado=0;

    // Devolve a antena criada
    return nova;
}

/// @brief Insere uma nova antena na lista ligada de forma ordenada por coordenadas
/// @param h Apontador para o início da lista de antenas
/// @param nova Apontador para a nova antena a inserir
/// @return Devolve o novo início da lista (caso a nova antena seja inserida no início)
Vertice* inserirAntena(Vertice* h, Vertice* nova) {
    Vertice* aux = h;

    // Se a nova antena for nula, não faz nada e devolve a lista original
    if (nova == NULL) {
        return h;
    }

    // Se a lista estiver vazia OU se a nova antena deve ser inserida no início
    if (h == NULL || nova->x < h->x || (nova->x == h->x && nova->y < h->y)) {
        // A nova antena passa a ser o novo início da lista
        nova->prox = h;         
        return nova;
    }

    // Percorre a lista até encontrar a posição correta para inserir a nova antena
    while (aux->prox != NULL && (aux->prox->x < nova->x || (aux->prox->x == nova->x && aux->prox->y < nova->y))) {
        aux = aux -> prox;
    }
    // Insere a nova antena entre aux e aux->prox
    nova->prox = aux->prox;
    aux->prox = nova;

    // Inicializa os campos padrão da nova antena
    nova->visitado = 0;
    nova->adj=NULL;

    // Devolve o início da lista (que não mudou)
    return h;
}

/// @brief Remove uma antena da lista ligada de vértices com base nas coordenadas (x, y)
/// @param h Apontador para o início da lista de vértices (antenas)
/// @param x Coordenada X da antena a remover
/// @param y Coordenada Y da antena a remover
/// @param res Apontador para uma variável que indica se a remoção foi bem-sucedida (true) ou não (false)
/// @return Devolve o novo início da lista de vértices
Vertice* removerAntena(Vertice* h, int x, int y, bool *res) {
    Vertice* aux = h;
    Vertice* aux2 = NULL;

    // Se a lista estiver vazia, não há nada para remover
    if (h == NULL) {
        return NULL;
    }

    // Caso a antena a remover esteja no início da lista
    if (h->x == x && h->y == y) {
        aux = h;                    // Guarda a antena a remover
        h = h->prox;                // Atualiza o início da lista
        free(aux);                  // Liberta a memória da antena removida
        *res = true;
        return h;
    }

    // Percorre a lista até encontrar a antena com as coordenadas dadas
    while (aux != NULL && (aux->x != x || aux->y != y)) {
        aux2 = aux;
        aux= aux->prox;
    }

    // Se não encontrou a antena, não faz nada
    if (aux == NULL) {
    *res = false;
    return h;
    }

    // Remove a antena da lista
    aux2->prox = aux->prox;         // Liga a antena anterior à próxima, e salta a atual
    free(aux);                      // Liberta a memória da antena removida
    *res = true;
    return h;                       // Devolve o início atualizado da lista
}


/// @brief Mostra no ecrã todas as antenas da lista ligada
/// @param h Apontador para o início da lista de vértices (antenas)
/// @return Devolve true se existirem antenas, false se a lista estiver vazia
bool mostrarAntenas(Vertice* h) {
    Vertice* aux = h;

    // Se a lista estiver vazia, não há nada para mostrar
    if (!h) {
        return false;
    }
    
    // Percorre toda a lista de vértices (antenas)
    while (aux) {
        printf("|    %2c      | (%2d,%2d) |\n", aux->freq, aux->x, aux->y);
        aux = aux->prox;
    }

    // Indica que a lista foi percorrida e as antenas foram mostradas com sucesso
    return true;
}

/// @brief Procura uma antena na lista ligada com base nas coordenadas e frequência
/// @param h Apontador para o início da lista de vértices (antenas)
/// @param freq Frequência da antena procurada
/// @param x Coordenada X da antena procurada
/// @param y Coordenada Y da antena procurada
/// @return Devolve o apontador para a antena encontrada, ou NULL se não existir
Vertice* procurarAntena(Vertice* h, char freq, int x, int y) {

    // Percorre a lista até encontrar um vértice com os dados coincidentes
    while (h != NULL) {
        if (h->freq == freq && h->x == x && h->y == y) {
            return h;
        }

        h= h->prox;
    }
    // Se não for encontrada nenhuma antena com os dados indicados devolve NULL
    return NULL;
}

/// @brief Restaura o campo 'visitado' de todos os vértices da lista para 0
/// @param h Apontador para o início da lista ligada de vértices (antenas)
/// @return true se a operação foi realizada, false se a lista estiver vazia
bool resetVisitado(Vertice* h) {
    Vertice* aux = h;

    // Verifica se a lista está vazia
    if (h == NULL) {
        return false;
    }

    // Percorre todos os vértices da lista e reinicia o campo 'visitado'
    while (aux != NULL) {
        aux->visitado = 0;
        aux = aux->prox;
    }

    // Indica que o reset foi feito com sucesso
    return true;
}

#pragma endregion

#pragma region Funções de Adjacencia
/// @brief Cria uma nova adjacência (ligação) entre dois vértices com a mesma frequência
/// @param origem Vértice de onde parte a ligação
/// @param destino Vértice para onde a ligação aponta
/// @return Devolve a nova aresta criada ou NULL se não for possível criar
Aresta* criarAdjacencia(Vertice* origem, Vertice* destino) {
    Aresta* novaAdjacencia;

    // Verifica se os dois vértices têm a mesma frequência
    // Só se forem compatíveis é que pode haver ligação
    if (origem->freq != destino->freq) {
        return NULL;
    }

    // Aloca memória para a nova aresta (ligação)
    novaAdjacencia = (Aresta*)malloc(sizeof(Aresta));

    // Verifica se a alocação foi bem-sucedida
    if (novaAdjacencia == NULL) {
        return NULL;
    }

    novaAdjacencia->destino = destino;              // Define o destino desta ligação
    novaAdjacencia->peso = 0;                       // Atribui o peso da ligação (ainda não atribuído)
    novaAdjacencia->prox = NULL;                    // Como esta aresta ainda não está ligada a outras, o próximo é NULL

    // Devolve a nova aresta criada 
    return novaAdjacencia;
}

/// @brief Insere uma nova aresta na lista de adjacências de um vértice
/// @param origem Apontador para o vértice onde queremos inserir a ligação
/// @param nova A nova ligação (aresta) que vai ser adicionada
/// @return Devolve a própria aresta inserida, ou NULL se falhar
Aresta* inserirAdjacencia(Vertice* origem, Aresta* novaAdjacencia) {
    // Verifica se o vértice de origem é válido
    if (origem == NULL) {
        return NULL;
    }
    // Verifica se a nova aresta a inserir é válida
    if (novaAdjacencia == NULL) {
        return NULL;
    }

    novaAdjacencia->prox = origem->adj;         // Liga a nova aresta à lista atual de adjacências do vértice
    origem->adj=novaAdjacencia;                 // Atualiza o início da lista para que a nova aresta fique em primeiro

    return novaAdjacencia;
}

/// @brief Mostra todas as antenas ligadas (adjacentes) a partir de um vértice (origem)
/// @param origem Apontador para o vértice cuja lista de adjacências se quer mostrar
/// @return true se existirem adjacências, false se não houver
bool mostrarAdjacencias(Vertice* origem) {
    // Apontador para percorrer a lista de arestas
    Aresta* aux;

    // Verifica se o vértice ou a lista de adjacências estão vazios
    if (origem == NULL || origem->adj == NULL) {
        return false;
    }

    // Inicializa o ponteiro auxiliar com o início da lista de adjacências
    aux = origem->adj;

    // Percorre a lista de arestas e imprime os vértices ligados (destinos)
    while (aux != NULL) {
        printf("(%d,%d) - %c\n", aux->destino->x, aux->destino->y, aux->destino->freq);
        aux = aux->prox;
    }

    // Indica que a função terminou com sucesso
    return true;
}

/// @brief Conta o número de adjacências (arestas) de um vértice (antena)
/// @param v Apontador para o vértice cuja lista de adjacências se quer contar
/// @return Número de arestas (ligações) encontradas
int contarAdjacencias(Vertice* v) {
    int counter = 0;
    Aresta* adj = v->adj;

    // Percorre a lista de adjacências e incrementa o contador
    while (adj != NULL) {
        counter++;
        adj = adj->prox;
    }

    // Devolve o total de adjacências encontradas
    return counter;
}
#pragma endregion

#pragma region Funções de Ficheiros
/// @brief Realiza um percurso em profundidade (DFS) a partir de uma antena
/// @param origem Vértice de início do percurso
/// @return true se o percurso foi feito, false se a origem for inválida
bool depthFirstTraversal(Vertice* origem) {
    Aresta* aux;

    // Verifica se o vértice de origem é válido
    if (origem == NULL) {
        return false;
    }

    // Marca o vértice atual como visitado
    origem->visitado = 1;

    // Percorre todas as adjacências (arestas) da antena atual
    aux = origem->adj;
    while (aux != NULL) {
        // Se o vértice de destino ainda não foi visitado, chama recursivamente
        if (aux->destino->visitado == 0) {
            aux->destino->visitado=1;
            depthFirstTraversal(aux->destino);
        }
        // Avança para a próxima adjacência
        aux = aux->prox;
    }
    return true;
}

/* /// @brief 
/// @param origem 
/// @return 
bool breadthFirstTraversal(Vertice* origem) {
    Aresta* aux;

    if (origem == NULL) {
        return false;
    }

    aux = origem->adj;
    if (aux != NULL) {
        aux->destino->visitado = 0;
        aux = aux->prox;
    }

} */

/// @brief Cria um grafo (lista ligada de antenas) a partir de um ficheiro de texto com o mapa da cidade
/// @param nomeFicheiro Nome do ficheiro de entrada com o mapa
/// @return Apontador para o grafo criado, ou NULL em caso de erro
Grafo* criarGrafoDeFicheiro(char* nomeFicheiro) {
    char c;
    int x = 0, y = 0;
    Vertice* novaAntena;
    Grafo* g;

    // Aloca memória para o grafo
    g = (Grafo*)malloc(sizeof(Grafo));
    if (!g) return NULL;

    g->h = NULL;           // Inicializa a lista ligada de vértices
    g->numVertices = 0;    // Começa com zero antenas

    FILE* fp = fopen(nomeFicheiro, "r");  // Abre o ficheiro em modo leitura
    if (fp == NULL) {
        return NULL;
    }

    // Percorre cada caractere do ficheiro
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            x++;       // Avança uma linha (vertical)
            y=0;     // Reinicia a coluna
        } else {
            if (c != '.') {
                // Cria uma nova antena se o caractere for uma letra (A-Z ou a-z)
                novaAntena = criarAntena(c, x, y);

                if (novaAntena) {
                    // Insere a antena na lista de forma ordenada
                    g->h = inserirAntena(g->h, novaAntena);
                    g->numVertices++;
                }
            }
            y++;  // Avança uma coluna (horizontal)
        }
    }

    fclose(fp);  // Fecha o ficheiro

    // Retorna o grafo criado com a lista de antenas
    return g;
}

/// @brief Grava a lista de antenas e respetivas adjacências num ficheiro binário.
///        Para cada antena, são gravados a frequência e as coordenadas, seguidos
///        dos dados das antenas adjacentes (frequência e coordenadas).
/// @param h Apontador para o início da lista de antenas (vértices).
/// @return true se a gravação for bem-sucedida, false em caso de erro.
bool gravarFicheiroBinario (Vertice* h) {  
    Vertice* listaVertices = h;
    Aresta* adj;

    // Abre o ficheiro em modo de escrita binária (cria novo ou substitui)
    FILE * fp = fopen("grafo.bin", "wb");

    // Verifica se houve falha na abertura do ficheiro
    if (fp == NULL) {
        return false;
    }

    // Verifica se a lista está vazia
    if (h == NULL) {
        return false;
    }

    // Percorre a lista de antenas (vértices)
    while (listaVertices != NULL) {
        // Grava os dados da antena atual (frequência e coordenadas)
        fwrite(&listaVertices->freq, 1, sizeof(char), fp);
        fwrite(&listaVertices->x, 1, sizeof(int), fp);
        fwrite(&listaVertices->y, 1, sizeof(int), fp);

        // Percorre a lista de adjacências (arestas) da antena atual
        adj = listaVertices->adj;

        // Contagem do número de adjacencias antes de percorrer a lista de adjacencias
        int n = contarAdjacencias(listaVertices);
        fwrite(&n, 1, sizeof(int), fp);

        while (adj != NULL) {
            // Grava os dados da antena de destino (adjacente)
            fwrite(&adj->destino->freq, 1, sizeof(char), fp);
            fwrite(&adj->destino->x, 1, sizeof(int), fp);
            fwrite(&adj->destino->y, 1, sizeof(int), fp);
            // Avança para a próxima aresta
            adj = adj->prox;
        }
        // Avança para o próximo vértice da lista
        listaVertices = listaVertices->prox;
    }
    // Fecha o ficheiro e indica sucesso
    fclose(fp);
    return true;
}

/// @brief Lê um ficheiro binário e reconstrói a lista de antenas e respetivas adjacências
/// @param nomeFicheiro Nome do ficheiro binário a abrir
/// @param res Apontador para um booleano que indica se a leitura foi bem sucedida
/// @return Devolve a lista de vértices (antenas) reconstruída, ou NULL em caso de erro
Vertice* lerFicheiroBinario (char* nomeFicheiro, bool *res) {
    // Variáveis auxiliares para armazenar temporariamente os dados lidos
    char freq, fAdj;
    int x, y, xAdj, yAdj, n;

    // Lista de antenas a ser construída
    Vertice* lista = NULL;

    // Abre o ficheiro em modo leitura binária
    FILE* fp = fopen(nomeFicheiro, "rb");

    // Se não abrir o ficheiro corretamente devolve null
    if (fp == NULL) {
        *res = false;
        return NULL;
    }

    // Lê os dados enquanto houver informação no ficheiro
    while (fread(&freq, sizeof(char), 1, fp) == 1 &&
       fread(&x, sizeof(int), 1, fp) == 1 &&
       fread(&y, sizeof(int), 1, fp) == 1) {

        // Cria nova antena e insere na lista
        Vertice* nova = criarAntena(freq, x, y);
        lista = inserirAntena(lista, nova);

        // Lê o número de adjacências associadas a esta antena
        fread(&n, sizeof(int), 1, fp); 

        // Lê os dados de cada adjacência e reconstrói as ligações
        for (int i = 0; i < n; i++) {
            fread(&fAdj, sizeof(char), 1, fp);
            fread(&xAdj, sizeof(int), 1, fp);
            fread(&yAdj, sizeof(int), 1, fp);

            // Procura na lista o vértice de destino com os dados lidos
            Vertice* destino = procurarAntena(lista, fAdj, xAdj, yAdj);
            if (destino != NULL) {
                // Cria a ligação (aresta) e insere-a na lista de adjacências da origem
                Aresta* novaAdj = criarAdjacencia(nova, destino);
                inserirAdjacencia(nova, novaAdj);
            }
        }
    }
    // Fecha o ficheiro e atualiza o resultado
    fclose(fp);
    *res = true;
    return lista;
}

#pragma endregion