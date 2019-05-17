#include <iostream>
#include <algorithm>
#include <vector>

int main(){
   int n, r;
   std::cin >> n; //number of positionspossible
   std::cin >> r; //number of red shops at a time

   std::vector<bool> v(n);
   std::vector<std::vector<int> > megalist;
   std::fill(v.begin(), v.begin() + r, true);

   do {
       std::vector<int> current;
       for (int i = 0; i < n; ++i) {
           if (v[i]) {
               std::cout << (i) << " ";
               current.push_back(i);
               std::cout << "pushed small" << std::endl;
           }
       }
       megalist.push_back(current);
       std::cout << "pushed large" << std::endl;
       std::cout << "\n";
   } while (std::prev_permutation(v.begin(), v.end()));
   return 0;
}
