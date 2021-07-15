# Ejercicio 4.a

La biblioteca tasks define una estructura para mantener el estado de cada tarea, la estructura contiene: la función que debe realizar, cada cuanto tiempo (ms) y un contador de los ticks transcurridos. También tiene funciones para inicializar una tarea y para definirla con una función y el tiempo que debe transcurrir entre tareas.

La función para ejecutar una tearea decrementa _st_ hasta llegar a 0 (transcurre el tiempo entre tareas) y luego ejecuta la tarea, volviendo a setear _st_ a _ms_ (el tiempo inicial).
