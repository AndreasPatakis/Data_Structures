
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdexcept>


using namespace std;



struct node {

    //katagrafi gewgrafikwn sintetagmenwn
    string x, y;

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
       
        string* time;
        string* coor;
        node* tmp = new node;
        tmp->next = NULL;
        tmp->previous = NULL;

      

        if (head == NULL)
        {
            tmp->hours = "00";
            tmp->minutes = "00";
            tmp->seconds = "00";
            tmp->x = to_string(fRand(getMinCoordinate(), getMaxCoordinate()));
            tmp->y = to_string(fRand(getMinCoordinate(), getMaxCoordinate()));
            head = tmp;
            tail = tmp;
        }
        else
        {
            //Setting timestamp
            time = get_time(tail->hours, tail->minutes, tail->seconds);
            tmp->hours = time[0];
            tmp->minutes = time[1];
            tmp->seconds = time[2];

            
              //Setting coordinates
            if (stoi(time[0]) < (rand() % 24))
            {
                tmp->x = tail->x;
                tmp->y = tail->y;

            }
            else
            {
                coor = get_coordinates(tail->x, tail->y);
                tmp->x = coor[0];
                tmp->y = coor[1];
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
        srand(time(0));
        int tixeos = rand() % 2;

       //if the random number is 0 tha kinithei prwta ston aksona y , an eine 1 ston x
        if (tixeos == 0 || x == getDestinationX())
        {
            if (y > getDestinationY())
            {
                tmp = y;
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
        else if (tixeos == 1 || y == getDestinationY())
        {

            if (x > getDestinationX())
            {
                tmp = x;
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
            cout << temp->hours << ":" << temp->minutes << ":" << temp->seconds << "\n";
            cout << "(" << temp->x << "," << temp->y << ") \n";
            temp = temp->next;
        }
    }

    void displayFromFinish() {
        node* temp = tail;
        while (temp != NULL) {
            // kati
            temp = temp->previous;
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

int main()
{

    linked_list ll;
     double dmin, dmax, tx, ty;
   
    //to plegma einai tetragwno ara min : xmin=ymin kai max: xmax=ymax

     cout << "Please enter the min width : ";
     cin >> dmin;
     cout << "Please enter the max width : ";
     cin >> dmax;

     ll.setMaxCoordinate(dmax);
     ll.setMinCoordinate(dmin);

     cout << "You walk in a : " << ll.getDimension() << "*" << ll.getDimension() << "region. \n";

     cout << "Now please give your destination coordinates. \n X: ";
     cin >> tx;
     cout << "Y: ";
     cin >> ty;

     ll.setDestinationX(tx);
     ll.setDestinationY(ty);

     //protimera
       //  i == 2.880 because a day has 1.440 minuutes and we create a new node every half a minute(30 sec)
     for (int i = 0; i < 2880; i++) {
         ll.add_node();
     }
     ll.displayFromStart();


     //xeirismos pithanotitas o xristis na valei lathos input
     //dmin,dmax double
     //tx,ty double kai dmin<x,y<dmax


    /* cout << "Please enter the min width : ";
     try {
         cin >> dmin;
         if (isnan(dmin)==true) 
             throw invalid_argument("Invalid syntax.");
         
         else
            return dmin;
     }
     catch (invalid_argument & e) {
         cout << "The min must be a number! "<< endl ;
         return 0;
     }

    cout << "Please enter the max width : ";
    try {
        cin >> dmax;
        if (isnan(dmax) == true) {
            throw invalid_argument("Invalid syntax.");
        }
        return dmax;
    }
    catch (invalid_argument & e) {
        cout << "The min must be a number! " << endl;
        return 0;
    }
   
   ll.setMaxCoordinate(dmax);
   ll.setMinCoordinate(dmin);

    cout << "You walk in a : " << ll.getDimension() << "*" << ll.getDimension() << "region. \n";


    cout << "Now please give your destination coordinates. \n X: ";
    try {
        cin >> tx;
        if (isnan(tx) == true)
            throw invalid_argument("The min must be a number!");
        else if (tx < ll.getMinCoordinate() || tx > ll.getMaxCoordinate())
            throw invalid_argument("Coordinates must be inside min and max dimension.");


         return tx;
    }
    catch (invalid_argument & e) {
        cout << &e << endl;
        return 0;
    }
    cout << "Y: " ;
    try {
        cin >> ty;
        if (isnan(ty) == true)
            throw invalid_argument("The min must be a number!");
        else if (ty < ll.getMinCoordinate() || ty > ll.getMaxCoordinate())
            throw invalid_argument("Coordinates must be inside min and max dimension.");


        return ty;
    }
    catch (invalid_argument & e) {
        cout << &e << endl;
        return 0;
    }

    ll.setDestinationX(tx);
     ll.setDestinationY(ty);

       //protimera
       //  i == 2.880 because a day has 1.440 minuutes and we create a new node every half a minute(30 sec)
     for (int i = 0; i < 20; i++) {
         ll.add_node();
     }
     ll.displayFromStart();

    */
   

}

