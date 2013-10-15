#include <vector>
#include <iostream>

using namespace std;
int walk(vector < int > array) {
    int start = 0;
    int end = array.size();
    int step_count = 0; 
    while(start<end){
        // always try to make maxinum forword, greedy algrithmn
        step_count++;
        int next_candidators = array[start];
        int max_step = 0;
        int next_start = start;
        for(int i=1; i<=next_candidators; i++){
            int test_pos = i+start;
            if(array[test_pos]+i > max_step){
                max_step = array[test_pos]+i;
                next_start = test_pos;
            }
            if(next_start > end){
                break; // already got one
            }
        }
        if(start == next_start){ // cant not make any forword
            return -1;
        }
        start = next_start; // make forword
    }
    return step_count;
}


int main(){
    int a[9] = {1, 3, 5, 2, 9, 3, 1, 1, 8};
    vector<int> test(a, a+9);
    int res = walk(test);
    cout<< res << endl;

    int b[9] = {1, 3, 2, 1, 0, 1, 1, 1, 8};
    vector<int> test1(b, b+9);
    res = walk(test1);
    cout<< res << endl;

    return 0;
}
