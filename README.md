# Zekin (developing)

Zekin is a naive scheme interpreter wrote in C.

To learn how to make an interpreter , I started the project.

## Feature :

   1. Tail Call Optimization
   2. Simple macro (may improve it after I finishing SICP)
   3. Multi-line comment (`#| multi-line |#`)
   4. Interesting functions
   5. A simple library manage mechanism
   6. Friendly interative mode (GNU readline)
   [Key binding list](http://readline.kablamo.org/emacs.html)

## Requirements :

   1. GCC
   2. [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)

## Install :
```bash
   make
```

## Usage :
```shell
   usage: zekin [-e exprs] [-h] [-i] [-v] [-l] [file ...]

   Yet another scheme interpreter

   positional arguments:
      file   scheme script to run

   optional arguments:
      -i     run file interactively

      -e     eval expressions and exit

      -v     information about version

      -l     show library path defined

      -h     show this help message and exit
```

## Goals :

#### General :

> 1. Macro
>
> 2. System calls
>
> 3. Provide some interesting functions to observe the ecology
>
> 4. Do some interesting optimizations
      (symbol , gc , TCO , any opt about speed and space)


#### Optional :

> 1. escape char in string (numberical , like \x \o ...)
>
> 2. more types , i.e. char , big number (8 byte current) , rational ...
>
> 3. string operations
>
> 4. support printf function
>
> 5. implement continuation

#### Final :

> Run repl.ss (scheme interpreter wrote in scheme) by using zekin

## Todo :

> 1. consider syntax expansion speed (cond vs if) [ done ]
>
> 2. consider the expressions below
> ```scheme
>    (define f (lambda (x) (if (= x 0) 0 (+ x (f (- x 1))))))
>    (f 100000) ; Can I opt it to tail call? (Do I need CPS?)
> ```
>
> 3. add let family , `let\*` , `letrec` ...
>
> 4. figureout `syntax-rules` and improve ( rewrite ) macro
>
> 5. consider tco , when apply a closure ,
      with non-lambda args , can I just update without new a env?

##  Reference :

#### Primary
```
; operators

'%               : <procedure:%>
'*               : <procedure:*>
'+               : <procedure:+>
'-               : <procedure:->
'/               : <procedure:/>
'mod             : <procedure:mod>

; boolean functions , predictors

'<               : <procedure:<>
'<=              : <procedure:<=>
'=               : <procedure:=>
'>               : <procedure:>>
'>=              : <procedure:>=>
'eq?             : <procedure:eq?>
'eqv?            : <procedure:eqv?>
'equal?          : <procedure:equal?>

'not             : <procedure:not>
'env?            : <procedure:env?>
'void?           : <procedure:void?>
'null?           : <procedure:null?>
'pair?           : <procedure:pair?>
'list?           : <procedure:list?>
'exact?          : <procedure:exact?>
'number?         : <procedure:number?>
'integer?        : <procedure:integer?>
'symbol?         : <procedure:symbol?>
'string?         : <procedure:string?>
'boolean?        : <procedure:boolean?>
'closure?        : <procedure:closure?>
'procedure?      : <procedure:procedure?>

; ctor , list

'car             : <procedure:car>
'cdr             : <procedure:cdr>
'cons            : <procedure:cons>
'void            : <procedure:void>
'length          : <procedure:length>


; environment

'eval            : <procedure:eval>
'apply           : <procedure:apply>
'global          : <environment>
'get-env         : <procedure:get-env>
'get-curenv      : <procedure:get-curenv>
'lookup-symbol   : <procedure:lookup-symbol>

; syntax

'if              : <syntax:if>
'quote           : <syntax:quote>
'define          : <syntax:define>
'lambda          : <syntax:lambda>
'set!            : <syntax:set!>
'set-car!        : <syntax:set-car!>
'set-cdr!        : <syntax:set-cdr!>
'syntax-rules    : <syntax:syntax-rules>

; io , system

'gc              : <procedure:gc>
'exit            : <procedure:exit>
'read            : <procedure:read>
'source          : <procedure:source>
'system          : <procedure:system>
'display         : <procedure:display>
'flush-output    : <procedure:flush-output>
```

#### Library
```
'or              : <macro>
'and             : <macro>
'cond            : <macro>
'case            : <macro>
'let             : <macro>
'begin           : <macro>

'caar            : <closure>
'cadr            : <closure>
'cdar            : <closure>
'cddr            : <closure>
'caaar           : <closure>
'caadr           : <closure>
'cadar           : <closure>
'caddr           : <closure>
'cdaar           : <closure>
'cdadr           : <closure>
'cddar           : <closure>
'cdddr           : <closure>
'caaaar          : <closure>
'caaadr          : <closure>
'caadar          : <closure>
'caaddr          : <closure>
'cadaar          : <closure>
'cadadr          : <closure>
'caddar          : <closure>
'cadddr          : <closure>
'cdaaar          : <closure>
'cdaadr          : <closure>
'cdadar          : <closure>
'cdaddr          : <closure>
'cddaar          : <closure>
'cddadr          : <closure>
'cdddar          : <closure>
'cddddr          : <closure>

'map             : <closure>
'fold            : <closure>
'filter          : <closure>

'list            : <closure>
'range           : <closure>
'assoc           : <closure>
'append          : <closure>
'indexof         : <closure>

'odd?            : <closure>
'even?           : <closure>

'show            : <closure>
'print           : <closure>
'newline         : <closure>
```
