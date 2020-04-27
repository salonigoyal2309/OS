
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
		self.done_rt=0
		self.p = [p0,i,p1,o,p2]
		self.btime = p0+p1+p2
		self.ctime = 0
		self.done=0
		
'''
	Calculates time at which process completes
'''

def findCompletionTime(q,quant,pi,pd,arr):

	

	t = arr[0].at
	mlf = [[] for i in range(q)]
	
	for i in range(q):
		mlf[i].append([-1,-1])
	
	cnt=0
	k=0
	n = len(arr)
	inp = []
	out = []
	ind = [0]*q
	
	
	while cnt!=n:
	
		while k<n and arr[k].at<=t:
			l=[]
			l.append(k)
			l.append(t)
			mlf[0].append(l)
			k+=1
			
		i=0

		while i<n:
		
			if len(mlf[i])>1 :
			
				l = mlf[i][0]
				if l[0]==-1 and l[1]==-1:
					l = mlf[i].pop(0)
					mlf[i].append(l)
					
				l = mlf[i][0]
				index = l[0]
				if arr[index].done_rt==0 :
					arr[index].done_rt=1
					arr[index].rt = t
					
				arr[index].p[arr[index].j] = max(0,arr[index].p[arr[index].j]-1)
				if t%quant[i]==0:
					l = mlf[i].pop(0)
					mlf[i].append(l)
				
			i+=1
		
		
		if t%pi==0 and t!=0:
			while len(mlf[q-1])>1:
				l = mlf[q-1][0]
				if l[0]==-1 and l[1]==-1:
					mlf[q-1].pop(0)
					mlf[q-1].append(l)
				l = mlf[q-1][0]
				index = l[0]
				time = l[1]
				
				if arr[index].p[arr[index].j]>0:
						mlf[q-1].pop(0)
						l[1] = t
						mlf[0].append(l)
				else:
					if arr[index].j==0:
						temp = []
						arr[index].j+=1
						temp.append(index)
						temp.append(t+arr[index].p[arr[index].j])
						temp.append(0)
						inp.append(temp)
						mlf[q-1].pop(0)
						
					elif arr[index].j==2:
						temp = []
						arr[index].j+=1
						temp.append(index)
						temp.append(t+arr[index].p[arr[index].j])
						temp.append(0)
						out.append(temp)
						mlf[q-1].pop(0)
					
					elif arr[index].j==4:
						cnt+=1
						arr[index].ctime=t
						mlf[q-1].pop(0)	
		elif t%pd==0 and t!=0:
			r=q-2 #index of queue whose processes is being checked
			while r>=0:
				i=0
				while len(mlf[r])>1:
					l = mlf[r][i]
					if l[0]==-1 and l[1]==-1 :
						mlf[r].pop(0)
						mlf[r].append(l)
						continue
						
					index = l[0]
					time = l[1]
					if arr[index].p[arr[index].j]>0:
						mlf[r].pop(i)
						l[1] = t
						mlf[r+1].append(l)
					else:
						if arr[index].j==0:
							temp = []
							arr[index].j+=1
							temp.append(index)
							temp.append(t+arr[index].p[arr[index].j])
							temp.append(r)
							inp.append(temp)
							mlf[r].pop(i)
							
						elif arr[index].j==2:
							temp = []
							arr[index].j+=1
							temp.append(index)
							temp.append(t+arr[index].p[arr[index].j])
							temp.append(r)
							out.append(temp)
							mlf[r].pop(i)
						
						elif arr[index].j==4:
							cnt+=1
							arr[index].ctime = t
							mlf[r].pop(0)
				r-=1
				
		
		if len(inp)>0:
			i=0
			while i<len(inp):
				l = inp[i]
				index = l[0]
				time = arr[index].p[arr[index].j]
				if l[1]+time<=t:
					temp = []
					temp.append(index)
					temp.append(t)
					arr[index].j+=1
					mlf[l[2]].append(temp)
					inp.pop(i)
				i+=1

		if len(out)>0:
			i=0
			while i<len(out):
				l = out[i]
				index = l[0]
				time = arr[index].p[arr[index].j]
				if l[1]+time<=t:
					temp = []
					temp.append(index)
					temp.append(t)
					arr[index].j+=1
					mlf[l[2]].append(temp)
					out.pop(i)
				i+=1
				
			
		
		t+=1	
		
		
def findWaitingTime(arr):
	
	for i in range(0,len(arr)):
		arr[i].wt = (arr[i].ctime-arr[i].btime)-arr[i].at
		
		
def findResponseTime(arr):

	for i in range(0,len(arr)):
		arr[i].rt = arr[i].wt

		
def findTurnaroundTime(arr):
	
	for i in range(0,len(arr)):
		arr[i].tat = arr[i].ctime-arr[i].at
						
							

def mlfq(q,quant,pi,pd,arr):
	
	arr.sort(key = lambda x : x.at)
	
	findCompletionTime(q,quant,pi,pd,arr)
	findWaitingTime(arr)
	findTurnaroundTime(arr)
	#findResponseTime(arr)
	
	print("pid	at	ctime	wtime	tat	rt")
	
	total_wtime = 0
	total_tat = 0
	total_rt = 0
	n = len(arr)
	
	for i in range(0,n):
		print(arr[i].pid,"	",arr[i].at,"	",arr[i].ctime,"	",arr[i].wt,"	",arr[i].tat,"	",arr[i].rt)
		total_wtime+=arr[i].wt
		total_tat+=arr[i].tat
		total_rt+=arr[i].rt
		
	print("avg wait time is : ",total_wtime/n)
	print("avg turn around time is : ",total_tat/n)
	print("avg response time is : ",total_rt/n)
	


f = open("MLFQ.dat", "r")

arr = []
cnt = 0
quanta = []

for x in f:
	l = []
	for i in x.split():
		if cnt==0:
			q = int(i)
			break
		if cnt==1:
			quanta.append(int(i))
			if len(quanta) == q: break
		if cnt==2:
			pd = int(i)
			break
		if cnt==3:
			pi = int(i)
			break
		if cnt>3:
			if i=='P' or i=="I" or i=="O" or i==" ": continue
			elif i=="-1": break
			else: l.append(int(i))
	if cnt>3:
		p1 = Process(l[0],l[1],l[2],l[3],l[4],l[5],l[6],l[7])
		arr.append(p1)
	cnt+=1

mlfq(q,quanta,pi,pd,arr)
