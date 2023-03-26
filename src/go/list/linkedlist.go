package list

import "errors"

type LinkedList struct {
	head *Node1P
	size int
}

type Node1P struct {
	value int
	next  *Node1P
}

func (linkedlist *LinkedList) Add(value int) {
	newNode := Node1P{value, nil}

	aux := linkedlist.head
	prev := aux
	//iterate until aux points to nil, and prev points to the last node
	for aux != nil {
		prev = aux
		aux = aux.next
	}

	if prev == nil {
		//head was pointing to nil
		linkedlist.head = &newNode
	} else {
		//head points to a node but prev.next needs to be updated
		prev.next = &newNode
	}
	linkedlist.size++
}

func (linkedlist *LinkedList) AddOnIndex(value int, index int) error {
	if index >= 0 && index <= linkedlist.size {
		newNode := Node1P{value, nil}
		if index == 0 {
			if linkedlist.head != nil {
				newNode.next = linkedlist.head
			}
			linkedlist.head = &newNode
		} else {
			prev := linkedlist.head
			//iterate until prev points to node on index-1
			for i := 0; i < index-1; i++ {
				prev = prev.next
			}
			newNode.next = prev.next
			prev.next = &newNode
		}
		linkedlist.size++
		return nil
	} else {
		if index < 0 {
			return errors.New("Can't add in linkedlist on index < 0")
		} else {
			return errors.New("Can't add in linkedlist on index > linkedlist.size")
		}
	}
}

func (linkedlist *LinkedList) RemoveOnIndex(index int) error {
	if index >= 0 && index < linkedlist.size {
		if index == 0 {
			linkedlist.head = linkedlist.head.next
		} else {
			del := linkedlist.head
			prev := linkedlist.head
			for i := 0; i < index; i++ {
				prev = del
				del = del.next
			}
			prev.next = del.next
			//when del becomes unreachable, GC will eventually free it
		}

		linkedlist.size--
		return nil
	} else {
		if index < 0 {
			return errors.New("Can't remove from linkedlist on index < 0")
		} else {
			return errors.New("Can't remove from linkedlist on index >= linkedlist.size")
		}
	}
}

func (linkedlist *LinkedList) Get(index int) (int, error) {
	if index >= 0 && index < linkedlist.size {
		aux := linkedlist.head
		//iterate until aux points to node on index specified
		for i := 0; i < index; i++ {
			aux = aux.next
		}
		return aux.value, nil
	} else {
		if index < 0 {
			return index, errors.New("Can't get value from linkedlist on index < 0")
		} else {
			return index, errors.New("Can't get value from linkedlist on index >= linkedlist.size")
		}
	}
}

func (linkedlist *LinkedList) Set(value, index int) error {
	if index >= 0 && index < linkedlist.size {
		aux := linkedlist.head
		//iterate until aux points to node on index specified
		for i := 0; i < index; i++ {
			aux = aux.next
		}
		aux.value = value
		return nil
	} else {
		if index < 0 {
			return errors.New("Can't set value in linkedlist on index < 0")
		} else {
			return errors.New("Can't set value in linkedlist on index >= linkedlist.size")
		}
	}
}

func (linkedlist *LinkedList) Size() int {
	return linkedlist.size
}
