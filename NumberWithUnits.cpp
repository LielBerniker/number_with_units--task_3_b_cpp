#include "NumberWithUnits.hpp"
using namespace std;
using ariel::NumberWithUnits;

namespace ariel
{
   map<string, map<string, double>> NumberWithUnits::graph;

   NumberWithUnits::NumberWithUnits(double num, const string &unit)
   {
      /* constructor for the  NumberWithUnits clas , the function get a number and string that 
     will represent the  NumberWithUnits
     if the name of the unit not exist in the data base of units throw an exeption  */
      if (NumberWithUnits::graph.find(unit) == NumberWithUnits::graph.end())
      {
         throw invalid_argument(ariel::IA_ERROR);
      }
      this->number = num;
      this->units = unit;
   }

   void NumberWithUnits::read_units(ifstream &units_file)
   {
      /*the function get a reference to a file and read the file line by line
      get the units in the line into the data base and the convert rate between them */
      size_t i = 0;
      size_t j = 0;
      string line;

      while (getline(units_file, line))
      {
         string unit_1;
         string unit_2;
         string number_u;
         i = 2;
         j = line.find_first_of(' ', i);
         unit_1 = line.substr(i, j - i);
         i = j + 3;
         j = line.find_first_of(' ', i);
         number_u = line.substr(i, j - i);
         i = j + 1;
         unit_2 = line.substr(i);
         NumberWithUnits::graph[unit_1][unit_2] = stod(number_u);
         NumberWithUnits::graph[unit_2][unit_1] = 1 / stod(number_u);
      }
      units_file.close();
   }

   double NumberWithUnits::get_num() const
   {
      /* return the number part in the NumberWithUnits*/
      return this->number;
   }

   string NumberWithUnits::get_unit() const
   {
      /* return the unit name part in the NumberWithUnits*/
      return this->units;
   }

   NumberWithUnits operator+(const NumberWithUnits &num_u1, const NumberWithUnits &num_u2)
   {
      /* a friend function that get two NumberWithUnits and if the second object can be
       converted into the first object by the information about the units , then convert the 
       seconed object and add the nuber of object two to the furst object .
       if cant be converted throw an exeption */
      double convert_val = 0;
      convert_val = NumberWithUnits::conected_units(num_u1, num_u2);
      if (convert_val == -1)
      {
         throw invalid_argument(ariel::IA_ERROR);
      }
      NumberWithUnits temp_num(num_u1.get_num() + num_u2.get_num() / convert_val, num_u1.units);
      return temp_num;
   }

   NumberWithUnits NumberWithUnits::operator+()const
   {
      /* return the NumberWithUnits  */
      return NumberWithUnits(this->number, this->units);
   }

   NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &num_u)
   {
      /* the function get a NumberWithUnits and if the object can be
       converted into the current object by the information about the units , then convert the 
        object and add the number of the object to the current object .
       if cant be converted throw an exeption 
       change the current  NumberWithUnits */
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
      /* a friend function that get two NumberWithUnits and if the second object can be
       converted into the first object by the information about the units , then convert the 
       seconed object and sub the number of object two to from the first object .
       if cant be converted throw an exeption */
      double convert_val = 0;
      convert_val = NumberWithUnits::conected_units(num_u1, num_u2);
      if (convert_val == -1)
      {
         throw invalid_argument(ariel::IA_ERROR);
      }
      NumberWithUnits temp_num(num_u1.get_num() - (num_u2.get_num() / convert_val), num_u1.units);
      return temp_num;
   }

   NumberWithUnits NumberWithUnits::operator-()const
   {
      /* return the NumberWithUnits but with - in the number part  */
      return NumberWithUnits(-(this->number), this->units);
   }

   NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &num_u)
   {
      /* the function get a NumberWithUnits and if the object can be
       converted into the current object by the information about the units , then convert the 
        object and sub the number of the object from the current object .
       if cant be converted throw an exeption 
       change the current NumberWithUnits */
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
      /* the function get two NumberWithUnits objects , check first if the seconed object can 
      be converted into the first object , if can be convert , copare the numbers part of the
      objects with the convertion of the seconed object number.
      and return true if the first object num is smaller then the seconed object num 
      else false
      if cant be converted throe a exeption*/
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
      /* the function get two NumberWithUnits objects , check first if the seconed object can 
      be converted into the first object , if can be convert , copare the numbers part of the
      objects with the convertion of the seconed object number.
      and return true if the first object num is smaller or equal then the seconed object num 
      else false
      if cant be converted throe a exeption*/
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
      /* the function get two NumberWithUnits objects , check first if the seconed object can 
      be converted into the first object , if can be convert , copare the numbers part of the
      objects with the convertion of the seconed object number.
      and return true if the first object num is bigger then the seconed object num 
      else false
      if cant be converted throe a exeption*/
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
      /* the function get two NumberWithUnits objects , check first if the seconed object can 
      be converted into the first object , if can be convert , copare the numbers part of the
      objects with the convertion of the seconed object number.
      and return true if the first object num is bigger or equal then the seconed object num 
      else false
      if cant be converted throe a exeption*/
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
      /* the function get two NumberWithUnits objects , check first if the seconed object can 
      be converted into the first object , if can be convert , copare the numbers part of the
      objects with the convertion of the seconed object number.
      and return true if the first object num is equal then the seconed object num 
      else false
      if cant be converted throe a exeption*/
      bool flag = false;
      double convert_val = 0;
      convert_val = NumberWithUnits::conected_units(num_u1, num_u2);
      if (convert_val == -1)
      {
         throw invalid_argument(ariel::IA_ERROR);
      }
      if (abs(num_u1.get_num() - (num_u2.get_num() / convert_val)) < ariel::EPS)
      {
         flag = true;
      }

      return flag;
   }

   bool operator!=(const NumberWithUnits &num_u1, const NumberWithUnits &num_u2)
   {
      /* the function get two NumberWithUnits objects , check first if the seconed object can 
      be converted into the first object , if can be convert , copare the numbers part of the
      objects with the convertion of the seconed object number.
      and return true if the first object num is not equal then the seconed object num 
      else false
      if cant be converted throe a exeption*/
      return !(num_u1 == num_u2);
   }

   NumberWithUnits NumberWithUnits::operator++(int)
   {
      /* increase the NumberWithUnits object numberr part by 1 ,but return a NumberWithUnits
        that contain the previous value*/
      double num_temp = this->number;
      string unit_temp = this->units;
      this->number += 1;
      NumberWithUnits temp_u(num_temp, unit_temp);
      return temp_u;
   }
   NumberWithUnits &NumberWithUnits::operator++()
   {
      /* increase the NumberWithUnits object numberr part by 1 , return the NumberWithUnits
        object*/
      this->number += 1;
      return *this;
   }
   NumberWithUnits NumberWithUnits::operator--(int)
   {
      /* decrease the NumberWithUnits object numberr part by 1 ,but return a NumberWithUnits
        that contain the previous value*/
      double num_temp = this->number;
      string unit_temp = this->units;
      this->number -= 1;
      NumberWithUnits temp_u(num_temp, unit_temp);
      return temp_u;
   }

   NumberWithUnits &NumberWithUnits::operator--()
   {
      /* decrease the NumberWithUnits object numberr part by 1 , return the NumberWithUnits
        object*/
      this->number -= 1;
      return *this;
   }

   NumberWithUnits NumberWithUnits::operator*(double real_num)
   {
      /* the function get a number , mult the number by the number part of the 
       NumberWithUnits object and return the resuls in NumberWithUnits object */
      NumberWithUnits temp_unit(this->number * real_num, this->units);
      return temp_unit;
   }

   NumberWithUnits operator*(double real_num, const NumberWithUnits &num_u)
   {
      /* friend function .the function get a number and  NumberWithUnits ,
       mult the number by the number part of the 
       NumberWithUnits object and return the resuls in NumberWithUnits object */
      NumberWithUnits temp_unit(num_u.get_num() * real_num, num_u.get_unit());
      return temp_unit;
   }

   ostream &operator<<(ostream &out, const NumberWithUnits &num_u)
   {
      /* the function get output stream and a NumberWithUnits, put into the output stream
       the NumberWithUnits values by a spicific order, then return the uotput stream */
      out << num_u.get_num() << "[" << num_u.get_unit() << "]";
      return out;
   }

   istream &operator>>(istream &in, NumberWithUnits &num_u)
   {
      /* the function get input stream and a NumberWithUnits, put into parameters the input stream
       then remove unnecessary chars , then check if the unit inserted match to one of the 
       units in the units information if it does ,insert the information to the NumberWithUnits object ,
       else throw an exeption */
      size_t i = 0;
      string unit_temp;
      char left = 0;
      char right = 0;
      double num_temp = 0;
      in >> num_temp >> left >> unit_temp;
      // check if the unit conatin the barrack
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
      /* this function is a static function that get two NumberWithUnits,
      the function is doing a bfs over the information base that holds all the information about 
      the units conections. the function check if there is any conection in between the first object
      to the seconed object. if there is a connection the function return the convert rate 
      else return -1 */
      map<string, double> nodes;
      double val = 0;
      if (num_u1.get_unit() == num_u2.get_unit())
      {
         return 1;
      }
      string temp_node;
      string temp_nigh;
      queue<string> queue_temp;
      nodes[num_u1.units] = 1;
      queue_temp.push(num_u1.get_unit());
      while (!queue_temp.empty())
      {
         temp_node = queue_temp.front();
         queue_temp.pop();
         // go over the specific unit all connections
         for (auto &element : NumberWithUnits::graph[temp_node])
         {
            temp_nigh = element.first;
            // if the unit didnt been checked yet
            if (nodes.find(temp_nigh) == nodes.end())
            { // insert the convrt rate of the unit to a map
               nodes[temp_nigh] = nodes[temp_node] * element.second;
               queue_temp.push(temp_nigh);
            }
            // if the unit is the current unit is the same as num2 unit
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