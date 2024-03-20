#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std;

class Policy{
protected:
    bool isChecked;
public:
    virtual void check(const string & parola)=0;
    bool getCheck()const{
        return isChecked;
    }
    virtual string tip()=0;

};
class LengthPolicy : public Policy{
private:
    uint16_t maxLength,minLength;
public:
    LengthPolicy(uint16_t minim){
        minLength=minim;
        maxLength=255;
        cout<<"Lungime"<<minim<<" "<<maxLength<<endl;
    }
    LengthPolicy(uint16_t minim, uint16_t max){
        minLength=minim;
        maxLength=max;
        cout<<"Lungime"<<minLength<<" "<<maxLength<<endl;
    }
    string tip() {return "lungime";}
    void check(const string & parola){
        if(parola.size()>=minLength && parola.size()<=maxLength) isChecked=true;
        else isChecked=false;
    }
};
class ClassPolicy : public Policy{
private:
    uint16_t minClassCount;
public:
    ClassPolicy(uint16_t val){
        minClassCount=val;
        cout<<"Class "<<val<<endl;
    }
    string tip(){return "class";}
    void check(const string & parola){
        int cifre=0,mica=0,mare=0,alte=0;
        char s[256];
        strcpy(s,parola.c_str());
        for(int i=0;i< strlen(s);i++){
            if(!isalnum(s[i])) alte++;
            if(isdigit(s[i])) cifre++;
            if(isalpha(s[i])){
                if(isupper(s[i])) mare++;
                else mica++;
            }
        }
        int k=0;
        if(cifre!=0) k++;
        if(mare!=0) k++;
        if(mica!=0) k++;
        if(alte!=0) k++;
        if(k>=minClassCount) isChecked=true;
        else isChecked=false;
    }
};
class IncludePolicy : public Policy{
private:
    char characterType;
public:
    IncludePolicy(char x){
        characterType=x;
        cout<<"Include "<<characterType<<endl;
    }
    string tip(){return "include";}
    void check(const string & parola){
        char s[256];
        strcpy(s,parola.c_str());
        for(int i=0;i< strlen(s);i++){
            if(characterType=='A'){
                if(isupper(s[i])) {
                    isChecked = true;
                    return;
                }
            }
            if(characterType=='a'){
                if(islower(s[i])){
                    isChecked=true;
                    return;
                }
            }
            if(characterType=='0'){
                if(isdigit(s[i])){
                    isChecked=true;
                    return;
                }
            }
            if(characterType=='$'){
                if(!isalnum(s[i])){
                    isChecked=true;
                    return;
                }
            }
        }
        isChecked=false;
    }
};
class NotIncludePolicy : public Policy{
private:
    char characterType;
public:
    NotIncludePolicy(char x){
        characterType=x;
        cout<<"Not include "<<characterType<<endl;
    }
    string tip(){return "ninclude";}
    void check(const string & parola){
        char s[256];
        strcpy(s,parola.c_str());
        for(int i=0;i< strlen(s);i++){
            if(characterType=='A'){
                if(isupper(s[i])) {
                    isChecked = false;
                    return;
                }
            }
            if(characterType=='a'){
                if(islower(s[i])){
                    isChecked=false;
                    return;
                }
            }
            if(characterType=='0'){
                if(isdigit(s[i])){
                    isChecked=false;
                    return;
                }
            }
            if(characterType=='$'){
                if(!isalnum(s[i])){
                    isChecked=false;
                    return;
                }
            }
        }
        isChecked=true;
    }
};
class RepetitionPolicy : public Policy{
private:
    uint16_t maxCount;
public:
    RepetitionPolicy(uint16_t val){
        maxCount=val;
        cout<<"Repetition "<<maxCount<<endl;
    }
    string tip(){return "repetition";}
    void check(const string & parola){
        char s[256];
        int  lmax=0;
        strcpy(s,parola.c_str());
        int k=1;
        for(int i=0;i< strlen(s);i++){
            if(s[i]==s[i+1]){
                k++;
                if(lmax<k) lmax=k;
            }
            else
            {
                k=1;
            }
        }
        if(lmax<= maxCount) isChecked=true;
        else isChecked=false;
    }
};
class ConsecutivePolicy : public Policy{
private:
    uint16_t maxCount;
public:
    ConsecutivePolicy(uint16_t val){
        maxCount=val;
        cout<<"Consecutive "<<maxCount<<endl;
    }
    string tip() {
        return "consecutive";
    }
    void check(const string & parola){
        char s[256];
        int  lmax=0;
        strcpy(s,parola.c_str());
        int k=1;
        for(int i=0;i< strlen(s);i++){

            if(s[i]==s[i+1]-1){
                k++;
                if(lmax<k) lmax=k;
            }
            else
            {
                k=1;
            }
        }
        if(lmax<= maxCount) isChecked=true;
        else isChecked=false;
    }
};
string checkPassword(string parola, vector<Policy *> parole){
    for(Policy * cerinta : parole){
        cerinta->check(parola);
        if(cerinta->getCheck()==false){
            return "NOK";
        }
    }
    return "OK";
}
int main(){
    int n;
    vector<Policy * > cerinte;
    cin>>n;
    cin.get();
    string cerinta;
    bool ok=false;
    char s[256];
    for(int i=0;i<n;i++){
        int val1,val2;
        int k=0;
        char t[20];
        cin.getline(s,256);
        char * p = strtok(s," ");
        while(p!=NULL){
            k++;

            if(k==1){
                string comanda(p);
                cerinta=comanda;
            }
            if(k==2){
                strcpy(t,p);
                if(cerinta=="include"){
                    cerinte.push_back(new IncludePolicy(p[0]));
                }
                if(cerinta=="repetition"){
                    val1= atoi(p);
                    cerinte.push_back(new RepetitionPolicy(val1));
                }
                if(cerinta=="consecutive"){
                    val1= atoi(p);
                    cerinte.push_back(new ConsecutivePolicy(val1));
                }
                if(cerinta=="class"){
                    val1= atoi(p);
                    cerinte.push_back(new ClassPolicy(val1));
                }
                if(cerinta=="ninclude"){
                    cerinte.push_back(new NotIncludePolicy(p[0]));
                }
            }
            if(k==3)
            {val1= atoi(t);
                val2=atoi(p);
                cerinte.push_back(new LengthPolicy(val1,val2));
            }
            p= strtok(NULL," ");
        }
        if(cerinta=="length" && k==2){
            val1= atoi(t);
            cerinte.push_back(new LengthPolicy(val1));
        }
    }

    string parola;
    while(cin>>parola){
        cout<<checkPassword(parola,cerinte)<<endl;
    }
    return 0;
}