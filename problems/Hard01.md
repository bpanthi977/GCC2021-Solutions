# Stable Partition
Brokers are an essential part of the banking industry.   
Credit Suisse, being an international bank, works in a variety of 
products including Investment Banking, Asset Management and so on.  
Credit Suisse also works with many different brokers, which form an essential
part of the whole business.  
We have been given an array of **N** brokers called **brokers**. Each broker in the broker list is 
identified by a positive integer **brokers[i]**.  
Let's denote the product of elements in a set S = **P<sub>S</sub>**.   
A brokers list is said to be stable if we can divide the brokers into two non-empty subsets set 
A and set B such that 
Gcd(**P<sub>A</sub>**, **P<sub>B</sub>**) = 1   
If the brokers list is stable, then print YES and also in how many ways can we divide this 
list of brokers.
If this isn't possible, print NO and 0.
Since the answer can be large print it mod (**10<sup>9</sup>+7**).

NOTE - The output should be printed in two different lines. Please refer
to the examples

### Problem Constraints
1 <= Size(brokers) <= 10<sup>5</sup>  
1 <= brokers<sub>i</sub> <= 10<sup>6</sup>

### Input Format
The first line contains an integer **N** denoting the size of the brokers
array.  
The second line contains **N** space separated integers
representing the **ith** element of the brokers array.

### Output Format
The first line contains YES or NO  
The second line an integer denoting the number of ways to divide the list
of brokers mod **10<sup>9</sup> + 7**

Note: Do not print Debug Statements while submitting the solution.

### Examples  
#### Example 1
Input
```
3  
2 3 1
```
  
Output
```
YES
6
```

Explanation
The subsets which satisfies the criteria are
```
{1}, {2, 3} = gcd(1, 6) = 1
{1, 2}, {3} = gcd(2, 3) = 1
{1, 3}, {2} = gcd(3, 2) = 1
{2, 3}, {1} = gcd(6, 1) = 1
{3}, {1, 2} = gcd(3, 2) = 1
{2}, {1, 3} = gcd(2, 3) = 1 
```
#### Example 2
Input
```
3  
2 3 6
```
  
Output
```
NO
0
```


