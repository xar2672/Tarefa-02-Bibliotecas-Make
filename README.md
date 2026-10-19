# Biblioteca de Álgebra, Geometria e Cálculo Numérico em C

Uma biblioteca modular em C voltada para computação científica e matemática avançada. O projeto abrange álgebra linear, manipulação de polinômios, geometria analítica 2D e 3D, cálculo diferencial/integral e métodos numéricos para resolução de equações.

---

## Estrutura de Diretórios

```text
.
├── include/              # Interfaces públicas (.h)
│   ├── vetores.h
│   ├── polinomios.h
│   ├── geometria.h
│   ├── calculo.h
│   └── calculo_numerico.h
├── src/                  # Implementações das funções (.c)
├── apps/                 # Aplicação cliente principal (main.c)
├── tests/                # Suíte de testes automatizados
├── build/                # Artefatos intermediários (.o)
├── lib/                  # Bibliotecas compiladas (libapp.a e libapp.so)
└── bin/                  # Executáveis gerados (client e test)
└── relatorios/           # Relatório + Slides + Vídeos do Projeto
```

---

## Módulos do Sistema

### 1. Álgebra Vetorial (`vetores.h`)
- Suporte a vetores em 2D, 3D e $N$-dimensionais;
- Operações de soma, subtração, multiplicação escalar, norma/módulo e normalização;
- Cálculo de produto escalar, produto vetorial (3D), ângulo em radianos e projeção vetorial.

### 2. Polinômios Esparsos (`polinomios.h`)
- Representação por lista encadeada ordenada por expoente;
- Remoção automática de termos nulos;
- Avaliação $P(x)$, soma de polinômios e derivada algébrica exata.

### 3. Geometria Analítica (`geometria.h`)
- **Formas Regulares:** Circunferências, triângulos, planos e esferas;
- **Formas Irregulares 2D:** Cálculo de área via Fórmula do Cadarço, perímetro, centroide e teste de Raycasting;
- **Malhas Irregulares 3D:** Cálculo de área superficial e volume de malhas fechadas por decomposição de tetraedros;
- **Geometria Espacial:** Construção de planos por 3 pontos, distância ponto-plano e interseção reta-plano.

### 4. Cálculo Diferencial e Integral (`calculo.h`)
- Aproximação de derivada $f'(x)$ por diferenças finitas centradas;
- Derivadas parciais $N$-dimensionais e cálculo do vetor gradiente;
- Integração numérica 1D pelo Método dos Trapézios Composto e integração dupla 2D pela Regra do Ponto Médio.

### 5. Métodos Numéricos (`calculo_numerico.h`)
- Busca de raízes de equações não lineares $f(x) = 0$:
  - **Método da Bissecção**
  - **Método de Newton-Raphson**
- Tratamento de erros via enum `StatusCalculo` (`SUCESSO`, `ERRO_NAO_CONVERGIU`, `ERRO_INTERVALO_INVALIDO`, `ERRO_DERIVADA_NULA`).

---

## Compilação e Uso (Makefile)

O gerenciamento da compilação é automatizado pelo Makefile do projeto:

| Comando | Descrição |
| :--- | :--- |
| `make all` | Compila os módulos, gera as bibliotecas estática (`libapp.a`) e dinâmica (`libapp.so`) e o cliente. |
| `make clean` | Remove todos os arquivos gerados nas pastas `build/`, `lib/` e `bin/`. |
| `make run` | Compila se necessário e executa a aplicação cliente em `apps/`. |
| `make test` | Compila e executa a suíte de testes em `tests/`. |
| `make install PREFIX=$HOME/.local` | Instala os cabeçalhos (`.h`) e as bibliotecas (`.a`/`.so`) no diretório especificado. |