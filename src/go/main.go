package main

import (
	"fmt"

	"github.com/eduardolfalcao/edi/src/go/list"
)

func main() {
	//var arraylist list.ArrayList
	arraylist := list.ArrayList{}
	limit := 15
	arraylist.Init(limit)

	for i := 0; i < limit; i++ {
		arraylist.Add(i)
	}
	for i := 0; i < limit; i++ {
		val, err := arraylist.Get(i)
		if err == nil {
			fmt.Println(val)
		}
	}
	for i := 0; i < limit; i++ {
		if i%2 == 0 {
			arraylist.Set(i*2, i)
		}
	}
	fmt.Println("######################")
	for i := 0; i < limit; i++ {
		val, err := arraylist.Get(i)
		if err == nil {
			fmt.Println(val)
		}
	}
}
