/*
思路：此题难点在于进位处理；也不能先把数组转为int型表达，因为可能会超过整型范围
可借助一个外部存储stack
*/
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include "assert.h"

using namespace std;

void addOne(const vector<int> &in, vector<int> &out) {
    out.clear();
    stack<int> st;
    int carry = 1;
    for(int pos=in.size()-1; pos>=0; pos--){
        int tmp = in[pos];
        assert(tmp>=0 && tmp<=9);
        if(carry==0){
            st.push(tmp);
            continue;
        }
        tmp = tmp+carry;
        if(tmp>=10){
            carry = 1;
            tmp = tmp - 10;
        }else{
            carry = 0;
        }
        st.push(tmp);
    }
    if(carry){
        st.push(carry);
    }
    //现在st里是倒序的结果
    while(!st.empty()){
        out.push_back(st.top());
        st.pop();
    }
}

void get_test_case(vector<int> &test){
    test.clear();
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);
    test.push_back(4);
    test.push_back(5);
}

void get_test_case2(vector<int> &test){
    test.clear();
    test.push_back(9);
    test.push_back(9);
    test.push_back(9);
    test.push_back(9);
    test.push_back(9);
}

void print_vector(vector<int> &v){
    for(int i=0; i<v.size(); i++){
        cout << v[i];
    }
}

int main(){
    vector<int> test;
    vector<int> result;
    //test_case_1
    get_test_case(test);
    cout << "input is : ";
    print_vector(test);
    cout << endl;
    addOne(test, result);
    cout << "output is : ";
    print_vector(result);
    cout << endl;
    //test_case_2
    get_test_case2(test);
    cout << "input is : ";
    print_vector(test);
    cout << endl;
    addOne(test, result);
    cout << "output is : ";
    print_vector(result);
    cout << endl;
    return 0;
}
