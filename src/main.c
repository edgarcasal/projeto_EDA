/**
 * @file main.c
 * @author Edgar Casal ()
 * @version 0.1
 * @date 2025-03-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include "funcoes.h"

int main () {
   Antena* lista = NULL;
   Nefasto* listaEfeitoNefasto = NULL;


   //Teste de criar/inserir antenas numa lista ligada, remoção de uma antena e imprimir antenas de uma lista ligada em forma tabular
   lista = inserirAntena(lista,'A', 0, 0);
   lista = inserirAntena(lista,'A', 0, 1);
   lista = inserirAntena(lista,'A', 1, 1);
   lista = inserirAntena(lista,'B', 1, 2);
   imprimirAntenas(lista);
   printf("\n");

   removerAntena(lista, 1, 1);
   imprimirAntenas(lista);
   printf("\n");

   //Teste de carregar um ficheiro txt, detetar efeito nefasto, e imprimir o conteúdo do ficheiro com os efeitos nefastos (#) adicionados
   printf("\n");
   lista = carregarAntenas("antenas.txt");
   listaEfeitoNefasto = efeitoNefasto(lista);
   imprimirAntenasNefasto("antenas.txt", listaEfeitoNefasto);
   printf("\n");
   imprimirNefasto(listaEfeitoNefasto);
   printf("\n");
   imprimirAntenas(lista);

   //gravarFicheiroBinario("listaAntenas", lista);
}