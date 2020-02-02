#include "ExpressionManager.h"
#include <stack>
#include <string>
#include <vector>
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
  stack<string> checker;
  for(int i = 0; i < expression.size(); ++i) {
    string tester;
    tester += expression.at(i);
    if(isLeftParen(tester)) {
      checker.push(tester);
    }
    else if(isRightParen(tester)) {
      if(checker.empty()) {
        return false;
      }
      else if(!isPair(checker.top(), tester)) {
        return false;
      }
      else {
        checker.pop();
      }
    }
    tester = "";
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
  for(vector<string>::iterator itr = tokens.begin(); itr != tokens.end(); ++itr) {
    if(isInt(*itr)) {
      expression.push(*itr);
    }
    else if(isOperator(*itr)) {
      if(expression.size() < 2) {
        return "invalid";
      }
      string rightExp = expression.top();
      expression.pop();
      string leftExp = expression.top();
      expression.pop();
      string newExp = "( " + leftExp + " " + *itr + " " + rightExp + " )";
      expression.push(newExp);
    }
    else {
      return "invalid";
    }
  }
  if(expression.size() == 1) {
    return expression.top();
  }
  else {
    return "invalid";
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
  int nextInt;
  int right;
  int left;
  stack<int> expression;
  vector<string> tokens;
  tokens = parseTokens(postfixExpression);
  string returnStr;

  for(int i = 0; i < tokens.size(); ++i) {
    if(isInt(tokens.at(i))) {
      stringstream ss;
      ss.str(tokens.at(i));
      ss >> nextInt;
      expression.push(nextInt);
    }
    else if(isOperator(tokens.at(i))) {
      if(expression.size() < 2) {
        while(!expression.empty()) {
          expression.pop();
        }
        return "invalid";
      }
      right = expression.top();
      expression.pop();
      left = expression.top();
      expression.pop();
      nextInt = performCalculation(left, right, tokens.at(i));
      if(nextInt == NULL) {
        return "invalid";
      }
      expression.push(nextInt);
    }
    else {
      return "invalid";
    }
  }
  if(expression.size() == 1) {
    stringstream ss;
    ss << expression.top();
    returnStr = ss.str();
    return returnStr;   
  }
  else {
    return "invalid";
  }
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
  string postfix;
  stack<string> operators;
  vector<string> tokens = parseTokens(infixExpression);

  if(!isBalanced(infixExpression)) {
    cout << "Error expression not balanced" << endl;
    return "invalid";
  }

  for(vector<string>::iterator itr = tokens.begin(); itr != tokens.end(); ++itr) {
    if(isInt(*itr)) {
      postfix += *itr;
      postfix += " ";
    }
    else if(isOperator(*itr)) {
      if(!process_operator(operators, postfix, *itr)) {
    cout << "Error process_operator failed" << endl;
        return "invalid";
      }
    }
    else {
    cout << "Error invalid token" << endl;
      return "invalid";
    }
  }
  postfix.pop_back();
  if(postfixEvaluate(postfix) == "invalid") {
    cout << "Error invalid final expression" << endl;
    return "invalid";
  }
  return postfix;
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
      exp == "*" || exp == "/" || exp == "%" ||
      exp == "(" || exp == ")" || exp == "[" ||
      exp == "]" || exp == "{" || exp == "}") {
    return true;
  }
  else {
    return false;
  }
}

bool ExpressionManager::isInt(string exp) {
  for(int i = 0; i < exp.size(); ++i) {
    if(!isdigit(exp.at(i))) {
      return false;
    }
  }
  return true;
}

int ExpressionManager::performCalculation(int left, int right, string oper) {
  int returnInt;

  if(oper == "+") {
    returnInt = left + right;
  }
  else if(oper == "-") {
    returnInt = left - right;
  }
  else if(oper == "*") {
    returnInt = left * right;
  }
  else if(right == 0) {
    return NULL;
  }
  else if(oper == "/") {
    returnInt = left / right;
  }
  else if(oper == "%") {
    returnInt = left % right;
  }
  else {
    cout << "ERROR in performCalculation" << endl;
    return NULL;
  }

  return returnInt;
}

bool ExpressionManager::isLeftParen(string t) {
  if(t == "(" || t == "[" || t == "{") {
    return true;
  }
  return false;
}

bool ExpressionManager::isRightParen(string t) {
  if(t == ")" || t == "]" || t == "}") {
    return true;
  }
  return false;
}

bool ExpressionManager::isPair(string left, string right) {
  if(left == "(" && right == ")" ||
      left == "[" && right == "]" ||
      left == "{" && right == "}") {
    return true;
  }
  return false;
}

int ExpressionManager::precedence(string oper) {
  if(oper == ")" || oper == "]" || oper == "}") {
    return 3;
  }
  else if(oper == "*" || oper == "/" || oper == "%") {
    return 2;
  }
  else if(oper == "+" || oper == "-") {
    return 1;
  }
  else if(oper == "(" || oper == "[" || oper == "{") {
    return 0;
  }
  else {
    return -1;
  }
}

bool ExpressionManager::process_operator(stack<string> &opStack, string &postfix, string &op) {
  if(opStack.empty() || isLeftParen(opStack.top()) || isLeftParen(op)) {
    opStack.push(op);
    return true;
  }
  else if(isRightParen(op)) {
    while(!isPair(opStack.top(), op)) {
      postfix += opStack.top() + " ";
      opStack.pop();
      if(opStack.empty()) {
        return false;
      }
    }
    opStack.pop();
    return true;
  }
  else {
    while(precedence(op) <= precedence(opStack.top())) {
      postfix += opStack.top() + " ";
      opStack.pop();
    }
    postfix += opStack.top();
    opStack.pop();
    return true;
  }
}
