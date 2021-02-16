# Filas

Assim como somos familiarizados com os termos *lista* e pilha, todos nós sabemos o que é uma **fila**. Nós sabemos o que é uma fila de clientes, uma fila de tarefas, etc. Neste caso, sempre que nos referirmos a uma fila, denotamos que só conseguimos adicionar novos itens no fim da fila e remover itens existentes pelo início da fila. 

Fila de pessoas            |  Fila em supermercado
:-------------------------:|:-------------------------:
![](imgs/filas/fila-pessoas.jpeg)  |  ![](imgs/filas/fila-supermercado.jpg)

**Definição:**
 > Filas são listas (ou coleções) de elementos com a restrição de que inserção só deve acontecer pela traseira ou cauda da fila, e remoção só pode ser realizada a partir da frente ou cabeça da fila. Por esta razão, o TAD fila é considerado do tipo FIFO: first-in-first-out.
 
 Para o nosso estudo, vamos iniciar com uma visão abstrata e superficial da ED fila. Vamos estudar o **TAD Fila**. Neste primeiro momento não nos preocuparemos com implementação, mas queremos apenas ter um entendimento superficial de suas operações básicas.

  ## TAD: Filas

- Inserir um elemento na traseira da fila: **enfileirar(e)** ou **push(e)**.
- Remover um elemento do frente da fila: **desenfileirar()** ou **pop()**.
- Ler o elemento da frente da fila: **frente()** ou **peek()**.
- Contar os elementos de uma fila: **tamanho()**.
- Perguntar se a fila está vazia: **vazia()**.
- Perguntar se a fila está cheia (caso haja limite): **cheia()**.

Experimente simular graficamente as seguintes operações:
 - enfileirar(5)
 - enfileirar(9)
 - enfileirar(25)
 - frente()
 - desenfileirar()
 - desenfileirar()
 - vazia()
 - tamanho()
 - frente()
 - desenfileirar()

 Onde filas são ou poderiam ser aplicadas:
 - quando houver um recurso que consegue processar uma requisição por vez (First-Come-First-Served): impressora
 - escalonamento de processos no Sistema Operacional: filas de prioridade

## Implementação: Filas usando Arrays

Como filas são listas com restrições, é possível perceber que nós podemos reaproveitar o código de ArrayList e modificá-lo para que ele incorpore as restrições de listas. 

Observações:
 - Na nossa primeira implementação de filas com arrays, quando a fila estiver cheia, não duplicaremos o tamanho do array.
 - Se a frente ou traseira da fila tangenciar a extremidade esquerda ou direita do array, respectivamente, utilizaremos o conceito de array circular para preencher todos os espaços do array.
     - Próxima posição traseira: tras = (tras+1)%n
     - Posição posição frontal: frente = (frente+n-1)%n
     - Fila está vazia quando: tras == -1 && frente == -1
     - Fila está cheia quando: (tras+1)%n == frente