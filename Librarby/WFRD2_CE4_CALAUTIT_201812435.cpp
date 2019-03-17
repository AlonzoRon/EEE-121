#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Book {
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
        bool operator == (Book b);
}; 

Book::Book(string title, string first_author, int publication_date) {
    this -> title = title;
    this -> first_author = first_author;
    this -> publication_date = publication_date;
    this -> borrowed = false;
}

string Book::get_title() {
    return this -> title;
}

string Book::get_first_author() {
    return this -> first_author;
}

int Book::get_publication_date() {
    return this -> publication_date;
}

bool Book::get_borrowed() {
    return this -> borrowed;
}

void Book::set_borrowed(bool val) {
    (this -> borrowed) = val;
} 

void Book::displayDetails() {
    cout << "Title: " << this -> title << endl;
    cout << "First Author: " << this -> first_author << endl;
    cout << "Publication Year: " << this -> publication_date << endl;
    cout << "On-shelf? " << (borrowed? "NO": "YES") << endl;
}

bool Book::operator == (Book b){
	if(this -> title == b.get_title() && this -> first_author == b.get_first_author() && this -> publication_date == b.get_publication_date() ){
		return true;
    }
	else{
		return false;		
	}
} 


class Person {
    private:
        string name;
        int num_onhold;
        Book booksBorrowed[10];

    public:
        Person(string name = "");
        string get_name();
        int get_onhold();
        void borrowBook(Book &b);
        void returnOldest(Book* book_list, int booklistSize);
        void displayDetails();
}; 

Person::Person(string name) {
    this -> name = name;
    this -> num_onhold = 0;
    this -> booksBorrowed[10];
}

string Person::get_name() {
    return this -> name;
}

int Person::get_onhold(){
	return this -> num_onhold;
}

void Person::borrowBook(Book &b){
	if (this -> num_onhold < 10){
		if (b.get_borrowed() == false){
			b.set_borrowed(true);
			this -> booksBorrowed[this -> num_onhold] = b;
			this -> num_onhold++;
		}
		else
			cout << "Currently Not Available" << endl;	
	}
	else
		cout << "Cannot borrow another book" << endl;	
}

void Person::returnOldest(Book* book_Arr, int M){
    for (int x = 0; x < M; x++){
        if (this -> booksBorrowed[0] == book_Arr[x]){
            book_Arr[x].set_borrowed(false);
            break;
        }
    }
    for (int x = 0; x < this -> num_onhold-1; x++){
        (this -> booksBorrowed[x]) = this -> booksBorrowed[x+1];
        }	
    this -> num_onhold--;
}

void Person::displayDetails() {
    int counter = 1;
    cout << "Name: " << this -> name << endl;
    cout << "Number of books on hold: " << this -> num_onhold << endl;
    cout << "Books Borrowed: " << endl;

	if (this -> num_onhold > 0){
		for (int x = 0; x < this -> num_onhold; x++){
			cout <<"---- details of book " << counter << " ----" << endl;
			this -> booksBorrowed[x].displayDetails();
            counter++;
		}
	}
	else{
		cout << "None" << endl;	
	}
}    

void query_date(int A, int B, int M, Book* book_Arr, int counter){
    for (int x = 0; x < M; x++){
        if (A <= book_Arr[x].get_publication_date() && book_Arr[x].get_publication_date() <= B){
            book_Arr[x].displayDetails();
            counter++;
        }
    }
    if (counter == 1)
        cout << "No Result" << endl;
}    

void query_author(string C, int M, Book* book_Arr, int counter){
    for (int x = 0; x < M; x++){
        if (C == book_Arr[x].get_first_author()){
            book_Arr[x].displayDetails();
            counter++;
        } 
    }
    if (counter == 1)
        cout << "No Result" << endl;
}

void query_title(string D, int M, Book* book_Arr, int counter){
    for (int x = 0; x < M; x++){
        if (D == book_Arr[x].get_title()){
            book_Arr[x].displayDetails();
            counter++;
        }
    }
    if (counter == 1)
        cout << "No Result" << endl;
    }

void return_oldest(int P, Person* person_Arr, Book* book_Arr, int M){
    if (person_Arr[P].get_onhold() > 0)
		person_Arr[P].returnOldest(book_Arr, M);
	else
		cout << "No books to return" << endl;
    }


int main() {

    int N, M, K;
    
    string C, D;
    int A, B, P;
    
    string name, events;
    string title, first_author, year;
    int publication_date;

    cin >> N >> M;

    Person* person_Arr;
    Book* book_Arr;

    person_Arr = new Person[N];
    book_Arr = new Book[M];

    for (int x = 0; x < N; x++){
        cin >> name;
        Person person_name(name);
        person_Arr[x] = person_name;
    }

    cin.ignore();
    for (int x = 0; x < M; x++){
        getline(cin, events);
        stringstream book_details(events);
      
        getline(book_details, title, ';');
        getline(book_details, first_author, ';');
        getline(book_details, year, ';');

        stringstream book_year(year);
        book_year >> publication_date;

        Book book_object(title, first_author, publication_date);
        book_Arr[x] = book_object;
    }

    cin >> K;

    for (int x = 0; x < K; x++){
        int counter = 1;
        cin>> events;

        if (events == "QUERY_DATE"){
            cin >> A >> B;
            query_date(A, B, M, book_Arr, counter);
        }
        else if (events == "QUERY_AUTHOR"){
            getline(cin, C);
            C.erase(0,1);
            query_author(C, M, book_Arr, counter);
        }
        else if (events == "QUERY_TITLE"){
            getline(cin, D);
            D.erase(0,1);
            query_title(D, M, book_Arr, counter);
        }
        else if (events == "BORROW"){
            cin >> P >> B;
            person_Arr[P].borrowBook(book_Arr[B]);
        }
        else if (events == "RETURN_OLDEST"){
            cin >> P;
            return_oldest(P, person_Arr, book_Arr, M);  
        }
        else if (events == "STATUS"){
            cin >> P;
            person_Arr[P].displayDetails();
        }
    }

    return 0;
}
