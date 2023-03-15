package list

type IList interface {
	Init()
	Add(value int)
	AddOnIndex(value int, index int)
	Remove()
	RemoveOnIndex(index int)
	Get(index int)
	Set(value int, index int)
	Size()
}
