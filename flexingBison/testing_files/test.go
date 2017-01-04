
# this is a test

func one(a int) {
    printInt(a)
}
func two(a int, b int) {
    printInt(a)
    printInt(b)
}


func main() {
    var i int

    for i = 2; i < 5; i = i + 1 {
        one(i)
        two(i,i*i)
        newline()
    }
}
