#include <iostream>
using namespace std;

int main(){
    string string = "she sells seashells by the seashore";

    for (size_t i = 32; i < 127; i++) {
        int character_count = 0;
        char character = char(i);
        // cout << char(i) << endl;

        for (size_t i = 0; i < string.size(); i++) {
            if(string[i] == character){
                character_count += 1;
            }
        }

        if (character_count > 0) {
            cout << "'" << character << "' = " << character_count << endl;
        }
    }
}
