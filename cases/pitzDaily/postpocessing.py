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

# # Скорость по X
# plt.plot(times, velocities_x, label="Average Velocity X", color="blue", marker="o")

# # Скорость по Y
# plt.plot(times, velocities_y, label="Average Velocity Y", color="green", marker="o")

# # Скорость по Z
# plt.plot(times, velocities_z, label="Average Velocity Z", color="red", marker="o")

# Модуль скорости (если нужно)
velocities_mag = np.sqrt(np.array(velocities_x)**2 + np.array(velocities_y)**2 + np.array(velocities_z)**2)
plt.plot(times, velocities_mag, label="Average Velocity Magnitude", color="black", linestyle="-", linewidth=2.0)

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


# # Временной шаг (предполагаем равномерный)
# dt = np.mean(np.diff(times))

# # Преобразование Фурье
# n = len(velocities_mag)
# fourier_transform = np.fft.fft(velocities_mag)
# frequencies = np.fft.fftfreq(n, d=dt)

# # Амплитудный спектр (только положительные частоты)
# amplitude_spectrum = 2.0 * np.abs(fourier_transform) / n
# positive_freq_indices = frequencies > 0
# positive_frequencies = frequencies[positive_freq_indices]
# positive_amplitudes = amplitude_spectrum[positive_freq_indices]

# # Построение графика амплитудного спектра
# plt.figure(figsize=(10, 6))
# plt.plot(positive_frequencies, positive_amplitudes, color="blue", linewidth=2)
# plt.title("Amplitude Spectrum of Outlet Velocity Magnitude")
# plt.xlabel("Frequency [Hz]")
# plt.ylabel("Amplitude")
# plt.grid(True)

# # Сохранение графика
# plt.savefig("fourier_transform_velocity.png", dpi=300, bbox_inches="tight")

# # Показать график
# plt.show()


from scipy.signal import find_peaks

# Пример данных (замените на свои)
times = np.linspace(0, 3.5, 1000)  # Временной ряд
velocities_mag = np.sin(2 * np.pi * 5 * times) + 0.85  # Пример сигнала с пиками

# Параметры для поиска пиков
min_peak_height = 0.95  # Минимальная высота пика
min_peak_distance = 50  # Минимальное расстояние между пиками (в индексах)

# Поиск высоких пиков
peaks, _ = find_peaks(velocities_mag, height=min_peak_height, distance=min_peak_distance)

# Проверка, что пики найдены
if len(peaks) == 0:
    print("Высокие пики не найдены.")
else:
    # Время и значения пиков
    peak_times = times[peaks]
    peak_values = velocities_mag[peaks]

    # Вычисление интервалов между высокими пиками
    time_intervals = np.diff(peak_times)

    # Средняя частота высоких пиков
    if len(time_intervals) > 0:
        average_period = np.mean(time_intervals)
        frequency = 1 / average_period
        print(f"Средняя частота высоких пиков: {frequency:.3f} Гц")
    else:
        print("Недостаточно пиков для вычисления частоты.")

    # Визуализация
    plt.figure(figsize=(12, 6))
    plt.plot(times, velocities_mag, label="Average Velocity Magnitude", color="black")
    plt.plot(peak_times, peak_values, "x", color="red", label="High Peaks")
    plt.title("High Peaks Detection")
    plt.xlabel("Time [s]")
    plt.ylabel("Velocity [m/s]")
    plt.legend()
    plt.grid(True)
    plt.show()