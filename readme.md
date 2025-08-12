# Trabalho 2
**Universidade Federal de Juiz de Fora**  
**Departamento de Ciência da Computação**  
**DCC059 – Teoria dos Grafos – Turma A**  
**Semestre 2025/1 - Profa Luciana Brugiolo - Tutor Rafael Freesz**  
**Grupo:**
- Guilherme Monteiro de Souza (M:202165562C)
- Gabriel Campos Lima Alves (M:202176005)
- Anderson Teixeira de Oliveira (M:202265504AB)

**Data entrega: 12/08**

Este documento descreve o Trabalho Prático 2, que consiste na extensão do TAD de grafos desenvolvido no TP1, incluindo agora algoritmos gulosos para o problema do **Conjunto Dominante de Arestas** (Edge Dominating Set), além de experimentos automáticos e geração de relatório.

## Objetivos

- Implementar e comparar algoritmos:
  - Guloso padrão
  - Guloso Randomizado Adaptativo (GRA)
  - Guloso Randomizado Adaptativo Reativo (GRAR)
- Medir qualidade da solução e tempo de execução.
- Gerar relatório tabular com os resultados dos experimentos.

## Orientações

- O código é em C++ puro, sem dependências externas.
- O grafo é representado por lista de adjacência.
- O programa lê instâncias de arquivos texto conforme o formato descrito em `instancias_t0/readme.txt`.
- O projeto está modularizado em pastas por componente.
- O relatório é gerado ao escolher a opção `r` no menu (execução automática dos experimentos).

## Estrutura de Diretórios

```
.
├── instancias_t0/
│   └── readme.txt
├── instancias_t1/
├── instancias_t2/
│   ├── imagens/
│   └── instances.txt
├── msc/
├── src/
│   ├── Aresta/
│   │   ├── Aresta.cpp
│   │   └── Aresta.h
│   ├── Gerenciador/
│   │   ├── Gerenciador.cpp
│   │   └── Gerenciador.h
│   ├── Grafo/
│   │   ├── Grafo.cpp
│   │   └── Grafo.h
│   ├── No/
│   │   ├── No.cpp
│   │   └── No.h
│   ├── SolucionadorEDS/
│   │   ├── SolucionadorEDS.cpp
│   │   └── SolucionadorEDS.h
│   └── main.cpp
```
> **Obs:** As pastas `imagens/` e os arquivos de instância são apenas para teste e experimentação. O código só utiliza os arquivos `.txt` das instâncias.

## Formato dos Arquivos de Instância

Veja o arquivo `instancias_t0/readme.txt` para detalhes completos.  
Exemplo de início de arquivo:
```
0 1 1
5
a 1
b 2
c 3
d 4
e 5
a b 5
b e 4
e c 3
d e 2
a e 1
```

## Como Compilar e Executar

### 1. Compilação

Abra o terminal na pasta `src/` e execute:

```bash
g++ -std=c++17 -O2 -o execGrupoX main.cpp Gerenciador/Gerenciador.cpp Grafo/Grafo.cpp No/No.cpp Aresta/Aresta.cpp SolucionadorEDS/SolucionadorEDS.cpp
```

### 2. Execução Interativa

Para usar o menu interativo (como no TP1):

```bash
./execGrupoX
```
- O programa irá solicitar no terminal o caminho do arquivo de grafo (via prompt) antes de abrir o menu.
- Informe um caminho válido, por exemplo:
  - `instancias_t0/grafo-t0-1.txt`
  - ou qualquer arquivo de `instancias_t1/` ou `instancias_t2/` no formato correto.
- Observação: argumentos na linha de comando são ignorados; o caminho do arquivo é sempre lido via prompt em `src/main.cpp`.

### 3. Execução Automática dos Experimentos e Geração de Relatório

Para rodar todos os experimentos do TP2 e gerar o relatório tabular dos algoritmos (em `relatorio_resultados.txt`):

