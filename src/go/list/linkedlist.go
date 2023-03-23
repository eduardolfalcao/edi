package list

type LinkedList struct {
	head *Node1P
	size int
}

type Node1P struct {
	value int
	next  *Node1P
}

func (linkedlist *LinkedList) Add(value int) {

}

func (linkedlist *LinkedList) AddOnIndex(value int, index int) error {
	return nil
}

func (linkedlist *LinkedList) Remove() error {
	return nil
}

func (linkedlist *LinkedList) RemoveOnIndex(index int) error {
	return nil
}

func (linkedlist *LinkedList) Get(index int) (int, error) {
	return -1, nil
}

func (linkedlist *LinkedList) Set(value, index int) error {
	return nil
}

func (linkedlist *LinkedList) Size() int {
	return 0
}
