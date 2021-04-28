#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <stack>
#include <sstream>
#include <cmath> 
#include <exception>

namespace ariel
{
    const double EPS = 0.001;
    const std::string IA_ERROR =  "the units do not match";
    class NumberWithUnits
    {
    public:
        NumberWithUnits(double num,const std::string& unit);
        static void read_units(std::ifstream& units_file);
        double get_num()const;
        std::string get_unit()const;
        friend NumberWithUnits operator+(const NumberWithUnits& num_u1,const NumberWithUnits& num_u2);
        NumberWithUnits operator+();
        NumberWithUnits& operator+=(const NumberWithUnits& num_u);
        friend NumberWithUnits operator-(const NumberWithUnits& num_u1,const NumberWithUnits& num_u2);
        NumberWithUnits operator-();
        NumberWithUnits& operator-=(const NumberWithUnits& num_u);

        friend bool operator<(const NumberWithUnits& num_u1,const NumberWithUnits& num_u2);
        friend bool operator<=(const NumberWithUnits& num_u1,const NumberWithUnits& num_u2);
        friend bool operator>(const NumberWithUnits& num_u1,const NumberWithUnits& num_u2);
        friend bool operator>=(const NumberWithUnits& num_u1,const NumberWithUnits& num_u2);
        friend bool operator==(const NumberWithUnits& num_u1,const NumberWithUnits& num_u2);
        friend bool operator!=(const NumberWithUnits& num_u1,const NumberWithUnits& num_u2);

        NumberWithUnits operator++(int);//a++
        NumberWithUnits& operator++();//++a
        NumberWithUnits operator--(int);//a--
        NumberWithUnits& operator--();//--a

        NumberWithUnits operator*(double real_num);
        friend NumberWithUnits operator*(double real_num,const NumberWithUnits& num_u);
        friend std::ostream& operator<<(std::ostream& out,const NumberWithUnits& num_u);
        friend std::istream& operator>>(std::istream& in,NumberWithUnits& num_u);

        static double conected_units(const NumberWithUnits& num_u1 ,const NumberWithUnits& num_u2);
       

    private:
       double number;
       std::string units;
       static std::map<std::string,std::map<std::string,double>> graph;
       
    };
 
}