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
- O relatório é gerado automaticamente após a execução dos experimentos.

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
./execGrupoX ../instancias_t0/grafo-t0-1.txt
```
- O programa irá exibir o menu de operações, incluindo a opção para rodar os algoritmos gulosos e ver a solução, qualidade e tempo.

### 3. Execução Automática dos Experimentos e Geração de Relatório

Para rodar todos os experimentos do TP2 e gerar o relatório tabular dos algoritmos (em `relatorio_resultados.txt`):

```bash
./execGrupoX
```
- O relatório será salvo na pasta `src/` com tabelas de qualidade, desvio percentual e tempo de execução para cada instância e algoritmo.

## Sobre o Relatório Gerado

O arquivo `relatorio_resultados.txt` contém:
- Tabela com o melhor e a média das soluções encontradas por cada algoritmo.
- Tabela de desvio percentual em relação à melhor solução conhecida.
- Tabela de tempo médio de execução (em segundos).

## Observações Finais

- O código está limpo, modular e sem dependências externas.
- Todos os algoritmos e métricas estão documentados no código-fonte.
- Para dúvidas sobre o formato das instâncias, consulte `instancias_t0/readme.txt`.
- Para dúvidas sobre o uso, consulte este README ou o tutor/professora.
