
#include "prefix.h"

//-----------------------------------------------------------------------------
// constructor
// initialize the array to the empty string 
// char arrays are terminated with '\0' so operator<< works properly

Prefix::Prefix() {
   expr[0] = '\0'; 
} 

//-----------------------------------------------------------------------------
// setPrefix
// Set a prefix expression made of single digit operands, operators +,-,*,/
// and no blanks or tabs contained in a file. The expression is valid in
// that each operator has two valid operands.

void Prefix::setPrefix(ifstream& infile) { 
    infile >> expr;
}

//-----------------------------------------------------------------------------
// evaluatePrefix 
// Evaluate a prefix expr made of single digit operands and operators +,-,*,/

int Prefix::evaluatePrefix() const {
    if (expr[0] == '\0') 
        return 0;

    int index = -1;                               // to walk through expr
    return evaluatePrefixHelper(index);
}

//-----------------------------------------------------------------------------
// evaluatePrefixHelper
// This function recursivly evaluates each value and returns the value of the expression
int Prefix::evaluatePrefixHelper(int& index) const {
    char symbol = expr[++index];
    
	if(isdigit(symbol))
	{
		return symbol - '0'; 
	}

	switch(symbol)
	{
		case '+':
			return evaluatePrefixHelper(index) + evaluatePrefixHelper(index);
			break;

		case '-':
			return evaluatePrefixHelper(index) - evaluatePrefixHelper(index);
			break;

		case '*':
			return evaluatePrefixHelper(index) * evaluatePrefixHelper(index);
			break;

		case '/':       
			if(expr[index + 2] == '0')  //This handles a divide by zero error and returns a 0 for the expression
			{
				cout << "\n== Cannot divide by zero! ==\n\n";
				return 0;
			}

			return evaluatePrefixHelper(index) / evaluatePrefixHelper(index);
			break;

		case NULL:
			return 0;
			break;

		default:
			cout << "Invalid input!\n";
			return 0;
			break;
	}
}

//-----------------------------------------------------------------------------
// outputAsPostfix, toPostfix
// Convert prefix expression to postfix and output

void Prefix::outputAsPostfix(ostream& out) const {
    if (expr[0] == '\0') 
        return;

    int index = -1;                           // to walk through expr
    int count = -1;                           // used to build postfix array
    char postfix[MAXSIZE];
    toPostfix(index, postfix, count);
    postfix[++count] = '\0';
    out << postfix;
}

//-----------------------------------------------------------------------------
// toPostFix 
// This function takes a prefix expression converts it to a post fix expression in
// a seperate char array
void Prefix::toPostfix(int& index, char postfix[], int& count) const 
{
    char symbol = expr[++index];
    
	if(isdigit(symbol))
	{
		count++;
		postfix[count] = symbol;
	}
	else if(symbol == '/' || symbol == '*' || symbol == '-' || symbol == '+')
	{      
		toPostfix(index, postfix, count);
		toPostfix(index, postfix, count);
		count++;
		postfix[count] = symbol;   
	}
	else return;

}

//-----------------------------------------------------------------------------
// operator<<
// display prefix expression as a string (char array)

ostream& operator<<(ostream& output, const Prefix& expression) {
    output << expression.expr;
    return output;
}

