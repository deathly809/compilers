
func stuff() {

    var x [10]int
    
    var i int
    for i = 0 ; i < 8; i = i + 1 {
        x[i] = readInt()
    }

    printInt(x[0] - x[1] + x[2] / x[3] * (x[4] - x[5] + x[6]*x[7]))
}

func main() {
	var a = readInt()
	var b = readInt()
	var c = readInt()

    printInt(a / b / c) # 3
    printInt(a - b - c) # 48
    printInt(a / b - c) # 4
    printInt(a - b / c) # 55
}
