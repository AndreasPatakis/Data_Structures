
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <list>


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
                    tmp->notmoving = rand() % 40 + 120;
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

    
};

class day {
public:
    list<linked_list> people;

     day(){}

};

int main()
{
    list<day> days;
    double dmin, dmax;
    
    //to plegma einai tetragwno ara min : xmin=ymin kai max: xmax=ymax

     while (true) {
         cout << "Please enter the min width : ";
         cin >> dmin;
         cout << "Please enter the max width : ";
         cin >> dmax;
         if (dmax > dmin) {
             break;
         }
         else {
             cout << "\nMaximum value must be greater than the minimum.\nPLease type again:\n\n";
             dmin = NULL;
             dmax = NULL;
         }
     }
     
     //d is equal to the number of days we want to create
     for (int d = 0; d <= 1; d++) {
         day day;

         //j is equal to the number of users we want to create
         for (int j = 0; j <= 2; j++) {
             linked_list person;
             person.setMaxCoordinate(dmax);
             person.setMinCoordinate(dmin);

             //  i == 2.880 because a day has 1.440 minuutes and we create a new node every half a minute(30 sec)
             srand(time(NULL));
             for (int i = 0; i < 100; i++) {
                 person.add_node();
             }
             day.people.push_back(person);
         }
         days.push_back(day);
     }
     
    

     for (day day : days) {
         cout << "\n------------------------------ NEW DAY ----------------------------- \n";
         for (linked_list person : day.people) {
             cout << "\n------------------------------ NEW PERSON ----------------------------- \n";
             person.displayFromStart();
         }
     }
    


    
   

}

