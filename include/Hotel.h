#ifndef HOTEL_H
#define HOTEL_H
#include <iostream>
#include <string>
#include <vector>
#include "Reservation.h"

using namespace std;

class Hotel
{
    public:
        Hotel();
        Hotel(int,string,int,int);
        ~Hotel();
        void setId(int);
        int getId();
        void setName(string);
        string getName();
        void setStars(int);
        int getStars();
        void setNumberOfRooms(int);
        int getNumberOfRooms();
        void printHotelInfo();
        void setFullInfo();
        static void printHotelCounter();
        vector<Reservation*> hotelReservations;

    private:
        int Id,Stars,NumberOfRooms;
        string Name;
        static int hotelCounter;
};

#endif // HOTEL_H
