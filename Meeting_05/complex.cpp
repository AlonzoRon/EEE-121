#include<iostream>
using namespace std;

class Complex{
public:

int real;
int img;

    Complex(int, int);
    Complex add(Complex);
    Complex subtract(Complex);
    Complex multiply(Complex);
    void print();
};

Complex::Complex(int a, int b){
    real = a;
    img = b;
    cout << "You created a complex number!" << endl;
}

Complex Complex::add(Complex other){
    int real_sum = real + other.real;
    int img_sum = img + other.img;
    return Complex(real_sum, img_sum);
}

Complex Complex::subtract(Complex other){
    int real_sum = real - other.real;
    int img_sum = img - other.img;
    return Complex(real_sum, img_sum);
}

void Complex::print(){
    cout << "(" << real << ", " << img << ")" << endl;
}

Complex Complex :: multiply(Complex other){
    int real_product = (real * other.real) - (img * other.img);
    int img_product = (img * other.real) + (real * other.img);
    return Complex(real_product, img_product);
}

int main(){
    Complex a(3, 4);
    Complex b(10, 0);

    Complex c = a.add(b);
    Complex d = a.subtract(b);
    Complex e = a.multiply(b);

    a.print();
    b.print();
    c.print();
    d.print();
    e.print();
}

