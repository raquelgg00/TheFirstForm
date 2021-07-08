# Clase Shape
Se van a explicar las funciones de esta clase de forma más detallada ya que maneja cuatro clases que piden distintos parametros. De esta manera los demás puede saber exactamente que hay que pasar por parámetro para cada función.

El tener la clase shape ayuda a la hora de comprobar colisiones (en aquellos casos donde se pueda emplear) frente a la clase Sprite, puesto que no hace falta estar comprobando continuamente si dos objetos se están tocando ya que no tenemos un borde transparente que rodea a la imagen y por tanto sobrecargar menos el juego.

Con esta clase se llaman a los métodos correspondientes para crear y modificar formas. Tenemos una variable denominada *shape_type* que se asigna cuando llamamos al constructor de Shape, donde le pasamos el tipo de forma que queremos crear y con esta variable gestionamos a que clase vamos a llamar dentro de cada método cuando se llame a la función genérica.

## Información
![FIgura convex](https://www.sfml-dev.org/tutorials/2.4/images/graphics-shape-convex.png)

Esta es una figura *convex*, podemos bastante formas modificando los puntos de esta (**setSize()** para establecer las esquinas y **setConvexPoints()**)
## Métodos
### Constructor y destructor
- **Shape(char[])** : Al contructor le pasamos una cadena de caracteres con la que indicamos el tipo de forma que vamos a crear (rectangle, circle, convex, triangle);

- **~Shape()**: Este es el destructor de la clase con el que borramos los objetos que hemos creado y liberamos memoria.

### Funciones de color y texturas
- **void setFillColor(int,int,int)** : Esta función es para asignar un color de relleno a la forma, le pasamos el color en rgb. Para buscar el color se puede entrar en [esta página](https://htmlcolorcodes.com/es/) y copiar los correspondientes valores como tres enteros en el parámetro de la función.

- **void setFillColor(char[])**: Hace lo mismo que la función anterior pero esta vex le podemos pasar un color (red, green, black, yellow, cyan, magenta o blue), por defecto, crea la forma blanca.

- **void setBorder(float, int, int, int)**: Esta función crea y rellena el borde de la forma. Como primer parámetro se pasa el grosor del borde y los otros tres parámetros son el valor en rgb respectivamente.

### Funciones básicas del objeto (Posición, rotación, tamaño y escala)
- **void setSize(float, float = 0)**: Con esta función establecemos el tamaño de la forma. Dependiendo de la forma se pasa de una forma u otra:
    - **Rectangle**: Pasar 2 parámetros (tamaño en 'x' y tamaño en 'y')
    - **Circle**: Pasar 1 parámetro (el radio)
    - **Triangle**: Pasar 1 parámetro (tamaño equivalente al radio)
    - **Convex**: -> Pasar el número de esquinas que se quiere tener, para establecer la posición de cada una llamar a setConvexPoints(), es decir, pasar solo un parámetro (aunque es float, redondeo hacia arriba)

- **setConvexPoints(int, float, float)**: Esta función es solo para la forma convex ya que tenemos que marcar la posición de cada forma. Tenemos que llamar a la función tantas veces como puntos hayamos establecido en setSize().Le pasamos lo siguiente:
    - **1º Parámetro**: El punto al que vamos a establecer la posición
    - **2º Parámetro**: La posición en x
    - **3º Parámetro**: La posición en y

- **void setPosition(float, float)**: Establecemos en que posición queremos que esté el objeto, le pasamos dos datos de tipo coma flotante, la 'x' y la 'y' respectivamente.

- **void setScale(float, float)**: EStablecemos la escala del objeto, le pasamos dos datos de tipo flotante, la escala en 'x' y en 'y' respectivamente.

- **void setRotation(float)**: Determinamos el angulo de rotación de la forma pasándole un dato de tipo float.

### Funciones básicas de colisión y posición
- **void getGlobalBounds()**: Devuelve las colisiones globales del objeto.

- **void getLocalBounds()**: Devuelve las colisiones locales del objeto.

- **void getXPosition()**: Devuelve la posción en x del objeto.

- **void getYPosition()**: Devuelve la posición en y del objeto.

### Funciones básicas GET de la forma
- **void getShape()**: Devuelve la forma.

- **void getRotation()**: Devuelve la rotación del objeto.

- **void getScale()**: Devuelve la escala del objeto.

### Funciones opcionales
- **void move(float, float)**: Le pasamos como parámetros dos float donde indicamos la posición a la que queremos mover la forma, la 'x' y la 'y' automáticamente.