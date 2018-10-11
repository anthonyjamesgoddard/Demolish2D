import numpy as np

# as demolish is a 2D collision detection software
# we only have to check the distance between line segs

# this is just an implementation of the well used
# penalty method for calculating the minimum distance
# between simplices in computational geometry.


# this will need to be implmented in C++, but having a 
# nice simple code in python will benefit us later on.

'''

hf - this is the hessian of f
gf - this is the gradient of f
h  - a vector of contraints
dh - differentiate 
we are minimising over two parameters, x[0], x[1]

give the vertices of the edge points of the line segment
as 
'''

def minimiseDistanceBetweenLineSegments(A,B,C,D,epsilon,tol):
    BA = B-A
    CD = D-C
    hf = np.array([[2*np.dot(BA,BA),-2*np.dot(BA,CD)],
                   [-2*np.dot(BA,CD), 2*np.dot(CD,CD)]])
    x = [0.33,0.1]
    for i in range(100):
        X = A + BA*x[0]
        Y = C + CD*x[1]
        gf = np.array([2*np.dot((X-Y),BA),-2*np.dot((X-Y),CD)])
        h = np.array([-x[0],x[0]-1,-x[1],x[1]-1])
        dh = np.array([[-1,1,0,0],[0,0,-1,1]])
        mask = (h>=0).astype('int')
        dmax = dh*np.vstack([mask,mask])
        grad = gf + eps*np.dot(dmax,np.maximum(np.zeros(4),h))
        hes = hf + eps*np.matmul(dmax,dmax.transpose()) + np.eye(2)/(eps **2)
        dx = np.linalg.solve(hes,grad);
        DX = np.dot(BA,dx[0])
        DY = np.dot(CD,dx[1])
        error = np.sqrt(np.dot(DX,DX) + np.dot(DY,DY))
        if(error<tol):
            break
        x = x-dx
    return x

A = np.array([1,2])
B = np.array([3,4])
C = np.array([10,12])
D = np.array([15,15])

eps = 0.01;tol = 0.001

print(minimiseDistanceBetweenLineSegments(A,B,C,D,eps,tol))

# there is something wrong with this code. It prints the wrong answer 





