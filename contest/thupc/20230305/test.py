# import sys
x,y=map(int,input().split())
if (x==1 and y==1):
    print("1")
elif (x!=1 and y==1):
    print("Poor E.S.!")
else:
    # sys.set_int_max_str_digits(1000000)
    sum=1
    cur=0
    for i in range(2,x+1):
        cur=(sum+y-2)//(y-1)
        sum+=cur
    print(cur)
