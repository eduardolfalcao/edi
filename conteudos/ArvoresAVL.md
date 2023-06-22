# Árvores Balanceadas AVL

Árvores AVL são árvores de busca binária balanceadas: isso significa que minimizam o número de comparações efetuadas no pior caso para operações de busca, inserção e remoção.

> O nome AVL vem de seus criadores soviéticos Adelson Velsky e Landis, e sua primeira referência encontra-se no documento "Algoritmos para organização da informação" de 1962.

## Conceitos

### Fator de balanceamento

O fator de balanceamento de um nó é a diferença entre a altura da sua subárvore direita (Hd) e a altura da subárvore esquerda (He)

```
Fator de balanceamento = Hd - He
```

> Uma forma informal de entender esse parâmetro é que se ele é menor ou igual a -2, a árvore está pendendo para a esquerda. Se ele for maior ou igual a 2, ela está pendendo para a direita

### Árvore balanceada

> Uma árvore é dita balanceada se todos os seus nós tiverem fator de balanceamento -1, 0, ou 1. Se pelo menos um dos nós tiver um fator de balanceamento maior que 1 ou menor que -1, ela é dita desbalanceada.

### Tipo estruturado Nó

Para fazer o rebalanceamento, adicionamos mais duas propriedades ao tipo estruturado BSTNode: a altura do nó `height` e seu fator de balanceamento `bf`

```go
type BSTNode struct {
	left   *BSTNode
	value  int
	height int
	bf     int
	right  *BSTNode
}
```

## Rotações

A estratégia que uma árvore AVL utiliza para se rebalancear são as rotações de nós desbalanceados.

Na **rotação à esquerda** de um nó raiz, seguem-se os passos

- Seu filho da direita vira a nova raiz
- O filho da esquerda da nova raiz vira filho da direita da raiz original
- A raiz original vira filho da esquerda da nova raiz
- Retornamos o endereço da nova raiz `right`

Abaixo está ilustrada a rotação à esquerda do nó 1

```
    1             3
     \           / \
      3    →    1   4    →  retorne endereço de 3
     / \         \
    2   4         2
```

Já na **rotação à direita** de um nó raiz, seguem-se os passos

- Seu filho da esquerda vira a nova raiz
- O filho da direita da nova raiz vira filho da esquerda da raiz original
- A raiz original vira filho da direita da nova raiz
- Retornamos o endereço da nova raiz `left`

### Rotações duplas

Existem alguns casos em que apenas uma rotação à esquerda ou a direita não vão rebalancear uma árvore. Tome como exemplo a árvore abaixo: como tentativa de diminuir o fator de balanceamento 3 da raiz, rotacionamos para direita o nó 64

```
        2                   2
       / \                 / \
      1   64              1   32
          / \                /  \
         32  70    →        16   64
        /   /              /       \
       16  30             12        70
      /                            /
    12                           30  
```

Nada mudou! a raiz continua com fator de balanceamento 3, tornando a árvore desbalanceada. Mas, se prosseguimos rotacionando o nó 2 para a esquerda, teremos uma árvore balanceada

```
        32
        / \
       2   64
      / \    \
     1   16   70    →   retorne endereço de 32
        /    /
       12  30
```

## Atualização dos parâmeros

As operações de rotação em AVLs são necessárias para seu rebalanceamento, mas ao mesmo tempo modificam as propriedades de altura e fator de balanceamento da antiga e da nova raiz. 

Por exemplo, abaixo está ilustrada a rotação à esquerda do nó 1 na árvore apresentada

```
    1             3
     \           / \
      3    →    1   4    →  retorne endereço de 3
     / \         \
    2   4         2
```

Observe que antes da rotação, tinhamos

- h(1) = 2, fb(1) = 1
- h(3) = 1, fb(3) = 0

Após a rotação, vamos ter que atualizar esses valores para

- h(1) = 1, fb(1) = 0
- h(3) = 2, fb(3) = -1

Como exercício, calcule os parâmetros de altura e fator de balanceamento dos nós 2 e 4 antes e depois da rotação, e perceberá que eles seguem intactos.

