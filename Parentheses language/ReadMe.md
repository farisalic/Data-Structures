# Parentheses based "programing language" project
This project showcases another usecase of *Stack* LIFO (Last In - First Out) data structure. This so-called language contains only parentheses and in order to compile successfully it must have all the parentheses inserted correctly. For the expression to be regular, each open parenthesis must have its matching close parenthesis, and the parenthesis hierarchy must be respected. Brackets follow a hierarchy: square brackets <> are the highest inner brackets, then round (), then square [], then curly {}. 

In other words, a curly brace cannot be opened inside another type of brace. Square brackets [] cannot be opened inside curly () or square <> brackets, but can be opened inside curly braces. A round bracket cannot be opened inside a pair of square brackets <>. It is necessary to load lines from standard input, where each line represents one expression.
The input characters are some of '[ ] ( ) { } < >'. Only "good" or "wrong" should be printed on the output. 

The program ends by reading all the characters from the input, that is, when the user ends the input by sending the EOF character.
