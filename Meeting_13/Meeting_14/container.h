template<typename T>
class Container{
private:
    T* arr;
    unsigned int sz;
    unsigned int buffer_size;
    
    void increase_buffer();
    
public:
    Container();
    ~Container();
    
    T operator[](int);
    unsigned int size();
    
    bool find(T);
    void remove_last();
    void insert(T);
};

template<typename T>
Container<T>::Container(){
    sz = 0;
    buffer_size = 10;
    arr = new T[buffer_size];
}

template<typename T>
Container<T>::~Container(){
    sz = 0;
    buffer_size = 10;
    delete[] arr;
}

template<typename T>
void Container<T>::remove_last(){
    sz--;
}

template<typename T>
bool Container<T>::find(T val){
    for(int i = 0; i < sz; i++){
        if (arr[i] == val) return true;
    }
    return false;
}

template<typename T>
void Container<T>::increase_buffer(){
    buffer_size++;
    T* arr2 = new T[buffer_size]; // buffer: 10
    
    for(int i = 0; i < buffer_size - 1; i++){
        arr2[i] = arr[i];
    }
    delete[] arr;
    arr = arr2;
}

template<typename T>
unsigned int Container<T>::size(){
    return sz;
}

template<typename T>
void Container<T>::insert(T val){
    if (sz == buffer_size){
        increase_buffer();
    }
    
    arr[sz] = val;
    sz++;
}

template<typename T>
T Container<T>::operator[](int idx){
    return arr[idx];
}

