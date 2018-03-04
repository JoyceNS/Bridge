source("Task0.r")
source("Task1.r")
source("Task2.r")

par(mfrow=c(4,2))

sorting<-function(data){
  dataset<-data[order(-data$ols),]
    return(dataset)
}

plotting <- function(dataset, percent){
  num_of_outliers <- round((nrow(dataset))*percent)
  outliers <- dataset[1:num_of_outliers,]
  remaining <- dataset[num_of_outliers+1:(nrow(dataset)),]
  plotdata(outliers)
  plotdata(remaining)
  
}

# a
complex9_outlier <- task2()


# b sort
complex9_outlier<-sorting(complex9_outlier) 

# c
plotting(complex9_outlier,.07)

# d
plotting(complex9_outlier,.14)

# e 
plotting(complex9_outlier,.21)

# g
outliers<-complex9_outlier[1:(round((nrow(complex9))*.21)),]
outliers<-outliers$ols
hist(outliers,breaks=50)


