#include "NumberWithUnits.hpp"
using namespace std;
using ariel::NumberWithUnits;

namespace ariel
{
   map<string, map<string, double>> NumberWithUnits::graph;
   NumberWithUnits::NumberWithUnits(double num, const string& unit)
   {
      if (NumberWithUnits::graph.find(unit) == NumberWithUnits::graph.end())
      {
         throw invalid_argument(ariel::IA_ERROR);
      }
      this->number = num;
      this->units = unit;
   }
   void NumberWithUnits::read_units(ifstream &units_file)
   {
      size_t i = 0;
      string line, temp_str;
      while (getline(units_file, line))
      {
         string unit_1;
         string unit_2;
         string number_u;
         i = 2;
         while (line.at(i) != ' ')
         {
            unit_1 += line.at(i);
            i++;
         }
         i += 3;
         while (line.at(i) != ' ')
         {
            number_u += line.at(i);
            i++;
         }
         i++;
         while (i < line.length())
         {
            unit_2 += line.at(i);
            i++;
         }
         NumberWithUnits::graph[unit_1][unit_2] = stod(number_u);
         NumberWithUnits::graph[unit_2][unit_1] = 1 / stod(number_u);
      }
   }
   double NumberWithUnits::get_num() const
   {
      return this->number;
   }
   string NumberWithUnits::get_unit() const
   {
      return this->units;
   }
   NumberWithUnits operator+(const NumberWithUnits &num_u1, const NumberWithUnits &num_u2)
   {
      double convert_val = 0;
      convert_val = NumberWithUnits::conected_units(num_u1, num_u2);
      if (convert_val == -1)
      {
         throw invalid_argument(ariel::IA_ERROR);
      }
      NumberWithUnits temp_num(num_u1.get_num() + num_u2.get_num() / convert_val, num_u1.units);
      return temp_num;
   }
   NumberWithUnits NumberWithUnits::operator+()
   {
      return NumberWithUnits(this->number, this->units);
   }
   NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits &num_u)
   {
      double convert_val = 0;
      convert_val = NumberWithUnits::conected_units(*this, num_u);
      if (convert_val == -1)
      {
         throw invalid_argument(ariel::IA_ERROR);
      }
      this->number += (num_u.get_num() / convert_val);
      return *this;
   }
   NumberWithUnits operator-(const NumberWithUnits &num_u1, const NumberWithUnits &num_u2)
   {
      double convert_val = 0;
      convert_val = NumberWithUnits::conected_units(num_u1, num_u2);
      if (convert_val == -1)
      {
         throw invalid_argument(ariel::IA_ERROR);
      }
      NumberWithUnits temp_num(num_u1.get_num() - (num_u2.get_num() / convert_val), num_u1.units);
      return temp_num;
   }
   NumberWithUnits NumberWithUnits::operator-()
   {
      return NumberWithUnits(-(this->number), this->units);
   }
   NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits &num_u)
   {
      double convert_val = 0;
      convert_val = NumberWithUnits::conected_units(*this, num_u);
      if (convert_val == -1)
      {
         throw invalid_argument(ariel::IA_ERROR);
      }
      this->number -= (num_u.get_num() / convert_val);
      return *this;
   }
   bool operator<(const NumberWithUnits &num_u1, const NumberWithUnits &num_u2)
   {
      bool flag = false;
      double convert_val = 0;
      convert_val = NumberWithUnits::conected_units(num_u1, num_u2);
      if (convert_val == -1)
      {
         throw invalid_argument(ariel::IA_ERROR);
      }
      if (num_u1.get_num() < (num_u2.get_num() / convert_val) && (num_u1 != num_u2))
          {
         flag = true;
      }
      return flag;
   }
   bool operator<=(const NumberWithUnits &num_u1, const NumberWithUnits &num_u2)
   {
      bool flag = false;
      double convert_val = 0;
      convert_val = NumberWithUnits::conected_units(num_u1, num_u2);
      if (convert_val == -1)
      {
         throw invalid_argument(ariel::IA_ERROR);
      }
      if (num_u1.get_num() < (num_u2.get_num() / convert_val) || (num_u1 == num_u2))
      {
         flag = true;
      }
      return flag;
   }
   bool operator>(const NumberWithUnits &num_u1, const NumberWithUnits &num_u2)
   {
      bool flag = false;
      double convert_val = 0;
      convert_val = NumberWithUnits::conected_units(num_u1, num_u2);
      if (convert_val == -1)
      {
         throw invalid_argument(ariel::IA_ERROR);
      }
      if (num_u1.get_num() > (num_u2.get_num() / convert_val) && (num_u1 != num_u2))
      {
         flag = true;
      }
      return flag;
   }
   bool operator>=(const NumberWithUnits &num_u1, const NumberWithUnits &num_u2)
   {
      bool flag = false;
      double convert_val = 0;
      convert_val = NumberWithUnits::conected_units(num_u1, num_u2);
      if (convert_val == -1)
      {
         throw invalid_argument(ariel::IA_ERROR);
      }
      if (num_u1.get_num() > (num_u2.get_num() / convert_val) || (num_u1 == num_u2))
      {
         flag = true;
      }
      return flag;
   }
   bool operator==(const NumberWithUnits &num_u1, const NumberWithUnits &num_u2)
   {
      bool flag = false;
      double convert_val = 0;
      convert_val = NumberWithUnits::conected_units(num_u1, num_u2);
      if (convert_val == -1)
      {
         throw invalid_argument(ariel::IA_ERROR);
      }
      if(abs(num_u1.get_num() - (num_u2.get_num() / convert_val))<ariel::EPS)
      {
         flag = true;
      }

      return flag;
   }
   bool operator!=(const NumberWithUnits &num_u1, const NumberWithUnits &num_u2)
   {
     return !(num_u1==num_u2);
   }
   NumberWithUnits NumberWithUnits::operator++(int)
   {
      double num_temp = this->number;
      string unit_temp = this->units;
      this->number += 1;
      NumberWithUnits temp_u(num_temp, unit_temp);
      return temp_u;
   }
   NumberWithUnits &NumberWithUnits::operator++()
   {
      this->number += 1;
      return *this;
   }
   NumberWithUnits NumberWithUnits::operator--(int)
   {
      double num_temp = this->number;
      string unit_temp = this->units;
      this->number -= 1;
      NumberWithUnits temp_u(num_temp, unit_temp);
      return temp_u;
   }
   NumberWithUnits &NumberWithUnits::operator--()
   {
      this->number -= 1;
      return *this;
   }
   NumberWithUnits NumberWithUnits::operator*(double real_num)
   {
      NumberWithUnits temp_unit(this->number * real_num, this->units);
      return temp_unit;
   }

   NumberWithUnits operator*(double real_num, const NumberWithUnits &num_u)
   {
      NumberWithUnits temp_unit(num_u.get_num() * real_num, num_u.get_unit());
      return temp_unit;
   }

   ostream &operator<<(ostream &out, const NumberWithUnits &num_u)
   {
      out << num_u.get_num() << "[" << num_u.get_unit() << "]";
      return out;
   }
   istream &operator>>(istream &in, NumberWithUnits &num_u)
   {
      size_t i = 0;
      string unit_temp;
      char left= 0;
      char right = 0;
      double num_temp = 0;
      in >> num_temp >> left >> unit_temp;
      if (unit_temp.find(']', 0) == string::npos)
      {
         in >> right;
      }
      else
      {
         i = unit_temp.find(']', 0);
         unit_temp = unit_temp.substr(0, i);
      }
      if (NumberWithUnits::graph.find(unit_temp) == NumberWithUnits::graph.end())
      {
         throw invalid_argument(ariel::IA_ERROR);
      }

      num_u.number = num_temp;
      num_u.units = unit_temp;
      return in;
   }

   double NumberWithUnits::conected_units(const NumberWithUnits &num_u1, const NumberWithUnits &num_u2)
   {
      map<string, double> nodes;
      double val = 0;
      if (num_u1.get_unit() == num_u2.get_unit())
      {
         return 1;
      }
      string temp_node;
      string temp_nigh;
      stack<string> stack_temp;
      nodes[num_u1.units] = 1;
      stack_temp.push(num_u1.get_unit());
      while (!stack_temp.empty())
      {
         temp_node = stack_temp.top();
         stack_temp.pop();
         for (auto &element2 : NumberWithUnits::graph[temp_node])
         {
            temp_nigh = element2.first;
            if (nodes.find(temp_nigh) == nodes.end())
            {
               nodes[temp_nigh] = nodes[temp_node] * element2.second;
               stack_temp.push(temp_nigh);
            }
            if (temp_nigh == num_u2.get_unit())
            {
               val = nodes[temp_nigh];
               return val;
            }
         }
      }
      return -1;
   }
}