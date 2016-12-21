
var (
	low = 0
	high = 0
	N = 0
)

func Update() int {
	var mid int
	mid = (low + high) / 2
	if mid * mid <= N {
		low = mid
	} else {
		high = mid
	}
}

func Main() {
	var n = readInt()
	low = 0
	high = n + 1
	for (high - low) > 1 {
		Update()
	}
	printInt(low)
}
