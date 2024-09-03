#include "duration.hpp"

Duration::Duration(){
  hours_=0;
  minutes_=0;
  seconds_=0;
};

Duration::~Duration(){};

Duration::Duration(const std::string& temp){
  std::stringstream ss(temp);
  char s;
  ss>>hours_>>s>>minutes_>>s>>seconds_;
};

Duration::Duration(const Duration& other){
  hours_=other.hours_;
  minutes_=other.minutes_;
  seconds_=other.seconds_;
};

Duration::Duration(Duration&& other){
  hours_=other.hours_;
  minutes_=other.minutes_;
  seconds_=other.seconds_;
};

Duration& Duration::operator=(const Duration& other){
  if(this!=&other){
    hours_=other.hours_;
    minutes_=other.minutes_;
    seconds_=other.seconds_;
  }
  return *this;
};
  hours_=other.hours_;
  minutes_=other.minutes_;
  seconds_=other.seconds_;
  return *this;
};

Duration::Duration(int sekunde){
  hours_=sekunde/3600;
  minutes_=(sekunde-hours_*3600)/60;
  seconds_=sekunde-minutes_*60-hours_*3600;
};

Duration::Duration(int sati, int minute, int sekunde){
  if(minute>=60 || sekunde>=60 || sekunde<0 || minute<0 || sati<0){
  throw std::out_of_range("Ne dozvoljena vrijednost minuta ili sekundi");
  }
  else{
  hours_=sati;
  minutes_=minute;
  seconds_=sekunde;
  }
};

Duration& Duration::set_h(int sati){
  if(sati<0) throw std::out_of_range("Vrijednost sati ne moze biti manja od 0");
  hours_=sati;
  return *this;
};

Duration& Duration::set_m(int minute){
  if(minute>=60 || minute<0){throw std::out_of_range("Invalid value");}
  else{minutes_=minute;}
  return *this;
};

Duration& Duration::set_s(int sekunde){
  if(sekunde>=60 || sekunde<0){throw std::out_of_range("Invalid value");}
  else{seconds_=sekunde;}
  return *this;
};

Duration::operator bool() const{
  if(hours_==0 && minutes_==0 && seconds_==0){return false;}
  else{return true;}
};

bool Duration::operator!() const{
  if(*this){return false;}
  else{return true;}
};

bool Duration::operator==(const Duration& other)const{
  if(hours_==other.hours_ && minutes_==other.minutes_ && seconds_==other.seconds_){
    return true;
  }
  else{
    return false;
  }
};

bool Duration::operator!=(const Duration& other)const{
  if(hours_==other.hours_ && minutes_==other.minutes_ && seconds_==other.seconds_){
    return false;
  }
  else{
  return true;
  }
};

int Duration::tts()const{
  return hours_*3600 + minutes_*60 + seconds_;
};

bool Duration::operator<(const Duration& other)const{
  if(tts() < other.tts()) return true;
  else return false;
};


bool Duration::operator>(const Duration& other)const{
  if(tts() > other.tts()) return true;
  else return false;
};

bool Duration::operator<=(const Duration& other)const{
  if(tts() <= other.tts()) return true;
  else return false;
};

bool Duration::operator>=(const Duration& other)const{
  if(tts() >= other.tts()) return true;
  else return false;
};

Duration& Duration::operator+=(const Duration& other){
 if(other){
   *this=Duration(tts() + other.tts());
 }
 return *this;
};

Duration Duration::operator+(const Duration& other)const{
  Duration temp;
  temp = tts() + other.tts();
  return temp;
};

Duration& Duration::operator-=(const Duration& other){
  if(other){
    if(*this < other) throw std::out_of_range("Nije moguce oduzeti");
    *this=tts() - other.tts();
  }
  return *this;
};

Duration Duration::operator-(const Duration& other)const{
  Duration temp=(*this);
  if(*this < other) throw std::out_of_range("Nije moguce oduzeti");
  if(other){
    temp = Duration(tts() - other.tts());
  }
  return temp;
};

Duration& Duration::operator*=(const int& broj){
  *this=Duration(this->tts()*broj);
  return *this;
};

Duration Duration::operator*(const int& broj)const{
  Duration temp;
  temp = Duration(this->tts()*broj);
  return temp;
};

Duration& Duration::operator/=(const int& broj){
  *this=Duration(this->tts() / broj);
  return *this;
};

Duration Duration::operator/(const int& broj)const{
  Duration temp;
  temp = Duration(this->tts() / broj);
  return temp;
};

std::ostream& operator<<(std::ostream& out, const Duration& other){
  out<<std::setfill('0');
  out<<std::setw(2)<<other.get_h()<<':'<<std::setw(2)<<other.get_m()<<':'<<std::setw(2)<<other.get_s();
  out<<std::setfill(' ');
  return out;
};

std::istream& operator>>(std::istream& in, Duration& other){
  int sati, minute, sekunde;
  char s1, s2;
  if((in>>sati>>s1>>minute>>s2>>sekunde) && s1==':' && s2==':'){
    other.set_h(sati);
    other.set_m(minute);
    other.set_s(sekunde);
  }
  else throw std::invalid_argument("Nevalidan unos");
  return in;
};
