/**
 * @file funcoes.c
 * @author Edgar Casal ()
 * @version 0.1
 * @date 2025-03-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "funcoes.h"
#include "malloc.h"


/// @brief Carrega os dados das antenas de um ficheiro de texto para uma lista ligada
/// @param nomeficheiro Nome do ficheiro de texto que contém o mapa de antenas
/// @return Devolve NULL se o arquivo não abrir/se não conseguir alocar espaço
Antena* carregarAntenas(char* nomeFicheiro) {
    FILE* fp;
    char c;
    Antena* h = NULL;
    Antena* aux;

    int x = 0;
    int y = 0;

    //Abre o ficheiro em modo de leitura
    fp = fopen(nomeFicheiro, "r");

    //Verifica se não conseguiu abrir
    if (fp == NULL) {
        return NULL;
    }

    //Percorre cada caractere até ao final do ficheiro
    while ((c = fgetc(fp))!=EOF) {
            //Se o caractere for uma letra, cria uma antena nova
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                aux = (Antena*)malloc(sizeof(Antena));
                if (aux == NULL) {
                    fclose(fp);
                    return NULL;    //Se o ficheiro não alocar espaço devolve NULL depois de fechar o ficheiro
                }

                aux->freq = c;
                aux->x = x;
                aux->y = y;
                aux->prox = h;
                h = aux;

                //Debug
                //printf("%c = (%d,%d)\n", aux->freq, aux->x, aux->y);
            }

            //Se encontrar uma mudança de linha, incrementa 1 linha e volta a coluna ao 0
            if (c == '\n') {
                x++;
                y=0;
            } else {
                y++;
            }
        }  
    fclose(fp);
    return h;   //Devolve a lista completa depois de fechar o ficheiro
}


/// @brief Cria e insere uma antena no início da lista ligada
/// @param h Apontador para o início da lista de antenas
/// @param freq Frequência da antena (A-Z, a-z), ex: 'A', 'b'
/// @param x Coordenada x da antena
/// @param y Coordenada y da antena
/// @return Devolve o novo início da lista
Antena* inserirAntena (Antena* h, char freq, int x, int y) {
    Antena* nova;

    nova = (Antena*)malloc(sizeof(Antena));     //Alocamento de espaço para o nova antena

    //Verifica se houve falha na alocação, devolve a lista inicial
    if (nova == NULL) {
        return h;
    }

    //Nova fica com os valores inseridos de frequência, e coordenadas x e y
    nova -> freq = freq;
    nova -> x = x;
    nova -> y = y;
    nova -> prox = h;   //Liga à antena anterior

    return nova;    //Devolve o Apontador para a nova antena, que fica a ser o novo início da lista ligada
}

/// @brief Remove uma antena da lista ligada e acordo com as coordenadas (x,y)
/// @param h Apontador para o início da lista de antenas
/// @param x Coordenada x da antena
/// @param y Coordenada y da antena
/// @return Devolve o início da lista depois de remover a antena
Antena* removerAntena (Antena * h, int x, int y) {
    Antena * aux = h; //Apontador auxiliar (aux) que aponta para o início da lista (h)
    Antena * aux2 = NULL; //Apontador auxiliar (aux2) que aponta para NULL (Apontador para a antena anterior)

    //Se o início da lista for nulo, devolve a lista
    if (h == NULL) {
        return h;
    }

    //Verifica e faz a remoção se as coordenadas(x,y) estiverem no início da lista
    if (h->x == x && h->y == y) {
        aux = h;
        h = h->prox;
        free(aux);
        return h;
    }

    // Procura a antena na lista
    while (aux != NULL && (aux->x != x || aux->y != y)) {
        aux2 = aux;
        aux = aux -> prox;
    }
    
    //Se a antena não for encontrada, devolve a lista
    if(aux == NULL) {
        return h;
    }

    //Remove a antena do meio ou do final
    aux2->prox = aux -> prox;
    free (aux);

    return h;
}


/// @brief Imprime todas as antenas de uma lista em formato tabular
/// @param h Apontador para o início da lista de antenas
void imprimirAntenas(Antena* h) {
    Antena* aux = h; //Apontador auxiliar (aux) que aponta para o início da lista (h)

    //Formato tabular
    printf("ANTENAS:\n");
    printf("| Frequência | Posição |\n");
    printf("|------------|---------|\n");

    //Percorre a lista ligada e imprime cada antena e as suas coordenadas
    while (aux != NULL) {
        printf("|    %2c      | (%2d,%2d) |\n", aux->freq, aux->x, aux->y);
        aux = aux -> prox; //Avança para a próxima antena da lista
    }
}


/// @brief Grava os dados das antenas num ficheiro binário
/// @param nomeFicheiro Nome do ficheiro de saída 
/// @param h Apontador para o início da lista de antenas
/// @return Devolve false se não conseguir abrir o ficheiro e true se conseguir gravar o ficheiro
bool gravarFicheiroBinario(char * nomeFicheiro, Antena* h) {
    Antena* aux = h;    //Apontador auxiliar (aux) que aponta para o início da lista (h)

    //Abre o ficheiro em modo de escrita binária
    FILE* fp = fopen(nomeFicheiro, "wb");

    //Se o ficheiro não for aberto devolve false
    if (fp == NULL) {
        return false;
    }

    // Percorre cada antena da lista ligada
    while (aux != NULL) {

        //fwrite precisa de saber onde estão os dados na memória, então precisamos de dizer para apontar para o endereço da frequência e das coordenadas
        fwrite(&(aux->freq), sizeof(char), 1, fp);
        fwrite(&(aux->x), sizeof(int), 1, fp);
        fwrite(&(aux->y), sizeof(int), 1, fp);
        aux = aux->prox;
    }

    fclose(fp);
    return true;
}

/// @brief Cria e insere um efeito nefasto novo numa lista
/// @param h Apontador para o início da lista de efeitos nefasto
/// @param x Coordenada x do efeito nefasto
/// @param y Coordenada y do efeito nefasto
/// @return Apontador para o novo início da lista
Nefasto* inserirNefasto(Nefasto* h, int x, int y) {
    Nefasto* novo;
    Nefasto* aux = h;

    //Percorre a lista para evitar coordenadas duplicadas e caso exista devolve a lista original
    while (aux != NULL) {
        if (aux->x == x && aux->y == y){
            return h;
        }
        aux = aux->prox;
    }

    //Alocamento de espaço 
    novo = (Nefasto*)malloc(sizeof(Nefasto));

    novo->x = x;
    novo->y = y;
    novo->prox = h; //Insere no início da lista

    return novo;    //Devolve o novo início da lista

}

/// @brief Calcula as posições com efeito nefasto baseado na lista de antenas existentes
/// @param h Apontador para o início da lista de antenas
/// @return Devolve uma lista ligada com todas as posições de efeitos nefastos encontradas
Nefasto* efeitoNefasto (Antena* h) {
    Nefasto* lista = NULL;
    Antena* aux = h;
    Antena* aux2;
    int x1, x2, y1, y2;

    //Percorre cada antena da lista
    while (aux != NULL) {
        aux2 = aux->prox; //Começa a comparação com a próxima antena

        while (aux2 != NULL) {
            if (aux->freq == aux2->freq) {  //Verifica se as antenas têm a mesma frequência

                /*
                * Cálculo do ponto com efeito nefasto entre duas antenas com a mesma frequência:
                * 
                * Para um par de antenas A1 e A2, onde:
                * - A1 está na posição (x1,y1)
                * - A2 está na posição (x2,y2)
                * 
                * O efeito nefasto acontece em dois pontos:
                * 1) Quando A1 está ao dobro da distância de A2:
                *    Ponto = (2*x1 - x2, 2*y1 - y2)
                * 2) Quando A2 está ao dobro da distância de A1:
                *    Ponto = (2*x2 - x1, 2*y2 - y1)
                */
                x1 = 2 * aux->x - aux2->x;
                y1 = 2 * aux->y - aux2->y;

                x2 = 2 * aux2->x - aux->x;
                y2 = 2 * aux2->y - aux->y;

                //Verifica se 1) está dentro dos limites do mapa e chama a função inserirNefasto para adicionar o ponto à lista ligada
                if (x1 >= 0 && y1 >= 0 && x1 < MAXi && y1 < MAXj) {
                    lista = inserirNefasto(lista, x1, y1);
                }
                //Verifica se 2) está dentro dos limites do mapa e chama a função inserirNefasto para adicionar o ponto à lista ligada  
                if (x2 >= 0 && y2 >= 0 && x2 < MAXi && y2 < MAXj) {
                    lista = inserirNefasto(lista, x2, y2);
                }
            }
            aux2 = aux2->prox;  //Avança para a próxima antena
            
        }
        aux = aux->prox;    //Avança para a próxima antena principal
    }
    return lista;   //Devolve a lista de efeitos nefastos
}

