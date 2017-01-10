
var (
    i = 0
)

func main() {
    var x [10]int

    for i = 0; i < 10; i = i + 1 {
        x[i] = i * i
    }
    
    for i = 9; i >= 0; i = i - 1 {
        printInt(x[i])
    }    
}
