
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdexcept>


using namespace std;


struct node {

    //katagrafi gewgrafikwn sintetagmenwn
    string x, y, moving_to, would_be_x, would_be_y;
    int node_number,notmoving,gps_failure_left, gps_failure_in_node;

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
        node* tmp = new node;
        tmp->next = NULL;
        tmp->previous = NULL;
        
      

        if (head == NULL)
        {
            tmp->hours = "00";
            tmp->minutes = "00";
            tmp->seconds = "00";
            tmp->node_number = 0;
            setDestinationX(fRand(getMinCoordinate(), getMaxCoordinate()));
            setDestinationY(fRand(getMinCoordinate(), getMaxCoordinate()));
            tmp->x = to_string(getDestinationX()); tmp->would_be_x = tmp->x;
            tmp->y = to_string(getDestinationY()); tmp->would_be_y = tmp->y;
            tmp->notmoving = rand() % 20 + 6;
            tmp->gps_failure_left = rand() % 10 + 2;
            tmp->gps_failure_in_node = rand() % 2869 + 1;
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
            tmp->node_number = tail->node_number + 1;
            tmp->gps_failure_in_node = tail->gps_failure_in_node;
            tmp->gps_failure_left = tail->gps_failure_left;

            
            //Setting coordinates
            if (tail -> notmoving > 0)
            {
                tmp->x = tail->x; tmp->would_be_x = tmp->x;
                tmp->y = tail->y; tmp->would_be_y = tmp->y;
                tmp->notmoving = tail->notmoving - 1;

            }
            else
            {
                if (tmp->gps_failure_left != -1 && tmp->node_number >= tmp->gps_failure_in_node) {
                    tmp->x = "NO_DATA";
                    tmp->y = "NO_DATA";
                    coor = get_coordinates(tail->would_be_x, tail->would_be_y);
                    tmp->would_be_x = coor[0]; tmp->would_be_y = coor[1];
                    tmp->gps_failure_left = tail->gps_failure_left - 1;
                    if (tmp->gps_failure_left == -1) {
                        tmp->gps_failure_left = rand() % 10 + 2;
                        tmp->gps_failure_in_node = rand() % 2869 + tmp->node_number;
                        tmp->x = tmp->would_be_x;
                        tmp->y = tmp->would_be_y;
                    }
                }
                else {
                    coor = get_coordinates(tail->x, tail->y);
                    tmp->x = coor[0]; tmp->would_be_x = tmp->x;
                    tmp->y = coor[1]; tmp->would_be_y = tmp->y;
                    //When destination is completed, give another one
                    if (tmp->x == to_string(getDestinationX()) && tmp->y == to_string(getDestinationY())) {
                        tmp->notmoving = rand() % 40 + 120;
                        setDestinationX(fRand(getMinCoordinate(), getMaxCoordinate()));
                        setDestinationY(fRand(getMinCoordinate(), getMaxCoordinate()));
                        tmp->moving_to = "MOVING TO: (" + to_string(getDestinationX()) + " : " + to_string(getDestinationY()) + ")";
                    }
                }
               
            }
                    

            //Setting linked list
            tail->next = tmp;
            (tail->next)->previous = tail;
            tail = tail->next;
        }
    }

    //Handling next day if user has not arrived in destination by 23:59:30
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
            tmp->node_number = 0;
            setDestinationX(atof(to_x.c_str()));
            setDestinationY(atof(to_y.c_str()));
            tmp->x = are_x;
            tmp->y = are_y;
            tmp->gps_failure_left = rand() % 10 + 2;
            tmp->gps_failure_in_node = rand() % 2869 + 1;
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
            cout << "\n"<<temp->hours << ":" << temp->minutes << ":" << temp->seconds <<" | Node: "<<temp->node_number<< " | Will_fail_in_node: "<<temp->gps_failure_in_node<< " | For: "<< temp->gps_failure_left<<"\n";
            cout << "WE ARE AT: (" << temp->x << "," << temp->y << ")"<<" | Would_be: ("<<temp->would_be_x<<" , " <<temp->would_be_y<<")\n";
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

     void Repair() {
         string current_x, current_y, to_go_x, to_go_y;
         double* speed;
         int time;
         for (int p = 0; p < 40; p++) {
             //cout << "-----------------------NEW PERSON-----------------------------------\n";
             node* curr_person = this->people[p].return_head();
             node* person = curr_person;
             while (curr_person != NULL) {
                // cout << "--------NEW NODE--------\n";
                 person = curr_person;
                 node* start_repair = new node;
                 time = 1;
                 //Find the first node that has no data
                 while (person != NULL) {
                     if (person->x == "NO_DATA") {
                         current_x = person->previous->x;
                         current_y = person->previous->y;
                         start_repair = person;
                         break;
                     }
                     else {
                         person = person->next;
                     }
                     if (person != NULL) {
                         //cout << "Node: " << person->node_number << " | Person_x: " << person->x << "\n";
                     }             
                 }
                 //Find the last node that has no data
                 while (person != NULL) {
                     if (person->x != "NO_DATA") {
                         to_go_x = person->x;
                         to_go_y = person->y;
                         curr_person = person;
                         break;
                     }
                     time += 1;
                     person = person->next;
                 }
                 if (person != NULL){
                     //Repair the route
                     person = start_repair;
                     speed = get_speed(current_x, current_y, to_go_x, to_go_y, time);
                     //Moves X
                     for (int i = 0; i < speed[2]; i++) {
                         if (stod(current_x) > stod(to_go_x)) {
                             person->x = to_string(stod(current_x) - speed[0]);
                             person->y = person->previous->y;
                             current_x = person->x;
                         }
                         else if (stod(current_x) < stod(to_go_x)) {
                             person->x = to_string(stod(current_x) + speed[0]);
                             person->y = person->previous->y;
                             current_x = person->x;
                         }
                         else { person->x = current_x; person->y = current_y; }
                         person = person->next;
                     }
                     //Moves Y
                     for (int i = 0; i < speed[3]; i++) {
                         if (stod(current_y) > stod(to_go_y)) {
                             person->y = to_string(stod(current_y) - speed[1]);
                             person->x = person->previous->x;
                             current_y = person->y;
                         }
                         else if (stod(current_y) < stod(to_go_y)) {
                             person->y = to_string(stod(current_y) + speed[1]);
                             person->x = person->previous->x;
                             current_y = person->y;
                         }
                         else { person->x = current_x; person->y = current_y; }
                         person = person->next;
                     }
                     curr_person = curr_person->next;
                 }
                 else { break; }                 
             }
             
         }
     }

     double* get_speed(string p_cur_x, string p_cur_y,string p_go_x,string p_go_y,int p_time) {

         double cur_x, cur_y, go_x, go_y, speed_x,speed_y,nodes_x,nodes_y;
         double* coor = new double[4];

         cur_x = stod(p_cur_x); 
         cur_y = stod(p_cur_y);
         go_x = stod(p_go_x);
         go_y = stod(p_go_y);
         
         speed_x = abs(cur_x - go_x);
         speed_y = abs(cur_y - go_y);

         if (p_time % 2 == 0) {
             nodes_x = p_time / 2; nodes_y = nodes_x;
             speed_x = speed_x / (p_time / 2);
             speed_y = speed_y / (p_time / 2);
         }
         else {
             if (speed_x > speed_y) {
                 nodes_x = (abs(p_time / 2) + 1); nodes_y = abs(p_time / 2);
                 speed_x = speed_x / (abs(p_time / 2 )+1);
                 speed_y = speed_y / abs(p_time / 2);
             }
             else {
                 nodes_x = abs(p_time / 2 ); nodes_y = (abs(p_time / 2) + 1);
                 speed_y = speed_y / (abs(p_time / 2) + 1);
                 speed_x = speed_x / abs(p_time / 2);
             }
         }

         coor[0] = speed_x;
         coor[1] = speed_y;
         coor[2] = nodes_x;
         coor[3] = nodes_y;
         return coor;


     }
};

