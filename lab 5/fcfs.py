
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

class Process:
	def __init__ (self,pid,pr,at,p0,i,p1,o,p2):
		self.pid = pid
		self.pr = pr
		self.at = at
		self.rt = 0
		self.wt = 0
		self.tat = 0
		self.input = i
		self.output = o
		self.j = 0
		self.p = [p0,i,p1,o,p2]
		self.btime = p0+p1+p2
		self.ctime = 0
		self.done=0
		
'''
	Calculates time at which process completes
'''
def findCompletionTime(arr):

	processor = []
	inp = []
	out = []
	
	tot_time=arr[0].at
	cnt=0
	k=1
	
	processor.append(0)
	
	while cnt<len(arr):
		#arr[i].ctime = max(arr[i-1].ctime,arr[i].at)+arr[i].btime
		if len(processor)>0: 
			
			#print(processor)
			#print(inp)
			#print(out)
			#print(tot_time)
			i = processor.pop(0)
			if arr[i].j==0 : arr[i].rt = tot_time-arr[i].at
			tot_time+=arr[i].p[arr[i].j]
		else:
			tot_time+=1
		
		#print(inp)
		#print(out)
		#print(tot_time)
		
		while k<len(arr) and arr[k].at<=tot_time:
			processor.append(k)
			k+=1
			
		while len(inp)>0 and inp[0][1]<=tot_time:
			processor.append(inp[0][0])
			arr[inp[0][0]].j+=1
			inp.pop(0)
			
		while len(out)>0 and out[0][1]<=tot_time:
			processor.append(out[0][0])
			arr[out[0][0]].j+=1
			out.pop(0)
		
		if arr[i].j==0:
			inp.append([i,tot_time+arr[i].input])
			arr[i].j+=1
		if arr[i].j==2:
			out.append([i,tot_time+arr[i].output])
			arr[i].j+=1
		if arr[i].j==4 and arr[i].done==0:
			cnt+=1
			arr[i].done=1
			arr[i].ctime = tot_time
		
		

'''
	Calculate waiting time of process
'''
		
def findWaitingTime(arr):
	
	for i in range(0,len(arr)):
		arr[i].wt = (arr[i].ctime-arr[i].btime)-arr[i].at
		
		
def findResponseTime(arr):

	for i in range(0,len(arr)):
		arr[i].rt = arr[i].wt

		
def findTurnaroundTime(arr):
	
	for i in range(0,len(arr)):
		arr[i].tat = arr[i].ctime-arr[i].at
		
	
def fcfs(arr):

	arr.sort(key = lambda x : x.at)	
	n = len(arr)
	i=0
	
	findCompletionTime(arr)
	findWaitingTime(arr)
	findTurnaroundTime(arr)
	#findResponseTime(arr)
	
	print("pid	at	ctime	wtime	tat	rt")
	
	total_wtime = 0
	total_tat = 0
	total_rt = 0
	
	for i in range(0,n):
		print(arr[i].pid,"	",arr[i].at,"	",arr[i].ctime,"	",arr[i].wt,"	",arr[i].tat,"	",arr[i].rt)
		total_wtime+=arr[i].wt
		total_tat+=arr[i].tat
		total_rt+=arr[i].rt
		
	print("avg wait time is : ",total_wtime/n)
	print("avg turn around time is : ",total_tat/n)
	print("avg response time is : ",total_rt/n)
	
''' Reading input.dat file '''	

f = open("input.dat", "r")

arr = []

for x in f:
	l = []
	for i in x.split():
		if i=='P' or i=="I" or i=="O" or i==" ": continue
		elif i=="-1": break
		else: l.append(int(i))
	p1 = Process(l[0],l[1],l[2],l[3],l[4],l[5],l[6],l[7])
	arr.append(p1)
	
fcfs(arr)
