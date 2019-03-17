#include <iostream>
#include "scheduler.h"
using namespace std;

int main(){
    Time t1(11, 45);
    Time t2(11, 50);
    Time t3(11, 50, "PM");
    Time t4(11, 59, "PM");
    Time t5(23, 59);

    // cout << t1 - t2 << endl;
    // cout << t2 - t1 << endl;
    // cout << t3 - t2 << endl;
    // cout << t5 - t4 << endl;

    Interval i1(Time(4, 0), 150);
    Interval i2(Time(4, 0), Time(6, 30));
    Interval i3(Time(2, 0, "PM"), Time(4, 0, "PM"));
    Interval i4(Time(3, 30, "PM"), Time(6, 0, "PM"));

    // cout << i1.duration() << endl;
    // cout << i2.duration() << endl;
    // cout << i3.duration() << endl;
    // cout << i4.overlap(i3).duration() << endl;

    Time t6(12, 00, "AM");
    Time t7(12, 30, "AM");
    Time t8(12, 00, "PM");
    Time t9(12, 30, "PM");
    Time t10(0, 0);
    Time t11(0, 30);

    // cout << t8.total_minutes << endl;
    // cout << t6.total_minutes << endl;
    // cout << t7.total_minutes << endl;
    // cout << t9.total_minutes << endl;
    // cout << t8 - t6 << endl;

    if (t6 == t10) cout << "equal" << endl;
    else cout << "not equal" << endl;

    if (t6 < t11) cout << "less than" << endl;
    else cout << "not less than" << endl;

    if (t11 > t10) cout << "greater than" << endl;
    else cout << "not greater than" << endl;

    Interval i10(t10, t8);
    Interval i11(Time(5, 15), Time(14, 0));

    Interval iteney = i10.overlap(i11);
    cout << iteney.duration() << endl;
}
