# include<iostream>
# include<fstream>
using namespace std;
bool comp(string s,string t){
    int i=0,j=0;
    while (i<s.size()&&j<t.size()){
        if (s[i]==t[j]){
            i++;
            j++;
        }else if (s[i]=='('){
            i++;
        }else if (s[i]==')'){
            i++;
        }else if (s[i]=='!'){
            if (t.substr(j,3)=="not"){
                i++;
                j+=3;
            }
            else return false;
        }else{
            return false;
        }
    }
    return i==s.size()&&j==t.size();
}
int main(int argc,char *argv[]){
    fstream fa,fb;
    fa.open(argv[1]);
    fb.open(argv[2]);
    string s,t,x;
    while (fa>>x) s+=x;
    while (fb>>x) t+=x;
    if (!comp(s,t)){
        cout<<s<<endl<<t<<endl;
        clog<<argv[1]<<" "<<"False"<<endl;
    }else{
        clog<<argv[1]<<" "<<"PASS"<<endl;
    }
} 