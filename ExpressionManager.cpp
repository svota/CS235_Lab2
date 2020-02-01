#include "ExpressionManager.h"
#include <stack>
#include <string>

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

    if(tester == ')' || tester == ']' || tester == '}') {
      if(checker.empty() ||
          checker.top() == '(' && tester != ')' ||
          checker.top() == '[' && tester != ']' ||
          checker.top() == '{' && tester != ']') {
        return false;
      }
      else {
        checker.pop();
      }
    }
  }
  return true;
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
  return "true";
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
string ExpressionManager::postfixEvaluate(string postfixExpression);
  cout << "PostfixEvaluate " << postfixExpression << endl;
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
