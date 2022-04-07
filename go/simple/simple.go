package main

import (
	"fmt"
)

func addOne(base int) int {
	return base + 1
}

func main() {
	result := addOne(15)

	fmt.Printf("result: %v\n", result)
}
