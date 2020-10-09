#include "Reservation.h"
#include "Date.h"

Reservation::Reservation()
{
}

Reservation::Reservation(string clientname,Date* checkinDate,int stayDurationdays){
    clientName = clientname;
    checkInDate = checkinDate;
    stayDurationDays = stayDurationdays;
}

Reservation::~Reservation()
{
}

void Reservation::setClientName(string clientname){
    clientName = clientname;
}

string Reservation::getClientName(){
    return clientName;
}

void Reservation::setCheckinDate(Date* inputdate){
    checkInDate = inputdate;
}

Date* Reservation::getCheckinDate(){
    return checkInDate;
}

void Reservation::setStayDurationDays(int stayDurationdays){
    stayDurationDays = stayDurationdays;
}

int Reservation::getStayDurationDays(){
    return stayDurationDays;
}

void Reservation::printReservation(){
    cout << "Name of client: " << clientName << endl;
    getCheckinDate()->printDate();
    cout << "Duration of staying: " << stayDurationDays << endl;
}
