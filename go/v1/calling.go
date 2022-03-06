package main

import (
	"fmt"
)

type Struct struct {
	variable int
}

func (s *Struct) doReceiver() int {
	return s.variable
}

func function(f int32) int64 {
	return int64(f)
}

func main() {
	fmt.Printf("Hello, World: %v\n", function(57005))

	s := Struct{}
	s.variable = 48879
	result := s.doReceiver()

	fmt.Printf("result %d\n", result)
}
