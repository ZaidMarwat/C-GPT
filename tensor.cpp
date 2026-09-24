#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
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
            std::cout << "Accessing position: " << pos << std::endl;
            return this->data[pos];
        }

        void add(Tensor& other){
            if (other.rows != this->rows || other.cols != this->cols) {
                throw std::runtime_error("Dimensions don't match");
            }

            for(int i = 0; i < this->data.size(); i++){
                this->data[i] += other.data[i];
            }
        }


        void multiply(Tensor& other){
            // 1,2,3    4,5,6
            if (other.rows != this->cols) {
                throw std::runtime_error("Dimensions don't match");
            }
            
            vector<float> v = vector<float>(this->rows * other.cols, 0.0f);

            for(int i = 0; i < this->rows; i++) {
                for(int j = 0; j < other.cols; j++) {
                    vector<float> row = vector<float>(this->cols, 0.0f);
                    vector<float> col = vector<float>(other.rows, 0.0f);
                    for(int k = 0; k < this->cols; k++) {
                        row[k] = this->data[k + this->cols*i];
                        col[k] = other.data[k*other.cols + j];
                    }
                    v[i * other.cols + j] = dot(row, col);
                }
            }
            this->data = v;
            this->cols = other.cols;

        }

        void softmax(){
            float sum = 0;
            for(int i = 0; i < this->data.size(); i++){
                sum += exp(data[i]);
            }
            for(int j = 0; j < this->data.size(); j++){
                data[j] = exp(data[j]) / sum;
            }
        }

        void transpose(){
            vector<float> v = vector<float>(this->rows * this->cols, 0.0f);
            for(int i = 0; i < this -> data.size(); i++){
                int r = i / this -> cols;
                int c = i % this -> cols;
                int pos = c * this -> rows + r;

                v[pos] = data[i];
            }
            this->data = v;
            int temp = this->rows;
            this->rows = this->cols;
            this->cols = temp;
        }

        void scalar_mul(int scale){
            for(int i = 0; i < this -> data.size(); i++){
                data[i] *= scale;
            }

        }

        void print(){
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < cols; j++){
                    std::cout << data[(i * cols) + j];
                    if (j < cols - 1){
                        std::cout << ", ";
                    }
                }
                std::cout << "\n";
            }
              
        }

    private:
        float dot(vector<float> row, vector<float> col) {
            float res = 0;
            for (int i = 0; i < row.size(); i++) {
                res += row[i] * col[i];
            }
            return res;
        }

};

int main(){
    Tensor t(3,2);
    t.at(0,0) = 5;
    t.print();
    t.at(0,1) = 2;
    t.print();
    t.at(1,0) = 3;
    t.print();
    t.at(2,1) = 2;
    t.print();
    std::cout << "\n";
    t.softmax();
    t.print();

}
