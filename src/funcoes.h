/**
 * @file funcoes.h
 * @author Edgar Casal ()
 * @version 0.1
 * @date 2025-03-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef FUNCOES_H
#define FUNCOES_H  
#include <stdbool.h>
#define MAXi 12             //Máximo número de linhas
#define MAXj 12             //Máximo número de colunas

/// @brief Estrutura que representa uma antena no mapa
typedef struct Antena {
    char freq;              //Frequência da antena (A-Z, a-z)
    int x, y;               //Coordenadas (linha, coluna)
    struct Antena* prox;    //Apontador para a próxima antena da lista
}Antena;

/// @brief Estrutura que representa uma localização com efeito nefasto
typedef struct Nefasto {
    int x, y;               //Coordenadas (linha, coluna)
    struct Nefasto* prox;   //Apontador para o próximo efeito na lista
}Nefasto;

/// @brief Declaração da função inserirAntena
/// @param h  para o início da lista de antenas
/// @param freq Tipo de frequência (Aa até Zz)
/// @param x Coordenada x da antena
/// @param y Coordenada y da antena
/// @return Devolve o novo início da lista
Antena* inserirAntena(Antena* h, char freq, int x, int y);

/// @brief Declaração da função removerAntena
/// @param h Apontador para o início da lista de antenas
/// @param x Coordenada x da antena
/// @param y Coordenada y da antena
/// @return Devolve o início da lista depois de remover a antena
Antena* removerAntena (Antena* h, int x, int y);

/// @brief Declaração da função gravarFicheiroBinario
/// @param nomeFicheiro Nome do ficheiro
/// @param h Apontador para o início da lista de antenas
/// @return Devolve false se não conseguir abrir o ficheiro e true se conseguir gravar o ficheiro
bool gravarFicheiroBinario(char * nomeFicheiro, Antena* h);

/// @brief Declaração da função carregarAntenas
/// @param nomeficheiro Nome do ficheiro de texto que contém o mapa de antenas
/// @return Devolve NULL se o arquivo não abrir/se não conseguir alocar espaço
Antena* carregarAntenas(char* nomeFicheiro);

/// @brief Declaração da função inserirNefasto
/// @param h Apontador para o início da lista de efeitos nefastos
/// @param x Coordenada x do efeito nefasto
/// @param y Coordenada y do efeito nefasto
/// @return Apontador para o novo início da lista
Nefasto* inserirNefasto (Nefasto* h, int x, int y);

/// @brief Declaração da função efeitoNefasto
/// @param h Apontador para o início da lista de antenas
/// @return Devolve uma lista ligada com todas as posições de efeitos nefastos encontradas
Nefasto* efeitoNefasto (Antena* h);

/// @brief Declaração da função imprimirAntenas
/// @param h Apontador para o início da lista de antenas
void imprimirAntenas(Antena* h);

/// @brief Declaração da função imprimirNefasto
/// @param h Apontador para o início da lista de efeitos nefastos
void imprimirNefasto(Nefasto* h);

/// @brief Declaração da função imprimirAntenasNefasto
/// @param nomeFicheiro Nome do ficheiro que contém o mapa das antenas
/// @param h Apontador para o início da lista de efeitos nefastos
void imprimirAntenasNefasto(char* nomeFicheiro, Nefasto* h);


#endif