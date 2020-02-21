import string,random
f = open("testinput.txt",'w')
choices = string.ascii_letters
for x in range(500):
    s = ""
    for x in range(64):
        s += random.choice(string.ascii_letters)
    f.write(s+'\n')
f.write('A'*64+'\n')