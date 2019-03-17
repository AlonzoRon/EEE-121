#include<iostream>
using namespace std;

template<typename T>
class Complex{
public:
    T real, imag;
    
    Complex();
    Complex(T, T);
    
    Complex operator+(Complex);
    Complex operator-(Complex);
    Complex operator*(Complex);
    
    void print();
};

template<typename T>
Complex<T>::Complex(){
    real = 0;
    imag = 0;
}

template<typename T>
Complex<T>::Complex(T a, T b){
    real = a;
    imag = b;
}

template<typename T>
Complex<T> Complex<T>::operator+(Complex<T> other){
    Complex s;
    
    s.real = real + other.real;
    s.imag = imag + other.imag;
    
    return s;
}

template<typename T>
Complex<T> Complex<T>::operator-(Complex<T> other){
    Complex s;
    
    s.real = real - other.real;
    s.imag = imag - other.imag;
    
    return s;
}

template<typename T>
Complex<T> Complex<T>::operator*(Complex<T> other){
    T a = real,       b = imag;
    T c = other.real, d = other.imag;
    
    Complex p(a*c - b*d, b*c + a*d);
    return p;
}

template<typename T>
ostream& operator<<(ostream& os, Complex<T> z) {
    os << "(" << z.real << ", " << z.imag << ")";
    return os;
}
// editing operators to your liking

template<typename T>
void Complex<T>::print(){
    cout << "(" << real << ", " << imag << ")" << endl;
}

int main(){
    Complex<float> A(3.5, 4.7);
    Complex<float> B(10.5, 0.9);
    
    Complex<float> sum = A + B;
    Complex<float> product = A * B;
    
    sum.print();
    product.print();
    cout << sum << endl;
}
