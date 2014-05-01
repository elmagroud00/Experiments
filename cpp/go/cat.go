package main

import(
		"./file"
		"fmt"
		"os"
)	 

func main(){
	hello := []byte("hello, world\n")
	file.Stdout.Write(hello)
	file, err := file.Open("/dose/not/exist", 0, 0)
	if file == nil{
		fmt.Printf("cannot open file; err = %s\n", err.String())
	}
}
