Experiencia de aprendizaje 5. Protocolos de comunicación (ASCII y binario)
============================================================================

Introducción
--------------

La comunicación eficiente entre dispositivos es esencial para crear experiencias interactivas y 
aplicaciones que respondan en tiempo real a datos del entorno. Esta experiencia de aprendizaje te 
sumergirá en el mundo de los protocolos de comunicación serial, centrándote en los formatos ASCII 
y binario, para establecer un vínculo entre un micro:bit y p5.js. Estos dos formatos son fundamentales 
para la transmisión de datos entre dispositivos, y comprender sus diferencias y aplicaciones prácticas 
te permitirá tomar decisiones informadas al diseñar sistemas que requieran la transferencia de información.

Durante las primeras tres sesiones, explorarás a fondo cómo enviar y recibir datos de múltiples sensores 
del micro:bit utilizando ambos formatos. A través de la experimentación y la investigación, entenderás 
cómo estructurar las tramas de datos, codificar y decodificar información, y cómo elegir el formato más 
adecuado según las necesidades de eficiencia, velocidad y legibilidad. 

En las siguientes tres sesiones, aplicarás lo aprendido para crear una aplicación interactiva de arte 
generativo en p5.js. Esta aplicación utilizará los datos de los sensores del micro:bit para influir 
en visualizaciones dinámicas, permitiéndote experimentar con la interacción en tiempo real entre 
hardware y software. Al final de esta experiencia, no solo habrás desarrollado una aplicación creativa, 
sino que también habrás profundizado en la comprensión de cómo los datos pueden ser transmitidos y 
utilizados de manera eficiente.

Esta experiencia no solo te brindará habilidades técnicas en programación y comunicación serial, sino 
que también te permitirá reflexionar sobre la importancia de elegir el protocolo de comunicación adecuado 
en función del contexto y los objetivos de tu proyecto. ¡Prepárate para una inmersión práctica y creativa 
en el mundo de la comunicación entre dispositivos!

Investigación 
---------------

Sesión 1: introducción a la comunicación de datos
***************************************************

La comunicación serial es un método de transmisión de datos en el que los bits se envían secuencialmente 
a través de un solo canal. Es esencial en dispositivos electrónicos para la transferencia eficiente 
de información.

Formato ASCII: ASCII es un estándar de codificación de caracteres que representa texto en computadoras 
y dispositivos de comunicación. Sus características son:

* Legible para humanos.
* Fácil de depurar.
* Ocupa más espacio, ya que convierte números en caracteres.

Formato Binario: transmisión de datos en su forma binaria nativa, sin conversión a caracteres. Sus 
características son:

* Más eficiente en términos de tamaño y velocidad.
* Requiere un manejo más cuidadoso para interpretar correctamente los datos.
  
.. list-table:: Comparación
    :widths: 25 25 25
    :header-rows: 1

    * - Aspecto
      - ASCII
      - Binario
    * - Eficiencia
      - Menor (datos más grandes)
      - Mayor (datos compactos) 
    * - Velocidad
      - Más lenta
      - Más rápida
    * - Facilidad
      - Más fácil de leer y depurar
      - Requiere interpretación adecuada
    * - Usos de Recursos
      - Mayor consumo
      - Menor consumo    

Ahora te propondre enviar datos de un solo sensor del micro:bit a p5.js usando tramas 
ASCII.

Considera los siguientes pasos:

1. En el micro:bit 

.. code-block:: python

    from microbit import *

    # Inicializar UART
    uart.init(baudrate=115200)

    while True:
        if button_a.was_pressed():
            x = accelerometer.get_x()
            data = str(x) + '\n'  # Agregar salto de línea para indicar el fin de la trama
            uart.write(data)
            sleep(100)

2. En p5.js 

.. code-block:: javascript

    let port;
    let connectBtn;
    let sensorValue = 0;


    function setup() {
        createCanvas(400, 400);
        background(220);
        port = createSerial();
        connectBtn = createButton('Connect to micro:bit');
        connectBtn.position(10, 10);
        connectBtn.mousePressed(connectBtnClick);
        textSize(32);
        textAlign(CENTER);
    }

    function draw() {
    
        background(220);

        text("Valor del sensor: " + sensorValue, width / 2, height / 2);


        if(port.availableBytes() > 0){
            sensorValue = port.readUntil('\n');
        }

        if (!port.opened()) {
            connectBtn.html('Connect to micro:bit');
        }
        else {
            connectBtn.html('Disconnect');
        }
    }

    function connectBtnClick() {
        if (!port.opened()) {
            port.open('MicroPython', 115200);
        } else {
            port.close();
        }
    }

