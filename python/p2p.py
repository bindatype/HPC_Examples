from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

if rank == 0:
   a=1
   b=2
   c=3
   d=4
   e=5
   f=6
   comm.send(a, dest=1, tag=11)
   comm.send(b, dest=2, tag=12)
   comm.send(c, dest=3, tag=13)
   comm.send(d, dest=4, tag=14)
   comm.send(e, dest=5, tag=15)
   comm.send(f, dest=6, tag=16)

elif rank == 1:
   data = comm.recv(source=0, tag=11)
   print rank,data

elif rank == 2:
   data = comm.recv(source=0, tag=12)
   print rank,data

elif rank == 3:
   data = comm.recv(source=0, tag=13)
   print rank,data

elif rank == 4:
   data = comm.recv(source=0, tag=14)
   print rank,data

elif rank == 5:
   data = comm.recv(source=0, tag=15)
   print rank,data

elif rank == 6:
   data = comm.recv(source=0, tag=16)
   print rank,data
