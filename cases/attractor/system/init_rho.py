import numpy as np

# Параметры
rho0 = 1.0
H = 1.0
nx, ny, nz = 10, 10, 1  # количество ячеек по осям (замените на свои)

# Координаты ячеек (пример)
y = np.linspace(0, H, ny)

# Генерация значений
rho_values = []
for j in range(ny):
    rho_values.append(rho0 * (1 - y[j] / H))

# Сохранение в файл
with open("rhoInitialValues", "w") as f:
    for val in rho_values:
        f.write(f"{val}\n")