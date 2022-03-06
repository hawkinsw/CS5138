package main

import (
	"fmt"
)

func looks_link_printf(format_string string, values ...int) {
	// We won't actually do anything here.
}

func main() {
	parameters := make([]int, 4)
	parameters[0] = 57005
	parameters[1] = 48879
	parameters[2] = 57005
	parameters[3] = 48879
	looks_link_printf("parameters %d, %d, %d, %d\n", parameters...)
	fmt.Printf("parameters %d, %d, %d, %d\n", parameters[0], parameters[1], parameters[2], parameters[3])
}
