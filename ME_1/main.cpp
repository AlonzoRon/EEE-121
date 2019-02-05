#include <iostream>
#include "scheduler.h"
using namespace std;

int main(){
    Time t1(11, 45);
    Time t2(11, 50);
    Time t3(11, 50, "PM");
    Time t4(11, 59, "PM");
    Time t5(23, 59);

    cout << t1 - t2 << endl;
    cout << t2 - t1 << endl;
    cout << t3 - t2 << endl;
    cout << t5 - t4 << endl;

    Interval i1(Time(4, 0), 150);
    Interval i2(Time(4, 0), Time(6, 30));
    Interval i3(Time(2, 0, "PM"), Time(4, 0, "PM"));
    Interval i4(Time(3, 30, "PM"), Time(6, 0, "PM"));

    cout << i1.duration() << endl;
    cout << i2.duration() << endl;
    cout << i3.duration() << endl;
    cout << i4.overlap(i3).duration() << endl;
}
