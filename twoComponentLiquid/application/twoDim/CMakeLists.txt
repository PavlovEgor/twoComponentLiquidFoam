
cmake_minimum_required(VERSION 2.8)	 # Проверка версии CMake.
										# Если версия установленной программы
										# старее указаной, произойдёт аварийный выход.

project(twoComp_2D)			# Название проекта

set(SOURCE_EXE twoDim.c)		# Установка переменной со списком исходников для исполняемого файла

set(SOURCE_LIB 	../../src/initialize.c
				../../src/LS_solvers.c
				../../src/step.c
				../../src/save.c)			# Тоже самое, но для библиотеки

add_library(TwoComp2D STATIC ${SOURCE_LIB})	# Создание статической библиотеки с именем foo

include_directories(../../include)

add_executable(twoDim ${SOURCE_EXE})	# Создает исполняемый файл с именем main

set(MYCOMPILE_FLAGS "-lm")

add_definitions(${MYCOMPILE_FLAGS})

target_link_libraries(twoDim TwoComp2D m)		# Линковка программы с библиотекой