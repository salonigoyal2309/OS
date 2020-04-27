'''
	ACT
	GYBNQKURP
	
'''

f = open("input.dat", "r")

cnt=0

for x in f:

	x = x.rstrip('\n')
	if cnt==0:
		msg1 = x
		cnt+=1
	elif cnt==1:
		key = x
		break

key=key.replace(" ", "")
key=key.upper()

msg1=msg1.replace(" ", "")
msg1=msg1.upper()



keyMatrix = [[0] * 3 for i in range(3)] 

messageVector = [[0] for i in range(3)]

cipherMatrix = [[0] for i in range(3)] 

def getKeyMatrix(key): 
	k = 0
	for i in range(3): 
		for j in range(3): 
			keyMatrix[i][j] = ord(key[k]) % 65
			k += 1

def encrypt(messageVector): 
	for i in range(3): 
		for j in range(1): 
			cipherMatrix[i][j] = 0
			for x in range(3): 
				cipherMatrix[i][j] += (keyMatrix[i][x] *
									messageVector[x][j]) 
			cipherMatrix[i][j] = cipherMatrix[i][j] % 26

def HillCipher(message, key): 


	getKeyMatrix(key)
	for i in range(3): 
		messageVector[i][0] = ord(message[i]) % 65

	
	encrypt(messageVector) 
	
	CipherText = ""
	for i in range(3): 
		CipherText+=chr(cipherMatrix[i][0] + 65) 
		
	f1 = open("cipher.dat", "w") 
	f1.write(CipherText)


HillCipher(msg1,key)
