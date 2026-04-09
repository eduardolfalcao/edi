---
title: Filas DEQUE (Filas de Duas Pontas) em Go 
description: Implementação de deques utilizando listas duplamente encadeadas e arrays circulares em Go.
author: eduardo@dca.ufrn.br
tags: Go, Data Structures, Deque
---

# Implementando Deques em Go

Neste tutorial, você irá implementar uma estrutura de dados do tipo **deque (double-ended queue)** em Go.

Um **deque** permite inserções e remoções em **ambas as extremidades** da estrutura.

Você construirá duas implementações:

* Um deque baseado em **lista duplamente encadeada**
* Um deque baseado em **vetor circular**

Ao final, você será capaz de:

* Implementar operações como `PushFront`, `PushBack`, `PopFront` e `PopBack`
* Entender que um deque pode simular tanto filas quanto pilhas
* Validar o comportamento com testes automatizados

---

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

## 🧩 Criar a interface do deque

Crie a pasta `deque` e o arquivo `ideque.go`:

```go
package deque

type IDeque interface {
	PushFront(value int)
	PushBack(value int)
	PopFront() (int, error)
	PopBack() (int, error)
	Front() (int, error)
	Back() (int, error)
	IsEmpty() bool
	Size() int
}
```

## 🧪 Criar os testes

1. Crie o arquivo `deque_test.go` dentro da pasta `deque`:

2. No arquivo `deque_test.go`, adicione o seguinte código:

