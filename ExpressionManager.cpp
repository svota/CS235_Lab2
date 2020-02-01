#include "ExpressionManager.h"
#include <stack>
#include <string>
#include <sstream>

using namespace std;

/*
* Checks whether an expression is balanced on its parentheses
*
* - The given expression will have a space between every number or operator
*
* @return true if expression is balanced
* @return false otherwise
*/

bool ExpressionManager::isBalanced(string expression) {
  stack <char> checker;
  for(int i = 0; i < expression.size(); ++i) {
    char tester = expression.at(i);
    if(tester == '(' || tester == '[' || tester == '{') {
      checker.push(tester);
    }
    else if(tester == ')' || tester == ']' || tester == '}') {
      if(checker.empty()) {
        return false;
      }
      else if(checker.top() == '(' && tester != ')' ||
          checker.top() == '[' && tester != ']' ||
          checker.top() == '{' && tester != '}') {
        return false;
      }
      else {
        checker.pop();
      }
    }
  }
  if(checker.empty()) {
    return true;
  }
  else {
    return false;
  }
}
        

      

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
string ExpressionManager::postfixToInfix(string postfixExpression) {
  cout << "PostfixToInfix " << postfixExpression << endl;
  stack<string> expression;
  vector<string> tokens;
  tokens = parseTokens(postfixExpression);
  for(iterator itr = tokens.begin(); itr != tokens.end(); ++itr) {
    if(isdigit(*itr->at(0)) {
      tokens.push(*itr);
    }
    else if(isOperator(*itr)) {
      string rightExp = tokens.top();
      tokens.pop();
      string leftExp = tokens.top();
      tokens.pop();
      string newExp = "(" + leftExp + " " + *itr + " " + rightExp + ")";
      tokens.push(newExp);
    }
  }
  if(tokens.size() == 1) {
    return tokens.top();
  }
  else {
    return "Error";
  }
}


/*
* Evaluates a postfix expression returns the result as a string
*
* - The given postfix expression will have a space between every number or operator.
* - Check lab requirements for what will be considered invalid.
*
* return the string "invalid" if postfixExpression is not a valid postfix Expression
* otherwise, return the correct evaluation as a string
*/
string ExpressionManager::postfixEvaluate(string postfixExpression) {
  cout << "PostfixEvaluate " << postfixExpression << endl;
  stack<char> expression;
  vector<string> tokens;
  tokens = parseTokens(postfixExpression);
  for(iterator itr = tokens.begin(); itr != tokens.end(); ++itr) {
    if(isdigit(*itr->at(0)) {
      stringstream ss;
      int nextint
      ss.str(*itr);
      ss >> nextint;
      operands.push(nextint);
    }
    else if(isOperator(*itr)) {
    // continue here
      cout << "is operator" << endl;
    }
  return "true";
}

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
string ExpressionManager::infixToPostfix(string infixExpression) {
  cout << "InfixToPostFix " << infixExpression << endl;
  return "true";
}

vector<string> ExpressionManager::parseTokens(string expression)
{
  stringstream ss(expression);
  string token;
  vector<string> tokens;
  while(getline(ss, token, ' '))
  {
    tokens.push_back(token);
  }
  return tokens;
}

bool ExpressionManager::isOperator(string exp) {
  if(exp == "+" || exp == "-" || 
      exp == "*" || exp == "/" || exp == "%") {
    return true;
  }
  else {
    return false;
  }
}
