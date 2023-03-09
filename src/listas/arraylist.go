package main

import "fmt"

type ArrayList struct {
	values [10]int
	tam    int
}

func (arrayList *ArrayList) Add(value int) {
	arrayList.values[arrayList.tam] = value
	arrayList.tam++
}

func main() {
	var arrayList ArrayList
	for i := 0; i < 10; i++ {
		arrayList.Add(i)
	}
	for i := 0; i < 10; i++ {
		fmt.Println(arrayList.values[i])
	}
	//name := "Go Developers"
	//fmt.Println("Azure for", name)
}
