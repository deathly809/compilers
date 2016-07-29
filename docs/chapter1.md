<style>
    body {
        width: 600px;
        margin-left: auto;
        margin-right: auto;
    }

    ol ol {
        list-style-type: upper-alpha;
    }
    ol ol li {
        padding-left: 10px;
    }

    img {
        display:block;
        margin-left: auto;
        margin-right: auto;
    }

    details {
        position:absolute;
        left: 50px;
        max-width: 200px;
    }

</style>

# Notes for Chapter 1 #

## Summary ##

1. Language Processors  
2. Compiler Phases
    * Syntactic Analysis
    * Semantic Analysis
    * Code Generation
3. Machine and Assembly Languages
4. Modeling in Compiler Design
5. Code Optimization
6. High-level languages
7. Compilers and Computer Architecture
8. Software Productivity and Software Security
9. Scope Rules
10. Environments
11. Block Structure
12. Parameter Passing
13. Aliasing

-------------------------------------

### 1.0 - Introduction ###

Programming languages are notations for describing computations to people and to machines.
Before software can run it must be translated into a form which a machine can run.
The software systems that do this translation are called **compilers**.
The study of compiler design touches upon multiple domains: programming 
languages, machine architecture, language theory, algorithms, and software engineering.

### 1.1 - Language Processors ###

A compiler is a program which takes in a program in one language, the *source language*, 
and translates it into another language, the *target language*.
If a compiler is given a source program with errors then it should report them.
An **interpreter** is a special type of language processor.
This program takes in one language and performs the actions described.
The target language for an interpreter is a series of actions.

A machine-targer program is in general faster than if it was executed with an interpreter.
However, an interpreter can usually give better error messages and has faster turn around 
for getting feedback aftr making changes to the source program.

The Java language processors consist of two parts: a compiler, and interpreter called the
virtual machine.
The compiler takes the source language and translates it to byte code while the virtual 
machines takes the byte code and runs it.
In addition to interpretering the virtual machine can also compile parts of the code to machine
code for performance boosts.
This is called *just in time* compiling.

Exercises for 1.1

1. What is the difference between a compiler and interpreter?

>   A compiler takes in a program, in its source language, and outputs the program 
>   in a new language, called the target language.
>   A compiler does not have to understand what the words mean.  It only need to
>   know how to translate it to the target langauge while keeping the semantics 
>   the same.
>
>
>   An interpreter takes in a source program, along with any neccessary input, and executes it.
>   An interpreter has to understand how to perform operations, such as addition.

2. What are the advantages of:
    1. A compiler over an interpreter? 
    2. An interpreter over a compiler?

>   A.  A compiler can translate the program to machine-language which can be, if properly
>       done, much faster than an interpreter.  In addition, the resource usage should be
>       smaller.
>
>   B.  An interpreter can provide better information for when errors occur.  In addition,
>       if a modification to the source program occurs the user can simply restarting 
>       execution of the program.  Additionally, it is much easier to provide a way to 
>       modify the source program during execution as well.  Interpreters usually provide  
>       garbage collection so resource management is more forgiving. 

3. What advantages are there to a language-processing system in which the compiler produces 
    assembly language rather than machine languages?

>   As long as an assembler exists for the assembly language we target on a machine we can
>   write programs for that machine.  Therefore, if the assembly language is popular then
>   our compiler is supported on multiple machines without us having to write our own assemblers
>   for each machine.

4. A compiler the translates a high-level language into another  high-level language is called a
    *source-to-source* translator.  What advantages are there to using C as a target language for
    a compiler?

    
>   C compilers exists for nearly all architectures.  In addition, C has been around for over 50
>   years and therefore C compilers are highly optimized.  This takes the complex optimization  
>   problems that you would have had to solve, and gives them to 50 years of optimizations.

5. Describe some of the tasks that an assember needs to perform.

>   The main job of an assembler is to take assembly code and convert it into its binary equivalnce
>   in machine code for the target machine.
>   It needs to be able to write the code in a format which the local operating system can load 
>   for execution.  It also converts the labels for jump instructions into their correct address.
>   Some assembly languages allow for macro functions, therefor those assemblers need to expand
>   those macros.


-------------------------------------

### 1.2  - The Structure of a Compiler ###

![Parts of a Compiler](./images/partsOfCompiler.png "Parts of a Compiler")

Inside of a compiler there are two parts: analysis and synthesis.
The analysis part breaks up the source program into constitent pieces and imposes a grammatical 
structure on them.
It then uses this structure to generate an *intermediate representation* of the source program.
If during analysis this structure is found to either be syntactically or semantically incorrect,
then a message must be presented to the programmer. 
During analysis information is also gathered and stored in what is called the **symbol table**, 
which along with the intermediate representation is passed to the synthesis part.

