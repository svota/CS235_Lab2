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
  Converts an infix expression into a postfix expression
  and returns the postfix expression
  - The given infix expression will have a space between every number or operator.
  - The returned postfix expression must have a space between every number or operator.
  - Check lab requirements for what will be considered invalid.
  return the string "invalid" if infixExpression is not a valid infix expression.
  otherwise, return the correct postfix expression as a string.
*/
string ExpressionManager::infixToPostfix(string infixExpression) {
cout << "InfixToPostFix " << infixExpression << endl;
  // Initialize postfix to an empty string
  string postfix;
  // Initialize the operator stack to an empty stack.
  stack<string> operators;
  // Split the postfix expression into a vector<string> of tokens
  vector<string> tokens = parseTokens(infixExpression);

  if(!isBalanced(infixExpression)) {
cout << "Error: expression not balanced" << endl;
    return "invalid";
  }

  // For each token in the list of tokens
  for(vector<string>::iterator itr = tokens.begin(); itr != tokens.end(); ++itr) {
    // if the next token is an operand (if it is a digit)
    if(isInt(*itr)) {
      // Append it to postfix (with a space following)
      postfix += *itr + " ";
cout << " added int " << *itr << endl;
cout << " current postfix: " << postfix << endl;
    }
    // else if the next token is an operator
    else if(isOperator(*itr)) {
      // Call process_operator() to process the operator
      if(!process_operator(operators, postfix, *itr)) {
        // If process_operator returns false, then indicate a syntax error
cout << " Error process_operator failed" << endl;
        return "invalid";
      }
    }
    else {
cout << " Error invalid token" << endl;
      // Indicate a syntax error
      return "invalid";
    }
  }
  // Pop remaining operators off the operator stack and append them to postfix 
  while(!operators.empty()) {
    postfix += operators.top() + " ";
cout << " added operator " << operators.top() << endl;
cout << " current postfix: " << postfix << endl;
    operators.pop();
  }
  // (with a space following each except for the last)
  postfix.pop_back();
  // To test if the resulting postfix is valid, you can call your postfixEvaluate function to see if you get a valid result
  if(postfixEvaluate(postfix) == "invalid") {
cout << " Error invalid final expression" << endl;
    return "invalid";
  }
  // If the result is valid, return postfix
  return postfix;
}


bool ExpressionManager::process_operator(stack<string> &opStack, string &postfix, string &op) {
cout << " In process_operator" << endl;
  // if the operator stack is empty OR the top stack is an opening parenthesis OR the current operator is an opening parenthesis 
  // Push the current operator onto the stack
  // return true
  if(opStack.empty() || isLeftParen(opStack.top()) || isLeftParen(op)) {
    opStack.push(op);
    cout << "   pushed current op: " << op << endl;
    return true;
  }
  // else if the current operator is a closing parenthesis
  else if(isRightParen(op)) {
    // while the top of the operator stack is not a matching opening parenthesis
    while(!isPair(opStack.top(), op)) {
      // pop off the top of the stack and append it to postfix (with a space after)
      cout << "   top of stack: " << opStack.top() << endl;
      postfix += opStack.top() + " ";
      cout << "   Current postfix: \"" << postfix << "\"" << endl;
      opStack.pop();
      // if operator stack becomes empty without finding a matching parenthesis, return false
      if(opStack.empty()) {
        cout << "   empty stack too early" << endl;
        return false;
      }
    }
    // pop off the matching opening parenthesis
    if(isPair(opStack.top(), op)) {
      opStack.pop();
      cout << "   Pair found." << endl;
      cout << "   Current postfix: \"" << postfix << "\"" << endl;
      // return true
      return true;
    }
  }
  else {
    // while the current operator precedence is less than or equal to the stack top precedence, pop stack onto postfix
    while(precedence(op) <= precedence(opStack.top())) {
cout << "   pushed current opStack.top(): " << opStack.top() << endl;
      postfix += opStack.top() + " ";
      opStack.pop();
    }
    // push the current operator
cout << "   pushed current op onto opStack: " << op << endl;
    opStack.push(op);
    // return true
    return true;
  }
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
