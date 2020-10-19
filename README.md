
# CryptoSockets - Ejercicio N° 1

- **Francisco Bertolotto - 102671**
- **https://github.com/fbertolotto/7542-TP1**
- **2do Cuatri - 2020**

---

## Enunciado
Se propuso desarrollar dos programas, emisor y receptor, capaces de comunicarse a traves del protocolo TCP - IPV4.
El emisor (cliente) enviara datos cifrados segun los argumentos especificados al momento de ejecutarlo; y el receptor (servidor) estara a cargo de recibirlos, decodificarlos e imprimirlos por salida estándar.

Los métodos disponibles serán:
- **[Cesar](https://es.wikipedia.org/wiki/Cifrado_C%C3%A9sar)**
- **[Vigenere](https://es.wikipedia.org/wiki/Cifrado_de_Vigen%C3%A8re)**
- **[RC4](https://es.wikipedia.org/wiki/RC4)**


## Diseño General

La estructura general del programa se divide en dos grandes módulos. El primero es el **socket**, que se encarga de la comunicación entre ambas partes y el segundo es el **criptógrafo** (crypto) que maneja los distintos métodos y realiza las acciones necesarias para la encriptacion o desencriptacion según sea el caso.


![Estructura General](Informe/estructura.png)

## Problemas Principales

### Distintos Metodos

La diferencia principal de los métodos, es su modo de operar; sin embargo los tres poseen `encriptar` y `desencriptar`. Para unirlos sin necesidad de tener una estructura por cada uno, se utilizo el `criptógrafo` quien posee un puntero a una función de encriptación  y otro a una función de desencriptación. De esta forma, al inicializar un criptógrafo, lo único que se debe variar son esos punteros, ya que entre método y método la diferencia es la función que se ejecuta. 

### criptógrafo

El criptógrafo se crea de forma genérica (sin estar condicionado por su tarea), si bien el servidor no encripta en este ejercicio, el `crypto` que posee tiene las capacidades de encriptar en caso de ser necesario. Lo mismo pero al revés ocurre con el cliente, quien no descifra nada. 
De esta manera, la ampliación de una comunicación `servidor -> cliente` encriptada es posible sin la necesidad de modificar el `crypto` que ya inicializaron.

### Variables que persisten a lo largo de todo el mensaje

Los métodos Vigenere y RC4 poseen ciertas variables que persisten a lo largo de todo el mensaje a descifrar. Para solucionar esto, el crypto reserva ciertos atributos para que puedan perdurar a lo largo de su existencia; ya que es lógico que cuando se destruya el crypto signifique que se termino y por lo tanto se pueden eliminar.


### Envio y recepcion de bytes

Se definió que el envio de bytes seria de 64 (para coincidir con lo leído por stdin). Para garantizar el correcto funcionamiento del crypto y el flujo de datos, se decidió usar un buffer de 65 bytes (64 bytes "visibles" para el uso y el ultimo un `'\0'`). Esto se utilizo como una medida de precaución, sin embargo el programa no depende de encontrar o no un `'\0'` para funcionar correctamente, ya que se guiá exclusivamente por los valores obtenidos por las funciones del sistema. Se encriptan y envían tantos bytes como haya leído el `fread()` y se desencriptan tantos bytes como haya recibido el `recv()`.

### Uso de memoria estatica

El conocer el tamaño de todas las estructuras de ante mano permitió realizar el ejercicio sin necesidad de `malloc`. Si bien se podría haber utilizado para guardar la totalidad del mensaje (ya que desconocemos su largo total) en una variable dinámica junto con `realloc`, no fue necesario ya que el crypto nos ofrece la posibilidad ir descifrando de a "chunks".
Esto ademas hubiese traído problemas en casos donde el mensaje hubiera sido extremadamente largo, ya que estaría en su totalidad en memoria.

## Diagramas

Para comprender mejor el programa en general se presentan varios diagramas.


### Flujo de Envio

![Flujo Envio](Informe/client_flow.png)

En este diagrama se aprecia el flujo del envio de datos, notar que este proceso se repite siempre y cuando el `read` del `file_reader` devuelva un valor distinto de `0`. En ese momento termina la ejecución.

### Flujo de Recepcion

![Flujo Recepcion](Informe/server_flow.png)

Estas operaciones, al igual que antes, se repiten siempre mientras que `recv` obtenga un valor distinto de `0`. Nota: no se encuentra en el diagrama pero luego, se escribe en salida estándar el mensaje original.