# -*- coding: utf-8 -*-
"""
Code for cubic Bezier curve fitting

@author: Ge Yin
"""

import matplotlib.pyplot as plt
import numpy as np
from numpy.linalg import inv

from basisFun import *
from chordLengthSeperation import *


def bezierFitting(p):
    """
    Bezier Fitting function
    :param p: array of points, and the curve will be fitted to these points
    :return q: control points of the fitted cubic bezier curve
    """

    t = Seperation(p)

    ## determine matrix L
    # l = p_j - p_0 b_0 - p_n b_3
    # l = p_j - a_0 - a_n
    p_j = [p[i] for i in range(1, len(p)-1)]
    p_j = np.array(p_j)

    a_0 = [p[0]*basisFun(t[i])[0] for i in range(1,len(t)-1)]
    a_0 = np.array(a_0)

    a_n = [p[-1]*basisFun(t[i])[-1] for i in range(1,len(t)-1)]
    a_n = np.array(a_n)

    l = p_j - a_0 - a_n
    l = np.array(l)

    ## determine matrix B
    b = [basisFun(t[i]) for i in range(1,len(t)-1)][1:3]
    b = np.array(np.transpose(b))
    bb_inv = inv(np.matmul(np.transpose(b),b))

    ## find optimal control point
    q = []
    for i in range(3):
        l_i = []
        for j in range(len(b)):
            l_i.append(l[j][i])
        q_i = np.matmul(np.matmul(bb_inv,np.transpose(b)),l_i)
        q.append(q_i)
    q = np.array(q)
    p0 = np.array([p[0][0], p[0][1], p[0][2]])
    q1 = np.array([q[0][0], q[1][0], q[2][0]])
    q2 = np.array([q[0][-1], q[1][-1], q[2][-1]])
    pn = np.array([p[-1][0], p[-1][1], p[-1][2]])

    complete_q = [p0,q1,q2,pn]
    complete_q = np.array(complete_q)
    return complete_q


def main():
    # prepare test data
    # 2D example
    p = [[0,0,0],
         [-1,3,0],
         [3,4,0],
         [8,2,0],
         [10,-2,0],
         [2,-6,0],
         [-2,-8,0]]
    p = np.array(p)
    bezierFitting(p)

    # optimise the control points
    q = bezierFitting(p)
    print('control points = ', q)

    # evaluate the curve
    interval = 1000
    f = []
    for i in range(interval+1):
        u = 1/interval*i
        f_tmp = bezierEval(q,u)
        f.append([f_tmp[0], f_tmp[1], f_tmp[2]])

    # prepare visualisation data

    p_x = np.transpose(p)[0]
    p_y = np.transpose(p)[1]
    p_z = np.transpose(p)[2]
    plt.plot(p_x, p_y, 'ro', label="Points")
    plt.plot(p_x, p_y, 'r--')

    q_x = np.transpose(q)[0]
    q_y = np.transpose(q)[1]
    q_z = np.transpose(q)[2]
    plt.plot(q_x, q_y, 'gs', label="Control Points")
    plt.plot(q_x, q_y, 'wx')
    plt.plot(q_x, q_y, 'g--')

    f_x = np.transpose(f)[0]
    f_y = np.transpose(f)[1]
    plt.plot(f_x, f_y, 'c-', label="Fitted Curve")

    plt.title('Cubic Bezier Curve Fitting')
    plt.xlabel('x')
    plt.ylabel('y')
    leg = plt.legend(loc='lower right', ncol=1, shadow=False, fancybox=False)
    leg.get_frame().set_alpha(0.5)
    plt.show()


if __name__ == '__main__':
    main()

