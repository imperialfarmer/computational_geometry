Cox De-Boor Algorithm:
====

## Idea
De-Boor Algorithm is an efficient and stable numerical method to evaluate the Splines.

For a spline with degree of k, it will insert the point of interest t* k times to make sure the spline passes through t*, then the position of control point in this case is just t*. The procedure of inserting can be seen as conducting subdivision on the lines between control points, the original ones as well as newly-generated ones.

## Algorithm 
```
Input: a value u 
Output: the point on the curve, p(u) 

If u lies in [uk,uk+1) and u != uk, let h = p (i.e., inserting u p times) and s = 0; 
If u = uk and uk is a knot of multiplicity s, let h = p - s (i.e., inserting u p - s time); 
Copy the affected control points pk-s, pk-s-1, pk-s-2, ..., pk-p+1 and pk-p 
to a new array and rename them as pk-s,0, pk-s-1,0, pk-s-2,0, ..., pk-p+1,0; 

for r := 1 to h do 
for i := k-p+r to k-s do 
begin 
Let ai,r = (u - ui) / ( ui+p-r+1 - ui ) 
Let pi,r = (1 - ai,r) pi-1,r-1 + ai,r pi,r-1 
end 
pk-s,p-s is the point p(u).
```
Details can be seen [MTU](https://pages.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/de-Boor.html)

