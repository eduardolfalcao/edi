package list

type DoublyLinkedList struct {
	head *Node2P
	tail *Node2P
	tam  int
}

type Node2P struct {
	prev  *Node2P
	value int
	next  *Node2P
}

func (doublylinkedlist *DoublyLinkedList) Add(value int) {

}

func (doublylinkedlist *DoublyLinkedList) AddOnIndex(value int, index int) error {
	return nil
}

func (doublylinkedlist *DoublyLinkedList) Remove() error {
	return nil
}

func (doublylinkedlist *DoublyLinkedList) RemoveOnIndex(index int) error {
	return nil
}

func (doublylinkedlist *DoublyLinkedList) Get(index int) (int, error) {
	return -1, nil
}

func (doublylinkedlist *DoublyLinkedList) Set(value, index int) error {
	return nil
}

func (doublylinkedlist *DoublyLinkedList) Size() int {
	return 0
}
