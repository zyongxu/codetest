#include <iostream>
#include <vector>
using namespace std;

int minimumTotal(vector<vector<int> > &triangle) {
        int height = triangle.size();
        vector<int> buffer (height, 0);
        buffer[0] = triangle[0][0];
        
        for(int i=1; i<height; i++) {
            vector<int> temp(buffer);

            buffer[0] = temp[0]+triangle[i][0];
            buffer[i] = temp[i-1]+triangle[i][i];
        
            for (int j=1; j<i; j++) {
                buffer[j] = min(temp[j-1], temp[j]) + triangle[i][j];
            }
        }
    
        int min = buffer[0];
        for (int i=1; i< height; i++) {
            min = min<buffer[i] ? min : buffer[i];
        }
        return min;
}

int main() {
    vector<vector<int> > test;
    test.push_back(vector<int>(1,-1));
    vector<int> temp;
    temp.push_back(2);
    temp.push_back(3);
    test.push_back(temp);
    vector<int> temp1;
    temp1.push_back(1);
    temp1.push_back(-1);
    temp1.push_back(-1);
    test.push_back(temp1);
    cout<<minimumTotal(test)<<endl;
    return 0;
}


