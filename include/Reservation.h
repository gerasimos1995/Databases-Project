#ifndef RESERVATION_H
#define RESERVATION_H
#include <sstream>
#include <string>
#include <iostream>
#include "Date.h"

using namespace std;

class Reservation
{
    public:
        Reservation();
        Reservation(string,Date*,int);
        ~Reservation();
        void setClientName(string);
        string getClientName();
        void setCheckinDate(Date*);
        Date* getCheckinDate();
        void setStayDurationDays(int);
        int getStayDurationDays();
        void printReservation();

    private:
        string clientName;
        Date* checkInDate;
        int stayDurationDays;
};

#endif // RESERVATION_H
