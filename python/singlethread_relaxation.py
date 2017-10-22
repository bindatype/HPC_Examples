import numpy

COLS = 6
ROWS = 4

M=numpy.zeros((ROWS+2, COLS))
M[0,:] = 1.
M[:,0] = 1.
initM = numpy.copy(M)

for i in xrange(100):
	for ROWelem in xrange(1,ROWS+1):
		for COLelem in xrange(1,COLS-1):
			M[ROWelem,COLelem] = (M[ROWelem,COLelem-1]
						+M[ROWelem,COLelem+1]
						+M[ROWelem-1,COLelem]
						+M[ROWelem+1,COLelem])/4.

print initM
print M
