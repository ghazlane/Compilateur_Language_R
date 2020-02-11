v <- LETTERS[1:6]
for ( i in v) {
   
   if (i == "D") {
      next
   }
   print(i)
}

pow <- function(x, y) {
# function to print x raised to the power y
result <- x^y
print(paste(x,"raised to the power", y, "is", result))
}


check <- function(x) {
if (x > 0) {
result <- "Positive"
}
else if (x < 0) {
result <- "Negative"
}
else {
result <- "Zero"
}
return(result)
}

1%/%2 
2%%4

x <- 1
repeat {
print(x)
x = x+1
if (x == 6){
break
}
}

i <- 1
while (i < 6) {
print(i)
i = i+1
}