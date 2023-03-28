package stack

type IStack interface {
	Push(value int)
	Pop() (int, error)
	Peek() (int, error)
	Empty() bool
	Size() int
}
