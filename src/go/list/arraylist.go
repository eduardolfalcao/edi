package list

/*type IList interface {
	Add(value int)
	AddOnIndex(value int, index int)
	Remove()
	RemoveOnIndex(index int)
	Get(value int)
	Set(value int, index int)
	Size()
}*/

type ArrayList struct {
	values   [10]int
	tam, cap int
}

func (arraylist *ArrayList) Add(value int) {
	arraylist.values[arraylist.tam] = value
	arraylist.tam++
}

func (arraylist *ArrayList) Get(index int) int {
	return arraylist.values[index]
}

func (arraylist *ArrayList) Set(value, index int) {
	arraylist.values[index] = value
}
