import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

rho = np.loadtxt("data.txt")
Nt, Nx = rho.shape

dt = 1e-7
dx = 1e-3

grid = np.linspace(0, dx * Nx, Nx)

fig, ax = plt.subplots()

line, = ax.plot(grid, rho[0], c="b")
# ax.set(xlim=[-2, 2], ylim=[-0.01, 5])

def update(frame):
    
    line.set_data(grid, rho[frame])

    return line, 


ani = animation.FuncAnimation(fig=fig, func=update, frames=Nt, interval=30)
plt.show()


fig, ax = plt.subplots()

line, = ax.plot(grid, rho[-1], c="b")
plt.show()
