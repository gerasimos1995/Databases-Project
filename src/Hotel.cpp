#include "Hotel.h"

int Hotel::hotelCounter=0;
vector<Reservation*> hotelReservations;

Hotel::Hotel()
{
    hotelCounter++;
}

Hotel::Hotel(int id,string name,int stars,int numberOfRooms)
: Id(id),Name(name),Stars(stars),NumberOfRooms(numberOfRooms)
{
    hotelCounter++;
}

Hotel::~Hotel()
{
}

void Hotel::setFullInfo(){
    int id,stars,numberOfRooms;
    string name;
    cout << "Type hotel's id: " << endl;
    cin >> id;
    setId(id);
    cout << "Type hotel's name: " << endl;
    cin >> name;
    setName(name);
    cout << "Type hotel's stars: " << endl;
    cin >> stars;
    setStars(stars);
    cout << "Type hotel's number of rooms: " << endl;
    cin >> numberOfRooms;
    setNumberOfRooms(numberOfRooms);
}

void Hotel::setId(int id){
    Id=id;
}

int Hotel::getId(){
    return Id;
}

void Hotel::setName(string name){
    while (name.length()>256){
        cout<< "The name you typed is too long. Please type another name: " ;
        cin >> name;
    }
    Name = name;
}

string Hotel::getName(){
    return Name;
}

void Hotel::setStars(int stars){
    Stars = stars;
}

int Hotel::getStars(){
    return Stars;
}

void Hotel::setNumberOfRooms(int numberOfRooms){
    NumberOfRooms=numberOfRooms;
}

int Hotel::getNumberOfRooms(){
    return NumberOfRooms;
}

void Hotel::printHotelCounter(){
    cout << "Hotels created: " << hotelCounter << endl;
}

void Hotel::printHotelInfo(){
    cout << "Hotel's id is: " << getId() << endl;
    cout << "Hotel's name is: " << getName() << endl;
    cout << "Hotel's stars are: " << getStars() << endl;
    cout << "Hotel's number of rooms is: " << getNumberOfRooms() << endl;
}