/// @brief Função que imprime as posições dos efeitos nefastos em forma tabular
/// @param h Apontador para o início da lista de efeitos nefastos
void imprimirNefasto(Nefasto* h) {
    Nefasto* aux = h;   //Apontador auxiliar (aux) que aponta para o início da lista (h)

    //Formato da tabela
    printf("EFEITOS NEFASTOS:\n");
    printf("| Posição |\n");
    printf("|---------|\n");

    //Percorre a lista efeitos nefasto enquanto o proxímo elemento não é nulo, ou seja, percorre até ao final da lista ligada
    while (aux != NULL) {
        printf("| (%2d,%2d) |\n", aux->x, aux->y);
        aux = aux -> prox; //Avança para a próxima posição da lista
    }
}


/// @brief Imprime o mapa original e adiciona as localizações com efeito nefasto (#)
/// @param nomeFicheiro Nome do ficheiro que contém o mapa das antenas
/// @param h Apontador para o início da lista de efeitos nefastos
void imprimirAntenasNefasto(char* nomeFicheiro, Nefasto* h) {
    int linha = 0, coluna = 0;
    char c;

    FILE * fp = fopen(nomeFicheiro, "r"); //Abre o ficheiro em modo de leitura

    if (fp == NULL) { // Verifica se o ficheiro abre
        return;
    }

    //Começa por ler o ficheiro caractere a caractere
    while ((c = getc(fp)) != EOF && linha < MAXi) {
        if (c == '\n') { //Se o caratere for a mudança de linha passa para a proxima linha, e volta a coluna ao zero, para começar do inicio da proxima linha
            linha++;
            coluna = 0;
            printf("\n");
        } else if (coluna < MAXj) { //Depois verifica se a posição tem o efeito nefasto
            Nefasto* aux = h;
            int nefasto = 0; //Inicializa como falso (não é nefasto)
            while (aux != NULL) {
                if (aux->x == linha && aux->y == coluna) {
                    nefasto = 1; //É nefasto
                    break; //A procura é interrompida
                }
                aux = aux->prox;
            }

            //Se (nefasto == 1)
            if (nefasto) {
                printf("#");  //Substitui por '#' se for nefasto
            } else if (c == '.' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                printf("%c", c);  //Imprime o caractere original
            }
            coluna++;
        }
    }
    fclose(fp); //Fecha o ficheiro
}