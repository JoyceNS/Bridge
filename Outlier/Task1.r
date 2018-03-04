library("RANN")

nn <- function(data){
  neighbor <- nn2(data[1:2], k=nrow(data), searchtype="radius", radius = 20)
  data$ols <- 1/(rowSums(neighbor$nn.idx > 0))
  dataset<-data
  return(dataset)
}
