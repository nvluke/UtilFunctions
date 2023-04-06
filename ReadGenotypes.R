library(Rcpp)
sourceCpp('~/ReadGenotypes.cpp')
X = ReadGeno('~/p1_mrk_001.txt')
#----------------------------------------------------------------------------
#Genotype file:            ~/p1_mrk_001.txt
#Number of individuals:    20000
#Number of markers:        30000
#Genotypes read in:        77.278 seconds
#----------------------------------------------------------------------------
#> dim(X$Genotypes)
#[1] 20000 30000
#> head(X$ID)
#[1] "421" "422" "423" "424" "425" "426"
#> 