```bash
./execGrupoX
```
- Quando o programa solicitar o caminho do grafo, informe qualquer instância válida (ex.: `instancias_t2/grafo-t2-1.txt`) apenas para entrar no menu.
- No menu, escolha a opção `r` (Gerar relatório de resultados). Isso chama `Gerenciador::gerarRelatorioAutomaticoEDS`, que executa os algoritmos Guloso, GRA e GRAR sobre as instâncias mapeadas de `instancias_t2/`.
- O arquivo `relatorio_resultados.txt` será salvo no diretório atual de execução (por exemplo, se você executou em `src/`, o arquivo ficará em `src/`).

## Sobre o Relatório Gerado

O arquivo `relatorio_resultados.txt` contém:
- Tabela com o melhor e a média das soluções encontradas por cada algoritmo.
- Tabela de desvio percentual em relação à melhor solução conhecida.
- Tabela de tempo médio de execução (em segundos).

## Opções do Sistema

A seguir estão as opções disponíveis no menu interativo (carregado após você informar o caminho do arquivo de grafo no prompt). Em várias opções, o sistema perguntará se deseja salvar a saída em arquivo; quando aceito, o arquivo é criado no diretório atual de execução.

- (`a`) Fecho transitivo direto de um nó
  - Requisitos: grafo direcionado.
  - Entrada: ID de um nó.
  - Saída opcional em arquivo: `fecho_trans_dir.txt`.

- (`b`) Fecho transitivo indireto de um nó
  - Requisitos: grafo direcionado.
  - Entrada: ID de um nó.
  - Saída opcional em arquivo: `fecho_trans_indir.txt`.

- (`c`) Caminho mínimo (Dijkstra)
  - Requisitos: grafo ponderado nas arestas.
  - Entrada: IDs de nó origem e destino.
  - Saída opcional em arquivo: `caminho_minimo_dijkstra.txt`.

- (`d`) Caminho mínimo (Floyd)
  - Requisitos: grafo ponderado nas arestas.
  - Entrada: IDs de nó origem e destino.
  - Saída opcional em arquivo: `caminho_minimo_floyd.txt`.

- (`e`) Árvore Geradora Mínima (Algoritmo de Prim)
  - Requisitos: grafo não direcionado, ponderado nas arestas e conexo.
  - Entrada: tamanho do subconjunto (entre 2 e ordem do grafo) e os IDs dos nós.
  - Saída opcional em arquivo: `agm_prim.txt`.

- (`f`) Árvore Geradora Mínima (Algoritmo de Kruskal)
  - Requisitos: grafo não direcionado, ponderado nas arestas e conexo.
  - Entrada: tamanho do subconjunto (entre 2 e ordem do grafo) e os IDs dos nós.
  - Saída opcional em arquivo: `agm_kruskal.txt`.

- (`g`) Árvore de caminhamento em profundidade
  - Requisitos: —
  - Entrada: ID do nó inicial.
  - Saída opcional em arquivo: `arvore_caminhamento_profundidade.txt`.

- (`h`) Raio, diâmetro, centro e periferia do grafo
  - Requisitos: grafo não direcionado (ponderação nas arestas é opcional).
  - Saída opcional em arquivo: `raio_diametro_centro_periferia.txt`.

- (`i`) Edge Dominating Set (Conjunto Dominante de Arestas)
  - Submenu de métodos:
    - (1) Guloso
    - (2) Guloso Randomizado Adaptativo (GRA): solicita número de iterações, semente e α (alpha).
    - (3) Guloso Randomizado Adaptativo Reativo (GRAR): solicita número de iterações e semente.
  - Exibe a solução (arestas), qualidade (tamanho do conjunto) e tempo de execução.
  - Saída opcional em arquivo: `eds_guloso.txt`, `eds_gra.txt` ou `eds_grar.txt`.

- (`r`) Gerar relatório de resultados
  - Executa automaticamente os algoritmos (Guloso, GRA e GRAR) nas instâncias mapeadas de `instancias_t2/`.
  - Gera o arquivo `relatorio_resultados.txt` no diretório atual, com tabelas de melhor/média, desvio percentual e tempos.
  - Dica: ao iniciar o programa, informe qualquer instância válida só para entrar no menu e então pressione `r`.

- (`0`) Sair
  - Encerra o programa.
