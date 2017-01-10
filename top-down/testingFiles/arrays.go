
func Main() {
    var x [10]int
    var i int
    for i = 0 ; i < 10; i = i + 1 {
        x[i] = i * i
    }
    for i = 0 ; i < 10; i = i + 1 {
        printInt(x[i])
    }
}
