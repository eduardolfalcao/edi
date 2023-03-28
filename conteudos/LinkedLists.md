# LinkedLists

Antes de iniciarmos, vamos motivar LinkedLists provendo uma visão geral do funcionamento do Gerenciamento de Memória.

A seguir representamos a memória RAM através de uma visão lógica. Note como dividimos a memória em uma sequência de bytes. 

![alt text](imgs/listas/linkedlist/linkedlist-gerenciamento-memoria-0.png)

Imagine que vamos escrever uma simples aplicação na linguagem C para alocar duas variáveis inteiras e um array para armazenar quatro inteiros. Como um int precisa de 4 bytes para ser armazenado, neste caso precisaríamos de 32 bytes, 8 para os inteiros, e 16 para o array. Os inteiros podem ser armazenados em qualquer posição da memória, mas os **arrays são sempre armazenados em blocos contíguos de memória**, e isto traz algumas implicações.

Observe a animação a seguir:

![alt text](imgs/listas/linkedlist/linkedlist-gerenciamento-memoria.gif)

Faz sentido que o Gerenciador de Memória busque minimizar a fragmentação, i.e., diminuir a quantidade de espaços de memória pequenos desalocados (ou de forma coloquial, diminuir a quantidade de "buracos"). Neste caso, o Gerenciador de Memória primeiro tentaria alocar o array *c* entre *b* e *a*, mas isto não seria possível pois *c* precisa de 16 bytes, mas há apenas 15 bytes disponíveis entre *a* e *b*.

Quando falamos de ArrayLists, sabemos que as listas são implementadas com arrays. Nesse caso, geralmente aloca-se uma quantidade específica de espaço para este array, e tenta-se expandir a medida que seja necessário. Um problema de ArrayLists é que ocasionalmente eles podem ter memória ociosa. Para evitar este desperdício de memória podemos usar um outro tipo de ED: a **LinkedList**.

**Definição:**
> LinkedLists (ou listas ligadas, em português) são listas implementadas com nós, e cada nó possui um espaço de memória para armazenar o elemento e outro espaço de memória para armazenar o ponteiro (endereço de memória) para o nó seguinte.

Segue ilustração de uma LinkedList contendo valores numéricos pares.

![alt text](imgs/listas/linkedlist/linkedlist-apresentacao.png)

Uma outra forma de ilustrar, que considero até mais fidedigno, é representando os valores dispostos de maneira lineares, como de fato acontece na memória RAM.

![alt text](imgs/listas/linkedlist/linkedlist-apresentacao-2.png)

Cada ED traz consigo vantagens e desvantagens na operação de um TAD. E com as LinkedLists não é diferente. 

## Considerações de Desempenho de Espaço (RAM)

Um ponto positivo é que listas ligadas nunca terão espaço ocioso, ao contrário de ArrayLists. No entanto, para cada elemento armazenado em uma lista ligada, um espaço adicional (4 bytes) é alocado para armazenar o ponteiro do próximo nó. Então, se tivermos um TAD lista que na maioria do tempo permanece (quase) totalmente preenchida, podemos dizer que nesse caso o ArrayList seria mais econômico em termos de espaço. Por outro lado, se essa lista permanece na maior parte do tempo com pouquíssimos elementos, então como a lista ligada não aloca espaço sem necessidade, neste caso, podemos dizer que ela seria mais econômica do que um ArrayList (a depender do tamanho do ArrayList).

## Considerações Iniciais de Desempenho de Tempo das Operações

O que já sabemos é que  ArrayLists são implementados com arrays e listas ligadas são implementadas via alocação de nós e ponteiros. Também sabemos que arrays alocam espaços contíguos de memória, e portanto, conseguimos calcular o exato endereço de memória de um elemento em qualquer posição do array. Não é possível fazer isto com listas ligadas, pois os nós são alocados de forma não-contígua na memória, o que atrapalha o desempenho para uma série de operações. Uma das poucas vantagens que essa estratégia promove é a possibilidade de utilização da memória mesmo quando fragmentada. Pense comigo, quantos bytes contíguos nós precisaríamos alocar para uma lista de 100000000 números implementada com ArrayLists e quantos bytes contíguos nós precisaríamos alocar para uma lista de 100000000 com LinkedLists?

## Operações em LinkedLists

Listas ligadas são compostas por nós. 
Cada nó tem um valor e um ponteiro para o próximo nó. 
A primeira coisa que precisamos fazer é criar a estrutura que representa o nó.


```c
struct no{
    int val;
    struct no *prox;
};
```

**Observação:** a partir de agora vamos colocar todas as nossas implementações de EDs em bibliotecas, ou seja, arquivos de extensão *.h*. Além disso, para fins de testes, vocês devem seguir exatamente as mesmas assinaturas de métodos que eu usar, pois assim eu conseguirei automatizar as correções.

