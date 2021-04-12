# barrel

A wacky esoteric programming language. I was inspired to write an esolang after randomly writing a [Small](https://esolangs.org/wiki/Small) interpreter and came up with this.

`barrel` is a simple, Turing-incomplete (probably) language with simple instructions. `barrel` programs have access to an integer accumulator ("the" accumulator), a decimal accumulator, a decimal stack, 32 integer registers, and a random number generator. `barrel` programs can also output anything, but cannot currently input anything.

Here is a list of instructions for `barrel`. This list may change at any time. Anything that `barrel` does not understand will be implicitly printed.

`+` - increase the accumulator  
`-` - decrease the accumulator  
`±` - toggles the sign of the accumulator
`a` - access the accumulator. This is a valid substitue for an actual number anywhere  
`d` - access the decimal accumulator. This is a valid substitue for an actual number anywhere  
`p` - print operator (prints the accumulator as a character value)  
`n` - print operator (prints the accumulator as an integer value)  
`√` - if the accumulator is greater than or equal to zero, sets the accumulator to the square root of the accumulator  
`…` - does nothing; useful for a "continue" statement
`^N` - set the accumulator to value N  
`|` - generate a random number  
`[` - push the accumulator onto the stack  
`]` - pop the top of the stack into the accumulator. If the stack is empty, a random number will be popped into the accumulator  
`{N` - push N onto the stack  
`}` - pop and discard the top of the stack  
`@N` - accesses register N (zero-indexed, 0 is the top). If location N is not filled, a random number will be returned  
`&N:X` - set register N (zero-indexed) to X. This is handy for toggling certain behaviors  
`#NX` - run instruction X N times (example: #3+ will increase the accumulator by 3). X must be only one character  
`!` - exit with code 0  
`'z'` - denotes a string literal of value z which will be printed immediately and discarded. May be any length. Escaping a ' in the middle is not allowed. Strings implicitly close (e.g. +++'z implies +++'z')  
`<N` - jump backwards N characters starting from the <. This does not take into account multi-character instructions (e.g. #3+<1 will not skip back to the #, instead putting +<1 in the instruction queue)  
`>N` - same as <N, but jumps forwards instead of backwards  
`?X$Y$Z$` - if X, then do Y. Otherwise, do Z. X can be 'T'rue or 'F'alse, or a number (read: the accumulator). Y and Z may be empty  

Fraction characters (e.g. "½") will expand to their literal decimal value when entered.

The `barrel` interpreter is written mostly in Qt. Warning: when exiting, the interpreter will probably crash due to a bug relating to threading.
