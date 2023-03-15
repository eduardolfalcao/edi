package list

type LinkedList struct {
	head *No
	tam  int
}

type No struct {
	value int
	next  *No
}
