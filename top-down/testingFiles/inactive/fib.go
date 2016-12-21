
var (
    zeros = 0
    ones = 0
)

func fib(n int) int {
    if n < 2 {
        if n == 0 {
            zeros = zeros + 1
        } else {
            ones = ones + 1
        }
        return 1
    }
    return fib(n -1) + fib(n - 2)
}

func main() {
    fib(1)
	printInt(zeros)
	printInt(ones)
}
