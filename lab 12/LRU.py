import time

def printit(hit,miss,answer):
	ratio = hit/float(hit+miss)
	print('\n\n--------------------------------------------------------------------------------')
	print(answer)
	print("hit ratio : ",ratio)


def LRU(pages,pageRefrence):

	queue = []
	occupied=0
	m = list(map(lambda x:0,range(1,10)))
	answer = []
	miss=0
	hit=0
	Time=1
	
	for j in range(0,len(pageRefrence)):
		
		i=pageRefrence[j]
		if m[i-1]!=0:
			answer.append("HIT")
			m[i-1]=Time
			Time+=1
			hit+=1
		else:
			if occupied==pages:
				t=Time
				k=len(queue)-1
				while k>=0:
					if m[queue[k]-1]!=0 and m[queue[k]-1]<t:
						t = m[queue[k]-1]
						x = queue[k]
					k-=1 
				m[x-1]=0
			else:
				occupied+=1
				
			answer.append("MISS")
			queue.append(i)
			miss+=1
			m[i-1]=Time
			Time+=1
		
		if (j+1)%25==0:
			printit(hit,miss,answer)
			time.sleep(1)
			
	printit(hit,miss,answer)
	time.sleep(1)


#Reading from file 
f = open("refrence.dat","r")
pageRefrence = []
i=0

for tup in f:

	if i==0: 
		pages = int(tup)
		i+=1
	else:
		for i in tup:
			if i!="," and i!="-" : pageRefrence.append(int(i))
			if i=="-": break

LRU(pages,pageRefrence)
	
