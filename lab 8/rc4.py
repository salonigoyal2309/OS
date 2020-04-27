'''

	123456
	345673244455665
	
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

s = []
t = []
for i in range(256):
	s.append(i)
	t.append(int(key[i%len(key)]))

j=0
for i in range(256):
	j = (j+s[i]+t[i])%256
	x = s[i]
	s[i]=s[j]
	s[j]=x
	
i=0
j=0
index=0
cipher = []
cipherans = ""
temp = []
while index<len(msg1):
	i = (i+1)%256
	j = (j+s[i])%256
	x = s[i]
	s[i]=s[j]
	s[j]=x
	p1 = (s[i]+s[j])%256
	k = s[p1]
	temp.append(k)
	cipher.append(int(msg1[index])^k)
	cipherans+= str(cipher[index])
	index+=1


f1 = open("cipher.dat", "w") 
f1.write(cipherans)


i=0
j=0
index=0
decrypt = []
decryptans = ""
while index<len(msg1):
	i = (i+1)%256
	j = (j+s[i])%256
	x = s[i]
	s[i]=s[j]
	s[j]=x
	p1 = (s[i]+s[j])%256
	k = s[p1]
	k = temp[index]
	decrypt.append(int(cipher[index])^k)
	decryptans+=str(decrypt[index])
	index+=1
	
print(decryptans)
