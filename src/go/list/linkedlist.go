package list

type LinkedList struct {
	head *No
	tam  int
}

type No struct {
	value int
	next  *No
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
