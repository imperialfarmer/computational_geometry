Least Square Error Cubic Bezier Fitting
====

## Idea
A curve can be optimally fitted to a sequence of points by adjusting the control points of a cubic bezier curve. The determination of control points is associated with the optimisation process of the square error between estimated curve and points. The best-fitted curve is found when square error reaches minimum. The first 
## Algorithm 
```
Input: 
p, an ordered squence of points, size N*3
Output: 
q, control points for the best-fitted cubic bezier curve, size 2*3

Algorithm:
determine normalised squence t from p // chord-length method
basis function evaluation b(u) at u // size 4*1 
define matrix L = p[1:N-1] + p[0]*b[t[1:N-1]][0] + p[-1]*b[t[1:N-1]][-1]]] // size (N-2)*3
define matrix B = [b[t[1:N-1]][1] b[t[1:N-1]][2]] // size (N-2)*2
q = (B.transpose()*B)^(-1)*B.transpose()*L
return q
```