* Analiza el código y comprende cómo se envían y reciben los datos en formato ASCII.
* Prueba la aplicación y observa cómo se actualiza el valor del sensor en p5.js.

Sesión 2: comunicación con múltiples sensores en ASCII
*********************************************************

Para enviar múltiples valores de sensores desde el micro:bit a p5.js, es necesario estructurar 
las tramas de datos de manera adecuada. Puedes utilizar diferentes delimitadores y separadores 
para organizar los datos y facilitar su decodificación en p5.js.

* Separadores: Usar comas, punto y coma o tabulaciones para separar valores.
* Delimitadores: Utilizar caracteres como '<' y '>' para indicar el inicio y fin de una trama.

Para enviar los datos desde el micro:bit deberás codificarlos en una cadena estructurada y 
decodificarlos en p5.js para obtener los valores individuales.

Ahora te propondré enviar datos de tres sensores del micro:bit a p5.js usando tramas ASCII.

Considera los siguientes pasos:

1. Para el micro:bit 

.. code-block:: python

    from microbit import *

    # Inicializar UART
    uart.init(baudrate=115200)

    while True:
        if button_a.was_pressed():
            x = accelerometer.get_x()
            y = accelerometer.get_y()
            temp = temperature()
            data = "<{},{},{}>\n".format(x, y, temp)  # Agregar un delimitador y una nueva línea al final
            uart.write(data)  # Enviar la trama de datos
            sleep(100)

2. Para p5.js

.. code-block:: javascript

    let port;
    let connectBtn;
    let sensorValues = [0, 0, 0];  // Valores de los sensores
    let sensorLabels = ['X', 'Y', 'Temp'];  // Etiquetas de los sensores

    function setup() {
        createCanvas(400, 400);
        background(220);
        port = createSerial();
        connectBtn = createButton('Connect to micro:bit');
        connectBtn.position(10, 10);
        connectBtn.mousePressed(connectBtnClick);
        textSize(32);
        textAlign(CENTER);
    }

    function draw() {
        background(220);

        for (let i = 0; i < sensorValues.length; i++) {
            text(sensorLabels[i] + ": " + sensorValues[i], width / 2, height / 2 + i * 40);
        }

        if (port.availableBytes() > 0) {
            let data = port.readUntil('\n');
            if (data) {
                let values = data.substring(1, data.length - 2).split(',');
                for (let i = 0; i < sensorValues.length; i++) {
                    sensorValues[i] = int(values[i]);
                }
            }
        }

        if (!port.opened()) {
            connectBtn.html('Connect to micro:bit');
        } else {
            connectBtn.html('Disconnect');
        }
    }

    function connectBtnClick() {
        if (!port.opened()) {
            port.open('MicroPython', 115200);
        } else {
            port.close();
        }
    }

* Analiza el código y comprende cómo se estructuran y decodifican las tramas de datos en p5.js.
* Prueba la aplicación y observa cómo se actualizan los valores de los sensores en p5.js.

Sesión 3: comunicación en formato binario
*******************************************

En la comunicación en formato binario los datos se transmiten en su forma binaria natural. Hay una 
mayor eficiencia en tamaño y velocidad. 

Comparado con ASCII:

* Eficiencia: en binario es más eficiente.
* Legibilidad: ASCII es más legible y fácil de depurar.
* Complejidad: en binario se requiere más cuidado al codificar y decodificar.

Ahora te mostraré cómo enviar datos en formato binario desde el micro:bit a p5.js.

Considera los siguientes pasos:

1. Para el micro:bit

.. code-block:: python

    from microbit import *
    import struct

    uart.init(baudrate=115200)

    while True:
        if button_a.was_pressed():
            x = accelerometer.get_x()
            y = accelerometer.get_y()
            temp = temperature()
            data = struct.pack('>2i1f',x,y,temp)
            uart.write(data)
            sleep(100)

2. Para p5.js

