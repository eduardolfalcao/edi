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

## 📦 Criar o projeto

1. Crie uma pasta chamada `aed1`

```bash
# vá para o diretório raiz
cd
mkdir aed1
cd aed1
```
   
2. Abra a pasta como workspace
3. No terminal:

```bash
go mod init aed1
```

O terminal deve exibir uma saída semelhante a:

```bash
go: creating new go.mod: module aed1
```

## 🧩 Criar a interface da fila

Nesta etapa, você definirá a interface que as filas implementarão.

Crie a pasta `queuefifo` e o arquivo `iqueue.go`:

```bash
cd aed1
mkdir deque
cd deque
touch iqueue.go
```
No arquivo `iqueue.go`, adicione o seguinte código:

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

```bash
cd aed1/deque
touch queue_test.go
```
No arquivo `queue_test.go`, adicione o seguinte código:

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

func TestCircularEnqueueAfterDequeue(t *testing.T) {
	defer setupTest()()

	for _, queue := range queues {

		// enche parcialmente
		for i := 0; i < size; i++ {
			queue.Enqueue(i)
		}

		// remove alguns
		for i := 0; i < size-2; i++ {
			queue.Dequeue()
		}

		// agora deve sobrar: [size-2, size-1]

		// adiciona mais elementos (deve usar espaço circular)
		for i := size; i < size+6; i++ {
			queue.Enqueue(i)
		}

		// agora sequência esperada:
		// size-2, size-1, size, size+1, ..., size+5

		for i := size - 2; i < size+6; i++ {
			val, err := queue.Front()

			if err != nil {
				t.Errorf("%T unexpected error: %v", queue, err)
			}

			if val != i {
				t.Errorf("%T got %d, expected %d", queue, val, i)
			}

			queue.Dequeue()
		}

		if queue.Size() != 0 {
			t.Errorf("%T expected empty queue, got size %d", queue, queue.Size())
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

Lembre-se de salvar o arquivo.

- Momentaneamente veremos um erro porque o arquivo `linkedlist_queue.go` ainda não foi criado.

## Implementar a fila com lista encadeada

Agora você iniciará a implementação de uma fila FIFO utilizando **lista encadeada**.

Nesta etapa, você criará a estrutura e os métodos da fila, deixando a implementação para os próximos passos.

---

1. Crie o arquivo.

```bash
cd aed1/deque
touch linkedlist_queue.go
```

2. No arquivo `linkedlist_queue.go`, adicione o seguinte código:

```go
package queuefifo

import "errors"

type LinkedListQueue struct {
	front *Node
	back  *Node
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

3. Salve o arquivo.

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
		queue.back.next = newNode
	}

	queue.back = newNode
	queue.size++
}
```

2. Salve o arquivo.

3. Agora você irá executar os testes para verificar o comportamento atual da fila.

```bash
cd aed1/queue
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

1. Crie o arquivo.

```bash
cd aed1/deque
touch array_queue.go
```

2. No arquivo `array_queue.go`, adicione o seguinte código:

```go
package queuefifo

import "errors"

type ArrayQueue struct {
  v []int
  front int
  back int
  size int
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

3. Salve o arquivo.

4. Implemente os próximos métodos na seguinte ordem:

- `IsEmpty`
- `Front`
- `Enqueue`
- `Dequeue`

Após cada implementação, execute novamente:

```bash
go test ./...
```

