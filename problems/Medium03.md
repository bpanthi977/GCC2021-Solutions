# **The Hackathon**
Credit Suisse has multiple departments; they are named as Department1, Department2 and Department3 respectively. We want to create a group of employees from these three departments so that they can participate in a hackathon.  But there are some rules which we need to keep in mind while forming the groups. <br>
<br>
•	There is a limit on the group size. A group can have a specified minimum and maximum number of employees. <br>
<br>
•	 The maximum number of employees from each department (Department1, Department2 and Department3) that can be part of a single group is also known.  <br>

Our aim is to process some requests in the order in which they are given. Each of the request contains a pair of employees who want to be in the same group. For each such request, the employees are placed in the same group if: <br>
<br>
•	The size of the group formed does not exceed the given maximum group limit. <br>
<br>
•	The number of employees in each department does not exceed the maximum for that particular department. <br>
<br>
The request is ignored if these conditions are not met. <br> <br>
After all the requests are considered, the organizer discards all groups with less than the minimum required members, and all remaining groups join the contest.
<br>
<br>
Complete the function **theHackathon** and print the names of all the employees present in the groups that have the maximum number of members. Print "no groups" if there are no groups. Print these names in lexicographical order, on separate lines. You need to take the employee information and requests from the standard input as described in the input format section.


### **Constraints:**
1.   5 <= n <= 10<sup>4</sup>
2.   5 <= m <= 5x10<sup>3</sup>
3.   2 <= a <= 100
4.   2 <= b <= 200 
5.   2 <= f,s,t <= 50
6.   name<sub>i</sub> is an alphanumeric string with at most 10 characters
7.   department<sub>i</sub> belongs to {1,2,3}
8.   All names are unique
9.   x<sub>i</sub>, y<sub>i</sub> are names of existing employees


### **Input Format:**
The first line of input contains seven space-separated integers <b>n</b>,<b>m</b>,<b>a</b>,<b>b</b>,<b>f</b>,<b>s</b>,<b>t</b>.

1. <b>n</b> -total number of employees
2. <b>m</b> -number of requests
3. <b>a</b> and <b>b</b> -minimum and maximum number of employees in a group, respectively.
4. <b>f</b>, <b>s</b> and <b>t</b> -maximum number of employees from the three departments (Department1, Department2 and Department3) in a group, respectively.
 
The <b>i<sup>th</sup></b> of the next <b>n</b> lines contains <b>name<sub>i</sub></b> and <b>department<sub>i</sub></b>, separated by a space, denoting the name and department of the <b>i<sup>th</sup> </b> employee, respectively.
<br>
<br>
The <b>i<sup>th</sup></b> of the next <b>m</b> lines describe the <b>i<sup>th</sup></b> query and contains two space-separated strings <b> x<sub>i</sub>, y<sub>i</sub></b> - denoting that employees <b>x<sub>i</sub></b> and <b>y<sub>i</sub></b> want to be placed in the same group.

### **Output Format:**
If there are no groups in the contest, print "no groups". Otherwise, print the names of all the employees contained in all largest groups, printing each name on a new line.<br>
The names must be sorted in increasing lexicographical order according to their ASCII values.<br>
Do not print Debug Statements while submitting the solution.

### **Examples:**

#### **Example 1:** 
Input:
```
5 7 2 3 2 2 2
A 1
B 2
C 3
D 1
E 2
A B
B A
C D
E D
E A
B D
B C
```

Output:
```
C
D
E
```

Explanation:
```
There are 5 employees and 7 requests. The groups can have between 2 and 3 members. 
A group can have at most 2 employees from the following departments Department1, Department2 and Department3.

A B: create group 1 with employees A and B: {A,B}.
B A: A and B are part of the same group, so no change is needed.
C D: create group 2 with employees C and D: {C,D}.
E D: add E to group 2:{C,D,E}.
E A: we cannot combine groups 1 and 2 because 2 + 3 = 5 > 3. (3 is the maximum number of employees a group can have)
B D: we cannot combine groups 1 and 2 because 2 + 3 = 5 > 3 
B C: we cannot combine groups 1 and 2 because 2 + 3 = 5 > 3

--------------------------------------------------------
Request	                                 Resulting Group(s)
--------------------------------------------------------
A B	                                 {A,B}
B A	                                 No Change ; {A,B}
C D	                                 {A,B} , {C,D}  
E D	                                 {A,B} , {C,D,E}   
E A	                                 No Change ; {A,B} , {C,D,E} 
B D	                                 No Change ; {A,B} , {C,D,E} 
B C	                                 No Change ; {A,B} , {C,D,E} 


The biggest group is group 2: {C,D,E}. Print the names of the employees of group 2.

```


#### **Example 2:** 
Input:
```
9 6 3 5 2 2 2
A 1
B 2
C 3
D 1
E 2
F 3
G 2
H 3
I 1
A B
C D
E D
F G
G C
F A
```

Output:
```
C
D
E
F
G
```


