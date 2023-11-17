#THT1 PART (II) (B) (b) (i)

exponential.likelihood <- function( y, lambda, c.plus ) {
  n <- length( y )
  s <- sum( y )
  result <- c.plus * lambda^( - n ) * exp( - s / lambda )
  return( result )
}

y <- c( 495, 541, 1461, 1555, 1603, 2201, 2750, 3468, 3516, 4319, 6622, 
        7728, 13159, 21194 )

lambda.grid=seq(2000, 15000, length=1000)
c.plus=1
c.real <- 0
plot( lambda.grid, exponential.likelihood( y, lambda.grid, c.plus ),
      type = 'l', lwd = 3, col = 'darkcyan', xlab = 'lambda',
      ylab = 'Likelihood' )

exponential.log.likelihood <- function( y, lambda, c.real ) {
  n <- length( y )
  s <- sum( y )
  result <- c.real - n * log( lambda ) - s / lambda
  return( result )
}
plot( lambda.grid, exponential.log.likelihood( y, lambda.grid, c.real ),
      type = 'l', lwd = 3, col = 'darkcyan', xlab = 'lambda',
      ylab = 'Log Likelihood' )

par( mfrow = c( 1, 1 ) )

exponential.inverse.cdf <- function( lambda, p ) {
  result <- - lambda * log( 1 - p )
  return( result )
}

plot( exponential.inverse.cdf( lambda.hat.mle,
                               ( ( 1:n ) - 0.5 ) / n ), y, type = 'l', lwd = 3, col = 'darkcyan',
      xlab = 'Exponential Quantiles', ylab = 'Sorted y Values',
      xlim = c( 0, max( y ) ) )

