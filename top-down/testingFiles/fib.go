
func Main() {
	var N = readInt()
	var p = 1
	var q = 1
	var t = 0

	for N > 1 {
		t = p + q
		p = q
		q = t
		N = N - 1
	}
	printInt(p)
}
