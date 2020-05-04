

#include <iostream>
#include <string>
using namespace std;


struct node {
    string hours, minutes, seconds;
    double x, y;
    node* next;
    node* previous;
};

class linked_list
{
private:
    node* head, * tail;
public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }

    void add_node()
    {
        string* time;
        node* tmp = new node;
        tmp->next = NULL;
        tmp->previous = NULL;

        if (head == NULL)
        {
            tmp->hours = "00";
            tmp->minutes = "00";
            tmp->seconds = "00";
            head = tmp;
            tail = tmp;
        }
        else
        {
            //Setting timestamp
            time = get_time(tail->hours, tail->minutes,tail->seconds);
            tmp->hours = time[0];
            tmp->minutes = time[1];
            tmp->seconds = time[2];
            //Setting coordinates

            //Setting linked list
            tail->next = tmp;
            (tail->next)->previous = tail;
            tail = tail->next;
        }
    }

    string *get_time(string p_hour, string p_minute, string p_sec) {
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
            cout << temp->hours << ":" << temp->minutes<< ":" << temp->seconds<<"\n";
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
};

int main()
{
    linked_list prwti_mera;
    //i == 2.880 because a day has 1.440 minuutes and we create a new node every half a minute(30 sec)
    for (int i = 0; i < 2880; i++) {
        prwti_mera.add_node();
    }
    prwti_mera.displayFromStart();
  
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
