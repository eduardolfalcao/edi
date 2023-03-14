package list

type IList interface {
	Add(value int)
	AddOnIndex(value int, index int)
	Remove()
	RemoveOnIndex(index int)
	Get(value int)
	Set(value int, index int)
	Size()
}
