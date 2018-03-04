library("colorspace")
library("randomcoloR")

complex9 <- read.csv(file="Complex9_GN16.txt",head=FALSE,sep=",",stringsAsFactors=FALSE)

graphics.off()
par("mar")
par(mar=c(1,1,1,1))

plotdata <- function(data){
  V1 <- data$V1
  V2 <- data$V2
  plot(V1,V2, col = c("blue","gray","red","green", "yellow", "black", "orange", "pink", "purple")[as.factor(data$V3)], main="Complex_9", cex=1)
}

plotdata(complex9)