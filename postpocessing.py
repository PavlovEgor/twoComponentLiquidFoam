import re
import numpy as np
import matplotlib.pyplot as plt

# Путь к лог-файлу
log_file_path = "log.MyrhoPimpleAdiabaticFoam"  # или "log", или другой путь

# Регулярное выражение для извлечения времени и скорости
pattern = r"Time = (\d+\.?\d*), Average outlet velocity = \(([\d\.\-eE+]+) ([\d\.\-eE+]+) ([\d\.\-eE]+)\)"

# Списки для хранения данных
times = []
velocities_x = []
velocities_y = []
velocities_z = []

# Чтение лог-файла
with open(log_file_path, "r") as file:
    for line in file:
        match = re.search(pattern, line)
        if match:
            time = float(match.group(1))
            vx = float(match.group(2))
            vy = float(match.group(3))
            vz = float(match.group(4))

            times.append(time)
            velocities_x.append(vx)
            velocities_y.append(vy)
            velocities_z.append(vz)

# Построение графика
plt.figure(figsize=(10, 6))

# Скорость по X
plt.plot(times, velocities_x, label="Average Velocity X", color="blue", marker="o")

# Скорость по Y
plt.plot(times, velocities_y, label="Average Velocity Y", color="green", marker="o")

# Скорость по Z
plt.plot(times, velocities_z, label="Average Velocity Z", color="red", marker="o")

# Модуль скорости (если нужно)
velocities_mag = np.sqrt(np.array(velocities_x)**2 + np.array(velocities_y)**2 + np.array(velocities_z)**2)
plt.plot(times, velocities_mag, label="Average Velocity Magnitude", color="black", linestyle="-", linewidth=2)

# Настройки графика
plt.title("Average Outlet Velocity Over Time")
plt.xlabel("Time [s]")
plt.ylabel("Velocity [m/s]")
plt.grid(True)
plt.legend()

# Сохранение графика
plt.savefig("average_outlet_velocity.png", dpi=300, bbox_inches="tight")

# Показать график
plt.show()