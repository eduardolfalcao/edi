package stack

import (
	"testing"
)

var size int
var stacks [2]IStack

func createStacks(size int) {
	arraystack := &ArrayStack{}
	(*arraystack).Init(size)
	stacks = [2]IStack{arraystack, &LinkedListStack{}}
}

func deleteStacks() {
	//in this case, createStacks alone solves the problem
	//however, I let the template here to be used in other tests
	stacks[0] = nil
	stacks[1] = nil
}

func setupTest() func() {
	//before each test
	size = 10
	createStacks(size)

	//after each test
	return func() {
		deleteStacks()
	}
}

func TestPush(t *testing.T) {
	defer setupTest()()
	for _, stack := range stacks {
		for i := 0; i < 2*size; i++ {
			stack.Push(i)
			if stack.Size() != i+1 {
				t.Errorf("%T size is %d, but we expected it to be %d", stack, stack.Size(), i+1)
			}
		}
	}
}

func TestPop(t *testing.T) {
	defer setupTest()()
	for _, stack := range stacks {
		for i := 0; i < size; i++ {
			stack.Push(i)
		}
		for i := size - 1; i >= 0; i-- {
			val, err := stack.Pop()
			if val != i {
				t.Errorf("Value popped from %T is %d, but we expected it to be %d", stack, val, i)
			}
			if err != nil {
				t.Errorf(err.Error())
			}
		}
	}
}

func TestPopEmptyStack(t *testing.T) {
	defer setupTest()()
	for _, stack := range stacks {
		_, err := stack.Pop()
		if err == nil {
			t.Errorf("When popping from empty %T we should get an error", stack)
		}
	}
}

func TestPeek(t *testing.T) {
	defer setupTest()()
	for _, stack := range stacks {
		stack.Push(1)
		for i := 0; i < size; i++ {
			val, err := stack.Peek()
			if val != 1 {
				t.Errorf("Value peeked from %T is %d, but we expected it to be 1", stack, val)
			}
			if err != nil {
				t.Errorf(err.Error())
			}
		}
	}
}

func TestPeekEmptyStack(t *testing.T) {
	defer setupTest()()
	for _, stack := range stacks {
		_, err := stack.Peek()
		if err == nil {
			t.Errorf("When peeking from empty %T we should get an error", stack)
		}
	}
}

func TestEmpty(t *testing.T) {
	defer setupTest()()
	for _, stack := range stacks {
		stack.Push(1)
		empty := stack.Empty()
		if empty == true {
			t.Errorf("When verifying if %T is empty got %t", stack, empty)
		}
	}
}

func TestEmptyEmptyStack(t *testing.T) {
	defer setupTest()()
	for _, stack := range stacks {
		empty := stack.Empty()
		if empty == false {
			t.Errorf("When verifying if %T is empty got %t", stack, empty)
		}
	}
}

func TestSize(t *testing.T) {
	defer setupTest()()
	for _, stack := range stacks {
		for i := 0; i < size; i++ {
			stack.Push(i)
			sizeReturned := stack.Size()
			if sizeReturned != i+1 {
				t.Errorf("When verifying size of %T got %d but should obtain %d", stack, sizeReturned, i+1)
			}
		}
	}
}

func TestSizeEmptyStack(t *testing.T) {
	defer setupTest()()
	for _, stack := range stacks {
		sizeReturned := stack.Size()
		if sizeReturned != 0 {
			t.Errorf("When verifying size of %T got %d but should obtain 0", stack, sizeReturned)
		}
	}
}
