package list

import "testing"

func TestInit(t *testing.T) {
	size := 10
	arraylist := ArrayList{}
	err := arraylist.Init(size)

	if err != nil {
		t.Errorf("Arraylist should be initialized but returned following error: %q", err)
	}

	arraysize := arraylist.size
	if arraysize != 0 {
		t.Errorf("Arraylist size is %d, but we expected it to be %d", arraysize, 0)
	}

	arraycap := len(arraylist.values)
	if arraycap != size {
		t.Errorf("Arraylist capacity is %d, but we expected it to be %d", arraycap, size)
	}
}

func TestInitError(t *testing.T) {
	size := -1
	arraylist := ArrayList{}
	err := arraylist.Init(size)
	if err == nil {
		t.Errorf("Arraylist shouldn't be initialized with negative size %d", size)
	}
}

func TestAdd(t *testing.T) {
	size := 5
	arraylist := ArrayList{}
	arraylist.Init(size)

	for i := 0; i < size*2; i++ {
		arraylist.Add(i)
		if arraylist.size != i+1 {
			t.Errorf("Arraylist size is %d, but we expected it to be %d", arraylist.size, i+1)
		}
		if arraylist.values[i] != i {
			t.Errorf("Arraylist value on index %d is %d, but we expected it to be %d", i, arraylist.values[i], i)
		}
	}
}

func TestAddOnIndexBeginning(t *testing.T) {
	size := 5
	arraylist := ArrayList{}
	arraylist.Init(size)

	for i := 0; i < size*2; i++ {
		arraylist.AddOnIndex(i, 0)
		if arraylist.size != i+1 {
			t.Errorf("Arraylist size is %d, but we expected it to be %d", arraylist.size, i+1)
		}
		if arraylist.values[0] != i {
			t.Errorf("Arraylist value on index 0 is %d, but we expected it to be %d", arraylist.values[0], i)
		}
	}
}

func TestAddOnIndexEnd(t *testing.T) {
	size := 5
	arraylist := ArrayList{}
	arraylist.Init(size)

	for i := 0; i < size*2; i++ {
		//same behavior of Add()
		arraylist.AddOnIndex(i, arraylist.size)
		if arraylist.size != i+1 {
			t.Errorf("Arraylist size is %d, but we expected it to be %d", arraylist.size, i+1)
		}
		if arraylist.values[i] != i {
			t.Errorf("Arraylist value on index %d is %d, but we expected it to be %d", i, arraylist.values[i], i)
		}
	}
}

func TestAddOnIndexMid(t *testing.T) {
	size := 5
	arraylist := ArrayList{}
	arraylist.Init(size)

	//fulfill arraylist with 1's
	for i := 0; i < size; i++ {
		arraylist.Add(1)
	}

	//add -1, 3 times, on index 2
	for i := 0; i < 3; i++ {
		arraylist.AddOnIndex(-1, 2)
	}

	//check values before index 2 are the same
	for i := 0; i < 8; i++ {
		if i >= 2 && i < 5 {
			if arraylist.values[i] != -1 {
				t.Errorf("Arraylist value on index %d is %d, but we expected it to be -1", i, arraylist.values[i])
			}
		} else {
			if arraylist.values[i] != 1 {
				t.Errorf("Arraylist value on index %d is %d, but we expected it to be 1", i, arraylist.values[i])
			}
		}
	}
}

func TestAddOnIndexError(t *testing.T) {
	size := 5
	arraylist := ArrayList{}
	arraylist.Init(size)

	err := arraylist.AddOnIndex(-1, -1)
	if err == nil {
		t.Errorf("Shouldn't be able to add on negative index on arraylist")
	}

	err = arraylist.AddOnIndex(-1, size*2)
	if err == nil {
		t.Errorf("Shouldn't be able to add on index out of bound of array capacity")
	}
}

func TestRemove(t *testing.T) {
	size := 5
	arraylist := ArrayList{}
	arraylist.Init(size)
	for i := 0; i < size; i++ {
		arraylist.Add(i)
	}

	for i := 0; i < size; i++ {
		arraylist.Remove()
		if arraylist.size != (size - i - 1) {
			t.Errorf("Arraylist size is %d, but we expected it to be %d", arraylist.size, (size - i - 1))
		}
	}
}

func TestRemoveError(t *testing.T) {
	size := 5
	arraylist := ArrayList{}
	arraylist.Init(size)

	err := arraylist.Remove()
	if err == nil {
		t.Errorf("Shouldn't be able to remove on arraylist with size 0")
	}
}

func TestRemoveOnIndexBeginning(t *testing.T) {
	size := 5
	arraylist := ArrayList{}
	arraylist.Init(size)

	for i := 0; i < size; i++ {
		arraylist.Add(i)
	}

	for i := 0; i < size; i++ {
		if arraylist.values[0] != i {
			t.Errorf("Arraylist value on index 0 is %d, but we expected it to be %d", arraylist.values[0], i)
		}
		arraylist.RemoveOnIndex(0)
		if arraylist.size != size-i-1 {
			t.Errorf("Arraylist size is %d, but we expected it to be %d", arraylist.size, size-i-1)
		}
	}
}

func TestRemoveOnIndexEnd(t *testing.T) {
	size := 5
	arraylist := ArrayList{}
	arraylist.Init(size)
	for i := 0; i < size; i++ {
		arraylist.Add(i)
	}

	for i := 0; i < size; i++ {
		arraylist.RemoveOnIndex(arraylist.size - 1)
		if arraylist.size != (size - i - 1) {
			t.Errorf("Arraylist size is %d, but we expected it to be %d", arraylist.size, (size - i - 1))
		}
	}
}

func TestRemoveOnIndexMid(t *testing.T) {
	size := 5
	arraylist := ArrayList{}
	arraylist.Init(size)
	for i := 0; i < size; i++ {
		arraylist.Add(i)
	}

	//remove on mid
	arraylist.RemoveOnIndex(2)
	//check if shift worked properly
	for i := 2; i < arraylist.size; i++ {
		if arraylist.values[i] != i+1 {
			t.Errorf("Arraylist value on index %d is %d, but we expected it to be %d", i, arraylist.values[i], i+1)
		}
	}
}
