package main

import (
	"fmt"

	"github.com/eduardolfalcao/edi/src/go/list"
)

func main() {
	arraylist := list.ArrayList{}
	arraylist.Init()

	limit := 15

	for i := 0; i < limit; i++ {
		arraylist.Add(i)
	}
	for i := 0; i < limit; i++ {
		fmt.Println(arraylist.Get(i))
	}
	for i := 0; i < limit; i++ {
		if i%2 == 0 {
			arraylist.Set(i*2, i)
		}
	}
	fmt.Println("######################")
	for i := 0; i < limit; i++ {
		fmt.Println(arraylist.Get(i))
	}
}
