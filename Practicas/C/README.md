# Algunos Conceptos
## fork()
La función fork se utiliza para crear un nuevo proceso que represente la duplicación del proceso de la persona que llama.
El proceso hijo es un duplicado del padre, existen algunas diferencias, como que el proceso hijo tiene su propio PID único

### pid_t fork(void)
    * Crea un nuevo proceso ("hijo")
    * El proceso hijo es un duplicado del "padre"
    * Los dos procesos:
        -Tienen PIDs diferentes
        -Corren en espaciso de memoria separados

### return fork()
    * Si todo va bien:
        -retorna al padre: PID del hijo
        -retorno al hijo: 0
    * Si hay errores:
        -retorno del padre: -1
        -el hijo no es creado

### pid_t wait(int *wstatus);
    
