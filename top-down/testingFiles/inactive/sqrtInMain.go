
var (
	low = 0
	high = 0
	N = 5 + 3
)

func Main() {
	N = readInt()
	low = 0
	high = N + 1
	for (high - low) > 1 {
		var mid int
		mid = (low + high) / 2
		if mid * mid <= N {
			low = mid
		} else {
			high = mid
		}
	}
	printInt(low)
}

