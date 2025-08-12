import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

Nt = 1000
Nx = 1000
Ncorr = 5

rho = np.empty(shape=(Nt, Nx))
A = np.empty(Nx)
B = np.empty(Nx)
C = np.empty(Nx)
D = np.empty(Nx)

A[0] = 0
B[0] = 1
C[0] = -1
D[0] = 0

A[-1] = 1
B[-1] = -1
C[-1] = 0
D[-1] = 0

u0 = 10.0
dt = 1e-5
dx = 1e-3
alpha = 5e-4
rho_1 = 1.5
rho_2 = 1.0

grid = np.linspace(0, dx * Nx, Nx)

def init():

    for i in range(0, Nx):
        if i < Nx//4 or i > 3 * Nx//4:
            rho[0][i] = rho_2
        elif i < Nx//2:
            rho[0][i] = rho_1 + (rho_2 - rho_1) * (Nx//2 - i) * 4 / Nx
        else:
            rho[0][i] = rho_1 - (rho_2 - rho_1) * (Nx//2 - i) * 4 / Nx


def step_implicite(i):
    if i == 0:
        init()
        return
    
    tmp = rho[i-1]
    for _ in range(Ncorr):

        A[1:-1] = -np.ones(Nx-2) * (dt * u0 / (dx * 2)) + tmp[:-2] * (dt * alpha / ((dx * dx) * 4))
        B[1:-1] = np.ones(Nx-2) - tmp[1:-1] * (dt * alpha / ((dx * dx) * 2))
        C[1:-1] = np.ones(Nx-2) * (dt * u0 / (dx * 2)) + tmp[2:] * (dt * alpha / ((dx * dx) * 4))
        D[1:-1] = rho[i-1][1:-1]
        
        tmp = solve_3_diag(A, B, C, D)

    rho[i] = tmp


def solve_3_diag(A, B, C, D):

    P = np.empty(Nx)
    Q = np.empty(Nx)

    x = np.empty(Nx)

    P[0] = 1
    Q[0] = 0

    for i in range(1, Nx):
        P[i] = - C[i] / (B[i] + A[i] * P[i-1])
        Q[i] = (D[i] - A[i] * Q[i-1]) / (B[i] + A[i] * P[i-1])

    x[-1] = Q[-1]

    for i in range(Nx-2, -1, -1):
        x[i] = P[i] * x[i+1] + Q[i]
    
    return x


def step_explicite(i):
    if i == 0:
        init()
        return

    tmp1 = rho[i-1][1:-1] + rho[i-1][1:-1] * rho[i-1][1:-1] * (dt * alpha / ((dx * dx) * 2))
    tmp2 = rho[i-1][2:] * (dt * u0 / (dx * 2)) + rho[i-1][2:] * rho[i-1][2:] * (dt * alpha / ((dx * dx) * 4))
    tmp3 = -rho[i-1][:-2] * (dt * u0 / (dx * 2)) + rho[i-1][:-2] * rho[i-1][:-2] * (dt * alpha / ((dx * dx) * 4))
    rho[i][1:-1] = ( tmp1 - tmp2 - tmp3)
                   
    rho[i][0] = rho[i][1]
    rho[i][-1] = rho[i][-2]


for i in range(Nt):
    step_implicite(i)

fig, ax = plt.subplots()

line, = ax.plot(grid, rho[0], c="b")
# ax.set(xlim=[-2, 2], ylim=[-0.01, 5])


def update(frame):
    
    line.set_data(grid, rho[frame])

    return line, 


ani = animation.FuncAnimation(fig=fig, func=update, frames=Nt, interval=1e-4)
plt.show()



fig, ax = plt.subplots()

line, = ax.plot(grid, rho[-1], c="b")
plt.show()
