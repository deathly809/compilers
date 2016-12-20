
package main

import "fmt"

var (
    zeros = 0
    ones = 0
)

func fib(n int) int {
    if n < 2 {
        if n == 0 {
            zeros++
        } else {
            ones++
        }
        return 1
    }
    return fib(n -1) + fib(n - 2)
}

func main() {
    fib(6)
    fmt.Println("zeros", zeros)
    fmt.Println("ones", ones)
}
