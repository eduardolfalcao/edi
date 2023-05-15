# Simulador de Algoritmos de Ordenação

Para usar esse simulador, clone este repositório do github [sorting-simulator](https://github.com/raphaelramosds/sorting-simulator) e siga as instruções de uso logo abaixo

## Apresentação

A função principal desse simulador é o `simulate` que possui a seguinte assinatura

```go
type func simulate(label string, sorting string, an int, fashion string);
```

## Parâmetros

`label` string

- Nome que você pode dar à simulação

`sorting` string

- Tipo do algoritmo de ordenação

| Código         | Descrição                                         |
|----------------|---------------------------------------------------|
| selection      | Selection sort in place                           |
| insertion     | Insertion sort in place                            |
| bubble        |  Bubble sort (otimizado)                           |
| merge         | Merge sort                                         |
| quick         | Quick sort (pivô é o último elemento da partição)  |
| quick-random   | Quick sort (escolha aleatória do pivô)            |
| counting       | Counting sort                                     |

`an` int

- Fator que controla o tamanho dos vetores a serem ordenados em cada simulação
- Esse parâmetro é o n-ésimo termo de uma PG de razão três. Então, se `an = 6`, o simulador vai ordenar vetores de valores inteiros de tamanhos 1, 3, 9, 27 e 81

`fashion` string

- Especificação da lista a ser ordenada

| Código  | Descrição                                                                                                |
|------------|----------------------------------------------------------------------------------------------------------|
| asc        | Gera uma lista com valores naturais ordenados crescentemente de 1 até n, em que n é o tamanho do array   |
| desc       | Gera uma lista com valores naturais ordenados decrescentemente de 1 até n, em que n é o tamanho do array |
| scientific | Gera uma lista de elementos com valores aleatórios escolhidos entre 1.000 e 1.000.000                    |
| random     | Gera uma lista com valores aleatórios escolhidos entre 1 e 100                                           |

## Exemplo de código

Para rodar os códigos deste simulador, você deve clonar esse repositório e rodar os códigos abaixo no arquivo `main.go`

### Exemplo 1

Comparação entre o countig sort no pior caso e no melhor caso. Essa simulação vai parar quando o array a ser ordenado tiver com 531441 elementos, que é três elevado a doze.

```go
package main

func main() {
	simulate("Counting Sort em que k é muito maior que n", "counting", 13, "scientific")
	simulate("Counting Sort em que k é menor que n", "counting", 13, "random")
}
```

Resultado

```bash

Algoritmo: Counting Sort em que k é muito maior que n 
1 elementos                      600ns 
3 elementos                      1.0253ms 
9 elementos                      4.061201ms 
27 elementos                     4.251ms 
81 elementos                     4.3132ms 
243 elementos                    4.5027ms 
729 elementos                    4.8699ms 
2187 elementos                   4.846901ms 
6561 elementos                   2.505ms 
19683 elementos                          3.3848ms 
59049 elementos                          4.5072ms 
177147 elementos                         10.509801ms 
531441 elementos                         45.718102ms 

Algoritmo: Counting Sort em que k é menor que n 
1 elementos                      700ns 
3 elementos                      3.7µs 
9 elementos                      2.2µs 
27 elementos                     1.5µs 
81 elementos                     1.6µs 
243 elementos                    1.8µs 
729 elementos                    4.6µs 
2187 elementos                   12.4µs 
6561 elementos                   67.5µs 
19683 elementos                          220.1µs 
59049 elementos                          328.7µs 
177147 elementos                         1.7725ms 
531441 elementos                         6.7597ms

```

### Exemplo 2

Comparação entre o bubble sort, selection sort e insertion sort. Sendo que o bubble sort vai ordenar um array ordenado de forma decrescente, enquanto que os outros vão fazê-lo para um array ordenado de forma crescente. Essa simulação vai parar quando o array a ser ordenado tiver com 19683 elementos, que é três elevado a 9.

```go
package main

func main() {
	simulate("Bubble sort (ASC)", "bubble", 10, "asc")
	simulate("Selection sort (DESC)", "selection", 10, "desc")
	simulate("Insertion sort (DESC)", "insertion", 10, "desc")
}

```

Resultado

```bash

Algoritmo: Bubble sort (ASC) 
1 elementos                      200ns 
3 elementos                      0s 
9 elementos                      100ns 
27 elementos                     100ns 
81 elementos                     200ns 
243 elementos                    500ns 
729 elementos                    1.4µs 
2187 elementos                   4µs 
6561 elementos                   16.9µs 
19683 elementos                          35.5µs 

Algoritmo: Selection sort (DESC) 
1 elementos                      500ns 
3 elementos                      0s 
9 elementos                      200ns 
27 elementos                     1.1µs 
81 elementos                     5.6µs 
243 elementos                    44.6µs 
729 elementos                    398.5µs 
2187 elementos                   3.3533ms 
6561 elementos                   37.2176ms 
19683 elementos                          293.3122ms 

Algoritmo: Insertion sort (DESC) 
1 elementos                      300ns 
3 elementos                      0s 
9 elementos                      100ns 
27 elementos                     400ns 
81 elementos                     1.9µs 
243 elementos                    12.3µs 
729 elementos                    111.8µs 
2187 elementos                   1.5205ms 
6561 elementos                   8.7785ms 
19683 elementos                          82.4036ms

```
