
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdexcept>


using namespace std;


struct node {

    //katagrafi gewgrafikwn sintetagmenwn
    string x, y, moving_to;
    int notmoving;

    //wra katagrafis
    string hours, minutes, seconds;

    //deiktes
    node* next;
    node* previous;
};

class linked_list
{
private:
    node* head, * tail;
    double dimension, dmin, dmax;
    double endX, endY;

public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
        dmin = 0;
        dmax = 0;
        endX = 0;
        endY = 0;
    }

    void add_node()
    {
       
        string* timer;
        string* coor;
        int notmoving;
        node* tmp = new node;
        tmp->next = NULL;
        tmp->previous = NULL;
        
      

        if (head == NULL)
        {
            tmp->hours = "00";
            tmp->minutes = "00";
            tmp->seconds = "00";
            setDestinationX(fRand(getMinCoordinate(), getMaxCoordinate()));
            setDestinationY(fRand(getMinCoordinate(), getMaxCoordinate()));
            tmp->x = to_string(getDestinationX());
            tmp->y = to_string(getDestinationY());
            tmp->notmoving = 6;
            head = tmp;
            tail = tmp;
        }
        else
        {
            //Setting timestamp
            timer = get_time(tail->hours, tail->minutes, tail->seconds);
            tmp->hours = timer[0];
            tmp->minutes = timer[1];
            tmp->seconds = timer[2];

            
            //Setting coordinates
            if (tail -> notmoving > 0)
            {
                tmp->x = tail->x;
                tmp->y = tail->y;
                tmp->notmoving = tail->notmoving - 1;

            }
            else
            {
                coor = get_coordinates(tail-> x,tail-> y);
                tmp->x = coor[0];
                tmp->y = coor[1];
                //When destination is completed, give another one
                if (tmp->x == to_string(getDestinationX()) && tmp->y == to_string(getDestinationY())) {
                    tmp->notmoving = 5;//rand() % 40 + 120;
                    setDestinationX(fRand(getMinCoordinate(), getMaxCoordinate()));
                    setDestinationY(fRand(getMinCoordinate(), getMaxCoordinate()));
                    tmp->moving_to = "MOVING TO: (" + to_string(getDestinationX())+ " : " + to_string(getDestinationY()) + ")";
                }

            }
           
            

            //Setting linked list
            tail->next = tmp;
            (tail->next)->previous = tail;
            tail = tail->next;
        }
    }

    void add_node(string are_x, string are_y, string to_x, string to_y)
    {

        string* timer;
        string* coor;
        node* tmp = new node;
        tmp->next = NULL;
        tmp->previous = NULL;



        if (head == NULL)
        {
            tmp->hours = "00";
            tmp->minutes = "00";
            tmp->seconds = "00";
            setDestinationX(atof(to_x.c_str()));
            setDestinationY(atof(to_y.c_str()));
            tmp->x = are_x;
            tmp->y = are_y;
            head = tmp;
            tail = tmp;
        }
        else
        {
            //Setting timestamp
            timer = get_time(tail->hours, tail->minutes, tail->seconds);
            tmp->hours = timer[0];
            tmp->minutes = timer[1];
            tmp->seconds = timer[2];

            //Setting coordinates
            coor = get_coordinates(tail->x, tail->y);
            tmp->x = coor[0];
            tmp->y = coor[1];

            //Setting linked list
            tail->next = tmp;
            (tail->next)->previous = tail;
            tail = tail->next;
        }
    }

   
    string* get_coordinates(string p_x, string p_y) {


        double x, y;
        double speed, distance;
        string* coor = new string[2];
        
        x = atof(p_x.c_str());
        y = atof(p_y.c_str());

        //speed between 3-6 km/h castin in cm/s
        speed = fRand(0.008, 0.016);

       
        //radius of the circle is the distance
        distance = speed * 30;
        double tmp;
       
      //generate a random way of walk
        int tixeos = rand() % 2;

       //if the random number is 0 tha kinithei prwta ston aksona y , an eine 1 ston x
        if (tixeos == 0 || (x == getDestinationX() && y != getDestinationY()))
        {
            if (y > getDestinationY())
            {
                tmp = y - distance;
                if (tmp > getDestinationY())
                    y = tmp;
                else y = getDestinationY();
            }

            else  if (y < getDestinationY())
            {
                tmp = y;
                tmp = y + distance;
                if (tmp < getDestinationY())
                    y = tmp;
                else y = getDestinationY();
            }
        }
        else if (tixeos == 1 || (y == getDestinationY() && x != getDestinationY()))
        {

            if (x > getDestinationX())
            {
                tmp = x - distance;
                if (tmp > getDestinationX())
                    x = tmp;
                else x = getDestinationX();
            }

            else  if (x < getDestinationX())
            {
                tmp = x;
                tmp = x + distance;
                if (tmp < getDestinationX())
                    x = tmp;
                else x = getDestinationX();
            }
        }
                      
   
        coor[0] = to_string(x);
        coor[1] = to_string(y);
       
        if (coor[0].length() == 1) coor[0].insert(0, "0");
        if (coor[1].length() == 1) coor[1].insert(0, "0");
        return coor;
       

    }


    string* get_time(string p_hour, string p_minute, string p_sec) {
        int hour, minute, sec;
        string* time = new string[3];
        hour = stoi(p_hour);
        minute = stoi(p_minute);
        sec = stoi(p_sec);
        //change time
        if (sec == 30) {
            sec = 0;
            if (minute == 59) {
                minute = 0;
                if (hour == 23) {
                    hour = 0;
                }
                else {
                    hour += 1;
                }
            }
            else {
                minute += 1;
            }
        }
        else {
            sec = 30;
        }
        //display time with strings
        time[0] = to_string(hour);
        time[1] = to_string(minute);
        time[2] = to_string(sec);
        if (time[0].length() == 1) time[0].insert(0, "0");
        if (time[1].length() == 1) time[1].insert(0, "0");
        if (time[2].length() == 1) time[2].insert(0, "0");

        return time;
    }


    node* return_tail() {
        return tail;
    }

    node* return_head() {
        return head;
    }

    void displayFromStart() {
        node* temp = head;
        while (temp != NULL) {
            cout << "\n"<<temp->hours << ":" << temp->minutes << ":" << temp->seconds << "\n";
            cout << "WE ARE AT: (" << temp->x << "," << temp->y << ")\n";
            if (temp->moving_to != "")  cout << temp->moving_to + "\n\n";
            temp = temp->next;
        }
    }


    double fRand(double fMin, double  fMax)
    {
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

   

    void setMinCoordinate(double dmin)
    {
        this->dmin = dmin;
    }

    void setMaxCoordinate(double dmax)
    {
        this->dmax = dmax;
    }

    void setDestinationX(double tx)
    {
        this->endX = tx;
    }

    void setDestinationY(double ty)
    {
        this->endY = ty;
    }

    double getDimension()
    {
        return abs(getMaxCoordinate()) - abs(getMinCoordinate());
    }

    double getMinCoordinate()
    {
        return this->dmin;
    }

     double getMaxCoordinate()
    {
        return this->dmax;
    }

     double getDestinationX()
     {
         return this->endX;
     }

     double getDestinationY()
     {
         return this->endY;
     }

     string get_tail_x() {
         return tail->x;
     }

     string get_tail_y() {
         return tail->y;
     }
    
};

