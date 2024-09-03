#pragma once
#include<iostream>
#include<stdexcept>
#include<string>
#include<iomanip>
#include<sstream>

class Duration {

  private:
    int hours_{0};
    int minutes_{0};
    int seconds_{0};

  public:
    Duration();
    Duration(const Duration& other);
    Duration(Duration&& other);
    Duration& operator=(const Duration& other);
    Duration& operator=(Duration&& other);
    ~Duration();

    Duration(int sekunde);
    Duration(int sati, int minute, int sekunde);
    Duration(const std::string& temp);

    int get_h()const{return hours_;};
    int get_m()const{return minutes_;};
    int get_s()const{return seconds_;};

    Duration& set_h(int sati);
    Duration& set_m(int minute);
    Duration& set_s(int sekunde);

    operator bool() const;
    bool operator!() const;

    bool operator==(const Duration& other)const;
    bool operator!=(const Duration& other)const;
    bool operator<(const Duration& other)const;
    bool operator>(const Duration& other)const;
    bool operator<=(const Duration& other)const;
    bool operator>=(const Duration& other)const;

    int tts()const;

    Duration& operator+=(const Duration& other);
    Duration operator+(const Duration& other)const;
    Duration& operator-=(const Duration& other);
    Duration operator-(const Duration& other)const;
    Duration& operator*=(const int& broj);
    Duration operator*(const int& broj)const;
    Duration& operator/=(const int& broj);
    Duration operator/(const int& broj)const;

};

std::ostream& operator<<(std::ostream& out, const Duration& other);
std::istream& operator>>(std::istream& in, Duration& other);

