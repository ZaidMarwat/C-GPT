#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Tensor {
    public:
        int rows;
        int cols;
        vector<float> data;
        Tensor(int r, int c){
            this -> rows = r;
            this -> cols = c;
            data = vector<float>(r*c, 0.0f);
        }

        float& at(int r, int c){
            int pos = r * cols + c;
            return data[pos];
        }

        void print(){
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < cols; j++){
                    std::cout << data[(i * rows) + j];
                    if (j < cols - 1){
                        std::cout << ", ";
                    }
                }
                std::cout << "\n";
            }
              
        }

};

int main(){
    Tensor t(3,2);
    t.at(0,0) = 5;
    t.print();
}