class day {
public:
    linked_list people[40];
     day(){
     }

};

bool Possible_Covid19_Infection(linked_list person[4], int day_num,day covid19_patients[4]) {
    bool danger_zone = false;
    double R = 1,user_x,user_y,patient_x,patient_y;
    int min_time_nearby = 15, max_minutes_after = 100;
    int time_nearby;
    int counter = 0;

    for (int p = 0; p < 40;p++) {
        //cout << "---------------------NEW PATIENT----------------------------\n";
        time_nearby = 0;
        counter = 0;
        node* patient = covid19_patients[day_num].people[p].return_head();
        node* user = person[day_num].return_head();
        while (user != NULL) {
            //temp patient and user
            node* temp_patient = patient;
            node* temp_user = user;
            //setting user and patient coords
            user_x = atof(user->x.c_str());
            user_y = atof(user->y.c_str());
            patient_x = atof(patient->x.c_str());
            patient_y = atof(patient->y.c_str());
            //checks if the user was in patients R at most 4 hours later, or less
            int i = 0;
            while(i<max_minutes_after*2 && temp_user!=NULL) {
                //cout << "Node: " << counter<< " | i: " << i << " | User_X: " << user_x << " | User_Y: " << user_y << " | Patient_X: " << patient_x << " | Patient_Y: " << patient_y << " | Time_NearBy: " << time_nearby << "\n";
                user_x = atof(temp_user->x.c_str());
                user_y = atof(temp_user->y.c_str());
                //check R
                if (abs(patient_x - user_x) <= R || abs(patient_y - user_y) <= R) {
                    time_nearby += 1;
                    user = temp_user;
                    break;
                }
                temp_user = temp_user->next;
                i += 1;
            }
            if (time_nearby >= min_time_nearby * 2) {
                danger_zone = true;
                return danger_zone;
            }
            user = user->next;
            patient = patient->next;
            counter += 1;
        }
        //checks if user has arrived to destination by the end of the day. If not, it continues searching and the next day
        //IT DOSE THE EXACT SAME THING AS ABOVE, JUST FOR THE NEXT DAY UNTIL USER ARRIVES AT DESTINATION
        if (day_num < 3) {
            node* patient = covid19_patients[day_num+1].people[p].return_head();
            node* user = person[day_num+1].return_head();
            
            while (((patient->x != to_string(person[day_num+1].getDestinationX())) || (patient->y != to_string(person[day_num+1].getDestinationY()))) && (user!=NULL && patient != NULL)) {
                //cout << "-----------------------NEXT DAY--------------------------\n";
                //temp patient and user
                node* temp_patient = patient;
                node* temp_user = user;
                //setting user and patient coords
                user_x = atof(user->x.c_str());
                user_y = atof(user->y.c_str());
                patient_x = atof(patient->x.c_str());
                patient_y = atof(patient->y.c_str());
                //checks if the user was in patients R at most 4 hours later, or less
                int i = 0;
                while (i < max_minutes_after * 2 && temp_user != NULL) {
                //cout << "Node: " << counter << " | i: " << i << " | User_X: " << user_x << " | User_Y: " << user_y << " | Dest_X: " << person[day_num].getDestinationX() << " | Dest_Y: " << person[day_num].getDestinationY() << " | Time_NearBy: " << time_nearby << "\n";
                    user_x = atof(temp_user->x.c_str());
                    user_y = atof(temp_user->y.c_str());
                    //check R
                    if (abs(patient_x - user_x) <= R || abs(patient_y - user_y) <= R) {
                        time_nearby += 1;
                        user = temp_user;
                        break;
                    }
                    //it must stop when user reaches his destination
                    if ((patient->x == to_string(person[day_num].getDestinationX())) && (patient->y == to_string(person[day_num].getDestinationY()))) {
                        if (time_nearby >= min_time_nearby * 2) {
                            danger_zone = true;
                            return danger_zone;
                        }
                    }
                    else {
                        temp_user = temp_user->next;
                        i += 1;           
                    }
                    
                }
                if (time_nearby >= min_time_nearby * 2) {
                    danger_zone = true;
                    return danger_zone;
                }
                user = user->next;
                patient = patient->next;
            }
        }
        cout << "\n The user you gave had no interaction with patient: " << p+1 << ". There are "<<40-(p+1)<<" left to check. Please wait...\n";
    }
    return false;
}




