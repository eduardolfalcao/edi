---
title: Filas FIFO em Go
description: Implementação de filas FIFO com listas encadeadas e arrays circulares em Go.
author: eduardo@dca.ufrn.br
tags: Go, Data Structures, FIFO Queue
---

# Implementando Filas FIFO em Go

Neste tutorial, você irá implementar uma estrutura de dados do tipo **fila (FIFO — First-In, First-Out)** em Go.

Você construirá duas implementações:

- Uma fila baseada em **lista encadeada**
- Uma fila baseada em **vetor circular**

Ao final, você será capaz de:

- Implementar operações como `Enqueue`, `Dequeue` e `Front`
- Comparar diferentes estratégias de implementação
- Validar o comportamento da fila com testes automatizados

**Pré-requisitos:**

- Conhecimento básico de Go
- Familiaridade com execução de comandos no terminal

Vamos começar criando o projeto e a estrutura inicial do código.

## Criar o projeto

Para começar, você irá criar o projeto em que implementará a fila.

1. Certifique-se de que a pasta **cloudshell_open** está selecionada.
  
2. Clique no <walkthrough-editor-spotlight spotlightId="menu-file">File Menu</walkthrough-editor-spotlight> e selecione **New Folder**.

3. No campo de nome, digite `aed1` e clique em **OK**.

4. Clique novamente no <walkthrough-editor-spotlight spotlightId="menu-file">File Menu</walkthrough-editor-spotlight> e selecione **Open Workspace**.

5. Escolha a pasta `cloudshell_open/aed1` e clique em **Open**.

6. Abra um terminal clicando em <walkthrough-editor-spotlight spotlightId="menu-terminal-new-terminal">New Terminal</walkthrough-editor-spotlight>.

7. No terminal, inicialize o módulo Go:

```bash
go mod init aed1
```

O terminal deve exibir uma saída semelhante a:

```bash
go: creating new go.mod: module aed1
```

## Criar a interface da fila

Nesta etapa, você definirá a interface que as filas implementarão.

1. Clique no <walkthrough-editor-spotlight spotlightId="menu-file">File Menu</walkthrough-editor-spotlight> e selecione **New Folder**.

2. Nomeie a pasta como `queuefifo` e clique em **OK**.

3. Clique novamente no <walkthrough-editor-spotlight spotlightId="menu-file">File Menu</walkthrough-editor-spotlight> e selecione **New File**.

4. Nomeie o arquivo como `iqueue.go` e clique em **OK**.

5. No arquivo `iqueue.go`, adicione o seguinte código:

```go
package queuefifo

type IQueue interface {
	Enqueue(value int)
	Dequeue() (int, error)
	Front() (int, error)
	IsEmpty() bool
	Size() int
}
```

6. Salve o arquivo.

## Criar os testes da fila

Agora você adicionará testes para validar o comportamento das implementações da fila.
Esses testes são genéricos: eles foram pensados para o TAD Fila-FIFO e independem da implementação.

1. Clique no <walkthrough-editor-spotlight spotlightId="menu-file">File Menu</walkthrough-editor-spotlight> e selecione **New File**.

2. Crie o arquivo dentro da pasta `queuefifo` e nomeie-o como `queue_test.go` e clique em **OK**.

3. No arquivo `queue_test.go`, adicione o seguinte código:

```go
package queuefifo

import (
	"testing"
)

var size int

var queues []IQueue

func createQueues(size int) {
  linkedListQueue := &LinkedListQueue{}
  queues = []IQueue{linkedListQueue}
	//arrayQueue := &ArrayQueue{}	
	//(*array_queue).Init(size)
	//queues = []IQueue{arrayQueue, linkedListQueue}
}

func deleteQueues() {
	queues = nil
}

func setupTest() func() {
	size = 10
	createQueues(size)

	return func() {
		deleteQueues()
	}
}

func TestEnqueue(t *testing.T) {
	defer setupTest()()
	for _, queue := range queues {
		for i := 0; i < 2*size; i++ {
			queue.Enqueue(i)
			if queue.Size() != i+1 {
				t.Errorf("%T size = %d, expected %d", queue, queue.Size(), i+1)
			}
		}
	}
}

func TestDequeue(t *testing.T) {
	defer setupTest()()
	for _, queue := range queues {
		for i := 0; i < size; i++ {
			queue.Enqueue(i)
		}
		for i := 0; i < size; i++ {
			val, err := queue.Dequeue()

      if err != nil {
				t.Errorf("%T unexpected error: %v", queue, err)
			}

      if val != i {
				t.Errorf("%T dequeued %d, expected %d", queue, val, i)
			}
			
			if queue.Size() != size-i-1 {
				t.Errorf("%T size = %d, expected %d", queue, queue.Size(), size-i-1)
			}
		}
	}
}

func TestDequeueEmptyQueue(t *testing.T) {
	defer setupTest()()
	for _, queue := range queues {
		_, err := queue.Dequeue()
		if err == nil {
			t.Errorf("%T expected error on dequeue from empty queue", queue)
		}
	}
}

func TestFront(t *testing.T) {
	defer setupTest()()
	for _, queue := range queues {
		for i := 0; i < size; i++ {
			queue.Enqueue(i)
			val, err := queue.Front()
      if err != nil {
				t.Errorf("%T unexpected error: %v", queue, err)
			}
      if val != 0 {
				t.Errorf("%T front = %d, expected 0", queue, val)
			}
			
		}
	}
}

func TestFrontEmptyQueue(t *testing.T) {
	defer setupTest()()
	for _, queue := range queues {
		_, err := queue.Front()
		if err == nil {
			t.Errorf("%T expected error on front from empty queue", queue)
		}
	}
}

func TestIsEmpty(t *testing.T) {
	defer setupTest()()
	for _, queue := range queues {
		queue.Enqueue(0)
		empty := queue.IsEmpty()
		if empty {
			t.Errorf("%T should not be empty", queue)
		}
	}
}

func TestIsEmptyOnEmptyQueue(t *testing.T) {
	defer setupTest()()
	for _, queue := range queues {
		if !queue.IsEmpty() {
			t.Errorf("%T should be empty", queue)
		}
	}
}

func TestSize(t *testing.T) {
	defer setupTest()()
	for _, queue := range queues {
		queue.Enqueue(0)
		if queue.Size() != 1 {
			t.Errorf("%T size = %d, expected 1", queue, queue.Size())
		}
	}
}

func TestSizeEmptyQueue(t *testing.T) {
	defer setupTest()()
	for _, queue := range queues {
		if queue.Size() != 0 {
			t.Errorf("%T size = %d, expected 0", queue, queue.Size())
		}
	}
}
```

