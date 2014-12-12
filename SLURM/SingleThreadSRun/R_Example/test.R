args <- commandArgs(TRUE)
JobID<-as.integer(args[1])
ProcID<-as.integer(args[2])

set.seed(1729001+JobID+ProcID)

library(quantreg)
nsim = 1000
n= 5000
STAT = NULL
for(i in 1:nsim)
{
	x = runif(n)
	y = 1+x+rnorm(n)
	STAT = rbind(STAT, lm(y~x)$coef)
}

pdf(paste("plot_",JobID,"_",ProcID,".pdf",sep=""))
plot(y~x)
dev.off()
save.image(paste("Example_",JobID,"_",ProcID,".Rdata",sep=""))
