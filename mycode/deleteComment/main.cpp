#include <string>
#include <iostream>
#include <fstream>

using namespace std;

string removeComment(string s) {
    string result;
    size_t len = s.length();
    size_t end = len;
    size_t begin = 0; // point to the start of uncomment section
    size_t pos = begin; // point to current character
    while(pos<len){
        if(s[pos]=='/'){
            pos++;
            if(s[pos]=='/'){
                result += s.substr(begin, pos-begin-2); // save uncomment section
                size_t eol =  s.find("\n",pos+1); //skip end of line
                if(eol==string::npos){
                    begin = len; 
                }else{
                    begin = eol;
                }
                pos = begin;
            }else if(s[pos]=='*'){
                result += s.substr(begin, pos-begin-2); // save uncomment section
                begin = s.find("*/",pos+1) + 2; // skip */
                pos = begin;
            }
        }else if(s[pos]=='\"'){
            size_t pair_pos = s.find("\"",pos+1);
            size_t new_begin = pair_pos+1; // start from next character
            result += s.substr(begin, new_begin-begin);
            begin = new_begin;
            pos = begin;
        }else{
            pos++;
        }
    }
    if(begin<len){
        result += s.substr(begin, pos-begin); // save the last section
    }
    return result;
}


int main(){
    string a = "wer // This is another comment";
    string b = "This /*is*/ another /*com*/ment \"sdfsd//dfdce/*duou*/sdf//dfd\"last";
    string ra = removeComment(a);
    cout << ra << endl;
    string rb = removeComment(b);
    cout << rb << endl;
    ifstream fin("input000.txt");  
    string input;
    string s;  
    while( getline(fin,s) )
    {   
        input += s;
        input += "\n";
        cout << "Read from file: " << s << endl; 
    }
    cout << input << endl;
    string output = removeComment(input);
    cout << output << endl;
    return 0;
}
