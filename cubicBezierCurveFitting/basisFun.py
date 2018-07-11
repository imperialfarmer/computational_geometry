# -*- coding: utf-8 -*-

import numpy as np
from math import *

def basisFun(u):
    """
    Basis functions of cubic bezier
    :param u: a float, parametric position of point of interest, u in [0,1]
    :return r: array of basis function values, size 4*1
    """

    basis = []
    basis.append((1-u)**3)
    basis.append(3*u*(1-u)**2)
    basis.append(3*u**2*(1-u))
    basis.append(u**3)

    basis = np.array(basis)

    return basis


def bezierEval(q,u):
    """
    Evaluate the bezier value at specific position
    :param  q: array of control points, p[i] in R^3
            u: float, parametric coordinate
    :return r: array of bezier function values, size 3*1
    """

    return np.matmul(basisFun(u),q)

