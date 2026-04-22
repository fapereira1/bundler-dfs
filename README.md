# bundler-dfs

Resolvedor de dependências do `Gemfile.lock` implementado em C usando DFS (Depth-First Search) e ordenação topológica.

Este projeto acompanha a série de artigos:
- [Parte I — Seu bundle install executa um algoritmo de grafos: a teoria por baixo do Bundler](https://medium.com/@fabioaugustopereira/seu-bundle-install-executa-um-algoritmo-de-grafos-ae22298aa396)
- Parte II — Em breve

## Como funciona

Lê um `Gemfile.lock`, constrói um grafo dirigido de dependências e calcula a ordem correta de instalação usando DFS. Detecta dependências circulares automaticamente.

## Requisitos

- Linux (testado no Debian 13 trixie)
- GCC 14+
- CMake 3.20+

```bash
sudo apt install -y gcc gdb make cmake
```

## Configurando o ambiente

```bash
git clone git@github.com:fapereira1/bundler-dfs.git
cd bundler-dfs
cmake -S . -B build
cmake --build build -j$(nproc)
```

## Rodando

Com o arquivo de exemplo incluso no repositório:

```bash
./build/bundler-dfs sample/Gemfile.lock
```

Com o seu próprio projeto Rails:

```bash
./build/bundler-dfs /caminho/para/seu/Gemfile.lock
```

Saída esperada:

```
Gems encontradas: 222

Ordem de instalação:
  1. zeitwerk
  2. tsort
  3. thor
  ...
105. rails
  ...
222. yaaf
```

## Estrutura do projeto

```
bundler-dfs/
├── src/
│   ├── main.c
│   ├── graph/          # lista de adjacência
│   ├── algorithms/     # DFS, detecção de ciclo, ordenação topológica
│   └── parser/         # parser do Gemfile.lock
├── sample/
│   └── Gemfile.lock    # Gemfile.lock do projeto rails_api_base
└── CMakeLists.txt
```

## Algoritmos implementados

- **DFS** — busca em profundidade com coloração de vértices (branco, cinza, preto)
- **Detecção de ciclo** — via vértice cinza na pilha de recursão
- **Ordenação topológica** — ordem de finalização do DFS

## Referência

`Gemfile.lock` de exemplo extraído do projeto [rails_api_base](https://github.com/rootstrap/rails_api_base).