4. Salve o arquivo.

- Momentaneamente veremos um erro porque o arquivo `linkedlist_queue.go` ainda não foi criado.

## Implementar a fila com lista encadeada

Agora você iniciará a implementação de uma fila FIFO utilizando **lista encadeada**.

Nesta etapa, você criará a estrutura e os métodos da fila, deixando a implementação para os próximos passos.

---

### Criar o arquivo

1. Clique no <walkthrough-editor-spotlight spotlightId="menu-file">File Menu</walkthrough-editor-spotlight> e selecione **New File**.

2. Nomeie o arquivo como `linkedlist_queue.go` e clique em **OK**.

---

### Definir estruturas e assinaturas

3. No arquivo `linkedlist_queue.go`, adicione o seguinte código:

```go
package queuefifo

import "errors"

type LinkedListQueue struct {
	front *Node
	rear  *Node
	size  int
}

type Node struct {
	val  int
	next *Node
}

func (queue *LinkedListQueue) Enqueue(val int) {
}

func (queue *LinkedListQueue) Dequeue() (int, error) {
	return 0, errors.New("not implemented")
}

func (queue *LinkedListQueue) Front() (int, error) {
	return 0, errors.New("not implemented")
}

func (queue *LinkedListQueue) IsEmpty() bool {
	return false
}

func (queue *LinkedListQueue) Size() int {
	return queue.size
}
```

4. Salve o arquivo.

## Implementar o método Enqueue

Nesta etapa, você implementará apenas a operação de inserção (`Enqueue`) da fila.

---

### Implementar funções e testar

1. No arquivo `linkedlist_queue.go`, localize o método `Enqueue` e substitua pelo código abaixo:

```go
func (queue *LinkedListQueue) Enqueue(val int) {
	newNode := &Node{val: val, next: nil}

	if queue.size == 0 {
		queue.front = newNode
	} else {
		queue.rear.next = newNode
	}

	queue.rear = newNode
	queue.size++
}
```

2. Salve o arquivo.

3. Agora você irá executar os testes para verificar o comportamento atual da fila.

```bash
go test ./...  #execute os testes
```
4. Neste momento:
   
 - Alguns testes ainda irão falhar (isso é esperado)
 - O objetivo é validar incrementalmente a implementação

5. Implemente os próximos métodos na seguinte ordem:

- `Front`
- `IsEmpty`
- `Dequeue`

Após cada implementação, execute novamente:

```bash
go test ./...
```

## Implementar a fila com array circular

Agora você iniciará a implementação de uma fila FIFO utilizando **array circular**.

Nesta etapa, você criará a estrutura e os métodos da fila, deixando a implementação para os próximos passos.

---

### Criar o arquivo

1. Clique no <walkthrough-editor-spotlight spotlightId="menu-file">File Menu</walkthrough-editor-spotlight> e selecione **New File**.

2. Nomeie o arquivo como `array_queue.go` e clique em **OK**.

---

### Definir estruturas e assinaturas

3. No arquivo `array_queue.go`, adicione o seguinte código:

```go
package queuefifo

import "errors"

type ArrayQueue struct {
  v []int;
  front int;
  rear int;
}

func (queue *ArrayQueue) Init(size int) {
}

func (queue *ArrayQueue) Enqueue(val int) {
}

func (queue *ArrayQueue) Dequeue() (int, error) {
	return -1, errors.New("error msg")
}

func (queue *ArrayQueue) Front() (int, error) {
	return -1, errors.New("error msg")
}

func (queue *ArrayQueue) IsEmpty() bool {
	return false
}

func (queue *ArrayQueue) Size() int {
	return queue.size
}
```

4. Salve o arquivo.

5. Implemente os próximos métodos na seguinte ordem:

- `Front`
- `IsEmpty`
- `Enqueue`
- `Dequeue`

Após cada implementação, execute novamente:

```bash
go test ./...
```