Logo, para atualizar os parâmetros de um nó, seguimos o algoritmo

- Se o nó não tem filhos, sua altura e fator de balanço é zero
- Se o nó tem filhos, recupere a altura do filho direito e esquerdo
- A altura do nó será a maior altura entre as duas
- O fator de balanço será a diferença entre a altura direita e esquerda

Abaixo a assinatura da função para ser implementada.

```go
func (bstNode *BstNode) UpdateProperties()
```

> Nas rotações, a ordem adequada é atualizar as propriedades da antiga raiz e depois as propriedades da nova raiz. Até porque vimos no algoritmo acima que o nó pai se baseia nas propriedades do filho para ser atualizado. Entender isso é importante para compreender o rebalanceamento a medida em que inserimos e removemos elementos da árvore, pois ela vai se rebalanceando do nó folha até a raiz por meio de chamadas recursivas. Então, se começamos a atualizar as propriedades das folhas, os seus pais vão se atualizar tendo como base as propriedades corretas dos seus filhos.

## Análise do balanceamento

Para identificar casos estranhos de rotação dupla como o apresentado na seção anterior, você precisa analisar o fator de balanceamento do nó que você quer rotacionar (o nó raiz `root`) e os fatores de balanceamento dos seus filhos esquerdo e direito.

A seguir estão duas subseções que apresentam as operações de rotações que precisam ser feitas para que a árvore do nó raiz analisado seja balanceada. Nessas análises, considere que o objeto `root *BSTNode`, pertencente a uma árvore binária de busca, foi passado como parâmetro para uma função de balanceamento e nela foram efetuadas as operações presentes na coluna Operações.

### Análise da subárvore esquerda

O primeiro caso de rebalanceamento, `bf(raiz) <= -2` e `bf(left) = -1`, é chamado de Esquerda-Esquerda. Nele, a subárvore pende para a esquerda e seu filho esquerdo também.

No segundo caso, `bf(raiz) <= -2` e `bf(left) = 0`, a subárvore esquerda ainda pende para a esquerda, mas a sua subárvore esquerda está levemente balanceada. 

Apesar dessas diferenças, o balanceamento nesses dois casos consiste em rotacionar a raiz para a direita.

Abaixo a assinatura da função para ser implementada.

```go
func (bstNode *BstNode) RebalanceLeftLeft() *BstNode
```

O terceiro caso, `bf(raiz) <= -2` e `bf(left) = 1`, é chamado de Esquerda-Direita. Nele, a subárvore pende para a esquerda, mas sua subárvore esquerda pende para a direita. Nesse caso, para balancear fazemos a rotação a esquerda da nova raiz e logo após a rotação a direita da antiga raiz.

Abaixo a assinatura da função para ser implementada.

```go
func (bstNode *BstNode) RebalanceLeftRight() *BstNode
```

### Análise da subárvore direita

No primeiro caso de rebalanceamento, `bf(raiz) >= 2` e `bf(right) = 1`, é chamado de Direita-Direita. Nele, a subárvore pende para a direita e sua subárvore direita também.

No segundo caso, `bf(raiz) >= 2` e `bf(right) = 0`, a subárvore ainda pende para a direita, mas a sua subárvore direita está levemente balanceada.

Apesar dessas diferenças, o balanceamento nesses dois casos consiste em rotacionar a raiz para a esquerda.

Abaixo a assinatura da função para ser implementada.

```go
func (bstNode *BstNode) RebalanceRightRight() *BstNode
```

No terceiro caso, `bf(raiz) >= 2` e `bf(right) = -1`, é chamado de Direita-Esquerda. Nele, a subárvore pende para a direita, mas sua subárvore direita pende para a esquerda. Nesse caso, para balancear fazemos a rotação a direita da nova raiz e logo após a rotação a esquerda da antiga raiz.

Abaixo a assinatura da função para ser implementada.

```go
func (bstNode *BstNode) RebalanceRightLeft() *BstNode
```
