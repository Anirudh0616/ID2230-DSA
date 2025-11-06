We can design a recursive function that calculates the Factorial of a positive integer n. We know that the factorial of 0 and 1 is 1 always and is given.

Algorithm Factorial(int n){
    if n == 0 or n == 1 then
        return 1
    else 
        return n*Factorial(n-1)
}


Clearly if n = 1 or n = 0 , The function returns 1. Assume the algorithm computes (n-1)! correctly

Then if we use the Factorial(n), it returns n x Factorial(n-1), which we know is n x ((n-1)!) => n! .

Thus we proved the correctness of the Factorial Algorithm, the invarient for this is that for n, the algorithm calculates the previous factorials correctly and returns them to the multiplier. I think.
