# Trabalho 2
<p align="center">
  <a href="https://www.ufjf.br/" rel="noopener">
    <img width=261 height=148 src="https://upload.wikimedia.org/wikipedia/commons/thumb/7/71/Logo_da_UFJF.png/640px-Logo_da_UFJF.png" alt="Logo UFJF">
  </a>
</p>

<h3 align="center">TP1 + TP2 — Teoria dos Grafos (UFJF/DCC059)</h3>

## 📝 Table of Contents
- [Sobre](#about)
- [Informações iniciais](#getting_started)
- [Informações do trabalho](#work_info)
- [Objetivos](#objetivos)
- [Orientações](#orientacoes)
- [Estrutura de Diretórios](#estrutura-de-diretorios)
- [Formato dos Arquivos de Instância](#formato-dos-arquivos-de-instancia)
- [Como Compilar e Executar](#como-compilar-e-executar)
- [Utilização](#usage)
- [Sobre o Relatório Gerado](#sobre-o-relatorio-gerado)
- [Opções do Sistema](#opcoes-do-sistema)
- [Tecnologias](#built_using)
- [Autores](#authors)
- [Menções](#acknowledgement)

## 🧐 Sobre <a name = "about"></a>
Projeto dos TPs 1 e 2 da disciplina DCC059 — Teoria dos Grafos (UFJF). O TP1 implementa o TAD de grafos em C++ (lista de adjacência) com operações clássicas: fechos transitivos, caminhos mínimos (Dijkstra, Floyd), árvores geradoras mínimas (Prim/Kruskal), árvore de caminhamento em profundidade, e medidas (raio, diâmetro, centro, periferia). O TP2 estende o sistema com heurísticas para o problema Edge Dominating Set (EDS): Guloso, GRA e GRAR, além de execução automática nas instâncias t2 e geração de relatório tabular (relatorio_resultados.txt), tudo acessado via menu interativo.

## 🏁 Informações iniciais <a name = "getting_started"></a>
### Pré-requisitos
- Compilador C++ com suporte a C++17 (g++ recomendado)
- Ambiente Linux/WSL/macOS (sem dependências externas)

### Visão geral
- Compilação e execução estão detalhadas em [Como Compilar e Executar](#como-compilar-e-executar).
- O caminho da instância é informado via prompt ao iniciar o binário.
- A geração do relatório é feita pela opção (`r`) no menu; a saída é `relatorio_resultados.txt` no diretório atual.

## 📌 Informações do trabalho <a name = "work_info"></a>
**Universidade:** Universidade Federal de Juiz de Fora (UFJF)  
**Departamento:** Ciência da Computação (DCC)  
**Disciplina:** DCC059 – Teoria dos Grafos – Turma A  
**Semestre:** 2025/1  
**Docente/Tutor:** Profa. Luciana Brugiolo • Tutor Rafael Freesz  
**Data de entrega:** 12/08  
Para a equipe completa, veja [Autores](#authors).

## Objetivos
<a name = "objetivos"></a>

- Implementar e comparar algoritmos:
  - Guloso padrão
  - Guloso Randomizado Adaptativo (GRA)
  - Guloso Randomizado Adaptativo Reativo (GRAR)
- Medir qualidade da solução e tempo de execução.
- Gerar relatório tabular com os resultados dos experimentos.

## Orientações
<a name = "orientacoes"></a>

- O código é em C++ puro, sem dependências externas.
- O grafo é representado por lista de adjacência.
- O programa lê instâncias de arquivos texto conforme o formato descrito em `instancias_t0/readme.txt`.
- O projeto está modularizado em pastas por componente.
- O relatório é gerado ao escolher a opção `r` no menu (execução automática dos experimentos).

## Estrutura de Diretórios
<a name = "estrutura-de-diretorios"></a>

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
<a name = "formato-dos-arquivos-de-instancia"></a>

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
<a name = "como-compilar-e-executar"></a>

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

## 🎈 Utilização <a name="usage"></a>
1) Compile a partir de `src/` e execute `./execGrupoX`.
2) Quando solicitado, informe o caminho do grafo, por exemplo `instancias_t0/grafo-t0-1.txt`.
3) No menu:
  - Use (`i`) para resolver EDS (Guloso, GRA, GRAR) na instância carregada e opcionalmente salvar o resultado.
  - Use (`r`) para rodar automaticamente os experimentos do TP2 em `instancias_t2/` e gerar `relatorio_resultados.txt`.

## Sobre o Relatório Gerado
<a name = "sobre-o-relatorio-gerado"></a>

O arquivo `relatorio_resultados.txt` contém:
- Tabela com o melhor e a média das soluções encontradas por cada algoritmo.
- Tabela de desvio percentual em relação à melhor solução conhecida.
- Tabela de tempo médio de execução (em segundos).

## Opções do Sistema
<a name = "opcoes-do-sistema"></a>

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

## Tecnologias <a name="built_using"></a>
- C++17
- g++
- Linux/WSL/macOS

## Autores <a name="authors"></a>
Grupo:
- Guilherme Monteiro de Souza (M:202165562C)
- Gabriel Campos Lima Alves (M:202176005)
- Anderson Teixeira de Oliveira (M:202265504AB)

## Menções <a name="acknowledgement"></a>
- Profa. Luciana Brugiolo (disciplina DCC059)
- Tutor Rafael Freesz