.. code-block:: javascript

    let port;
    let connectBtn;
    let sensorValues = [0, 0, 0]; // Valores de los sensores
    let sensorLabels = ["X", "Y", "Temp"]; // Etiquetas de los sensores

    function setup() {
    createCanvas(400, 400);
    background(220);
    port = createSerial();
    connectBtn = createButton("Connect to micro:bit");
    connectBtn.position(10, 10);
    connectBtn.mousePressed(connectBtnClick);
    textSize(32);
    textAlign(CENTER);
    }

    function draw() {
    background(220);

    for (let i = 0; i < sensorValues.length; i++) {
        text(
        sensorLabels[i] + ": " + sensorValues[i],
        width / 2,
        height / 2 + i * 40
        );
    }

    if (port.availableBytes() >= 12) {
        let data = port.readBytes(12);
        if (data) {
            const buffer = new Uint8Array(data).buffer;
            const view = new DataView(buffer);
            sensorValues[0] = view.getInt32(0);
            sensorValues[1] = view.getInt32(4);
            sensorValues[2] = view.getFloat32(8);
        }
    }

    if (!port.opened()) {
        connectBtn.html("Connect to micro:bit");
    } else {
        connectBtn.html("Disconnect");
    }
    }

    function connectBtnClick() {
    if (!port.opened()) {
        port.open("MicroPython", 115200);
    } else {
        port.close();
    }
    }

* Analiza el código y comprende cómo se empaquetan y desempaquetan los datos en formato binario.
* Prueba la aplicación y observa cómo se actualizan los valores de los sensores en p5.js.
* Reflexiona sobre las ventajas en eficiencia y las dificultades al interpretar datos binarios.

Reto
------

Vas a crear una aplicación de arte generativo interactivo en tiempo real que te permita 
variar los parámetros visuales a través de los sensores del micro:bit. Utilizarás los
datos de los sensores para influir en la apariencia de la visualización, creando una
experiencia interactiva y creativa.

* Implementa una versión en ASCII de la comunicación entre el micro:bit y p5.js.
* Implementa una versión en binario de la comunicación entre el micro:bit y p5.js.
* Compara las diferencias en eficiencia, velocidad y complejidad entre los dos formatos.

En tu bitácora
***************

* Código fuente de las aplicaciones para el micro:bit y p5.js de la versión ASCII.
* Código fuente de las aplicaciones para el micro:bit y p5.js de la versión binaria.
* Reflexiones sobre las diferencias entre los formatos ASCII y binario en términos de eficiencia, 
  velocidad y complejidad.

..
    Experimento
    let serial;
    let serialPortIsWorking = false;
    let sensorValue = 0;
    let connectButton;

    function setup() {
    createCanvas(400, 400);
    background(220);
    serial = createSerialWithEvents(); // Usar la función con eventos personalizados

    connectButton = createButton("Conectar Serial");
    connectButton.position(10, 10);
    connectButton.mousePressed(connectSerial);
    }

    function draw() {
    background(220);

    if (serialPortIsWorking === true) {
        textSize(32);
        text("Valor del sensor: " + sensorValue, 10, height / 2);
        sensorValue += 1;
    }
    }

    async function connectSerial() {
    
    if (!serial.opened()) {
        
        try{
        await serial.open('MicroPython', 115200);
        console.log("Puerto serial abierto");
        serialPortIsWorking = true;
        // Configurar eventos
        serial.on("data", gotData);
        } catch (err) {
        console.error("Error al abrir el puerto serial:", err);
        }

    }
    else{
        serial.close();
        serialPortIsWorking = false;
        console.log("Puerto serial cerrado");
    }

    print("terminó connectSerial");
    }

    function gotData(data) {
    sensorValue = int(data);
    }

    function createSerialWithEvents() {
    let serial = createSerial(); // Crear la instancia de WebSerial
    serial.events = {}; // Objeto para almacenar eventos

    // Método para registrar eventos
    serial.on = function (event, callback) {
        if (!this.events[event]) {
        this.events[event] = [];
        }
        this.events[event].push(callback);
    };

    // Método para disparar eventos
    serial.trigger = function (event, ...args) {
        if (this.events[event]) {
        this.events[event].forEach((callback) => callback(...args));
        }
    };

    // Verificar datos periódicamente y lanzar el evento 'data' si hay datos
    setInterval(() => {
        if (serial.available() > 0) {
        let data = serial.readUntil("\n"); // Leer hasta un salto de línea
        if (data) {
            serial.trigger("data", data.trim()); // Disparar el evento 'data'
        }
        }
    }, 100); // Verificar datos cada 100 ms

    return serial;
    }
