<style>
    body {
        width: 700px;
        margin-left: auto;
        margin-right: 75px;
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
        left: 15px;
        max-width: 215px;
    }

</style>

# Compilation Notes #

## Summary ##

1. Phases of Compilation

## Phases of Compilation

The three phases of compilation are **syntactic analysis**, **contexual analysis**, and **code generation**.
Syntactic analysis is where the source code is parsed to validate that it conforms with the source languages syntax and determine its phase structure. 
Contexual analysis checks to make sure the source code conforms to the contexual constraints of the languages, such as type and scope rules.
Code generation deals with converting the validated source code into some output language, machine code or byte code, which conforms to the semantic rules of the language.  

The input of the syntactic phase is the contents of the source file, the output is usually an abstract syntax tree (AST).
The subtrees correspond to the phrases (commands, expressions, declarations, etc) of the source program.
The leaf nodes correspond to identifiers, literals, and operators after all other terminal symbols have been discarded.  

### Syntactic



### Contexual

### Code Generation