The synthesis portion of the compiler constructs the target program using the symbol table and 
intermediate representation.  
The analysis portion is usually called the frontend, while the synthesis portion is called the 
backend.


![Phases of Compilation](./images/phases.png "Phases of Compilation")


The compilation process is broken into *phases*, each which transforms one representation of the
source program to another.
Some phases are joined together in practice, such as the *lexical* and *syntax analyzers*.
Along with the new intermediate representation, the symbol table is passed along to the next
phase.
Some of the phases can be optimization phases which allows for better target programs to be 
generated.
Some optimizations are: efficient target programs, faster target programs, and smaller target
programs.

#### 1.2.1 - Lexical Analysis ####

The first phase of compilation is the lexical phase in which the source program is read in and 
tokenized.  The output is a stream of tokens, called lexemes, of the form:

```
<token-name,attribute-value>
```

The *token-name* is an abstract symbol used during syntax analysis.
The *attribute-value* points to an entry in the symbol table for this token.
The symbol table here would hold information related to the name, type, and raw value of the
lexeme.

Here is an example

```
position = initial + rate * 60
```

1. *position* is a lexeme that would be mapped to token `<id,1>`, where id the an abstract symbol 
    standing for *identifier*.  The numeric value 1 points to an entry in the symbol table for 
    position.
2. The assignment symbol *=* is a lexeme mapped to the token `<=>`, with the attribute-value 
    removed.  
3. *intial* is a lexeme that is mapped into the token `<id,2>`
4. *+* is mapped to `<+>`
5. *rate* is a lexeme mapped to `<id,3>`
6. *\** is mapped to to `<*>`
7.  *60* is a lexeme mapped to `<60>`

The final representation is

```
<id,1> <=> <id,2> <+> <id,3> <*> <60>
```

The full translation from the source program to a assembly program.  

![Full Translation](./images/fullTranslation.png "Full Translation")

#### 1.2.2  - Syntax Analysis ####

Given tokens, we need to perform *syntactic analysis* on them, also called *parsing*.
In this phase we take in a stream of tokens and create a new intermediate representation, usually what
is called a *syntax tree*, or *parse tree*.
This tree represents the syntactic structure of the source program, or token stream.
The typical representation is that interior nodes are operations, while leaves are values and identifiers.

#### 1.2.3  - Semantic Analysis ####

The semantic analyzer uses the syntax tree to symbol table to verify that the semantics of the 
source program are correct.
One important verification is called *type checking* which verifies that for an operation all the values 
used are of the correct type.
For example, with array indexing the parameter is required to be an integral value rather than a float.
Another example is the modulus operator, it requires that the values be integral as well.

In the language some type of conversions are possible, called *coercions*.
For example during multiplication one parameter is an integral value, while the other a floating point value.
The language allows for the integral value to be promoted to a floating point representation for this operation.
The type checker will add an extra node between the operator and value which signifies that it should be 
promoted or demoted as needed.

#### 1.2.4  - Intermediate Code Generation ####

<details>
    <summary>
        Three-address code
    </summary>
    <p>The three-address code makes it similar to assembly code.  </p>
</details>


Many compilers generate an explicit low-level or machine-like intermediate representation.
This representation has two properties: it should be easy to produce and easy to translate into 
the target machine language.
One such representation is called *three-address code*, which consists of a sequence of assembly 
like instructions with at most three operands per instruction.

Example:

```
t1 = inttofloat(60)
t2 = id3 * t1
t3 = id2 + t2
id1 = t3
```

Notice there are some properties about these operations.
Each instruction has at most one operator on the right side.
The instructions fix the order in which operations are to be done; the multiplications
precede the additions.
The compiler must generate temporary names to hold values computed by the instructions.

#### 1.2.5  - Code Optimization ####

Portions of code optimizations are machine independent.
These optimization phases can optimize a few alternative targets: size, speed, and resource utilization.

For an example we use the above code in section 1.2.4.
An example of an optimization is that at compile time a constant integral value can be 
converted to a floating value.
In addition, the variables `t2` and `t3` are only used to propagate values, they can be removed.

```
t1  = id3 * 60.0
id1 = id2 + t1
```

Code optimization can take a significant amount of time.
There exists some simple optimizations which can significantly improve running 
times while not taking too much time. 


#### 1.2.6  - Code Generation ####

Code generation takes the intermediate representation and converts it to the target langauge.
If the target is machine-code then registers and memory locations need to be selected.
One important role during code generation is judicious assignment of registers.

The previous example might be converted into the following code

```
LDF  R2,  id3
MULF R2,  R2, #60.0
LDF  R1,  id2
ADDF R1,  R1, R2
STF  id1, R1
```

#### 1.2.7  - Symbol-Table Management ####