//Number of days we want to use
day days[4];
day patients_days[4];



 void create_routes(double dmin, double dmax, int users, string array ) {
    bool arrived;
    string current_x, current_y, to_arrive_x, to_arrive_y;
    for (int p = 0; p < users; p++) {
        arrived = true;
        current_x = "";
        current_y = "";
        to_arrive_x = "";
        to_arrive_y = "";
        //d is equal to the number of days we have
        for (int d = 0; d < 4; d++) {
            linked_list person;
            person.setMaxCoordinate(dmax);
            person.setMinCoordinate(dmin);
            //  i == 2.880 because a day has 1.440 minuutes and we create a new node every half a minute(30 sec)
            for (int i = 0; i < 2880; i++) {
                if (arrived) {
                    person.add_node();
                }
                else {
                    person.add_node(current_x, current_y, to_arrive_x, to_arrive_y);
                    arrived = true;
                }
            }
            if ((person.get_tail_x() != to_string(person.getDestinationX())) || (person.get_tail_y() != to_string(person.getDestinationY()))) {
                current_x = person.get_tail_x();
                current_y = person.get_tail_y();
                to_arrive_x = to_string(person.getDestinationX());
                to_arrive_y = to_string(person.getDestinationY());
                arrived = false;
            }
            if (array == "covid19") {
                patients_days[d].people[p] = person;
            }
            else {
                days[d].people[p] = person;
            }
           

        }
    }
}

 bool function1_menu(){
     int pos;
     linked_list random_user[4];
     cout << "\nChoose which user to examine for being in dangerous zone:\n Give a number between 1 and 40 to choose user.(Press 0 if you want to exit this function).\n ";
     while (true) {
         cin >> pos;
         if (pos == 0) {
             return false;
         }
         else if (pos > 40 || pos < 1) {
             cout << "Please choose a number between 1 and 40.\n";
         }
         else {
             pos = pos - 1;
             break;
         }
     }

     for (int i = 0; i < 4; i++) {
         random_user[i] = days[i].people[pos];
     }

     int choose_day;
     cout << "\nChoose a day in order to start searching. Choose a number between 1-4.\n ";
     while (true) {
         cin >> choose_day;
         if (choose_day > 4 || choose_day < 1) {
             cout << "Please choose a number between 1 and 4.\n";
         }
         else {
             choose_day = choose_day - 1;
             break;
         }
     }

     cout << "And the answer is...\n";
     if (Possible_Covid19_Infection(random_user, choose_day, patients_days)) {
         cout << "\n The user was found near a Covid19 patient. Danger Zone.\n";
     }
     else {
         cout << "\n The user was not found near a Covid19 patient, no reason to panic.\n";
     }
     return true;
 }


 

int main()
{
    double dmin, dmax;
    bool arrived;
    int pos;
    string to_arrive_x, to_arrive_y,current_x,current_y;  
    
       

    //--------------------------------- <MAIN> -----------------------------------------


    while (true) {
        cout << "Please enter the min width : ";
        cin >> dmin;
        cout << "Please enter the max width : ";
        cin >> dmax;
        if (dmax > dmin) {
            cout << "\nRoutes are being created. This proccess may take some minutes. Please wait...\n";
            break;
        }
        else {
            cout << "\nMaximum value must be greater than the minimum.\nPLease type again:\n\n";
            dmin = NULL;
            dmax = NULL;
        }
    }

    //---------------------------------------------------- CREATING 40 USERS --------------------------------------------------------------------------------

    create_routes(dmin, dmax, 40, "users");
    
    //-------------------------------------------SOME COVID19 PATIENTS (5)--------------------------------------------------

    create_routes(dmin, dmax, 40, "covid19");
    
    //------------------------------------------------------- FUNCTION 1---------------------------------------------------------
    
    while (true) {
        if (!function1_menu()) {
            break;
        }
    }
   

    


    //--------------------------------- <\MAIN> -----------------------------------------




   
        


     
     

}

