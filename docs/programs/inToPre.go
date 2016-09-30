package main

type stack struct {
    stk [100]rune
    pos   int
}

func (s *stack) Push(v rune) {
    s.stk[s.pos] = v
	s.pos++
}

func (s *stack) Pop() rune {
    s.pos--
    return s.stk[s.pos]
}

func (s *stack) Empty() bool {
    return s.pos == 0
}

func (s *stack) Peek() rune {
    return s.stk[s.pos - 1]
}

// Ruturns true if a has higher precedence
func precedence(a , b rune) bool {
    if a == b {
        return true
    }
    if a == '+' || a == '-' {
        if b == '*' || b == '/' {
            return false
        }
        return true
    }

	return b == '+' || b == '-'
}

func isDigit(r rune) bool {
    return '0' <= r && r <= '9'
}

func reverse(data []rune) {
    left := 0
    right := len(data) - 1
    for left < right {
        t := data[left]
        data[left] = data[right]
        data[right] = t
        left++
        right--
    }
}

func isOp(c rune) bool {
	return c == '+' || c == '-' || c == '*' || c == '/'
}
func main() {
    // answer should be : - + + 1 * 2 / 5 2 4 3  
    data := []rune{'1', '+', '2', '*' , '5', '/', '2' , '+' , '4' , '-' , '3' } 
    result := []rune(nil)

    // Step 1 - Reverse array
    reverse(data)

    // Step 2 - Convert to postfix
    stk := &stack{}
    for i := range data {
        if isOp(data[i]) {
            for !stk.Empty() {
                if precedence(stk.Peek(),data[i]) {
                    result = append(result,stk.Pop())
                }else {
                    break
                }
            }
            stk.Push(data[i])
        } else {
            result = append(result,data[i])
        }
    }

    for !stk.Empty() {
        result = append(result,stk.Pop())
    }
    // Step 3 - reverse
    reverse(result)

    for i := range result {
        print(string(result[i]), " ")
    }
    println()
}
