# CalculatorCpp
create application for calculating base expressions

# Run
1. cmake
2. make
3. run your binary file after step 2 with argument. Where argument is your math expression wgere each characters derive from other with space. For example 
   ./Calculator ( 6 + 7 ) * 2

# Support basic operation

1. binary minus
2. binary plus
3. binary multiplier
4. binary divider
5. unary minus
6. unary plus
7. bracket expression
8. support calculating expression if multiplier was missed

This operators have base priority. See core/Token.h. For example unary minus has base_priority = 100

# Unsupport calculating follow expressions:

1. 1 * * 1             //not realize unary multiplier
2. 1 / / 1             //not realize unary divider

Also for calculating you should create instance of CalculatorNew class and call metode (std::string expression) or calculateDangerous(std::string expression), where 
calculateDangerous(std::string expression) not handling error, but operator (std::string expression) handling error

# Input requirements

Input expression must meet the following requirements:

1. Each characters must separate from another characters space or spaces. For example ( 6 + 7 ) + 8. For detail see file ./test/Calculator_tests.cpp
