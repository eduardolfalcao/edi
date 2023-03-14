package main

import (
	"fmt"

	"github.com/eduardolfalcao/edi/src/go/list"
)

func main() {
	var arraylist list.ArrayList
	for i := 0; i < 15; i++ {
		arraylist.Add(i)
	}
	for i := 0; i < 15; i++ {
		fmt.Println(arraylist.Get(i))
	}
	for i := 0; i < 15; i++ {
		if i%2 == 0 {
			arraylist.Set(i*2, i)
		}
	}
	fmt.Println("######################")
	for i := 0; i < 10; i++ {
		fmt.Println(arraylist.Get(i))
	}
}