Ao contrário de ArrayLists, em que precisamos inicializar um array, LinkedLists podem inicializar com o primeiro nó nulo, pois sempre que adicionarmos um novo nó utilizaremos a função *malloc* para alocarmos espaço na RAM para o novo nó. 
No entanto, precisamos pelo menos inicializar as variáveis que representará a nossa lista:

```c
struct linkedlist {
    struct no* cabeca;
    int tamanho;
};
```

Na minha implementação eu estou usando a variável int tamanho pois sempre que eu adicionar um novo nó eu incrementarei esta variável. Isto evita a lenta contagem de elementos quando alguém precisar saber quantos elementos possui aquela lista.

### Imprimir Lista

Ao criar uma LinkedList precisamos criar uma variável para guardar o endereço do primeiro nó da lista. Este elemento é chamado de *cabeça* (em inglês, *head*).

Para imprimir a lista, basta partir da cabeça e imprimir o valor de todos os nós, até que não haja mais nós, ou em outras palavras, até que o ponteiro para o próximo nó seja NULL.

![alt text](imgs/listas/linkedlist/linkedlist-impressao.gif)

Segue código-fonte da função imprimir lista:
```c
void imprimirLista(struct linkedlist* lista) {
    //usamos o aux para percorrer a lista
    if (lista->cabeca != NULL) {
        struct no* aux = lista->cabeca;
        //navega partindo da cabeça até chegar NULL
        printf("[");
        do {
            printf("%d", aux->val);
            aux = aux->prox;
            if (aux != NULL) {
                printf(", ");
            }
        } while (aux != NULL);
        printf("]");
    }
    else {
        printf("A lista está vazia!");
    }
}
```

### Inserir Elemento no Fim da Lista

Temos dois casos principais:
1. **A lista está vazia.** Nesse caso, basta apontar a cabeça da lista para o nó recém-criado.
2. **A lista não está vazia.** Nesse caso, precisamos percorrer até o último elemento da lista e atualizar o valor de *prox* desse último nó para o nó recém-criado.

Em ambos os casos sempre precisaremos usar a função malloc para alocar espaço para o novo nó. Além disso, sempre incrementaremos a variável tamanho.

Segue assinatura da função para vocês implementarem:
```c
void inserirElementoNoFim(struct linkedlist* lista, int valor)
```

A seguir é apresentada uma ilustração (superficial) de como ocorre a inserção de um valor ao fim da lista:
![alt text](imgs/listas/linkedlist/linkedlist-inserir-fim.gif)

Alguns detalhes não estão representados nesta animação. Por exemplo, vamos precisar de uma variável auxiliar para encontrar o fim da lista.

### Inserir Elemento no Início da Lista

Mais uma vez, temos dois casos principais:
1. **A lista está vazia.** Nesse caso, basta apontar a cabeça da lista para o nó recém-criado.
2. **A lista não está vazia.** Nesse caso, basta apontar o ponteiro *prox* do nó recém-criado para o endereço que a cabeça da lista aponta, pois o novo nó precisa apontar para a antiga cabeça da lista. Por fim, apontamos a cabeça da lista para o nó recém-criado.

Em ambos os casos sempre precisaremos usar a função malloc para alocar espaço para o novo nó. Além disso, sempre incrementaremos a variável tamanho.

Segue assinatura da função para vocês implementarem:
```c
void inserirElementoNoInicio(struct linkedlist* lista, int valor)
```

### Inserir Elemento em Posição Específica da Lista

Segue assinatura da função para vocês implementarem:
```c
void inserirElementoEmPosicao(struct linkedlist* lista, int valor, int posicao)
```

### Obter Elemento em Posição Específica da Lista

Segue assinatura da função para vocês implementarem:
```c
int obterElementoEmPosicao(struct linkedlist* lista, int posicao)
```

### Remover Elemento em Posição Específica da Lista

Segue assinatura da função para vocês implementarem:
```c
void removerElementoEmPosicao(struct linkedlist* lista, int posicao)
```

## Noções de Desempenho

| Operação | ArrayLists | LinkedLists |
| -------- | ---------- | ----------- |
| Inserir elemento no fim (ainda há espaço no array) | performance **não tem relação** com o tamanho da lista: **O(1)**  | performance **tem relação** com o tamanho da lista: **O(n)** |
| Inserir elemento no fim (não há espaço no array) | quando a realocação não pode ser feita reaproveitando o mesmo espaço: **O(n)** | performance **tem relação** com o tamanho da lista: **O(n)** |
| Inserir elemento no início | quando se insere na primeira posição de uma lista não vazia: **O(n)** | **O(1)** |
| Inserir elemento em posição | inserção no início: **O(n)** | inserção no fim: **O(n)** |
| Obter elemento em posição | conseguimos calcular o endereço de memória: **O(1)** | **O(n)** |
| Atualizar elemento em posição | **O(1)** | **O(n)** |
| Obter tamanho da lista | **O(1)** | **O(1)** |
| Remover elemento no fim | **O(1)** | **O(n)** |
| Remover elemento no início | **O(n)** | **O(1)** |
| Remover elemento em posição | **O(n)** | **O(n)** |

