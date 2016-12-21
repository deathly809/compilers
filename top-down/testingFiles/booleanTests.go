
func Main() {

	var a = true
	var b = false

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

	if b | a {
		printInt(5)
	}

	if b & a {
		printInt(6)
	}

	if b | b {
		printInt(8)
	}

	if a & a {
		printInt(9)
	}

    if ! b {
        printInt(10)
    }

    if ! a {
        printInt(11)
    }

    if !(a & b) {
        printInt(12)
    }

    if b | !a {
        printInt(13)
    }

    if a & !b {
        printInt(13)
    }


    if a & b | !a & !b {
        printInt(14)
    } else {
        printInt(15)
    }


}
