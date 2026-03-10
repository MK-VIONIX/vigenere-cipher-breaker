#include <bits/stdc++.h>
using namespace std;

char key_solver(string s){

    char key=0;
    int best_score = INT_MIN;

    for(int k=0;k<256;k++){

        string result = s;
        int point = 0;

        for(int j=0;j<result.size();j++){
            result[j] ^= k;
        }

        for(int i=0;i<result.size();i++){

            if(result[i]==' ') point+=6;
            else if(result[i]=='E'||result[i]=='e') point+=5;
            else if(result[i]=='T'||result[i]=='t'||result[i]=='A'||result[i]=='a') point+=4;
            else if(result[i]=='O'||result[i]=='o'||result[i]=='i'||result[i]=='I'||result[i]=='n'||result[i]=='N') point+=3;
            else if(result[i]=='s'||result[i]=='S'||result[i]=='h'||result[i]=='H'||result[i]=='r'||result[i]=='R') point+=2;
            else if(result[i]=='^'||result[i]=='@'||result[i]=='#'||result[i]=='$'||result[i]=='%'||result[i]=='*'||result[i]=='{'||result[i]=='}') point-=10;
            else if((result[i]>='A'&&result[i]<='Z')||(result[i]>='a'&&result[i]<='z')) point+=1;
            else point-=2;
        }

        if(point > best_score){
            best_score = point;
            key = k;
        }
    }

    return key;
}

string base64_decode(string s){

    string table="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    vector<int> val(256,-1);

    for(int i=0;i<64;i++){
        val[table[i]]=i;
    }

    string decoded;
    int buffer=0,bits=0;

    for(char c:s){

        if(c=='=') break;

        buffer=(buffer<<6)+val[c];
        bits+=6;

        if(bits>=8){
            bits-=8;
            decoded.push_back((buffer>>bits)&255);
        }
    }

    return decoded;
}

double hamm_dist(string s1,string s2){
    int count=0;

    for(int i=0;i<s1.size();i++){
        count+=__builtin_popcount((unsigned char)(s1[i]^s2[i]));
    }

    return (double)count/(double)s1.size();
}

int main(){

    freopen("challenge_6.txt","r",stdin);

    string text,line;

    while(getline(cin,line)){
        text+=line;
    }

    text=base64_decode(text);  

    double count=0,normalized_value=INT_MAX;
    int key_size=2,keys;

    while(key_size<41){

        for(int i=0;i+2*key_size<=text.size();i+=key_size){

            string s1,s2;

            s1=text.substr(i,key_size);
            s2=text.substr(i+key_size,key_size);

            count+=hamm_dist(s1,s2);
        }

        double var=(count/(double)((int)text.size()/key_size));

        if(var<normalized_value){
            normalized_value=var;
            keys=key_size;
        }

        key_size++;
        count=0;
    }

   string key;
  
   	for(int i=0;i<keys;i++){

    string block;

    for(int j=i;j<text.size();j+=keys){
        block.push_back(text[j]);
    }

   

    key.push_back(key_solver(block));



   }
   string plaintext;

for(int i=0;i<text.size();i++){
    plaintext.push_back(text[i] ^ key[i % key.size()]);
}

cout << "\n\n" << plaintext;
}