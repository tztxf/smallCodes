#include <string>
#include <iostream>
#include <stack>

using namespace std;

bool isMatch(const char &a, const char &b){
    if((a=='(' && b==')') || 
       (a=='[' && b==']') || 
       (a=='{' && b=='}')){
        return true;
    }
    return false;
}

bool isMatch(const string &in) {
    stack<char> st;
    for(int pos=0; pos<in.length(); pos++){
        if(st.empty()){
            st.push(in[pos]);
            continue;
        }
        if(isMatch(st.top(), in[pos])){ //匹配则pop
            st.pop();
        }else{
            st.push(in[pos]);
        }
    }
    if(st.empty()){
        return true;
    }
    return false;
}


int main(){
    string a = "{[({}[]())]}"; //match
    string b = "[(){[([)]}]"; //unmatch
    cout << "a isMatch : " << isMatch(a) << endl;
    cout << "b isMatch : " << isMatch(b) << endl;
    return 0;
}
