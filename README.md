README
=======


Grammar
========

We use a subset of the Go language.  We only support loops, conditionals, functions, and assignment.  We provide a subset of pre-defined functions.

Example
=======

<pre>
func doIt(i int) {
    if i < 0 {
        return;
    }
    println(i)
    doIt(i-1)
}

// Main method
func main() {
    i := readInt()

    if i < 3 {
        println("i is less than 3")
    } else {
        i++
    }

    doIt(i)

    for i > 0 {
        println(i)
        i = i - 1
    }

}
</pre>