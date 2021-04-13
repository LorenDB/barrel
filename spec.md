# The barrel spec
`barrel` is a simple, Turing-incomplete (probably) language with simple instructions. Barrel programs have access to a decimal accumulator, a decimal stack, 32 decimal registers, and a random number generator. Furthermore, barrel has good support for functions. Barrel programs can also output various values, but cannot currently input anything.

## Definitions
Decimal numbers shall be defined to be equivalent to a C++ `long double`. This allows a large range of values to be used in barrel.

## The accumulator
The accumulator is the heart of a barrel program's calculations. It is the only method of performing mathematical operations on a number, and normally stores the value that is being manipulated or examined. The accumulator may be incremented, decremented, added to, subtracted from, multiplied, divided, squared, square-rooted, negated, bitwise-shifted, equality-compared, primality-tested, and otherwise modified and accessed. The accumulator can store decimal numbers or integers.

## The stack
Barrel programs have access to a decimal stack, limited in size only by your system's hardware. Any value may be pushed onto the stack at any time; however, only the top value may be accessed without modifying the stack. Behavior when a program attempts to pop a value from an empty stack is undefined. The interpreter may return a random value, halt the program, return a default value, or otherwise behave as the author of the interpreter deems best.

## The registers
The 32 decimal registers are useful for storing items that you want guaranteed access to later, as opposed to the top-only access behavior of the stack. The state of the registers at startup is undefined. They may be uninitialized or initialized to a certain value.

## Commands
Below is a list of instructions for barrel. This list may change at any time. Anything that barrel does not understand will be implicitly printed. In this list, `N`, `X`, `Y`, and `Z` imply values or instructions that are passed to the operator and are not actually part of the operator unless specified.

If an instruction does not seem to perform as this table specifies, please ensure that you are using the correct character—some of the characters in this table look similar to each other, but have different Unicode values. To this end, Unicode values are provided in hexadecimal.

|Instruction|Unicode value     |What it does                                                                  |
|-----------|------------------|------------------------------------------------------------------------------|
|`+`        |`U+002B`          |Increases the accumulator.                                                    |
|`-`        |`U+002D`          |Decreases the accumulator.                                                    |
|`^N`       |`U+005E`          |Sets the accumulator to value `N`.                                            |
|`±`        |`U+00B1`          |Toggles the sign of the accumulator.                                          |
|`√`        |`U+221A`          |Square roots the accumulator if it is not negative.                           |
|`¶`        |`U+00B6`          |Prints a newline.                                                             |
|`|`        |`U+007C`          |Sets the accumulator to a random integer value.                               |
|`…`        |`U+2026`          |Does nothing. Useful for a "continue" statement.                              |
|`[`        |`U+005B`          |Pushes the accumulator's value onto the stack.                                |
|`]`        |`U+005D`          |Pops the top of the stack into the accumulator.                               |
|`{N`       |`U+007B`          |Pushes `N` onto the stack.                                                    |
|`}`        |`U+007D`          |Pops and discards the top of the stack.                                       |
|`@N`       |`U+0040`          |Accesses register N.                                                          |
|`'N'`      |`U+0027`          |Prints a string with value `N`. Strings are self-closing (e.g. `'N` -> `'N'`).|
|`!`        |`U+0021`          |Exits the program with code `0`.                                              |
|`#NX`      |`U+0023`          |Runs instruction X N times. X is currently limited to one instruction.        |
|`n`        |`U+006E`          |Prints the accumulator as a decimal value.                                    |
|`p`        |`U+0070`          |Prints the accumulator as a character.                                        |
|`a`        |`U+0061`          |Accesses the accumulator. This is a valid substitute for an acutal number.    |
|`&N:X`     |`U+0026`, `U+003A`|Sets register N to have a value of `X`.                                       |
|`?X:Y:Z:`  |`U+003F`, `U+003A`|If X is true, executes Y; otherwise, executes Z. Y and Z may be empty.        |
|`✓`        |`U+2713`          |Evaluates to `true`.                                                          |
|`❌`        |`U+274C`          |Evaluates to `false`.                                                         |
|`π`        |`U+03C0`          |Evaluates to the mathematical constant `pi` (`3.14159...`)                    |
|`e`        |`U+0065`          |Evaluates to the mathematical constant `e` (`2.718281828...`)                 |
|`¤`        |`U+00A4`          |Defines a location that can be jumped to.                                     |
|`↓`        |`U+2193`          |Pushes the current location to the LP stack.                                  |
|`↑`        |`U+2191`          |Pops the top of the LP stack and goes there.                                  |
|`→N`       |`U+2192`          |Jumps forward N jump locations after pushing the current location.            |
|`←N`       |`U+2190`          |Jumps backward N jump locations after pushing the current location.           |

## Numbers
As you may have noticed, barrel defines various accessors and constants (`π`, `a`, `@1`, etc.). However, there are other ways of coding in numbers. Fraction characters will expand to their literal decimal value (e.g. `½` expands to `0.5`). Also, if a non-digit is given where a number is expected, e.g. `^T`, barrel will simply use the Unicode value of that character. In the example given in the previous sentence, barrel would push the value `84` into the accumulator since the character `T` has the ASCII value `84`.

## Jumping
As shown in the command table, barrel has support for jumping to predefined positions. It also supports pushing arbitrary locations to a stack and jumping to them later. This is best used for the equivalent of a function call. For example, take this snippet: `¤#@0+↑` This is a barrel function which will add the value in register 0 to the accumulator. Functions in barrel don't have names; they must be accessed by doing a jump. Therefore, if you have a program that looks like `&0:10→1n¶→1n¶!¤#@0+↑`, it will call the trailing function twice before exiting. The `→` command, of course, implicitly pushes the current location onto the stack. The `↑` command will return execution to the previous point.

You should be careful about getting your function calls right; however, if you try to jump farther than the number of functions you have (`&0:10→1n¶→3n¶!¤#@0+↑`), barrel will jump as far as possible and then stop.