```go
package deque

import "testing"

var size int
var deques []IDeque

func createDeques(size int) {
	linked := &DoublyLinkedListDeque{}

	// Para ativar array também:
	// array := &ArrayDeque{}
	// array.Init(size)

	deques = []IDeque{linked}
	// deques = []IDeque{array, linked}
}

func deleteDeques() {
	deques = nil
}

func setupTest() func() {
	size = 10
	createDeques(size)
	return func() {
		deleteDeques()
	}
}

func TestPushBack(t *testing.T) {
	defer setupTest()()

	for _, d := range deques {
		for i := 0; i < 2*size; i++ {
			d.PushBack(i)
			if d.Size() != i+1 {
				t.Errorf("%T size = %d, expected %d", d, d.Size(), i+1)
			}
		}
	}
}

func TestPushFront(t *testing.T) {
	defer setupTest()()

	for _, d := range deques {
		for i := 0; i < 2*size; i++ {
			d.PushFront(i)
			if d.Size() != i+1 {
				t.Errorf("%T size = %d, expected %d", d, d.Size(), i+1)
			}
		}
	}
}

func TestPopFront(t *testing.T) {
	defer setupTest()()

	for _, d := range deques {
		for i := 0; i < size; i++ {
			d.PushBack(i)
		}

		for i := 0; i < size; i++ {
			val, err := d.PopFront()
			if err != nil {
				t.Errorf("%T unexpected error: %v", d, err)
			}
			if val != i {
				t.Errorf("%T got %d, expected %d", d, val, i)
			}
			if d.Size() != size-i-1 {
				t.Errorf("%T size = %d, expected %d", d, d.Size(), size-i-1)
			}
		}
	}
}

func TestPopBack(t *testing.T) {
	defer setupTest()()

	for _, d := range deques {
		for i := 0; i < size; i++ {
			d.PushBack(i)
		}

		for i := 0; i < size; i++ {
			val, err := d.PopBack()
			if err != nil {
				t.Errorf("%T unexpected error: %v", d, err)
			}
			expected := size - i - 1
			if val != expected {
				t.Errorf("%T got %d, expected %d", d, val, expected)
			}
			if d.Size() != size-i-1 {
				t.Errorf("%T size = %d, expected %d", d, d.Size(), size-i-1)
			}
		}
	}
}

func TestPopEmpty(t *testing.T) {
	defer setupTest()()

	for _, d := range deques {
		if _, err := d.PopFront(); err == nil {
			t.Errorf("%T expected error on PopFront", d)
		}
		if _, err := d.PopBack(); err == nil {
			t.Errorf("%T expected error on PopBack", d)
		}
	}
}

func TestFront(t *testing.T) {
	defer setupTest()()

	for _, d := range deques {
		for i := 0; i < size; i++ {
			d.PushBack(i)
			val, err := d.Front()
			if err != nil {
				t.Errorf("%T unexpected error: %v", d, err)
			}
			if val != 0 {
				t.Errorf("%T front = %d, expected 0", d, val)
			}
		}
	}
}

func TestBack(t *testing.T) {
	defer setupTest()()

	for _, d := range deques {
		for i := 0; i < size; i++ {
			d.PushBack(i)
			val, err := d.Back()
			if err != nil {
				t.Errorf("%T unexpected error: %v", d, err)
			}
			if val != i {
				t.Errorf("%T back = %d, expected %d", d, val, i)
			}
		}
	}
}

func TestFrontBackEmpty(t *testing.T) {
	defer setupTest()()

	for _, d := range deques {
		if _, err := d.Front(); err == nil {
			t.Errorf("%T expected error on Front", d)
		}
		if _, err := d.Back(); err == nil {
			t.Errorf("%T expected error on Back", d)
		}
	}
}

func TestIsEmpty(t *testing.T) {
	defer setupTest()()

	for _, d := range deques {
		if !d.IsEmpty() {
			t.Errorf("%T should be empty", d)
		}
		d.PushBack(1)
		if d.IsEmpty() {
			t.Errorf("%T should not be empty", d)
		}
	}
}

func TestSize(t *testing.T) {
	defer setupTest()()

	for _, d := range deques {
		if d.Size() != 0 {
			t.Errorf("%T size should be 0", d)
		}
		d.PushBack(1)
		if d.Size() != 1 {
			t.Errorf("%T size should be 1", d)
		}
	}
}

func TestSingleElement(t *testing.T) {
	defer setupTest()()

	for _, d := range deques {
		d.PushBack(42)

		val, err := d.PopFront()
		if err != nil {
			t.Errorf("%T unexpected error: %v", d, err)
		}
		if val != 42 {
			t.Errorf("expected 42, got %d", val)
		}

		if !d.IsEmpty() {
			t.Errorf("%T should be empty after removing single element", d)
		}
	}
}

func TestMixedOperations(t *testing.T) {
	defer setupTest()()

	for _, d := range deques {
		d.PushBack(1)
		d.PushFront(2)
		d.PushBack(3)

		val, err := d.PopFront() // 2
    if err != nil {
	    t.Errorf("%T unexpected error: %v", d, err)
    }
		if val != 2 {
			t.Errorf("expected 2, got %d", val)
		}

		val, err = d.PopBack() // 3
    if err != nil {
	    t.Errorf("%T unexpected error: %v", d, err)
    }
		if val != 3 {
			t.Errorf("expected 3, got %d", val)
		}

		val, err = d.PopFront() // 1
    if err != nil {
	    t.Errorf("%T unexpected error: %v", d, err)
    }
		if val != 1 {
			t.Errorf("expected 1, got %d", val)
		}
	}
}

func TestPushCircularRight(t *testing.T) {
	defer setupTest()()

	for _, d := range deques {
		for i := 0; i < size; i++ {
			d.PushBack(i)
		}
		for i := 0; i < size-2; i++ {
			d.PopFront()
		}

		for i := 10; i < 16; i++ {
			d.PushBack(i)
		}

		for i := 8; i < 16; i++ {
			val, err := d.PopFront()
			if err != nil {
				t.Errorf("%T unexpected error: %v", d, err)
			}
			if val != i {
				t.Errorf("expected %d, got %d", i, val)
			}
		}

		if d.Size() != 0 {
			t.Errorf("%T should be empty", d)
		}
	}
}

func TestPushCircularLeft(t *testing.T) {
	defer setupTest()()

	for _, d := range deques {
		for i := 0; i < size; i++ {
			d.PushBack(i)
		}
		for i := 0; i < 2; i++ {
			d.PopBack()
		}

		for i := -1; i > -3; i-- {
			d.PushFront(i)
		}

		for i := -2; i < 8; i++ {
			val, err := d.PopFront()
			if err != nil {
				t.Errorf("%T unexpected error: %v", d, err)
			}
			if val != i {
				t.Errorf("expected %d, got %d", i, val)
			}
		}

		if d.Size() != 0 {
			t.Errorf("%T should be empty", d)
		}
	}
}
```
3. Salve o arquivo.

- Momentaneamente veremos um erro porque o arquivo `linkedlist_deque.go` ainda não foi criado.


# 🔗 Implementação com Lista Duplamente Encadeada

1. Crie `linkedlist_deque.go`:

