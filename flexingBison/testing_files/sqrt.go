
var (
	low = 0
	high = 0
	N = 5 + 3
)

func Update() int {
	var mid int
	mid = (low + high) / 2
	if (mid * mid) <= N {
		low = mid
	} else {
		high = mid
	}
}

func main() {
	N = readInt()
	low = 0
	high = N + 1
    printInt(low)
    printInt(high)
	for (high - low) > 1 {
        printInt(low)
        printInt(high)
		Update()
	}
	printInt(low)
}

