#ifndef __MYINFIXCALCULATOR_H__
#define __MYINFIXCALCULATOR_H__

#include <algorithm>
#include <string>

#include "MyStack.h"
#include "MyVector.h"

class MyInfixCalculator{

  public:

    MyInfixCalculator()
    {

    }

    ~MyInfixCalculator()
    {

    }

    double calculate(const std::string& s)
    {
        // code begins
        MyVector<std::string> token_vect;
        MyVector<std::string> postfix_vect;
        tokenize(s, token_vect);
        // for (int i=0; i < token_vect.size(); i++) {
        //   std::cout << token_vect[i] << "\n";
        // }
        infixToPostfix(token_vect, postfix_vect);
        // for (int i=0; i < postfix_vect.size(); i++) {
        //   std::cout << postfix_vect[i] << "\n";
        // }
        double ans = calPostfix(postfix_vect);
        return(ans);
      //  tokenize(s, )
        // code ends
    }

  private:

    // returns operator precedance; the smaller the number the higher precedence
    // returns -1 if the operator is invalid
    // does not consider parenthesis
    int operatorPrec(const char c) const
    {
        switch(c)
        {
            case '*':
                return 2;
            case '/':
                return 2;
            case '+':
                return 3;
            case '-':
                return 3;
            default:
                return -1;
        }
    }

    // checks if a character corresponds to a valid parenthesis
    bool isValidParenthesis(const char c) const
    {
        switch(c)
        {
            case '(':
                return true;
            case ')':
                return true;
            default:
                return false;
        }
    }

    // checks if a character corresponds to a valid digit
    bool isDigit(const char c) const
    {
        if(c >= '0' && c <= '9')
            return true;
        return false;
    }

    // computes binary operation given the two operands and the operator in their string form
    double computeBinaryOperation(const std::string& ornd1, const std::string& ornd2, const std::string& opt) const
    {
        double o1 = std::stod(ornd1);
        double o2 = std::stod(ornd2);
        switch(opt[0])
        {
            case '+':
                return o1 + o2;
            case '-':
                return o1 - o2;
            case '*':
                return o1 * o2;
            case '/':
                return o1 / o2;
            default:
                std::cout << "Error: unrecognized operator: " << opt << std::endl;
                return 0.0;
        }
    }


    // tokenizes an infix string s into a set of tokens (operands or operators)
    void tokenize(const std::string& s, MyVector<std::string>& tokens)
    {
        // code begins
          for(int i=0; i< s.size(); i++) {
            char val = s[i];
            if (isDigit(s[i]) || (s[i] == '-' && isDigit(s[i+1]) && (!isDigit(s[i-1]) && s[i-1] != ')'))) {
              std::string whole_num;
              if (s[i] == '-') {
                whole_num += s[i];
                i++;
              }
              while (isDigit(s[i]) || s[i] == '.') {
                // const char value = s[i];
                whole_num += s[i];
                i++;
              }
              if (isDigit(s[i]) == false) {
                i--;
              }
              //double whole_float = std::stod(whole_num);
              tokens.push_back(whole_num);
            }
            else if (isValidParenthesis(s[i])) {
              char temp = s[i];
              std::string temp2(1, temp);
              tokens.push_back(temp2);
            }
            else {
              //char op_val = operatorPrec(val);
              char temp = s[i];
              std::string temp2(1, temp);
              tokens.push_back(temp2);
            }
          }

        // code ends
    }

    // converts a set of infix tokens to a set of postfix tokens
    void infixToPostfix(MyVector<std::string>& infix_tokens, MyVector<std::string>& postfix_tokens)
    {
        // code begins
    // take the infix and follow instructions with popping values on and off the stack from the book and have infix be the values you read from and postfix be the values you push to.
    MyStack<char> stack;
    //std::string stack_top;
    std::string right_paren = "(";
    std::string val;

    for (size_t i = 0; i < infix_tokens.size(); ++i) {
      val = infix_tokens[i];
      char first = val[0];

      if(isDigit(first) || ((first == '-') && isDigit(val[1]))) {
        postfix_tokens.push_back(val);
      }
      else if (first == '(') {
        stack.push('(');
      }
      else if (first == '+' || first == '-' || first == '*' || first == '/') {
        if(stack.empty() || stack.top() == '(') {
          stack.push(first);
        }
        else {
          int stack_prec = operatorPrec(stack.top());
          int op_prec = operatorPrec(first);
          if(op_prec < stack_prec || stack.top() == '(') {
            stack.push(first);
          }
          else {
            while (op_prec >= stack_prec && stack.top() != '(' && !stack.empty()) {
              postfix_tokens.push_back(std::string(1, stack.top()));
              stack.pop();
              stack_prec = operatorPrec(stack.top());
              op_prec = operatorPrec(first);
            }
            stack.push(first);
          }
        }
      }
      else if (first == ')') {


        while(stack.top() != '(' && !stack.empty()) {
          postfix_tokens.push_back(std::string(1, stack.top()));
          stack.pop();
        }
        stack.pop();
      }
    }

   while(!stack.empty()) {
     //stack_top = stack.top();
     postfix_tokens.push_back(std::string(1, stack.top()));
     stack.pop();
   }

        // code ends
    }

    // calculates the final result from postfix tokens
    double calPostfix(const MyVector<std::string>& postfix_tokens) const
    {
        // code begins
      MyStack<std::string> stack;
      double ans;
      std::string num1;
      std::string num2;
      //
      for (int i = 0; i < postfix_tokens.size(); i++) {
        std::string val = postfix_tokens[i];
        //std::cout << val << "\n";
        char first = val[0];
        if (isDigit(first) || ((first == '-') && isDigit(val[1]))) {
          stack.push(val);
          //std::cout << val << " was pushed to stack\n";
        }
        else if (first == '+' || first == '-' || first == '*' || first == '/'){
          // std::string first = stack.top();
          if(!stack.empty()) {
            num1 = stack.top();
            stack.pop();
            // std::string second = stack.top();
            if(!stack.empty()) {
              num2 = stack.top();
              stack.pop();
            }
            else {
              std::cout << "error\n";
            }

            // // double ans;
            ans = computeBinaryOperation(num2, num1, &first);
            std::string ans_string = std::to_string(ans);
            stack.push(ans_string);
            //std::cout << ans_string << " was calculated and pushed\n";
          }
          else {
            std::cout << "error?\n";
          }

          //std::cout << ans_string << " was calculated and pushed\n";
        }
      }

    
      std::string final_str = stack.top();
      double final = stod(final_str);
      return(final);
      //return(2.3);
      // code ends
    }
};

#endif // __MYINFIXCALCULATOR_H__
