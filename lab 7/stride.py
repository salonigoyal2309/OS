
''' 
	pid = process id
	pr = priority
	at = arrival time
	rt = response time
	wt = waiting time
	tat = turnaround time
	btime = burst time
	ctime = completion time
	
'''
import queue 
from random import randint

class Process:
	def __init__ (self,pid,tickets,p0,i,p1,o,p2):
		self.pid = pid
		self.tickets = tickets
		self.pas=0
		self.stride = 0
		self.rt = 0
		self.wt = 0
		self.tat = 0
		self.input = i
		self.output = o
		self.j = 0
		self.usable = 1
		self.done_rt=0
		self.p = [p0,i,p1,o,p2]
		self.btime = p0+p1+p2
		self.ctime = 0
		self.done=0
		
		
def divide(arr,i,t_tickets):
	
	j=i
	l=0
	for i in range(len(arr)):
		if arr[i].usable==1: l+=1
	
	if l==0: return
	
	everyone = t_tickets//l
	for i in range(len(arr)):
		if arr[i].usable==1: 
			arr[i].tickets=everyone
			k=i
			
	last = t_tickets%l
	arr[k].tickets+=last
	
def retrieve(arr,i,t_tickets):

	j=i
	l=0
	for i in range(len(arr)):
		if arr[i].usable==1: l+=1
		
	if l==0: 
		return
	
	everyone = t_tickets//l
	for i in range(len(arr)):
		if arr[i].usable==1: 
			arr[i].tickets=everyone
			k=i
			
	last = t_tickets%l
	arr[k].tickets+=last
	
		
'''
	Calculates time at which process completes
'''
def findCompletionTime(total_tickets,arr):
	
	inp = []
	out = []
	n = len(arr)
	
	cnt=0
	t=0
	
	while cnt<n:
		
		j=0
		i=n
		ps = 1000000
		
		for j in range(n):
			if arr[j].usable==1 and arr[j].pas<=ps:
				ps = arr[j].pas
				i=j
			
		if i==n : t+=1
		
			
		if i<n and arr[i].j==0:
			arr[i].pas+=arr[i].stride
			t+=arr[i].p[arr[i].j]
			arr[i].j+=1
			l=[]
			l.append(i)
			l.append(t+arr[i].p[arr[i].j])
			inp.append(l)
		elif i<n and arr[i].j==2:
			arr[i].pas+=arr[i].stride
			t+=arr[i].p[arr[i].j]
			arr[i].j+=1
			l=[]
			l.append(i)
			l.append(t+arr[i].p[arr[i].j])
			out.append(l)
		elif i<n and arr[i].j==4:
			arr[i].pas+=arr[i].stride
			t+=arr[i].p[arr[i].j]
			cnt+=1
			arr[i].ctime = t
			arr[i].usable=0
			arr[i].done=1
		
		if i<n : arr[i].usable=0
			
		i=0
		while i<len(inp):
			
			if t>=inp[i][1]:
				l = inp.pop(i)
				index = l[0]
				arr[index].usable=1
				arr[index].j+=1
			else: i+=1
			
		i=0
		while i<len(out):
			
			if t>=out[i][1]:
				l = out.pop(i)
				index = l[0]
				arr[index].usable=1
				arr[index].j+=1
			else: i+=1
		
		
	
def findWaitingTime(arr):
	
	for i in range(0,len(arr)):
		arr[i].wt = (arr[i].ctime-arr[i].btime)
		
		
def findResponseTime(arr):

	for i in range(0,len(arr)):
		arr[i].rt = arr[i].wt

		
def findTurnaroundTime(arr):
	
	for i in range(0,len(arr)):
		arr[i].tat = arr[i].ctime
						
							

def ss(total_tickets,arr,big_num):
	
	arr.sort(key = lambda x : x.pas)
	
	for i in range(len(arr)):
		arr[i].stride = big_num//arr[i].tickets
		print(arr[i].stride)
	
	findCompletionTime(total_tickets,arr)
	findWaitingTime(arr)
	findTurnaroundTime(arr)
	#findResponseTime(arr)
	
	print("pid	at	ctime	wtime	tat	rt")
	
	total_wtime = 0
	total_tat = 0
	total_rt = 0
	n = len(arr)
	
	for i in range(0,n):
		print(arr[i].pid,"	0	",arr[i].ctime,"	",arr[i].wt,"	",arr[i].tat,"	",arr[i].rt)
		total_wtime+=arr[i].wt
		total_tat+=arr[i].tat
		total_rt+=arr[i].rt
		
	print("avg wait time is : ",total_wtime/n)
	print("avg turn around time is : ",total_tat/n)
	print("avg response time is : ",total_rt/n)
	


f = open("lottery.dat", "r")

arr = []
cnt = 0

for x in f:
	l = []
	for i in x.split():
		if cnt==0:
			total_tickets = int(i)
			break
		if cnt==1:
			total_p = int(i)
			break
		if cnt==2:
			big_num = int(i)
			break
		if cnt>2:
			if i=='P' or i=="I" or i=="O" or i==" ": continue
			elif i=="-1": break
			else: l.append(int(i))
	if cnt>2:
		#print(l)
		p1 = Process(l[0],l[1],l[2],l[3],l[4],l[5],l[6])
		arr.append(p1)
	cnt+=1

ss(total_tickets,arr,big_num)
