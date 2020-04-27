#include <iostream>
#include <stdio.h>
#include<time.h>
#include<bits/stdc++.h>
#define pid 1

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

   int avg,disp;
   cout<<"Enter time in sec to calculate again : ";
   cin>>avg;
   cout<<"Enter time in sec to display output : ";
   cin>>disp;

    bool flag=true;
    clock_t startTime1,currentTime1,startTime2,currentTime2;
    float user_mode=0,kernel_mode=0,idle=0,avail_mem=0,free_mem=0,swap_total=0,swap_free=0,
    swap_part=0,swap_size=0,fifteen_min=0,ctxt_switches=0,interrupt=0;
    startTime1 = clock();
    int cnt=0;
    startTime2 = clock();

    while(flag){        

	currentTime1 = ((double)(clock() - startTime1))/CLOCKS_PER_SEC;
	currentTime2 = ((double)(clock() - startTime2))/CLOCKS_PER_SEC;
	
	if(currentTime2>disp){
		cout<<endl<<"Percentage of time cpu spends in user mode : "<<(user_mode/((float)cnt))<<" Percantage of time cpu spends in kernel mode : "<<kernel_mode/(float)cnt<<" Percantage of time cpu is idle : "<<idle/(float)cnt<<endl<<endl;

		cout<<"Free memory is : "<<(free_mem/(float)cnt)<<"kb Available memory is : "<<(avail_mem/(float)cnt)<<"kb"<<endl<<endl;

	cout<<"Total swap memory is : "<<(swap_total/(float)cnt)<<"kb Free swap memory is : "<<(swap_free/(float)cnt)<<"kb"<<endl<<endl;

		cout<<"load avg in last 15 minutes is : "<<fifteen_min/(float)cnt<<endl<<endl;

		cout<<"ctxt_switches : "<<ctxt_switches/(float)cnt<<endl<<endl;

		cout<<"Interrupts : "<<interrupt/(float)cnt<<endl;

	startTime2=clock();
	}
	
	if(currentTime1>avg){
    	
	ifstream in;
	cnt++;
    	in.open("/proc/stat",ios::binary);
	
    	string getinputcontent,word;
    	float p=0,q=0,r=0,sum=0;
	
    
	while(in>>word){
		//cout<<word<<endl;
		if(word=="cpu"){

			in>>word;
			sum+=calc(word);
			//cout<<sum<<" ";
			p=sum;
			in>>word;
			sum+=calc(word);
			//cout<<sum-p<<" ";
			in>>word;
			q=calc(word);
			sum+=q;
			//cout<<q<<" ";
			in>>word;
			r=calc(word);
			//cout<<r<<" ";
			sum+=r;
			int j=6;
			while(j--){
				in>>word;
				sum+=calc(word);
				//cout<<calc(word)<<" ";
			}
			//cout<<endl;
			break;

		}
	}

	//cout<<"%age of time cpu spends in user mode : "<<p/(float)sum<<" %age of time cpu spends in kernel mode : "<<q/(float)sum<<" %age of time cpu is idle : "<<r/(float)sum<<endl;

	user_mode+=(p/(float)sum);
	kernel_mode+=(q/(float)sum);
	idle+=(r/(float)sum);


	ifstream in2;
	in2.open("/proc/meminfo",ios::binary);

	while(in2>>word){
		//cout<<word<<endl;
		if(word=="MemFree:"){
			//cout<<word<<endl;
			//in2>>word;
			in2>>word;
			p=calc(word);
			in2>>word;
			//in2>>word;
			in2>>word;
			in2>>word;
			q = calc(word);
			break;
		} 
	
	//cout<<word<<" "<<p<<endl;
	
	}

	free_mem+=p;
	avail_mem+=q;

	while(in2>>word){
		
		if(word=="SwapTotal:"){
			//cout<<word<<endl;
			//in2>>word;
			in2>>word;
			p=calc(word);
			in2>>word;
			//in2>>word;
			in2>>word;
			in2>>word;
			q = calc(word);
			break;
		} 
		
	}

	swap_total+=p;
	swap_free+=q;


	ifstream in3;
	in3.open("/proc/loadavg",ios::binary);

	while(in3>>word){
		//cout<<word<<endl;
		in3>>word;
		in3>>word;
		p=calc(word);
		//cout<<word<<" "<<p<<endl;
		break;
	
	//couty<<word<<" "<<p<<endl;
	
	}

	fifteen_min+=p;

	ifstream in4;
	in4.open("/proc/stat",ios::binary);

	while(in4>>word){
		//cout<<word<<endl;
		if(word=="ctxt"){
			//cout<<word<<endl;
			//in2>>word;
			in4>>word;
			p=calc(word);
			break;
		} 
	
	//cout<<word<<" "<<p<<endl;
	
	}

	ctxt_switches+=p;

	ifstream in5;
	in5.open("/proc/stat",ios::binary);

	while(in5>>word){
		//cout<<word<<endl;
		if(word=="intr"){
			in3>>word;
			p=calc(word);
		//cout<<word<<" "<<p<<endl;
			break;
		}
	
	//couty<<word<<" "<<p<<endl;
	
	}

	interrupt+=p;


	startTime1 = clock();

	}

    }
	
}
