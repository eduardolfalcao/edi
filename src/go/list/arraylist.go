package list

import "fmt"

type ArrayList struct {
	values []int
	tam    int
}

func (arraylist *ArrayList) Init() {
	fmt.Println("Testando init de ArrayList")
	arraylist.values = make([]int, 10)
}

func (arraylist *ArrayList) double() {
	doubledValues := make([]int, len(arraylist.values)*2)
	for i := 0; i < len(arraylist.values); i++ {
		doubledValues[i] = arraylist.values[i]
	}
	arraylist.values = doubledValues
}

func (arraylist *ArrayList) Add(value int) {
	if arraylist.tam == len(arraylist.values) {
		arraylist.double()
	}
	arraylist.values[arraylist.tam] = value
	arraylist.tam++
}

func (arraylist *ArrayList) Get(index int) int {
	return arraylist.values[index]
}

func (arraylist *ArrayList) Set(value, index int) {
	arraylist.values[index] = value
}
