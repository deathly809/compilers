
func max(a int, b int) int {
    if a > b {
        a = 5
     #   return a
    }
    #return b
}

func min(a int, b int) int {
    if a < b {
        a = b
        #return a
    }
    #return b
}

func sort(arr []int) {
    var N int #len(arr)
    var i int
    for i = 1; i < N; i = i + 1 {
        var j = i
        var tmp = arr[j]
        for j > 0 & arr[j - 1] < tmp {
            arr[j] = arr[j-1]
        }

        if j != i {
            arr[j] = tmp
        }
    }
    
}

func main() {
    var i int
    for i = 0; i < 10; i = i + 1 {
        printInt(i)
    }
}