<details>
    <summary>
        Symbol Table
    </summary>
    <p>
        The symbol table holds information about variables such as types and values if provided.
        In addition to information about the variables also the file, line number, position in 
        the line is included.  In addition we also keep track of the scope of the variables.
        Remember passed along during compilation.
    </p>
</details>

Symbol tables are data-structures used to contain information about variables used in the 
source program which can be quickly stored and retrieved.
Special variables such as functions extra information such as the number of parameters,
the types of each variables, the method of passing arguments, and types returned.


#### 1.2.8  - The Grouping of Phases into Passes  ####

Several phases might be grouped together into passes.
This is sometimes done to increase efficiency along with sharing information. 

#### 1.2.9  - Compiler Construction Tools ####

This includes ides, debuggers, versioning, profilers, test harnesses, etc.

<details>
    <summary>
        Tools
    </summary>
    <p>
    Some of these are confusing.
    </p>
</details>

1. Parser generators - Given a grammar produce a parser
2. Scanner generators - Produce lexical analyzers from regular expressions
3. Syntax-directed translation engines - produce collections of routines from the parse 
    tree and generate intermediate code
4. Code-generator generators - Produce a code generator from rules for translating each 
    operation into machine language.
5. Data-flow analysis engines - Facilitates gather information and how values are 
    transmitted from one part of a program.  This is critical for code optimization.
6. Compiler-construction toolkits - Integrated set of routines for constructing various 
    phases of a compiler.

### 1.3  - The Evolution of Programming Languages ###

#### 1.3.1 - The Move to Higher-level Languages ####

#### 1.3.2 - Impacts on Compilers ####

#### 1.3.3 - Exercises ####

1. Indicate each of the following terms:
    ```
    a) imperative b) declarative c) von Neumann
    d) object-oriented e) functional f) third-generation
    g) fourth-generation h) scripting
    ```    
apply to which of the following languages:
    ```
    1) C 2) C++ 3) Cobol 4) Fortran 5) Java
    6) Lisp 7) ML 8) Perl 9) Python 10) VB
    ```

### 1.4 -  The Science of a Building a Compiler ###

#### 1.4.1  - The Science of Code Optimization ####

### 1.5 - Applications of Compiler Technology ###

#### 1.5.1 - Implementation of High-Level Programming Languages ####

#### 1.5.2 - Optimizations for Computer Architecture ####

#### 1.5.3 - Design of New Computer Architectures ####

#### 1.5.4 - Program Translations ####

#### 1.5.5 - Software Productivity Tools ####

### 1.6 - Programming Language Basics ###

#### 1.6.1 - The Static/Dynamic Distinction ####

#### 1.6.2 - Environment and States ####

#### 1.6.3 - Static Scope and Block Structure ####

#### 1.6.4 - Explicit Access Control ####

#### 1.6.5 - Dynamic Scope ####

#### 1.6.5 - Dynamic Scope ####

#### 1.6.6 - Parameter Passing Mechanisms ####

#### 1.6.7 - Aliasing ####

#### 1.6.8 - Exercises ####

1. For the block-structured C code given below, indicate the values assigned to *w, x, y,* and *z*.
```
int w, x, y, z;
int i = 4, j = 5;
{
    int j = 7;
    i = 6;
    w = i + j;
}
x = i + j;
{
    int i = 8;
    y = i + j;
}
z = i + j;
```

2. Repeat with code below 
```
int w, x, y, z;
int i = 3, j = 4;
{
    int i = 5;
    w = i + j;
}
x = i + j;
{
    int j = 6;
    i = 7;
    y = i + j;
}
z = i + j;
```

3. Give the scope for each of the twelve declarations below
```
{   int w, x, y, z;     /* Block B1 */
    {   int x, z;          /* Block B2 */
        {   int w, x;      /* Block B3*/}
    }
    {   int w, x;          /* Block B4 */
        {   int y, z;      /* Block B5*/}
    }
}
```

4. What is printed with the code below
```
#define a (x+1)
int x = 2;
void b() { x = a; printf("%d\n", x);}
void c() { int x = 1; printf("%d\n", a);}
void main() { b(); c(); }
```

### 1.7 - Summary ###

1. Language Processors  
2. Compiler Phases
    * Syntactic Analysis
    * Semantic Analysis
    * Code Generation
3. Machine and Assembly Languages
4. Modeling in Compiler Design
5. Code Optimization
6. High-level languages
7. Compilers and Computer Architecture
8. Software Productivity and Software Security
9. Scope Rules
10. Environments
11. Block Structure
12. Parameter Passing
13. Aliasing

### 1.8 - References ###

1. Bergin, T.J. and R.G. Gibson, History of Programming Languages, ACM Press, New York, 1996

