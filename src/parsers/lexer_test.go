package parsers

import "testing"

func run(t *testing.T, data [][]string, f ParseToken) {
	for _, v := range data {
		read, rem, _ := f(v[0])
		if read != v[1] || rem != v[2] {
			t.Logf("For value '%s' expected read = %s, rem = %s; found read = %s, rem = %s", v[0], v[1], v[2], read, rem)
			t.Fail()
		}
	}
}

func checkErrors(t *testing.T, data [][]string, f ParseToken) {
	for _, v := range data {
		read, rem, err := f(v[0])
		if err == nil {
			t.Logf("For value %s we expected an error", v[0])
		} else if read != v[1] || rem != v[2] {
			t.Logf("For value '%s' expected read = %s, rem = %s; found read = %s, rem = %s", v[0], v[1], v[2], read, rem)
			t.Fail()
		}
	}
}

func TestReal(t *testing.T) {
	valid := [][]string{
		{"1.0", "1.0", ""},
		{"0.1", "0.1", ""},
		{"1.00001e-1", "1.00001e-1", ""},
		{"1.00001e+1", "1.00001e+1", ""},
		{"1.00001e1", "1.00001e1", ""},
	}

	splits := [][]string{
		{"1", "", "1"},
		{".", "", "."},
		{"1.00001e--1", "1.00001", "e--1"},
		{"1.00001e+1E1", "1.00001e+1", "E1"},
		{".e", "", ".e"},
	}

	run(t, valid, Real)
	run(t, splits, Real)
}

func TestID(t *testing.T) {
	valid := [][]string{
		{"hi", "hi", ""},
		{"test", "test", ""},
		{"_this9", "_this9", ""},
		{"_", "_", ""},
		{"_910", "_910", ""},
	}

	errors := [][]string{
		{"34", "", "34"},
		{"7a_", "", "7a_"},
		{"6_", "", "6_"},
		{"9_9a", "", "9_9a"},
	}

	splits := [][]string{
		{"_hello9&", "_hello9", "&"},
		{"_hello9+derp", "_hello9", "+derp"},
	}

	run(t, valid, IDFunc)
	run(t, splits, IDFunc)
	checkErrors(t, errors, IDFunc)
}

func TestInteger(t *testing.T) {
	valid := [][]string{
		{"1", "1", ""},
		{"2", "2", ""},
		{"3", "3", ""},
		{"4", "4", ""},
		{"5", "5", ""},
		{"1234567890000123456", "1234567890000123456", ""},
		{"0xDeadBeef", "0xDeadBeef", ""},
		{"0775", "0775", ""},
		{"0XDeAdbEeF", "0XDeAdbEeF", ""},
		{"0X1234567890abcdefABCDEF", "0X1234567890abcdefABCDEF", ""},
		{"0x1234567890abcdefABCDEF", "0x1234567890abcdefABCDEF", ""},
		{"0xABCDEF1234567890abcdef", "0xABCDEF1234567890abcdef", ""},
		{"0x1234567890ABCDEFabcdef", "0x1234567890ABCDEFabcdef", ""},
	}

	splits := [][]string{
		{"3a4", "3", "a4"},
		{"7a_", "7", "a_"},
		{"6_", "6", "_"},
		{"9_9a", "9", "_9a"},
		{"008", "00", "8"},
		{"10F", "10", "F"},
	}

	errors := [][]string{
		{"_hello9&", "", "_hello9&"},
		{"_hello9 five   ", "", "_hello9 five   "},
		{"0xG", "", "0xG"},
		{"0x", "", "0x"},
		{"0X", "", "0X"},
	}

	run(t, valid, Integer)
	run(t, splits, Integer)
	checkErrors(t, errors, Integer)

}

func TestString(t *testing.T) {
	full := [][]string{
		{"\"hello\"", "\"hello\"", ""},
		{"\"\"", "\"\"", ""},
		{"\"9078eljsfg\"", "\"9078eljsfg\"", ""},
	}

	split := [][]string{
		{"hello", "", "hello"},
		{"\"he\"llo", "\"he\"", "llo"},
		{"\"hell\"o", "\"hell\"", "o"},
	}

	run(t, full, StringFunc)
	run(t, split, StringFunc)

}
