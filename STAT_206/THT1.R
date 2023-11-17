#compute for NPV, PPV, FOR, FDR
alpha.star = 1/350

alpha=alpha.star

beta=0.99
gamma=0.95

PPV=function(alpha, beta, gamma){
  result=alpha*beta/(alpha*beta + (1-alpha)*(1-gamma))
  return (result)
}
NPV=function(alpha, beta, gamma){
  result=((1-alpha)*gamma)/(alpha*(1-beta)+(1-alpha)*gamma)
  return (result)
} 
FDR=function(alpha, beta, gamma){
  result=1-PPV(alpha, beta, gamma)
  return (result)
}
FOR=function(alpha, beta, gamma){
  result=1-NPV(alpha, beta, gamma)
  return (result)
}

PPV.E.1=PPV(alpha, beta, gamma)
NPV.E.1=NPV(alpha, beta, gamma)
FDR.E.1=FDR(alpha, beta, gamma)
FOR.E.1=FOR(alpha, beta, gamma)

print(PPV.E.1)
#[1] 0.05368764 first elisa had crap positive predictive value
#because the specificity is so low

print(NPV.E.1)
#[1] 0.9999698 really high

print(FDR.E.1)
#[1] 0.9463124

print(FOR.E.1)
#[1] 3.016045e-05

# (4) Plot the PPV and NPV for problem (4)(a)
alpha.grid = seq(0, 10 * alpha.star, length=1000)
plot(alpha.grid, PPV(alpha.grid, beta, gamma),
     type='l', lwd=3, col='darkcyan', xlab='alpha',
     ylab='PPV', main='THT 1 Problem (II)(A)(4)(a)', ylim=c(0,1))

alpha.grid = seq(0, 10 * alpha.star, length=1000)
plot(alpha.grid, NPV(alpha.grid, beta, gamma),
     type='l', lwd=3, col='red', xlab='alpha',
     ylab='NPV', main='THT 1 Problem (II)(A)(4)(a)',ylim=c(0,1))

