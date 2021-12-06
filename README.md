# kennison-cop3330-ch07-ex01-03 user guide

calculator.cpp functions as a standard calculator with a few extra benefits.

I chose to implement the drill from the chapter as well so there are some key differences from the
given calculator program. The biggest being the change of the quit and declaration keywords. They
are further discussed below.

<-- Semicolon preface -->

No matter what input you give it must be followed by a semicolon. The semicolon serves a very
important purpose in this program as it signifies the end of a statement or expression and
that it is ready to print; without it's inclusion the program will not function correctly

<-- standard four function use (plus modulo) -->

When launched the user will be prompted with "> ".

This means that you may enter a statement or expression.

You may enter any basic four function expression, or even a modulo expression followed by a semicolon.

Examples of four function input:
1) 1+5;
2) 2 * 10;
3) 3 /3;
4) 10 - 7;
5) 15% 5;
6) 6;

You can even input multiple statements or expression in the same line if you so please (EX: 1+1; 2-3; 5*6;

all will be computed and output in the order they were entered.

<-- fancy keywords and functions -->

Other than the basic four functions, there are also five keywords important to the program.
Those being "#", "const", "sqrt", "pow", and "exit". The details of each can be found below

1) '#' (and or the declaration keyword)
  by using the keyword "#" you store a specific value into a variable you can name.
  Simply start your line with "#" followed by your desired name "=" and the value you want.
  ("# <name> = <value>;"). For the value section you may also enter an expression or a 
  previously defined variable or constant. Once declared, the output will clarify it's value.
  
  Examples of input following the "#" keyword:
  1) '#' x = 10;
  2) '#' y = 20*5;
  3) '#' g = y;
  
  (ignore the '' hashtag enlarges text in readme files on github apparently)
  
  Variables also have another function. Their values can be reassigned later in the program.
  To do so you just input its name followed by "=" and the new value. 
  ("<existing variable> = <new value>;").
  
  Example of changing a variables value:
  1) x = 5;
  2) y = 5 + y;
  3) g = 10 * 6;

2) const (the constant declaration keyword)
  By using const you can essentially declare a variable that cannot be changed later in the program.
  To do so just input const followed by the desired name "=" the value you want.
  ("const <name> = <value>;").
  
  Examples of input following the const keyword:
  1) const x = 10;
  2) const y = 20*5;
  3) const g = y;
  
3) sqrt (the square root function key word)
  By using the keyword sqrt you can find the square root of a given input. To do so input sqrt 
  followed by "(" your given value and ")". ("sqrt(<value>);")
  
  Examples of input following the sqrt keyword:
  1) sqrt(25);
  2) sqrt(6 + 3);
  3) sqrt(x); // where x is a pre established variable or constant
  
4) pow (the exponent function key word)
  By using the keyword pow you can find the power of any number, given that it is to the power of 
  a positive integer. Because of this restriction, variables and constants may not be used as 
  the second variable in this functionTo do so input pow followed by "(" your given number "," any
  postive integer ")". ("pow(<value>, <positive integer>);"). 
  
  Examples of input following the pow keyword:
  1) pow(5, 2);
  2) pow(x, 5); // where x is a pre established variable or constant
  3) pow(6,10);
  
5) exit (the quit keyword)
  By using this keyword you can quit the calulator program. Preferrably input exit followed by a 
  semicolon. If not done you will be prompted to enter a character to exit the program.
  
  Examples of input using the exit keyword:
  1) exit;
  2) exit
  
<-- Intense Math -->
  Using everything discussed above you can insert some quit complex inputs into the calulator.
  
  An example of more advanced input being:
  Ex) # x = 10; const y = 5; x = pow(sqrt((x*2)+y), 4); x + 5;
  
 
