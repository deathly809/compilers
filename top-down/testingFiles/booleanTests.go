
func Main() {
	var a = true
	var b = true

	if a {
		printInt(1)
	}

	if b {
		printInt(2)
	}

	if a & b {
		printInt(3)
	}

	if a | b {
		printInt(4)
	}
}
