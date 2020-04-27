#include <iostream>
#include <stdio.h>
#include<time.h>
#include<bits/stdc++.h>

using namespace std;

float calc(string word){

	int i,x=0,y=1;
	bool flag=false;
	for(i=0;i<word.length();i++){
               if(word[i]=='.'){
			flag=true;
			continue;
		}
		x=x*10+(word[i]-'0');
		if(flag) y*=10;
	}

	float ans = x/(float)y;
	return ans;
	
}

int main(int argc, char *argv[]){

	string pid;
	cout<<"enter process id : ";
	cin>>pid;
	
	string file="",word;

	ifstream in;
	file+="/proc/"+pid+"/cmdline";
	in.open(file,ios::binary);

	if(!in){
		cout<<"NO such process id exit"<<endl;
		exit(0);
	}

	cout<<"commandline of given process is : ";

	while(in>>word){
		cout<<word<<" ";
	}

	cout<<endl;

	int utime,stime,cutime,cstime;
	ifstream in2;
	file="";

	file+="/proc/"+pid+"/stat";
	in2.open(file,ios::binary);

	if(!in2){
		cout<<"NO such process id exist"<<endl;
		exit(0);
	}

	int j=14;
	while(j--){
		in2>>word;
		//cout<<word;
	}

	utime = calc(word);
	in2>>word;
	stime = calc(word);
	in2>>word;
	cutime = calc(word);
	in2>>word;
	cstime = calc(word);

	cout<<"TIme for which process was running in user mode : "<<utime<<" TIme for which process was running in kernel mode "<<stime<<endl;
	cout<<"TIme for which process was waiting in user mode : "<<cutime<<" TIme for which process was waiting in kernel mode "<<cstime<<endl;

	ifstream in3;
	file="";

	file+="/proc/"+pid+"/environ";
	in3.open(file,ios::binary);

	if(!in3){
		cout<<"NO such process id exist"<<endl;
		exit(0);
	}

	cout<<"Environment of process is : ";
	while(in3>>word){
		cout<<word<<" ";
	}
	
	cout<<endl;

	ifstream in4;
	file="";

	file+="/proc/"+pid+"/maps";
	in4.open(file,ios::binary);

	if(!in4){
		cout<<"NO such process id exist"<<endl;
		exit(0);
	}

	cout<<"Address space of process is : ";

	string getinputcontent;
	while(getline(in4, getinputcontent)){
		cout<<getinputcontent<<endl;
	}
	
	cout<<endl;


}
