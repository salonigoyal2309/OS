#include <iostream>
#include "stdio.h"
#include<bits/stdc++.h>

using namespace std;

using namespace std;

int main(){
        
    ifstream in;
    in.open("/proc/cpuinfo",ios::binary);
	
    string getinputcontent,word;
    int p=1;
    int cpu[100],core[100];
    
    while(getline(in, getinputcontent)){
	while(in>>word){
		if(word=="processor") p++;
                if(word=="MHz"){
			in>>word;
			in>>word;
			//float x = (stof)word;
                        cout<<p<<" frequency :"<<word<<endl;
		}
		if(word=="cores"){
			in>>word;
			in>>word;
                        cout<<p<<" cpu cores :"<<word<<endl;
		}
	}
    }

    cout<<"Total processor : "<<p<<endl;

   ifstream in2;

    in2.open("/proc/version",ios::binary);
    
    cout<<"version of kernel : "; 
    while(in2>>word){
	cout<<word<<" ";
    }

    cout<<endl;


    ifstream in3;

    in3.open("/proc/meminfo",ios::binary);
    
    cout<<"Amount of memory allocated : "; 
    while(in3>>word){
	cout<<word<<" ";
        in3>>word;
        cout<<word<<" ";
        in3>>word;
        cout<<word<<endl;
        break;
    }


    ifstream in4;

    in4.open("/proc/uptime",ios::binary);
    
    cout<<"Amount of time since the system was last booted (day:hr:min:sec format) : "; 
    int x=0;
    while(in4>>word){
        int i;
	for(i=0;i<word.length();i++){
                if(word[i]=='.') break;
		x=x*10+(word[i]-'0');
	}
        cout<<(x/60)/24<<" days : "<<(x/60)%24<<" hrs : "<<x%60<<" minutes : ";
        i++;
        for(i;i<word.length();i++){
		cout<<word[i];
	}
        cout<<" secs "<<endl;
	break;
    }
	
	
}
