// RPN calculator

#include <iostream>
#include <string>
#include <stack>

class IncorrectNumberOfOperands {};
class InvalidInput {};
class StackTooLarge {};

using namespace std;
bool is_str_digit(string);  // returns true if input parameter string is and integer (e.g., "127343")
bool is_str_operator(string); // returns true if the input parameter is an operator character (e.g., "+", "*")

int main() {
  string in;
  stack<string> st;   // stack definition

  cin >> in;

  try {
    while(in != "q") {
      if(is_str_digit(in)){
        st.push(in);
      } else if(is_str_operator(in)) {
        // Make sure we have enough operands
        if (st.size() < 2) {
          throw IncorrectNumberOfOperands();
        }

        int value1 = stoi(st.top());
        st.pop();
        int value2 = stoi(st.top());
        st.pop();

        // Stores the result
        int value3 = 0;

        switch(in[0]) {
          case '+':
            value3 = value2 + value1;
            break;
          case '-':
            value3 = value2 - value1;
            break;
          case '*':
            value3 = value2 * value1;
            break;
          case '/':
            value3 = value2 / value1;
            break;
        }
        st.push(to_string(value3));
      } else {
        // If we don't have an operator or digit we have invalid input
        throw InvalidInput();
      }
      cin >> in;
    }

    // Make sure the stack has the correct number of values
    if (st.size() > 1) {
      throw StackTooLarge();
    }
    cout << "The answer is : " << st.top() << endl;
    return 0;
  } catch (IncorrectNumberOfOperands) {
    cout << "Not enough operands in the stack!\n";
    return 1;
  } catch (InvalidInput) {
    cout << "Invalid input! Neither an operator nor integer was input\n";
    return 1;
  } catch (StackTooLarge) {
    cout << "The stack had too many items left! Was expecting only 1\n";
    return 1;
  }
}

bool is_str_digit(string s) {
  for (int i = 0; i < s.length(); ++i) {
    if(!isdigit(s[i]))
      return false;
    }
  return true;
}

bool is_str_operator(string s) {
    return (s.length()==1 && (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0]== '/'));
}
