#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "ExpressionManagerInterface.h"

using namespace std;


class ExpressionManager
{
public:
	ExpressionManager() {}
	virtual ~ExpressionManager() {}

	/*
	* Checks whether an expression is balanced on its parentheses
	*
	* - The given expression will have a space between every number or operator
	*
	* @return true if expression is balanced
	* @return false otherwise
	*/

	bool isBalanced(string expression);

	/**
	* Converts a postfix expression into an infix expression
	* and returns the infix expression.
	*
	* - The given postfix expression will have a space between every number or operator.
	* - The returned infix expression must have a space between every number or operator.
	* - Redundant parentheses are acceptable i.e. ( ( 3 * 4 ) + 5 ).
	* - Check lab requirements for what will be considered invalid.
	*
	* return the string "invalid" if postfixExpression is not a valid postfix expression.
	* otherwise, return the correct infix expression as a string.
	*/
	string postfixToInfix(string postfixExpression);

	/*
	* Evaluates a postfix expression returns the result as a string
	*
	* - The given postfix expression will have a space between every number or operator.
	* - Check lab requirements for what will be considered invalid.
	*
	* return the string "invalid" if postfixExpression is not a valid postfix Expression
	* otherwise, return the correct evaluation as a string
	*/
	string postfixEvaluate(string postfixExpression);

	/*
	* Converts an infix expression into a postfix expression
	* and returns the postfix expression
	*
	* - The given infix expression will have a space between every number or operator.
	* - The returned postfix expression must have a space between every number or operator.
	* - Check lab requirements for what will be considered invalid.
	*
	* return the string "invalid" if infixExpression is not a valid infix expression.
	* otherwise, return the correct postfix expression as a string.
	*/
	string infixToPostfix(string infixExpression);

private:
  /*
  * Converts a string into a vector of tokens
  */
  vector<string> parseTokens(string expression);

  // Checks if a string is an operator
  bool isOperator(string exp);

  // Checks if a string is a set of digits (an int)
  bool isInt(string exp);

  // Performs a calculation with two ints and a string for the operator.
  // Error if the operator is not supported
  int performCalculation(int left, int right, string oper);

  // Checks if a string is a left parenthesis
  bool isLeftParen(string t);

  // Checks if a string is a right parenthesis
  bool isRightParen(string t);

  // Checks that the strings form a pair of parentheses
  bool isPair(string left, string right);
  
  // Returns the numeric precedence of an operator
  int precedence(string oper);

  // Processes operators for infix to postfix conversion
  bool process_operator(stack<string> &opStack, string &postfix, string &op);
};