bool Possible_Covid19_Infection(linked_list person[4], int day_num,day covid19_patients[4]) {
    bool danger_zone = false;
    double R = 1,user_x,user_y,patient_x,patient_y;
    int min_time_nearby = 15, max_minutes_after = 100;
    int time_nearby;
    int counter = 0;

    for (int p = 0; p < 40;p++) {
       // cout << "---------------------NEW PATIENT----------------------------\n";
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
            while (user != NULL && patient != NULL) {
               if (((patient->x != to_string(person[day_num + 1].getDestinationX())) || (patient->y != to_string(person[day_num + 1].getDestinationY())))){
                   // cout << "-----------------------NEXT DAY--------------------------\n";
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
                        // cout << "Node: " << counter << " | i: " << i << " | User_X: " << user_x << " | User_Y: " << user_y << " | Dest_X: " << person[day_num].getDestinationX() << " | Dest_Y: " << person[day_num].getDestinationY() << " | Time_NearBy: " << time_nearby << "\n";
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
               else {
                  break;
               }
                
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

 double dmin, dmax;

 void main_menu() {
     string input;
     while (true) {
         while (true) {
             cout << "Please enter the min width : ";
             cin >> input;
             try {
                 dmin = stod(input);
                 break;
             }
             catch (const std::invalid_argument & ia) {
                 std::cerr << "\nInvalid argument: Please give an integer.\n";
             }
         }

         while (true) {
             cout << "Please enter the max width : ";
             cin >> input;
             try {
                 dmax = stod(input);
                 break;
             }
             catch (const std::invalid_argument & ia) {
                 std::cerr << "\nInvalid argument: Please give an integer.\n";
             }
         }
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
 }

 void function1_menu(){
     string input;
     int pos;
     linked_list random_user[4];
     while (true) {
         cout << "\nChoose which user to examine for being in dangerous zone:\n Give a number between 1 and 40 to choose user.\n ";
         while (true) {
             cin >> input;
             try {
                 pos = stod(input);
                 if (pos > 40 || pos < 1) {
                     cout << "Please choose a number between 1 and 40.\n";
                 }
                 else {
                     pos = pos - 1;
                     break;
                 }
                 break;
             }
             catch (const std::invalid_argument & ia) {
                 std::cerr << "\nInvalid argument: Please give an integer.\n";
             }
         }

         for (int i = 0; i < 4; i++) {
             random_user[i] = days[i].people[pos];
         }

         int choose_day;
         cout << "\nChoose a day in order to start searching. Choose a number between 1-4.\n ";
         while (true) {
             cin >> input;
             try {
                 choose_day = stod(input);
                 if (choose_day > 4 || choose_day < 1) {
                     cout << "Please choose a number between 1 and 4.\n";
                 }
                 else {
                     choose_day = choose_day - 1;
                     break;
                 }
             }
             catch (const std::invalid_argument & ia) {
                 std::cerr << "\nInvalid argument: Please give an integer.\n";
             }
             
         }

         cout << "And the answer is...\n";
         if (Possible_Covid19_Infection(random_user, choose_day, patients_days)) {
             cout << "\n The user was found near a Covid19 patient. Danger Zone.\n";
         }
         else {
             cout << "\n The user was not found near a Covid19 patient, no reason to panic.\n";
         }
         cout << "\nDo you want to repeat this function again? [y/n]\n";
         cin >> input;
         if (input == "y" || input == "yes") {
             //pass
         }
         else if (input == "n" || input == "no") {
             break;
         }
         else {
             cout << "\nPlease answer y for yes or n for no.\n";
         }
     }
     
 }

 int Find_Crowded_Places(int day_num, int time_interval[2], double square_region[2], int min_stay_duration) {
     int user_inside = 0;
     int duration;
     int hours = time_interval[1] - time_interval[0];
     string start_time = to_string(time_interval[0]), finish_time = to_string(time_interval[1]);
     double x1, x2, y1, y2, user_x, user_y;
     if (time_interval[0] < 9) { start_time = "0" + to_string(time_interval[0]); }
     if (time_interval[1] < 9) { finish_time = "0" + to_string(time_interval[1]); }
     for (int p = 0; p < 40; p++) {
        // cout << "\n------------------------ NEW USER -----------------------------------\n";
         x1 = square_region[0];
         x2 = square_region[1];
         y1 = square_region[0];
         y2 = square_region[1];
         if (x1 > x2) { x2 = square_region[0]; x1 = square_region[1]; }
         if (y1 > y2) { y1 = y2; y1 = square_region[1]; }
         duration = min_stay_duration * 2;
         node* user = days[day_num].people[p].return_head();
         while (user->hours != start_time) {
             user = user->next;
         }
         int i = 0;
        while(i < hours*120 && user != NULL) {
             //cout << "Time: " << user->hours << ":" << user->minutes << ":" << user->seconds << " | User_X: " << user->x << " | User_Y: " << user->y << " | X: " << x1 << " | Y:" << x2 << " | Duration: " << duration << " | Inside: " << user_inside<<"\n";
             user_x = atof(user->x.c_str());
             user_y = atof(user->y.c_str());
             if ((user_x >= x1 && user_x <= x2) && (user_y >= y1 && user_y <= y2)) {
                 duration -= 1;
             }
             if (duration == 0) {
                 user_inside += 1;
                 break;
             }
             user = user->next;
             i += 1;
         }
     }
     return user_inside;
 }
 
 void function2_menu() {
     int time_interval[2], day_num, min_stay_duration, results;
     double square_region[2];
     string input;
     while (true) {
         cout << "\nIt's time to see how many users where found in a given square region of interest.\n";
         while (true) {
             cout << "\n To begin with, give the X coordinate of the square region you want to search in.(Double precision number.)\n";
             cin >> input;
             try {
                 square_region[0] = stod(input);
                 break;
             }
             catch (const std::invalid_argument & ia) {
                 std::cerr << "\nInvalid argument: Please give a double precision number.\n";
             }
         }
         while (true) {
             cout << "\n Now give the Y coordinate of the square region you want to search in.(Double precision number.)\n";
             cin >> input;
             try {
                 square_region[1] = stod(input);
                 break;
             }
             catch (const std::invalid_argument & ia) {
                 std::cerr << "\nInvalid argument: Please give a double precision number.\n";
             }
         }

         while (true) {
             while (true) {
                 cout << "\n Give the an hour to start searching from. It must be a number between 0 - 23( which means 00:00:00 - 23:59:30).\n";
                 cin >> input;
                 try {
                     time_interval[0] = stoi(input);
                     if (time_interval[0] < 0 || time_interval[0] > 23) {
                         cout << "\n Time must be a number between 0 - 23( which means 00:00:00 - 23:59:30).Please try again\n";
                     }
                     else {
                         break;
                     }
                 }
                 catch (const std::invalid_argument & ia) {
                     std::cerr << "\nInvalid argument: Please give an interger.\n";
                 }
             }
             while (true) {
                 cout << "\n Now give the the hour of to stop searching. It must be a number between 0 - 23( which means 00:00:00 - 23:59:30).\n";
                 cin >> input;
                 try {
                     time_interval[1] = stoi(input);
                     if (time_interval[1] < 0 || time_interval[1] > 23) {
                         cout << "\n Time must be a number between 0 - 23( which means 00:00:00 - 23:59:30).Please try again\n";
                     }
                     else {
                         break;
                     }
                 }
                 catch (const std::invalid_argument & ia) {
                     std::cerr << "\nInvalid argument: Please give an interger.\n";
                 }
             }
             if (time_interval[1] <= time_interval[0]) {
                 cout << "\n The ending hour must be greater than the starting one. Please try again.\n";
             }
             else {
                 break;
             }
         }
        

         while (true) {
             cout << "\n Give a minimum stay duration(in minutes).\n";
             cin >> input;
             try {
                 min_stay_duration = stoi(input);
                 break;
             }
             catch (const std::invalid_argument & ia) {
                 std::cerr << "\nInvalid argument: Please give an interger.\n";
             }
         }
         while (true) {
             cout << "\n Lastly, choose a day between 1-4 in which the search will take place.\n";
             cin >> input;
             try {
                 day_num = stoi(input);
                 if (day_num > 4 || day_num < 1) {
                     cout << "\n Give a number between 1 and 4. Please try again.\n";
                 }
                 else {
                     break;
                 }
             }
             catch (const std::invalid_argument & ia) {
                 std::cerr << "\nInvalid argument: Please give an interger.\n";
             }
         }
         results = Find_Crowded_Places(day_num, time_interval, square_region, min_stay_duration);
         cout << "\n" << results << " where found inside the square region, day and time interval you gave.\n";
         cout << "\nDo you want to repeat this function again? [y/n]\n";
         cin >> input;
         if (input == "y" || input == "yes") {
             //pass
         }
         else if (input == "n" || input == "no") {
             break;
         }
         else {
             cout << "\nPlease answer y for yes or n for no.\n";
         }
     }
   
 }

 void function3_menu() {
     for (int d = 0; d < 4; d++) {
         days[d].Repair();
         patients_days[d].Repair();
     }
 }

int main()
{
    bool arrived;
    int pos;
    string to_arrive_x, to_arrive_y,current_x,current_y;  
    

    //--------------------------------- <MAIN> -----------------------------------------

    main_menu();

    //---------------------------------------------------- CREATING 40 USERS --------------------------------------------------------------------------------

    create_routes(dmin, dmax, 40, "users");
   
    //-------------------------------------------SOME COVID19 PATIENTS (5)--------------------------------------------------

    create_routes(dmin, dmax, 40, "covid19");

    //------------------------------------------------------- FUNCTION 1---------------------------------------------------------

    function3_menu();
    
    //------------------------------------------------------- FUNCTION 1---------------------------------------------------------
    
    function1_menu();
   
    //------------------------------------------------------- FUNCTION 2---------------------------------------------------------

    function2_menu();

    //--------------------------------- <\MAIN> -----------------------------------------
    
   

}

