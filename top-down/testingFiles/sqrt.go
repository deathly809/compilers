
var (
	low = 0
	high = 0
)

func Update(n int) int {
	var mid int
	mid = (low + high) / 2
	if mid * mid <= N {
		low = mid
	} else {
		high = mid
	}
}

func Main() {
	var n = ReadInt()
	low = 0
	high = n + 1
	for (high - low) > 1 {
		update()
	}
	Print(low)
}
