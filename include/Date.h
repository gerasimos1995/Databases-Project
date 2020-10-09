#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <cstdlib>


using namespace std;

class Date
{
    public:
        Date();
        Date(int,int,int);
        ~Date();
        void printDate();
        int getDay();
        int getMonth();
        int getYear();
        //string convertCheckinDate(Date &);

    private:
        int Day,Month,Year;
};

#endif // DATE_H
