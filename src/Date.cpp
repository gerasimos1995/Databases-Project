#include "Date.h"

Date::Date()//random date
{
    Month = rand()%12+1;
    if ((getMonth()==1)||(getMonth()==3)||(getMonth()==5)||(getMonth()==7)||(getMonth()==8)||(getMonth()==10)||getMonth()==12){
        Day = rand()%31+1;
    }else if ((getMonth()==2)||(getMonth()==4)||(getMonth()==6)||(getMonth()==9)||(getMonth()==11)){
        Day = rand()%30+1;
    }
    Year = rand()%1000+2016;
}



Date::Date(int day,int month,int year)
{
        Day = day;
        Month = month;
        Year = year;
}

Date::~Date(){
}

int Date::getDay(){
    return Day;
}

int Date::getMonth(){
    return Month;
}

int Date::getYear(){
    return Year;
}

void Date::printDate(){
    cout << "Date of check-in: " << Day << "/" << Month << "/" << Year << "(d/m/y)" << endl;
}
