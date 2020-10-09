#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include "Hotel.h"
#include "Date.h"
#include "Reservation.h"
#include "RBtree.h"
#include "Trie.h"
#include "Node.h"

using namespace std;

int binary_search(vector <Hotel*> &vec, int lo, int hi, int key){//recursion for binary search
    int mid;

    if (lo > hi){
        return -1;
    }else{
        mid = (lo + hi) / 2;
        if (vec[mid]->getId() == key){
            return mid;
        }else if (vec[mid]->getId() > key){
            binary_search(vec, lo, mid - 1, key);
        }else if (vec[mid]->getId() < key){
            binary_search(vec, mid + 1, hi, key);
        }
    }
}

int interpolation_search(vector <Hotel*> &vec, int key, int siz){//loop for interpolation search
    int low = 0;
    int high = siz - 1;
    int mid;

    while (vec[low]->getId() <= key && vec[high]->getId() >= key){
        mid = low + ((key - (vec[low]->getId())) * (high - low)) / ((vec[high]->getId()) - (vec[low]->getId()));
        if (vec[mid]->getId() < key){
            low = mid + 1;
        }else if (vec[mid]->getId() > key){
            low = mid - 1;
        }else{
            return mid;
        }
    }

    if (vec[low]->getId() == key){
        return low;
    }else{
        return -1;
    }
}

int toint(string s){//conversion from string to int
    int result;
    stringstream convert(s);

    if ( !(convert >> result) ){
        result = 0;
    }
    return result;
}

int split(const string &s, char delim, vector<string> &elems){//split the line with delimiter ;
    stringstream ss;
    ss.str(s);
    string item;
    int d=0;

    while (getline(ss, item, delim)) {
        elems.push_back(item);
        d++;
    }
    return d;
}

Date* tokenize_date(string s){//create from a string date(d/m/y) a date object
    int arg1,arg2,arg3;
    istringstream is(s);
    vector<string> date;
    for (string s;getline(is,s,'/');){
        date.push_back(s);
    }
    arg1 = toint(date[0]);
    arg2 = toint(date[1]);
    arg3 = toint(date[2]);
    Date *newdate= new Date(arg1,arg2,arg3);
    return newdate;
}

string convertCheckinDate(Date *input){//convert a date object to string
    string str;
    ostringstream os;

    os << input->getDay() << "/" << input->getMonth() << "/" << input->getYear();
    str = os.str();
    return str;
}

/*vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}*/

