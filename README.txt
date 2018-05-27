roll V0.1.2

This is a simple, command-line electronic dice tool, suitable for roleplaying
games.  It began as a simple project for personal convenience and to experiment
with the lex and yacc tools, but it has since grown significantly in scope.

Following is an informal summary of how to operate the program.  Anything
preceded by an octothorpe character ('#') is a comment and would be ignored
by the parser if it were input.


=== ROLLING DICE ===
To roll dice, write the roll you want to make in standard die notation, e.g.:
> 3d6   # roll three six-sided dice
> 1d4   # roll one four-sided die 

If you only want to roll one die, the preceding '1' may be omitted:
> d20   # roll one twenty-sided die

The string "d%" is accepted as a synonym for "1d100":
> d%    # roll one one-hundred-sided die

You are not limited to the dice that are geometrically possible in real life,
you may roll dice with any natural number of faces:
> d13
> d47
> d23

Similarly, as in the GURPS books, the following '6' may be omitted for rolls
only involving six-sided dice:
> 3d    # roll three six-sided dice

Do note, however, that a lone letter 'd' is not accepted as a synonym for 1d6.

The letter d is considered its own operator, the 'dice operator', and is thus
not sensitive to whitespace between it and its operands; '3 d 6' is the same as
'3d6'. Both capital and minuscule d's are supported.

If you want to see an actual list of the dice that were rolled, turn on the
'verbose' setting (see below).


== ARITHMETIC OPERATIONS ==
Addition, subtraction, multiplication, and (integer) division may be used to
modify the result of a roll:
> 1d4 + 1   # roll 1d4 and add 1 to the result
> 5 + d20   # roll 1d20 and add 5 to the result
> 2d6 - 2   # roll 2d6 and subtract 2 from the result
> 1d4 * 4   # roll 1d4 die and multiply the result by 4
> 3d8 / 2   # roll 3d8 and divide the result by 2

Neither operand need be constant:
> 1d6 + 1d8 # roll 1d6 and 1d8 and add the results of the two dice together

If desired, "rolls" consisting only of constant arithmetic may be made:
> 4 + 6     # add 4 to 6, yielding 10

Standard order of operations is followed, with the dice operator taking the
highest precedence. Parentheses are allowed for explicit association:
> 1d6 * 2 + 4   # roll 1d6, multiply the result by 2, and add 4 to that result
> 1d6 * (2 + 4) # roll 1d6 and multiply it by the sum of 2 and 4

The numbers on either side of the dice operator may be replaced with explicitly
associated expressions, which may themselves include die rolls:
> (3d6)d10  # roll a number of d10 determined by a roll of 3d6
> 3d(1d6)   # roll 3 dice with a number of sides determined by a roll of 1d6


=== CHECKS ===
Checks are boolean expressions expressed in the form of a mathematical
inequality:
> 1d6 > 3       # success if the value of a roll of 1d6 is greater than 3
> 1d20 >= 15    # success if the value of a roll of 1d20 is greater than 15
> d% <= 33      # a check with a 33% chance of success

Note that stringing together inequalities, e.g. "1 < 2 < 3 ..." is not
implemented and may produce unexpected results.
