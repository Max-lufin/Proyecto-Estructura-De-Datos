 # Proyecto-I-Estructura-De-Datos

Este proyecto consiste en la implementación de un sistema de recuperacion eficiente de información, desarrollado en lenguaje C. El objetivo principal es el uso de Índices Invertidos y estructuras de datos dinámicas lineales para crear un motor de busqueda, evitando escaneos secuenciales exhaustivos en grandes volúmenes masivos de datos.

El sistema permite cargar usuarios, publicaciones (Post), lista de amistad y "likes" de las publiciones desde archivos de texto, procesarlos en memoria dinámica, filtrar palabras irrelevantes (stopwords) y realizar búsquedas rápidas.

# Estructura del Proyecto

El proyecto está organizado en las siguientes carpetas:

- `/src`: Contiene el código fuente principal (`main.c`).
- `/include`: Contiene el archivo de cabecera (`estructuras.h`) donde se definen las estructuras de datos: listas enlazadas, vocabulario, usuarios y posts.
- `/data`: Contiene los archivos de texto fuente (`usuarios.txt`, `posts.txt`, `amigos.txt`, `likes.txt`).

# Estructuras de Datos

Se implementaron las siguientes listas enlazadas dinámicas:

- **Índice Invertido:** Diccionario o "vocabulario" de términos asociados a una lista de posteos, representados mediante IDs de post.
- **Listas de Amigos:** Listas enlazadas asociadas a cada usuario para gestionar sus amigos.
- **Likes:** Sublistas asociadas a cada publicación.

# Instrucciones de Compilación

Para compilar el proyecto, primero debe estar ubicado en la carpeta `/src` y utiliza el compilador `gcc` desde la terminal:

```bash
gcc main.c -o buscador
```

Una vez compilado, puedes ejecutar el programa con:

```bash
./buscador
```
# funcionalidades

El sistema cuenta con un menú interactivo que permite las siguientes funciones:

- **Información de Usuario:** Permite consultar los datos de un usuario mediante su ID único y despliega la lista de sus amigos y nombre de usuario.

- **Búsqueda por Hashtag:** Utiliza el índice invertido para localizar publicaciones que contienen un hashtag específico. Esta función incluye:

  - **Tokenización:** Separa las frases en términos individuales.

  - **Filtrado de Stopwords:** Omite conectores gramaticales que no aportan valor a la búsqueda, por ejemplo: `el`, `de`, `y`.

  - **Visualización:** Despliega el ID del post, el texto original y la cantidad de likes.

- **Salir:** Finaliza el programa liberando correctamente toda la memoria dinámica utilizada.

# Consideraciones Técnicas

- **Gestión de Memoria:** El programa utiliza `malloc` para la creación dinámica de nodos y `free`, a través de funciones dedicadas como `liberarMemoriaUsuario`, para garantizar la correcta liberación de recursos al finalizar.

- **Robustez:** Se implementó el uso de `long long int` para el manejo de IDs, previniendo desbordamientos de memoria,tambien se implemento con la libreria `string.h`  la funcion strcpy para comparar cadena de caracteres.

# Información Académica

- **Institución:** Universidad de Valparaíso.

- **Escuela:** Escuela de Ingeniería Informática.

