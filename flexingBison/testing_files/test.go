
func other(a int,  b int) {
    if a < 1 {
        printInt(b)
    } else {
        other(a - 1, b * a)
    }
}

func main() {
    other(5,1)
}
