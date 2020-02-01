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
    cout << "loop number " << i << " testing " expression.at(i) << endl;
    if(tester == '(' || tester == '[' || tester == '{') {
      checker.push(tester);
      cout << "    pushed" << endl;
    }
    else if(tester == ')' || tester == ']' || tester == '}') {
      if(checker.empty()) {
        cout << "     False: close paren on empty stack" << endl;
        return false;
      }
      else if(checker.top() == '(' && tester != ')' ||
          checker.top() == '[' && tester != ']' ||
          checker.top() == '{' && tester != ']') {
        cout << "     False: paren does not match" << endl;
        return false;
      }
      else {
        checker.pop();
        cout << "  Removing top of stack: parenthesis match" << endl;
      }
    }
  }
  if(checker.empty()) {
    cout << "True: All paren match" << endl;
    return true;
  }
  else {
    cout << "False: extra open paren" << endl;
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
string ExpressionManager::postfixEvaluate(string postfixExpression) {
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
