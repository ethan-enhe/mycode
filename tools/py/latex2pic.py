from urllib.parse import quote
import re
#f=open("test.md","r")
#cont=f.read();
#f.close()

cont=''
while True:
    try:
        cont=cont+input()+'\n'
    except EOFError:
        break
cont=eval(repr(cont).replace('\\cr','\\cr '))

pat=re.compile(r'\$\$.*?\$\$',re.DOTALL)
it=pat.search(cont)
while it:
    tmp='![](https://www.zhihu.com/equation?tex='+quote(it.group()[2:-2])+')';
    cont=cont[:it.start()]+tmp+cont[it.end():]
    it=pat.search(cont)

pat=re.compile(r'\$.*?\$',re.DOTALL)
it=pat.search(cont)
while it:
    tmp='![](https://www.zhihu.com/equation?tex='+quote(it.group()[1:-1])+')';
    cont=cont[:it.start()]+tmp+cont[it.end():]
    it=pat.search(cont)

print(cont)
#f=open("gen.md","w")
#f.write(cont)
#f.close()