```go
package deque

import "errors"

type DoublyLinkedListDeque struct {
	front *Node
	back  *Node
	size  int
}

type Node struct {
	prev *Node
	val  int
	next *Node
}

func (deque *DoublyLinkedListDeque) PushFront(val int) {
	newNode := &Node{val: val}
	if deque.size == 0 {
    deque.front = newNode
		deque.back = newNode
	} else {
		newNode.next = deque.front
		deque.front.prev = newNode
    deque.front = newNode
	}
	deque.size++
}

func (deque *DoublyLinkedListDeque) PushBack(val int) {
}

func (deque *DoublyLinkedListDeque) PopFront() (int, error) {
	return 0, errors.New("not implemented")
}

func (deque *DoublyLinkedListDeque) PopBack() (int, error) {
	return 0, errors.New("not implemented")
}

func (deque *DoublyLinkedListDeque) Front() (int, error) {
	return 0, errors.New("not implemented")
}

func (deque *DoublyLinkedListDeque) Back() (int, error) {
	return 0, errors.New("not implemented")
}

func (deque *DoublyLinkedListDeque) IsEmpty() bool {
	return deque.size == 0
}

func (deque *DoublyLinkedListDeque) Size() int {
	return deque.size
}
```

2. Salve o arquivo.

3. As funções PushFront, IsEmpty e Size já estão implementadas.

4. Implemente os próximos métodos na seguinte ordem:

- `Front`
- `Back`
- `PushBack`
- `PopFront`
- `PopBack`

Após cada implementação, execute novamente:

```bash
go test ./...
```

---

# 🔄 Implementação com Array Circular

- Lembre-se que no array circular, os índices devem ser manipulados usando aritmética modular.
- ⚠️ Atenção: a parte mais desafiadora desta implementação é o redimensionamento do vetor circular. Certifique-se de manter a ordem dos elementos ao copiar para o novo vetor.

Crie `array_deque.go`:

```go
package deque

import "errors"

type ArrayDeque struct {
  v     []int
	front int
	back  int
	size  int
}

// size define a capacidade inicial do vetor
func (deque *ArrayDeque) Init(size int) {
}

// quando o vetor estiver cheio, sua capacidade deve ser duplicada
// copie os elementos respeitando a ordem lógica do deque e reajuste front e back
func (deque *ArrayDeque) PushBack(val int) {
}

// quando o vetor estiver cheio, sua capacidade deve ser duplicada
// copie os elementos respeitando a ordem lógica do deque e reajuste front e back
func (deque *ArrayDeque) PushFront(val int) {
}

func (deque *ArrayDeque) PopFront() (int, error) {
	return 0, errors.New("not implemented")
}

func (deque *ArrayDeque) PopBack() (int, error) {
	return 0, errors.New("not implemented")
}

func (deque *ArrayDeque) Front() (int, error) {
	return 0, errors.New("not implemented")
}

func (deque *ArrayDeque) Back() (int, error) {
	return 0, errors.New("not implemented")
}

func (deque *ArrayDeque) IsEmpty() bool {
	return false
}

func (deque *ArrayDeque) Size() int {
	return 0
}
```

2. Salve o arquivo.

3. Implemente os próximos métodos na seguinte ordem:

- `Size`
- `IsEmpty`
- `Front`
- `Back`
- `PushFront`
- `PushBack`
- `PopFront`
- `PopBack`

Após cada implementação, execute novamente:

```bash
go test ./...
```

---

# 🧠 Conclusão e Insight final

Um deque (double-ended queue) é uma estrutura versátil que pode atuar como fila ou pilha, sendo útil em diversos cenários:

* **Fila (FIFO)** → usando `PushBack` + `PopFront`
* **Pilha (LIFO)** → usando `PushBack` + `PopBack`

* Aplicações
  * Algoritmos com janela deslizante (sliding window): usado para manter máximos/mínimos em tempo O(n)
  * Undo/Redo em editores: inserção e remoção eficiente nas extremidades
  * Gerenciamento de tarefas (schedulers): inserção prioritária no início ou fim da fila

* Trade-offs:
  * Lista encadeada: mais flexível, mas maior overhead de memória
  * Array circular: melhor localidade de cache, mas exige controle de índices e eventualmente precisa redimensionar o vetor quando estiver cheio
    * As operações de inserção possuem custo amortizado Theta(1) na implementação com vetor dinâmico. 

---

Fim 🚀
