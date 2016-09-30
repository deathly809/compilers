package main

import "fmt"

func add(x , y float64) float64 {
    return x + y
}

func subtract(x , y float64) float64 {
    return x - y
}

func multiply(x , y float64) float64 {
    return x * y
}

func divide(x , y float64) float64 {
    return x / y
}

func readCharacter() rune {
	c := '_'
	fmt.Scanf("%c",&c)
	return c
}

func readFloat() float64 {
	return float64(readCharacter() - '0')
}

func main() {
    println("Welcome to the calculator")
    for {
		res := 0.0
		x := readFloat()
		op := readCharacter()
        y := readFloat()
		readCharacter()

        err := false
        errMsg := ""

        switch op {
            case '+':
                res = add(x,y)
            case '-':
                res = subtract(x,y)
            case '*':
                res = multiply(x,y)
            case '/':
                if y != 0 {
                    res = divide(x,y)
                } else {
                    err = true
                    errMsg = "Divide by zero"
                }
            default:
                err = true
                errMsg = "Invalid operator"
        }
        if err {
            fmt.Println(errMsg)
			break
        } else {
            fmt.Println(res)
        }
    }
}
