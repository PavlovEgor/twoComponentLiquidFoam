import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import cm



Nx = 100
Ny = 150
Nt = 1000

rho = np.loadtxt("rho.txt")
rho = np.reshape(rho, (Nx, Ny))

plt.imshow(rho)
plt.show()

# rho_1   = 1.5
# rho_2   = 1.0
# Y = (rho_1 / (rho_1 - rho_2)) * (1 - (rho_2 / rho))

dt = 1e-3
dx = 1e-3
dy = 1e-3

grid = np.meshgrid(np.linspace(0, dy * Ny, Ny), np.linspace(0, dx * Nx, Nx))

plt.style.use('_mpl-gallery')

# Plot the surface
fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
ax.plot_surface(grid[0], grid[1], rho, cmap=cm.Blues)

ax.set(xticklabels=[],
       yticklabels=[],
       zticklabels=[])

plt.show()

