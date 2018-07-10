Computational Geometry
====
Some commonly-used algorithms in b-spline and NURBS
----

## De-Boor Algorithm:
De-Boor Algorithm is an efficient and stable numerical method to evaluate the Splines.
### Basic idea
For a spline with degree of k, it will insert the point of interest t* k times to make sure the spline passes through t*, then the position of control point in this case is just t*. The procedure of inserting can be seen as conducting subdivision on the lines between control points, the original ones as well as newly-generated ones.
### How to choose the control points to subdivide


### Algorithm 
```
Input: 
k // Spline Degree, which is also required multiplicity
P=[P_0,P_1,...,P_N-1] // Control Point 
t* // Parameter of interest
Output: 
P(t*) // Evaluation of Spline at t*

Algorithm:
define t = [t_0,t_1,...,t_N-1]
define d
// map control points to sequence in unit range
for i in [0, N-2]:
       t_i <- |P_i+1 - P_i|
       d += t_i
for i in [0, N-2]:
       t_i /= d
       
// first, locate which interval in t t* lies:
find p: t* in [t_p,t_p+1)

       
       
```

