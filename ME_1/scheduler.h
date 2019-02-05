class Time{
public:
    Time(unsigned int = 0, unsigned int = 0);
    Time(unsigned int, unsigned int, std::string);

    bool operator==(Time);
    bool operator<(Time);
    bool operator>(Time);

    int operator-(Time);

private:
    unsigned int hh, mm;
    unsigned int total_minutes;
};

Time::Time(unsigned int hh, unsigned int mm){
    this -> hh = hh;
    this -> mm = mm;

    this -> total_minutes = 60 * this -> hh + this -> mm;
}

Time::Time(unsigned int hh, unsigned int mm, std::string meridiem){
    if (meridiem == "AM") {
        this -> hh = hh;
    }
    else if (meridiem == "PM") {
        this -> hh = 12 + hh;
    }
        this -> mm = mm;
        this -> total_minutes = 60 * this -> hh + this -> mm;
}

bool Time::operator==(Time other){
    if (this -> total_minutes == other.total_minutes) return true;
    else return false;
}

bool Time::operator<(Time other){
    if (this -> total_minutes < other.total_minutes) return true;
    else return false;
}

bool Time::operator>(Time other){
    if (this -> total_minutes > other.total_minutes) return true;
    else return false;
}
int Time::operator-(Time other){
    return this -> total_minutes - other.total_minutes;
}

class Interval{
public:
    Time start, end;

    Interval(Time, unsigned int);
    Interval(Time, Time);

    unsigned int duration();
    Interval overlap(Interval);

private:
    unsigned int minutes_start;
    unsigned int minutes_end;
    unsigned int minutes_duration;
};

Interval::Interval(Time time, unsigned int duration){
    Time temp(0, 0);
    this -> minutes_start = time - temp;
    this -> minutes_end = this -> minutes_start + duration;
    this -> minutes_duration = this -> minutes_end - this -> minutes_start;
}

Interval::Interval(Time time_1, Time time_2){
    Time temp(0, 0);
    this -> minutes_start = time_1 - temp;
    this -> minutes_end = time_2 - temp;
    this -> minutes_duration = this -> minutes_end - this -> minutes_start;
}

unsigned int Interval::duration(){
    return this -> minutes_duration;
}

Interval Interval::overlap(Interval other){
    unsigned int i1_start, i1_end, i2_start, i2_end;
    i1_start = this -> minutes_start;
    i1_end = this -> minutes_end;
    i2_start = other.minutes_start;
    i2_end = other.minutes_end;

    if(i2_start > i1_end || i2_end < i1_start){
        return Interval(Time(0, 0), 0);
    }


    unsigned int o_max, o_min, o_duration;
    unsigned int o_hours, o_minutes;

    o_min = std::max(i1_start, i2_start);
    o_max =  std::min(i1_end, i2_end);

    o_duration = o_max - o_min;
    o_hours = o_min / 60;
    o_minutes = o_min - (o_hours * 60);

    //std::cout << o_hours << " " << o_minutes << std::endl;

    return(Interval(Time(o_hours, o_minutes), o_duration));
}
