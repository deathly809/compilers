
var (
    i = 0
    j = 10
)

func Main() {
    for i <= j {
        printInt(i)
        printInt(j)
        i = i + 1
        j = j - 1
    }
}
