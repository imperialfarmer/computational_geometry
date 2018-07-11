# -*- coding: utf-8 -*-

from math import *

def Seperation(p):
    """
    Generate the normalised sequence of control points based on chord length
    :param p:   array of points
    :return t:  array of normalised parametric coordinates of p
    """

    d = 0
    t =[]
    t.append(d)

    for i in range(len(p)-1):
        d += sqrt( (p[i+1][0]-p[i][0])**2 + (p[i+1][1]-p[i][1])**2 + (p[i+1][2]-p[i][2])**2 )
        t.append(d)

    for i in range(len(t)):
        t[i] /= d

    # for checking
    print(d)
    print(t)

    return t
