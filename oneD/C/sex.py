import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Параметры задачи
u0 = 1.0      # Скорость переноса
alpha = 5e-3   # Коэффициент диффузии
L = 20.0      # Длина пространственной области
T = 5.0       # Время моделирования

# Параметры сетки
Nx = 2000      # Количество пространственных узлов
Nt = 2000     # Количество временных шагов
dx = L / Nx   # Пространственный шаг
dt = T / Nt   # Временной шаг

# Проверка условий устойчивости
CFL = abs(u0) * dt / dx
diffusion_stability = alpha * dt / dx**2

print(f"Число Куранта (CFL): {CFL:.4f}")
print(f"Параметр устойчивости диффузии: {diffusion_stability:.4f}")

if CFL > 1.0:
    print("Предупреждение: CFL > 1, схема может быть неустойчивой!")
if diffusion_stability > 0.5:
    print("Предупреждение: параметр диффузии > 0.5, схема может быть неустойчивой!")

# Создание сетки
x = np.linspace(0, L, Nx, endpoint=False)

# Начальное условие (гауссов импульс)
def gaussian(x, mu, sigma):
    return np.exp(-(x - mu)**2 / (2 * sigma**2))

rho = gaussian(x, mu=L/4, sigma=L/20) + 0.5*gaussian(x, mu=3*L/4, sigma=L/30)

# Подготовка для анимации
fig, ax = plt.subplots(figsize=(10, 6))
line, = ax.plot(x, rho, 'b-', lw=2)
ax.set_xlim(0, L)
ax.set_ylim(-0.1, 1.5)
ax.set_xlabel('Пространство, x')
ax.set_ylabel('Плотность, ρ')
ax.set_title('Решение уравнения переноса с нелинейной диффузией')
ax.grid(True)

# Функция для обновления решения на каждом шаге
def update(n):
    global rho
    rho_new = np.zeros_like(rho)
    
    for i in range(Nx):
        # Периодические граничные условия
        left = (i - 1) % Nx
        right = (i + 1) % Nx
        
        # Конвективный член (upwind схема)
        if u0 >= 0:
            conv = u0 * (rho[i] - rho[left]) / dx
        else:
            conv = u0 * (rho[right] - rho[i]) / dx
        
        # Диффузионный член (центральная разность)
        rho2_left = rho[left]**2
        rho2_center = rho[i]**2
        rho2_right = rho[right]**2
        
        diff = (alpha/2) * (rho2_right - 2*rho2_center + rho2_left) / dx**2
        
        # Обновление решения
        rho_new[i] = rho[i] - dt * (conv + diff)
    
    rho = rho_new.copy()
    line.set_ydata(rho)
    ax.set_title(f'Решение уравнения: t = {n*dt:.2f} / {T:.2f}')
    return line,

# Создание анимации
ani = FuncAnimation(fig, update, frames=Nt, interval=20, blit=True)

plt.tight_layout()
plt.show()

# Для сохранения анимации (раскомментируйте при необходимости)
# ani.save('transport_equation.gif', writer='pillow', fps=30)