package list

import (
	"testing"
)

var size int
var lists [3]IList

func createLists(size int) {
	arraylist := &ArrayList{}
	(*arraylist).Init(size)
	lists = [3]IList{arraylist, &LinkedList{}, &DoublyLinkedList{}}
}

func deleteLists() {
	//in this case, createLists alone solves the problem
	//however, I let the template here to be used in other tests
	lists[0] = nil
	lists[1] = nil
	lists[2] = nil
}

func setupTest() func() {
	//before each test
	size = 10
	createLists(size)

	//after each test
	return func() {
		deleteLists()
	}
}

func TestAdd(t *testing.T) {
	defer setupTest()()
	for _, list := range lists {
		for i := 0; i < size; i++ {
			list.Add(i)
			if list.Size() != i+1 {
				t.Errorf("%T size is %d, but we expected it to be %d", list, list.Size(), i+1)
			}
		}
	}
}

func TestAddOnIndexBeginning(t *testing.T) {
	defer setupTest()()
	for _, list := range lists {
		for i := 0; i < size; i++ {
			list.AddOnIndex(i, 0)
			if list.Size() != i+1 {
				t.Errorf("%T size is %d, but we expected it to be %d", list, list.Size(), i+1)
			}
			val, err := list.Get(0)
			if val != i {
				t.Errorf("%T value on index 0 is %d, but we expected it to be %d", list, val, i)
			}
			if err != nil {
				t.Errorf(err.Error())
			}
		}
	}
}

func TestAddOnIndexEnd(t *testing.T) {
	defer setupTest()()
	for _, list := range lists {
		for i := 0; i < size; i++ {
			//same behavior of Add()
			list.AddOnIndex(i, list.Size())
			if list.Size() != i+1 {
				t.Errorf("%T size is %d, but we expected it to be %d", list, list.Size(), i+1)
			}
			val, err := list.Get(i)
			if val != i {
				t.Errorf("%T value on index %d is %d, but we expected it to be %d", list, i, val, i)
			}
			if err != nil {
				t.Errorf(err.Error())
			}
		}
	}
}

func TestAddOnIndexMid(t *testing.T) {
	defer setupTest()()
	for _, list := range lists {
		//fulfill list with 1's
		for i := 0; i < size; i++ {
			list.Add(1)
		}

		//add -1, 3 times, on index 2
		for i := 0; i < 3; i++ {
			list.AddOnIndex(-1, 2)
		}

		//check values before index 2 are the same
		for i := 0; i < 8; i++ {
			val, err := list.Get(i)
			if i >= 2 && i < 5 {
				if val != -1 {
					t.Errorf("%T value on index %d is %d, but we expected it to be -1", list, i, val)
				}
			} else {
				if val != 1 {
					t.Errorf("%T value on index %d is %d, but we expected it to be 1", list, i, val)
				}
			}
			if err != nil {
				t.Errorf(err.Error())
			}
		}
	}
}

func TestRemoveOnIndexBeginning(t *testing.T) {
	defer setupTest()()
	for _, list := range lists {
		for i := 0; i < size; i++ {
			list.Add(i)
		}

		for i := 0; i < size; i++ {
			val, err := list.Get(0)
			if val != i {
				t.Errorf("%T value on index 0 is %d, but we expected it to be %d", list, val, i)
			}
			if err != nil {
				t.Errorf(err.Error())
			}
			list.RemoveOnIndex(0)
			if list.Size() != size-i-1 {
				t.Errorf("%T size is %d, but we expected it to be %d", list, list.Size(), size-i-1)
			}
		}
	}
}

func TestRemoveOnIndexEnd(t *testing.T) {
	defer setupTest()()
	for _, list := range lists {
		for i := 0; i < size; i++ {
			list.Add(i)
		}

		for i := size - 1; i >= 0; i-- {
			val, err := list.Get(i)
			if val != i {
				t.Errorf("%T value on index 0 is %d, but we expected it to be %d", list, val, i)
			}
			if err != nil {
				t.Errorf(err.Error())
			}
			list.RemoveOnIndex(i)
			if list.Size() != i {
				t.Errorf("%T size is %d, but we expected it to be %d", list, list.Size(), i)
			}
		}
	}
}

func TestRemoveOnIndexMid(t *testing.T) {
	defer setupTest()()
	for _, list := range lists {
		for i := 0; i < size; i++ {
			list.Add(i)
		}

		//remove on mid
		list.RemoveOnIndex(2)
		for i := 2; i < list.Size(); i++ {
			val, err := list.Get(i)
			if val != i+1 {
				t.Errorf("%T value on index %d is %d, but we expected it to be %d", list, i, val, i+1)
			}
			if err != nil {
				t.Errorf(err.Error())
			}
		}
	}
}

func TestSet(t *testing.T) {
	defer setupTest()()
	for _, list := range lists {
		//fulfill list with 1's
		for i := 0; i < size; i++ {
			list.Add(1)
		}

		//set -1 on even indexes
		for i := 0; i < size; i++ {
			if i%2 == 0 {
				list.Set(-1, i)
			}
		}

		//check values before index 2 are the same
		for i := 0; i < size; i++ {
			val, err := list.Get(i)
			if i%2 == 0 {
				if val != -1 {
					t.Errorf("%T value on index %d is %d, but we expected it to be -1", list, i, val)
				}
			} else {
				if val == -1 {
					t.Errorf("%T value on index %d is %d, but we expected it to be different from -1", list, i, val)
				}
			}
			if err != nil {
				t.Errorf(err.Error())
			}
		}
	}
}
