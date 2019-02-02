#include<iostream>
#include<string>
#include<sstream>
using namespace std;

class Book{
private:
    string title;
    string first_author;
    int publication_date;
    bool borrowed;
public:
    Book(string title = "", string first_author = "", int publication_date = 0);
    string get_title();
    string get_first_author();
    int get_publication_date();
    bool get_borrowed();
    void set_borrowed(bool val);
    void displayDetails();
    bool operator==(Book b); //optional
};

Book::Book(string title, string first_author, int publication_date){
    this -> title = title;
    this -> first_author = first_author;
    this -> publication_date = publication_date;
}

string Book::get_title(){
    return this -> title;
}

string Book::get_first_author(){
    return this -> first_author;
}

int Book::get_publication_date(){
    return this -> publication_date;
}
void Book::displayDetails(){
    cout << "Title: " << this -> title << endl;
    cout << "First Author: " << this -> first_author << endl;
    cout << "Publication Date: " << this -> publication_date << endl;
}

class Person{
private:
    string name;
    int num_onhold;
    Book booksBorrowed[10];
public:
    Person(string name = "");
    string get_name();
    void borrowBook(Book &b);
    void returnOldest(Book* book_list); // can also be book array
    void displayDetails();
};

Person::Person(string name){
    this -> name = name;
}
string Person::get_name(){
    return this -> name;
}


Person* person_arrayer(Person* person_arr, int number_person){
    for (int i = 0; i < number_person; i++) {
        string person;
        cin >> person;
        Person man(person);

        person_arr[i] = man;
    }
    return person_arr;
}

    // for (int i = 0; i < number_person; i++) {
    //     cout << person_arr[i].get_name() << endl;
    // }

Book* book_arrayer(Book* book_arr, int number_book){
    for (int i = 0; i < number_book; i++) {
        string input;
        string book_name, book_author;
        string book_year;
        string delimiter = ";";
        int publication_year;

        if(i == 0) cin.ignore();
        getline(cin, input);

        stringstream book_details(input);

        getline(book_details, book_name, ';');
        getline(book_details, book_author, ';');
        getline(book_details, book_year, ';');

        stringstream year_number(book_year);
        year_number >> publication_year;

        // cout << book_name << endl;
        // cout << book_author << endl;
        // cout << publication_year << endl;

        // string book_name = book_details.substr(0, book_details.find(delimiter));
        // book_details.erase(0, book_details.find(delimiter) + 1);
        // string book_author = book_details.substr(0, book_details.find(delimiter));
        // book_details.erase(0, book_details.find(delimiter) + 1);
        // int book_year = std::stoi(book_details);

        // cout << book_author << book_year << book_name << endl;

        Book current_book(book_name, book_author, publication_year);

        book_arr[i] = current_book;
    }

    // for (int i = 0; i < number_book; i++) {
    //     book_arr[i].displayDetails();
    // }
    return book_arr;
}

void query_date(int date_a, int date_b, Book*& book_arr){
    int counter = 1;
    for (size_t i = 0; i < sizeof(book_arr) - 1; i++) {
        int current_year;
        current_year = book_arr[i].get_publication_date();

        if(current_year >= date_a and current_year <= date_b){
            cout << "-----Query Date Match " << counter << "-----" << endl;
            book_arr[i].displayDetails();
            counter++;
        }
    }
    if (counter == 1) cout << "No Result" << endl;
}

void event_selector(int number_of_events, Book*& book_arr, Person*& person_arr){
    for (size_t i = 0; i < number_of_events; i++) {
        string command;
        string input;
        string second_statement, third_statement;
        string second_string;
        int second_int, third_int;

        if(i == 0) cin.ignore();
        getline(cin, input);

        stringstream choice(input);
        getline(choice, command, ' ');

        if(command == "QUERY_AUTHOR" or command == "QUERY_TITLE"){
            getline(choice, second_string);
        }

        else{
            getline(choice, second_statement, ' ');
            getline(choice, third_statement);

            stringstream second(second_statement);
            stringstream third(third_statement);

            second >> second_int;
            third >> third_int;
        }
        // The following lines of code now are the beginning of the choices

        if(command == "QUERY_DATE") query_date(second_int, third_int, book_arr);

    }
}


int main(){
    int number_person, number_book;
    cin >> number_person >> number_book;

    Person* person_arr;
    Book* book_arr;

    person_arr = new Person[number_person];
    book_arr = new Book[number_book];

    person_arr = person_arrayer(person_arr, number_person);
    book_arr = book_arrayer(book_arr, number_book);


    int number_of_events;
    cin >> number_of_events;
    event_selector(number_of_events, book_arr, person_arr);
}
