import math
import random
import sys

keep=0
n=int(sys.argv[1])
for i in range(1,n+1):
	x=random.random()
	y=random.random()
#	if math.sqrt(x*x+y*y)<=1:
	if (x*x+y*y)<=1:
		keep+=1
pi=4.0*keep/n
error = abs(pi - math.pi)
print ("pi is approximately %.16f, error is %.16f" % (pi, error))

