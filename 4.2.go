package main

import (
	"encoding/hex"
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

func year(s string, lo, hi int) bool {
	i, err := strconv.Atoi(s)
	return err == nil && lo <= i && i <= hi
}

func hgt(s string) bool {
	switch {
	case strings.HasSuffix(s, "cm"):
		i, err := strconv.Atoi(strings.TrimSuffix(s, "cm"))
		return err == nil && 150 <= i && i <= 193
	case strings.HasSuffix(s, "in"):
		i, err := strconv.Atoi(strings.TrimSuffix(s, "in"))
		return err == nil && 59 <= i && i <= 76
	}
	return false
}

func hcl(s string) bool {
	if strings.HasPrefix(s, "#") {
		_, err := hex.DecodeString(s[1:])
		return err == nil
	}
	return false
}

func ecl(s string) bool {
	return map[string]bool{
		"amb": true,
		"blu": true,
		"brn": true,
		"gry": true,
		"grn": true,
		"hzl": true,
		"oth": true,
	}[s]
}

func pid(s string) bool {
	_, err := strconv.Atoi(s)
	return err == nil && len(s) == 9
}

func main() {
	b, _ := ioutil.ReadFile("input.txt")
	valid := 0
	for _, s := range strings.Split(string(b), "\n\n") {
		m := map[string]func(string) bool{
			"byr": func(s string) bool { return year(s, 1920, 2002) },
			"iyr": func(s string) bool { return year(s, 2010, 2020) },
			"eyr": func(s string) bool { return year(s, 2020, 2030) },
			"hgt": hgt,
			"hcl": hcl,
			"ecl": ecl,
			"pid": pid,
		}
		for _, f := range strings.Fields(s) {
			kv := strings.Split(f, ":")
			if val, ok := m[kv[0]]; ok && val(kv[1]) {
				delete(m, kv[0])
			}
		}
		if len(m) == 0 {
			valid++
		}
	}
	fmt.Println(valid)
}
