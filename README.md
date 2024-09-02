# GamificandoPendientes
Una plataforma que utiliza elementos de juego para motivar a las personas, estableciendo desafíos, recompensas y reconocimiento por alcanzar objetivos.
Descripción
Este programa es una plataforma para gestionar tareas, recompensas y usuarios. Permite registrar tareas con un código único, asignar recompensas y puntos, y gestionar la información de los usuarios que completan las tareas. La información se guarda en un archivo y se puede cargar y guardar según sea necesario.

Funcionalidades
Registrar Tareas: Permite agregar nuevas tareas con una descripción, puntos de recompensa, recompensa y tema. También se puede especificar el usuario que completará la tarea.
Revisar Tareas Pendientes: Muestra una lista de todas las tareas que aún no han sido completadas.
Completar Tarea: Permite completar una tarea ingresando el código de la tarea. El usuario que completó la tarea recibe puntos y la recompensa asociada.
Revisar Puntos y Recompensas: Muestra la información de todos los usuarios, incluyendo puntos y recompensas acumuladas.
Guardar y Cargar Datos: Los datos se pueden guardar en un archivo y cargar desde él para mantener la información persistente entre ejecuciones del programa.
Instrucciones de Uso
Compilación: Compila el programa usando un compilador C++. Por ejemplo, con g++:

Opción 1: Registrar una nueva tarea.
Opción 2: Revisar tareas pendientes.
Opción 3: Completar una tarea.
Opción 4: Revisar puntos y recompensas.
Opción 5: Guardar y salir.
Detalles Técnicos
Estructuras de Datos:

Usuario: Almacena el nombre del usuario, puntos acumulados y recompensas.
Tarea: Almacena el código de la tarea, descripción, puntos de recompensa, recompensa y tema.
Plataforma: Administra usuarios y tareas, y proporciona funciones para agregar, completar y mostrar tareas y usuarios.
Archivos:

datos_plataforma.txt: Archivo para guardar y cargar la información de usuarios y tareas.
Ejemplo de Uso
Al ejecutar el programa y seleccionar la opción para agregar una tarea, el usuario será solicitado para ingresar la descripción, puntos de recompensa, recompensa, tema, y nombre del usuario que completará la tarea. Si el usuario no está registrado, el programa lo registrará automáticamente.
