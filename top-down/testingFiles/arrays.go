
# this is a comment

func Main() {
    var x [10]int
    var i int
                # (1) this is a comment

    for i = 0 ; i < 10; i = i + 1 {
        x[i] = i * i
    }

    for i = 9 ; i >= 0; i = i - 1 {
        printInt(x[i])
    }
}
