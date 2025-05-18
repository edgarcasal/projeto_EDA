#  Projeto Estruturas de Dados Avançadas 
Desenvolvido para a disciplina de Estruturas de Dados Avançadas (IPCA).  

**FASE 1 - Listas Ligadas (Gestão de Antenas e Efeitos Nefastos)**

**Descrição**:  
Sistema em C que gerencia antenas e calcula efeitos nefastos (interferências) baseados em alinhamentos e frequências. 

**Funcionalidades**:  
 - Inserir e remover antenas de uma lista ligada
 - Carregar antenas de um ficheiro de texto
 - Calcular pontos de interferência entre antenas alinhadas  
 - Visualizar mapa com efeitos nefastos ('#')  

**Tecnologias**:  
- Linguagem: **C**  
- Estruturas de dados: **Listas ligadas**  
- Ferramentas: Git, Doxygen (documentação)  

---

**FASE 2 – Grafos e Percursos**

**Descrição:**  
Expansão da Fase 1 com representação de antenas como vértices de um grafo. São criadas adjacências entre antenas com a mesma frequência, permitindo aplicar algoritmos de percurso como DFS.

**Funcionalidades adicionais:**  
- Representação de antenas como grafo com listas de adjacência  
- Criação de adjacências entre antenas com a mesma frequência  
- Percurso em profundidade (DFS) sobre o grafo  
- Gravação e leitura do grafo em ficheiro binário ('grafo.bin')  
- Remoção de antenas com atualização da estrutura  

**Tecnologias adicionais:**  
- Estruturas: **Grafo com lista de adjacência**  
- Ficheiros binários  
- Modularização com biblioteca estática ('libfuncoes.a')  


## Como Compilar e Executar

```bash
make         # Compila o projeto e a biblioteca
./prog       # Executa o programa principal
make clean   # Limpa os ficheiros compilados


## Como Compilar e Executar

- '/fase1': Implementação com listas ligadas (gestão de antenas e efeitos nefastos)
- '/fase2': Representação com grafos, adjacências, DFS, e gravação/leitura em ficheiros binários
- 'relatorio.pdf': Documento técnico com explicações e testes
