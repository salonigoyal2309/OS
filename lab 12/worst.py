import threading
import time

#Prints output every in every 50 seconds
def printit(ratio , externalFragmentation):
  print ('\n\n--------------------------------------------------------------------------------')
  print ('Successful Allocation Ratio : ',ratio)
  print ('External Fragmentation : ',externalFragmentation)
  return

# Process class storing Process Id , arrival time(at) ,size of process , time at which process should be removed from memory(ed)
class Process:
	def __init__(self,pid,at,size,et):
		self.pid = pid
		self.at = at
		self.size = size
		self.et = at+et
		

#first Fit algorithm implementation
def worstFit(process,mem_size):
	
	memBuffer= []
	memBuffer.append([0,mem_size])
	success=0
	reached=0
	externalFragmentation=0
	
	for p in process:
		
		#Removing processes who have reched their end time
		for i in range(0,len(memBuffer)):
			q = memBuffer[i]
			if q[0]==0: continue
			if process[q[0]-1].et<=p.at:
				memBuffer[i][0]=0
		
		tempBuffer = []
		i=0
		while i<len(memBuffer):
			q = memBuffer[i]
			if q[0]!=0:
				tempBuffer.append(q)
				i+=1
			else:
				sm=0
				while i<len(memBuffer) and memBuffer[i][0]==0:
					sm = sm+memBuffer[i][1]
					i=i+1
				if sm>0: tempBuffer.append([0,sm])
		
		memBuffer = tempBuffer
		
		#checking if we can allocate memory for incoming process
		free=0
		alloted=0
		tempBuffer=[]
		mn=0

		for i in range(0,len(memBuffer)):
			q = memBuffer[i]
			if q[0]==0 and q[1]>=p.size:
				mn = max(mn,q[1])
				
			if alloted==0 and q[0]==0: free+=q[1]
			
		reached+=1
		if mn==0 and free>=p.size: externalFragmentation+=p.size
		
		if mn!=0:
			
			for i in range(0,len(memBuffer)):
				q = memBuffer[i]
				if q[1]==mn:
					alloted=1
					tempBuffer.append([p.pid,p.size])
					if q[1]>p.size: tempBuffer.append([0,q[1]-p.size])
				else:
					tempBuffer.append(q)
		
			memBuffer = tempBuffer
			success+=1
			
		ratio = (success/float(reached))*100
		
		printit(ratio,externalFragmentation)
		time.sleep(1)
		 

#Reading from file 
f = open("alloc.dat","r")
mem_size=0
process = []
index=1

for tup in f:
	x = list(map(int,tup.split()))
	if len(x)==1:
		mem_size = x[0]
	elif x[0]!=-1 and x[1]!=-1 and x[2]!=-1:
		process.append(Process(index,x[0],x[1],x[2]))
		index = index+1

worstFit(process,mem_size)
	
