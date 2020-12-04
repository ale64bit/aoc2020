package main

import (
	"fmt"
	"io/ioutil"
	"strings"
)

func main() {
	b, _ := ioutil.ReadFile("input.txt")
	valid := 0
	for _, s := range strings.Split(string(b), "\n\n") {
		m := map[string]bool{
			"byr": true,
			"iyr": true,
			"eyr": true,
			"hgt": true,
			"hcl": true,
			"ecl": true,
			"pid": true,
		}
		for _, f := range strings.Fields(s) {
			kv := strings.Split(f, ":")
			delete(m, kv[0])
		}
		if len(m) == 0 {
			valid++
		}
	}
	fmt.Println(valid)
}