int main()
{
    int counter = 0;
    string argument;

    RBtree rbtree;
    Trie trie;
    vector <Hotel*> hotelist;
    vector <string> elems;
    fstream file;
    cout << "Give a name for the file you want to work with(type one character for default file): " << endl;
    cin >> argument ;
    if (argument.length()==1){
        file.open("file.txt");
    }else if (argument.length()>1){
        file.open(argument.c_str());
    }
    file.close();

    int ch;
    do
    {
        cout << "Press 1 to load hotels and reservations from file.\n";
        cout << "Press 2 to save hotels and reservations to file.\n";
        cout << "Press 3 to add a hotel and its reservations to file.\n";
        cout << "Press 4 to search and display a hotel by giving its id.\n";
        cout << "Press 5 to display all Hotels of specific stars category and number of reservations.\n";
        cout << "Press 6 to display reservations by surname search.\n";
        cout << "Press 7 to exit.\n";
        cin >> ch;
        if (ch==1){//load
            if (counter<1){
                if (argument.length()==1){
                    file.open("file.txt");
                }else if (argument.length()>1){
                    file.open(argument.c_str());
                }
                string line,temp_name,temp_client;
                int temp_id,temp_stars,temp_numrooms,temp_staydurationdays;
                Date* temp_date;
                /*while(getline(file,line)){
                        string s;
                        char delim=';';
                        split(line,delim,elems);
                }*/
                char delim=';';
                int index=0;
                int sum_pr_line_size=0;

                while (!file.eof()){
                    int l=0;
                    int curr_line_size;
                    int pr_line_size;
                    getline(file,line);
                    curr_line_size = split(line,delim,elems);
                    cout << "Index: " << index << endl;
                    cout << "curr_line_size: " << curr_line_size << endl;
                    if (index==0){
                        pr_line_size=0;
                    }
                    cout << "pr_line_size: " << pr_line_size << endl;

                    for (int k=0; k<curr_line_size; k++){
                        cout << "k: " << k << endl;
                        if (k==0){
                            temp_id = toint(elems[k+sum_pr_line_size]);
                        }else if (k==1){
                            temp_name = elems[k+sum_pr_line_size];
                        }else if (k==2){
                            temp_stars = toint(elems[k+sum_pr_line_size]);
                        }else if (k==3){
                        temp_numrooms = toint(elems[k+sum_pr_line_size]);
                        }
                        if (k==3){
                            Hotel *hotel = new Hotel(temp_id,temp_name,temp_stars,temp_numrooms);
                            hotelist.push_back(hotel);
                            hotelist[index]->printHotelInfo();
                            rbtree.insert(hotel);
                        }

                        if ((k>=4)&&((k%3)==1)){
                            temp_client = elems[k+sum_pr_line_size];
                        }else if ((k>=4)&&((k%3)==2)){
                            temp_date = tokenize_date(elems[k+sum_pr_line_size]);
                        }else if ((k>=4)&&((k%3)==0)){
                            temp_staydurationdays = toint(elems[k+sum_pr_line_size]);
                        }
                        if((k>=4)&&((k%3)==0)){
                            Reservation *reservation = new Reservation(temp_client,temp_date,temp_staydurationdays);
                            hotelist[index]->hotelReservations.push_back(reservation);
                            hotelist[index]->hotelReservations[l]->printReservation();
                            trie.addWord(hotelist[index]->hotelReservations[l]->getClientName());
                            l++;
                        }

                    }
                    pr_line_size=curr_line_size;
                    sum_pr_line_size=sum_pr_line_size+pr_line_size;
                    index=index+1;
                }

                counter++;
                cout << "Load succesfull.\n";
                file.close();
            }else{
                cout << "File is already loaded.\n";
            }
        }else if (ch==2){//save
            Date* temp_date;
            if (argument.length()==1){
                file.open("file.txt");
            }else if (argument.length()>1){
                file.open(argument.c_str());
            }
            for (int i=0; i<hotelist.size(); i++){

                file << hotelist[i]->getId() << ";" << hotelist[i]->getName() << ";" << hotelist[i]->getStars() << ";" << hotelist[i]->getNumberOfRooms();

                for (int j=0; j<hotelist[i]->hotelReservations.size(); j++){
                    temp_date = hotelist[i]->hotelReservations[j]->getCheckinDate();
                    file << ";" << hotelist[i]->hotelReservations[j]->getClientName() << ";" << convertCheckinDate(temp_date) << ";" << hotelist[i]->hotelReservations[j]->getStayDurationDays();
                }
                file << endl;
            }
            file.close();
            cout << "Save was succesfull\n" ;
        }else if (ch==3){//add a hotel
            string temp_name,temp_client,temp_date;
            int temp,temp_id,temp_stars,temp_numrooms,temp_staydurationdays;
            Date* date;

            cout << "\nGive hotel's id: ";
            cin >> temp_id;
            cin.ignore();
            cout << "\nGive hotel's name:";
            getline(cin,temp_name);
            cout << "\nGive hotel's stars(0-5): ";
            cin >> temp_stars;
            cout << "\nGive hotel's number of rooms: ";
            cin >> temp_numrooms;
            Hotel *newhotel = new Hotel(temp_id,temp_name,temp_stars,temp_numrooms);
            hotelist.push_back(newhotel);
            int l = hotelist.size();
            cout << "How many reservations does the hotel has?\n";
            cin >> temp;
            for (int i=0; i<temp; i++){
                cout << "\nGive name of client of reservation " << i << ": ";
                cin >> temp_client;
                cout << "\nGive check-in date of reservation " << i << "(in this form d/m/y): ";
                cin >> temp_date;
                cout << "\nGive stay duration days of reservation " << i << ": ";
                cin >> temp_staydurationdays;
                date = tokenize_date(temp_date);
                Reservation *newreservation = new Reservation(temp_client,date,temp_staydurationdays);
                hotelist[l-1]->hotelReservations.push_back(newreservation);
            }
        }else if (ch==4){//search id
            int temp,ch_;
            cout << "Give the id of the hotel you want to access.\n";
            cin >> temp;

            cout << "If you want to search with linear search type 1.\n";
            cout << "If you want to search with binary seatch type 2.\n";
            cout << "if you want to search with interpolation search type 3.\n";
            cout << "If you want to search id through red-black tree type 4.\n";
            cin >> ch_;
            if (ch_ == 1){
                for (int i=0; i<hotelist.size(); i++){
                    if (temp == hotelist[i]->getId()){
                        hotelist[i]->printHotelInfo();
                    }
                }
            }else if (ch_ == 2){
                //bubblesort
                int temp_id,temp_stars,temp_numofrooms;
                int flag = 1;
                string temp_name;
                int l = hotelist.size();

                for (int j=1; (j<=l)&&flag; j++){
                flag = 0;
                    for (int i=0; i<l-1; i++){
                        if (hotelist[i]->getId() > hotelist[i+1]->getId()){
                            temp_id = hotelist[i]->getId();
                            temp_name = hotelist[i]->getName();
                            temp_stars = hotelist[i]->getStars();
                            temp_numofrooms = hotelist[i]->getNumberOfRooms();
                            hotelist[i]->setId(hotelist[i+1]->getId());
                            hotelist[i]->setName(hotelist[i+1]->getName());
                            hotelist[i]->setStars(hotelist[i+1]->getStars());
                            hotelist[i]->setNumberOfRooms(hotelist[i+1]->getNumberOfRooms());
                            hotelist[i+1]->setId(temp_id);
                            hotelist[i+1]->setName(temp_name);
                            hotelist[i+1]->setStars(temp_stars);
                            hotelist[i+1]->setNumberOfRooms(temp_numofrooms);
                            hotelist[i]->hotelReservations.swap(hotelist[i+1]->hotelReservations);
                            flag = 1;
                        }
                    }
                }
                cout << "Bubblesort completed.\n";
                int k = binary_search(hotelist,0,l,temp);
                if (k == -1){
                    cout << "The requested id did not match any hotel's id.\n";
                }else if (k>=0){
                    hotelist[k]->printHotelInfo();
                }
            }else if (ch_ == 3){
                //bubblesort
                int temp_id,temp_stars,temp_numofrooms;
                int flag = 1;
                string temp_name;
                int l = hotelist.size();

                for (int j=1; (j<=l)&&flag; j++){
                flag = 0;
                    for (int i=0; i<l-1; i++){
                        if (hotelist[i]->getId() > hotelist[i+1]->getId()){
                            temp_id = hotelist[i]->getId();
                            temp_name = hotelist[i]->getName();
                            temp_stars = hotelist[i]->getStars();
                            temp_numofrooms = hotelist[i]->getNumberOfRooms();
                            hotelist[i]->setId(hotelist[i+1]->getId());
                            hotelist[i]->setName(hotelist[i+1]->getName());
                            hotelist[i]->setStars(hotelist[i+1]->getStars());
                            hotelist[i]->setNumberOfRooms(hotelist[i+1]->getNumberOfRooms());
                            hotelist[i+1]->setId(temp_id);
                            hotelist[i+1]->setName(temp_name);
                            hotelist[i+1]->setStars(temp_stars);
                            hotelist[i+1]->setNumberOfRooms(temp_numofrooms);
                            hotelist[i]->hotelReservations.swap(hotelist[i+1]->hotelReservations);
                            flag = 1;
                        }
                    }
                }
                cout << "Bubblesort completed.\n";
                int k = interpolation_search(hotelist,temp,l);
                if (k == -1){
                    cout << "The requested id did not match any hotel's id.\n";
                }else if (k>=0){
                    hotelist[k]->printHotelInfo();
                }
            }else if (ch_ == 4){
                rbtree.search(temp);
            }
        }else if (ch==5){//search with stars and reservation
            int temp_stars,temp_numofreservations;
            int flag = 0;

            cout << "Give number of stars: \n";
            cin >> temp_stars;
            cout << "Give number of reservations: \n";
            cin >> temp_numofreservations;
            for (int i=0; i<hotelist.size(); i++){
                if (temp_stars==hotelist[i]->getStars()){
                    if(temp_numofreservations==hotelist[i]->hotelReservations.size()){
                        hotelist[i]->printHotelInfo();
                        flag = 1;
                    }
                }
            }
            if (flag == 0){
                cout << "No hotel was found with the specific number of stars and reservations.\n";
            }
        }else if (ch==6){//search for reservation
            string temp_name;
            int ch_;
            bool b;

            cout << "Give surname: \n";
            cin >> temp_name;
            cout << "If you want to search with linear search type 1.\n";
            cout << "If you want to search with trie tree type 2.\n";
            cin >> ch_;
            if (ch_ == 1){
                for (int i=0; i<hotelist.size(); i++){
                    for (int j=0; j<hotelist[i]->hotelReservations.size(); j++){
                        if (temp_name==hotelist[i]->hotelReservations[j]->getClientName()){
                            hotelist[i]->hotelReservations[j]->printReservation();
                        }
                    }
                }
            }else if(ch_ == 2){
                b=trie.searchWord(temp_name);
                if (b == true){
                    cout << "The surname you gave matched a reservation.\n";
                }else if (b == false){
                    cout << "The surname you gave didn't match a reservation.\n";
                }
            }

        }

    }while(ch!=7);
    Hotel::printHotelCounter();
    return 0;
}
