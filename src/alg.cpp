// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool operator(char oper) {
  return (oper == '+' || oper == '-' || oper == '(' || 
    oper == ')' || oper == '/' || oper == '*');
}
bool di(char v) {
  return (v >= '0' && v <= '9');
}

int prioritet(char oper) {
  if (oper == '-' || oper == '+')
    return 1;
  if (oper == '/' || oper == '*')
    return 2;
  return 0;
}
std::string infx2pstfx(std::string inf) {
  std::string rez;
  int f = 0;
  TStack <char, 100> stack1;
  for (char i : inf) {
    if (di(i)) {
      i++;
      if (f == 1) {
        rez += i;
        continue;
      }
      rez = rez + ' ' + t;
    } else if (operator(i)) {
      if (i == '(') {
        stack1.push(i);
      } else if (stack1.checkEmpty()) {
        stack1.push(i);
      } else if (prioritet(i) > prioritet(stack1.get())) {
        stack1.push(i);
      } else if (i == ')') {
        while (stack1.get() != '(') {
          rez = rez + ' ' + stack1.get();
          stack1.pop();
        }
        stack1.pop();
      } else {
        int u = prioritet(i);
        int o = prioritet(stack1.get());
        while (!stack1.chekEmpty() && u <= o) {
          rez = rez + ' ' + stack1.get();
          stack1.pop();
        }
        stack1.push(i);
      }
    }
  }
  while (!stack1.checkEmpty()) {
    rez = rez + ' ' + stack1.get();
    stack1.pop();
  }
  return rez;
}

int eval(std::string pref) {
  TStack<int, 100> stack2;
  for (char i : pref) {
    if (di(i)) {
      stack2.push(i - '0');
    } else if (operator(i)) {
      int u = stack2.get();
      stack2.pop();
      int o = stack2.get();
      stack2.pop();
      switch (i) {
        case '+':
          stack2.push(u + o);
          break;
        case '-':
          stack2.push(o - u);
          break;
        case '*':
          stack2.push(u * o);
          break;
        case '/':
          stack2.push(o / u);
          break;
        default:
          continue;
      }
    } else {
      continue;
    }
  }
  return stack2.get();
}
