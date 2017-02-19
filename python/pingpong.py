from mpi4py import MPI

comm = MPI.COMM_WORLD  
size = comm.Get_size()
rank = comm.Get_rank() 
stat = MPI.Status()


counter = 0
#start game (serve)
if rank == 0:
	comm.send(counter, dest=1)
	
for i in range(1,10):
	if rank == 0:
   		counter = comm.recv(source=1)
		counter+=1
		print rank,counter
		comm.send(counter, dest=1)
	if rank == 1:
                counter = comm.recv(source=0)
                counter+=1
		print rank,counter
                comm.send(counter, dest=0)


