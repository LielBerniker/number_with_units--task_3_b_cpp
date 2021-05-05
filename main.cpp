
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;
void print_all_units()
{
  ifstream units_file{"mytxt_units.txt"};
  string line;
  while (getline(units_file, line))
  {
    cout << line << "\n";
  }
}
int main()
{
  ifstream units_file{"mytxt_units.txt"};
  NumberWithUnits::read_units(units_file);
  

  while (1)
  {
    NumberWithUnits num1{1, "m"};
    NumberWithUnits num2{1, "m"};
    bool flag = false;
    string oper;
    string line;
    print_all_units();
    cout << "\nplease choose two units and an operator to use on the units:\n";
    cout << "please choose the first unit from the list(choose by name)\n and the amout of the unit\n the input shoukd look like this:  30[kg] for exmple\n";
    cin >> num1;
    while (!flag)
    {
      cout << "\nplease choose the  seconed unit from the list(choose by name)\n and the amout of the unit\n if the units are not convertable you will need to choose again \n the input shoukd look like this:  30[kg] for exmple\n";
      cin >> num2;
      if (NumberWithUnits::conected_units(num1, num2) == -1)
      {
        cout << "the units cant be converted\n";
      }
      else
      {
        flag = true;
        cout << "the units can be converted !!!\n";
      }
    }
    cout << "please insert one of the operators\n   [ + , - , += , -+ , < , > , <= , >= , != , == ]\n";
    cin >> oper;

    if (oper == "+")
    {
      cout << (num1 + num2) << "\n";
    }
    else if (oper == "-")
    {
      cout << (num1 - num2) << "\n";
    }
    else if (oper == "+=")
    {
      cout << (num1 += num2) << "\n";
    }
    else if (oper == "-=")
    {
      cout << (num1 -= num2) << "\n";
    }
    else if (oper == "<")
    {
      if (num1 < num2)
      {
        cout << "num1 is smaller then num2\n";
      }
      else
      {
        cout << "num1 is not smaller then num2\n";
      }
    }
    else if (oper == "<=")
    {
      if (num1 <= num2)
      {
        cout << "num1 is smaller then num2 or equal to it\n";
      }
      else
      {
        cout << "num1 is not smaller then num2 or equal to it\n";
      }
    }
    else if (oper == ">=")
    {
      if (num1 >= num2)
      {
        cout << "num1 is bigger then num2 or equal to it\n";
      }
      else
      {
        cout << "num1 is not bigger then num2 or equal to it\n";
      }
    }
    else if (oper == ">")
    {
      if (num1 > num2)
      {
        cout << "num1 is bigger then num2\n";
      }
      else
      {
        cout << "num1 is not bigger then num2\n";
      }
    }
    else if (oper == "==")
    {
      if (num1 == num2)
      {
        cout << "num1 is equal to num2\n";
      }
      else
      {
        cout << "num1 is not equal to num2\n";
      }
    }
    else if (oper == "!=")
    {
      if (num1 != num2)
      {
        cout << "num1 is not equal to num2\n";
      }
      else
      {
        cout << "num1 is equal to num2\n";
      }
    }
    cout << "to stop a exit press 3\n else press any key\n";
    cin >> oper;
    if (oper == "3")
    {
      break;
    }
  }
}
//clang++-9 -g -std=c++2a -Werror main.cpp NumberWithUnits.cpp -o main
