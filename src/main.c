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
   Antena* nova;
   bool r;

   //Teste de criar/inserir antenas numa lista ligada, remoção de uma antena e imprimir antenas de uma lista ligada em forma tabular

   lista = inserirAntena(lista, criarAntena('A', 3, 2));
   lista = inserirAntena(lista, criarAntena('A', 4, 2));
   lista = inserirAntena(lista, criarAntena('A', 1, 2));

   if (lista != NULL) {
      printf("ANTENAS:\n");
      printf("| Frequência | Posição |\n");
      printf("|------------|---------|\n");
      imprimirAntenas(lista);
   } else {
      printf("Não existe lista de antenas.\n");
   }
   printf("\n");
   removerAntena(lista, 3, 2, &r);
   if (r == false) {
      printf("Antena não existe\n");
   }

   if (lista != NULL) {
      printf("ANTENAS:\n");
      printf("| Frequência | Posição |\n");
      printf("|------------|---------|\n");
      imprimirAntenas(lista);
   } else {
      printf("Não existe lista de antenas.\n");
   }
   printf("\n");


   //Teste de carregar um ficheiro txt, detetar efeito nefasto, e imprimir o conteúdo do ficheiro com os efeitos nefastos (#) adicionados
   printf("\n");
   lista = carregarAntenas("antenas.txt");
   listaEfeitoNefasto = efeitoNefasto(lista);

   if (imprimirAntenasNefasto("antenas.txt", listaEfeitoNefasto)){
      printf("\nMapa atualizado com efeito nefasto.\n");
   } else {
      printf ("Lista do mapa atualizado com efeitos nefasto não existe.\n");
   }
   printf("\n");
   if (listaEfeitoNefasto) {
      printf("EFEITOS NEFASTOS:\n");
      printf("| Posição |\n");
      printf("|---------|\n");
      imprimirNefasto(listaEfeitoNefasto);
   } else {
      printf ("Lista de efeitos nefasto não existe.\n");
   }


   //if (gravarFicheiroBinario("listaAntenas", lista)) {
   //   printf ("Ficheiro guardado em binário.\n");
   //}
}