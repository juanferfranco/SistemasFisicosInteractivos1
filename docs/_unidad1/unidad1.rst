Unidad 1. Software para sistemas embebidos
==============================================

.. warning:: ESTOY REFORMANDO ESTA UNIDAD

    Estoy haciendo algunos cambios a esta unidad. 
    Te pido me esperes un par de días. Estoy decidido a optimizar los 
    costos del hardware externo para que la inversión no sea tan 
    alta.

..
  Introducción
  --------------

  En esta unidad vas a aprender técnicas para programar 
  los sistemas embebidos (controladores) que permitirán capturar y/o generar 
  la información que fluye desde y hacia el mundo exterior 
  de la aplicación interactiva.

  Propósito de aprendizaje
  ***************************

  Modelar el software del controlador, mediante estados, eventos 
  y acciones.

  Implementar el software del controlador mediante las técnicas de
  programación adecuadas que permitan sacarle el máximo provecho a
  dicho controlador.

  Evaluación
  ---------------------------

  Para realizar la evaluación vas a utilizar 
  `este <https://classroom.github.com/a/oSPO_9kn>`__ repositorio.

  Recuerda entregar la documentación solicitada en el archivo 
  README.md

  En un escape room se requiere construir una aplicación para controlar 
  una bomba temporizada.La siguiente figura ilustra la interfaz de la bomba. 
  El circuito de control de la bomba está compuesto por tres sensores digitales,
  en este caso pulsadores, denominados UP, DOWN, ARM,
  un display (simulado con el serial), un LED que indica si la bomba está 
  armada o no y un LED que simula la activación de la bomba.

  .. image:: ../_static/bomb.png
    :alt: bomba

  El controlador funciona así:

  * Inicia en modo de ``configuración``, es decir, sin hacer cuenta regresiva aún, 
    la bomba está ``desarmada``. El valor inicial del conteo regresivo es de 20 segundos.
  * En el modo de configuración, los pulsadores UP y DOWN permiten
    aumentar o disminuir el tiempo inicial de la bomba. El LED de bomba armada  
    está PERMANENTEMENTE apagado.
  * El tiempo se puede programar entre 10 y 30 segundos con cambios de 1 segundo.
  * El tiempo de configuración se debe visualizar enviando 
    el valor del conteo ``SOLO`` cada que cambie.
  * El pulsador ARM arma la bomba.
  * Una vez armada la bomba, comienza la cuenta regresiva que será visualizada
    por el serial por medio de una cuenta regresiva en segundos. El LED 
    de bomba armada funciona a una frecuencia de 1 Hz.
  * La bomba explotará (se activa la salida de activación de la bomba) cuando
    el tiempo llegue a cero. 
  * Cuando la bomba explote el LED que simula la activación de la bomba 
    funcionará a 5 Hz durante 5 segundos. 
  * Luego de los 5 segundos el control regresará al modo de
    configuración.
  * Una vez la bomba esté armada es posible desactivarla ingresando un código
    de seguridad. El código será la siguiente secuencia de pulsadores
    presionados uno después de otro:  UP, DOWN, UP, DOWN, UP, UP, ARM. Ten 
    presente que el controlador solo debe verificar si la secuencia es correcta 
    una vez la reciba completa.
  * Si la secuencia se ingresa correctamente la bomba pasará de nuevo
    al modo de configuración de lo contrario continuará la fatal cuenta
    regresiva.
  * Debes almacenar la clave de desarmado de la bomba en un arreglo.
  * Debes definir una función a la cual le pasarás la dirección en memoria 
    de dos arreglos: uno con la clave recibida y otro con la clave correcta. 
    La función deberá devolver un `bool <https://www.arduino.cc/reference/en/language/variables/data-types/bool/>`__ 
    así: true si la clave recibida es igual a la clave almacenada o 
    false si las claves no coinciden.

  Arquitectura del software:

  Tu aplicación debe tener dos tareas:

  * La tarea del controlador.
  * Una tarea que controle un LED a una frecuencia de 0.5 Hz.

  Ten presente las siguientes restricciones:

  * Para la lectura de los botones ``DEBES`` usar la biblioteca 
    `ezButton <https://github.com/ArduinoGetStarted/button>`__.

  Para la documentación:

  * Define y explica los estados que usaste para resolver el problema.
  * Define y explica los eventos que usaste.
  * Define y explica las acciones.
  * Explica cómo probaste el funcionamiento correcto de la aplicación.
  * Explica cómo resolviste el problema de la clave.

  Trayecto de actividades
  ---------------------------

  Ejercicios 
  ************

  Ejercicio 1: introducción  
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  .. warning:: RECUERDA LO QUE APRENDERÁS EN ESTE CURSO

      En este curso aprenderás a construir aplicaciones interactivas 
      que lean información del mundo exterior y lo modifiquen.

  ¿Recuerdas que te mostré al iniciar el curso un trabajo de grado realizado 
  por estudiantes del programa? Te voy a pedir que veas algunos segundos del 
  video del DEMO de `este <https://tdaxis.github.io/demo.html>`__ trabajo.

  Déjame te hablo de nuevo de este sistema porque es un excelente resumen 
  de lo que busco que aprendas con este curso.

  .. figure:: ../_static/TDAxis.jpg
    :alt: TDAxis
    :class: with-shadow
    :align: center
    :width: 100%

    Demo del sistema TDAxis

  |

  La idea de la aplicación es VARIAR las visuales y el audio con la 
  información del movimiento que se captura en tiempo real de una bailarina.

  La imagen está dividida en 4 partes. En la esquina superior izquierda 
  observarás ``LA APLICACIÓN INTERACTIVA`` que está corriendo en un computador. 
  Esta aplicación se encargará de proyectar las visuales que están en la esquina 
  superior derecha y controlador el software de audio que está en la esquina inferior 
  derecha. Observa la esquina inferior izquierda. Allí verás una captura 
  en tiempo real de los movimientos de una bailarina.

  ¿Cómo se captura este movimiento? Se hace por medio de unos dispositivos que te 
  mostraré en estos videos:

  * `Perception Neuron Trailer <https://youtu.be/v72P7q0sIXI>`__. 
  * `Bailarina controlando un metahumano <https://youtu.be/pynCWHD8RPg>`__. 

  Los dispositivos que llevan puestos las personas en los videos están computados por:

  * Un sensor para medir el movimiento.
  * Un computador embebido o microcontrolador que lee la información del sensor.
  * Un radio de comunicación inalámbrica para transmitir la información leída.

  La información se le entrega al computador que ejecuta la aplicación interactiva 
  usando un ``PROTOCOLO DE COMUNICACIÓN``. El protocolo es un acuerdo que se establece 
  entre las partes involucradas en la comunicación de tal manera que ambas 
  puedan entenderse.

  ¿Por qué te muestro todo esto?

  Porque en este curso vamos a realizar un recorrido por los elementos que 
  componente este tipo de aplicaciones. 

  En esta unidad vas a programar un microcontrolador similar al que tienen 
  los dispositivos de captura de movimiento. En las unidades 2 y 3 vas 
  experimentar con dos tipos de protocolos de comunicación. Finalmente, 
  en la unidad 4 construirás una aplicación simple que integre todos los 
  elementos. 

  .. warning:: ESTO ES MUY IMPORTANTE 

      Las aplicaciones que realizarás serán simples, PERO si lo analizas 
      te darás cuenta que contienen todos los elementos necesarios para que 
      entiendas cómo funcionan las aplicaciones que te mostré en los videos.

  .. note:: hay otro curso en el programa para seguir profundizando  

      En el programa encontrarás otro curso llamado sistemas físicos 
      interactivos 2. Es una curso de la línea de experiencias interactivas 
      que puedes tomar como optativa del ciclo profesional si no estás en 
      la línea de experiencias. En este curso vas a construir una aplicación 
      usando todo lo que aprenderás en sistemas físicos interactivos 1. 
      Mira por ejemplo `el proyecto <https://github.com/juanferfranco/RisitasCorp_Rider>`__ 
      que realizaron unos de tus compañeros.

  Ejercicio 2: ¿Cómo funciona un microcontrolador? 
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  Un microcontrolador es un computador dedicado a ejecutar una aplicación 
  específica para resolver un problema muy concreto. Por ejemplo, leer la información 
  de un sensor y transmitir esa información a un computador. 

  En este curso vas a utilizar el sistema 
  `raspberry pi pico <https://www.raspberrypi.com/products/raspberry-pi-pico/>`__. 

  Ejercicio 3: ¿Cómo puedes programar el microcontrolador? 
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  Para programar el microcontrolador vas a necesitar:

  * Un editor de código de C++.
  * Varios programas que permitan transformar el código de C++ a 
    instrucciones de máquina.
  * Almacenar las instrucciones de máquina en la memoria flash 
    del microcontrolador.

  Sigue estos pasos:

  * Descarga la versión .ZIP del IDE de arduino versión 1.8.19
  * Descomprime el archivo .ZIP
  * Busca la carpeta donde está el archivo arduino.exe y crea 
    allí el carpeta portable.
  * Abre el programa arduino.exe.
  * Sigue las instrucciones de la sección Installing via Arduino Boards Manager 
    que encontrarás en `este <https://github.com/earlephilhower/arduino-pico#installing-via-arduino-boards-manager>`__ 
    repositorio. 

  Ahora vas a probar que puedes programar el raspberry pi pico:

  * Conecta al computador el raspberry pi pico.
  * En el menú Herramientas/Placa/Raspberry PI selecciona la tarjeta 
    Raspberry Pi Pico.
  * En el menú Herramientas/Puerto selecciona asignado por el sistema 
    operativo al raspberry. 

  Ingresa el siguiente programa:

  .. code-block:: cpp

      void setup() {
        pinMode(LED_BUILTIN, OUTPUT);
      }

      void loop() {
        static uint32_t previousTime = 0;
        static bool ledState = true;

        uint32_t currentTime = millis();

        if( (currentTime - previousTime) > 100){
          previousTime = currentTime;
          ledState = !ledState; 
          digitalWrite(LED_BUILTIN, ledState);
        }
      }

  Por último presiona el ícono Subir, el segundo ubicado en la esquina }
  superior izquierda. Al hacer esto ocurrirán varias cosas:

  * Se transformará el programa de código C++ a lenguaje de máquina.
  * Se enviará el código de máquina del computador a la memoria flash del 
    raspberry pi a través del puerto que el sistema operativo le asignó 
    a la tarjeta.

  Deberás ver el LED ubicado al lado del conectar USB enciendo y apagando 
  muy rápido.

  Ejercicio 3a: retrieval practice (evaluación formativa)
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  En este punto te voy a pedir que coloques bajo control de versión 
  un programa y practiques lo que estudiantes en la 
  introducción de control de versión.

  * Conforma tu equipo de trabajo (recuerda que el equipo es de dos personas,
    NO UNA).
  * Acepta la evaluación que está `aquí <https://classroom.github.com/a/SwuS7pD_>`__. 
    El sistema primero te pedirá que crees el equipo de trabajo. Esto 
    lo hace solo uno de los miembros del equipo, mientras que el otro solo tendrá 
    que unirse al equipo. Luego aceptas la evaluación. Esto lo hace cada miembro.

  .. warning:: MUY IMPORTANTE

      DOS PERSONAS no pueden trabajar al mismo tiempo sobre el mismo archivo 
      cuando el proyecto está bajo control de versión porque se crean 
      conflictos, es decir, el sistema no sabe cuál de las dos versiones 
      del archivo es la correcta.

  * Ve a la terminal y clona el repositorio.
  * En la carpeta donde está el repositorio vas a crear un proyecto para 
    el raspberry pi pico usando el IDE de Arduino.
  * Usa el mismo código del ejercicio, pero esta vez cambia el 100 por un 500. 
    observa el resultado de esta cambio.
  * Una vez termines el programa, lo veas funcionando y documentes el efecto 
    del cambio, ``DEBES cerrar el IDE de Arduino``.
  * Regresa a la terminal. Realiza un commit con esta nueva versión del programa.
  * Ahora añade el archivo README.md. Coloca el nombre del equipo, el nombre 
    de los integrantes y el ID. Coloca en el archivo el resultado del cambio de 
    100 a 500. Describe lo que viste.
  * Realiza un segundo commit para incluir el archivo README.md con la documentación. 
  * Sincroniza el repositorio local con el remoto.

  Ejercicio 4: retrieval practice (evaluación formativa)
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  En este punto tu equipo de trabajo ya debe estar creado. Solo tendrás 
  que aceptar la evaluación `aquí <https://classroom.github.com/a/MMdNOCa1>`__.

  En el repositorio de la evaluación solo debes adicionar un archivo README.md 
  con el nombre del equipo, integrantes y ID y un enlace a un repositorio 
  ``PÚBLICO`` donde harás lo siguiente:

  * Crea un proyecto para el raspberry pi.
  * En el código modifica el 500 por 1000.
  * Coloca el proyecto bajo control de versión.
  * Sincroniza tu repositorio local con un repositorio público en 
    Github. El enlace a este repositorio será el que coloques 
    en el archivo README.md de la evaluación.

  Ejercicio 5: documentación 
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  Para programar el raspberry pi pico tienes mucha documentación con información. 
  Algunos sitios que pueden serte de utilidad son:

  * `API de arduino <https://www.arduino.cc/>`__. 
  * `Port para raspberry pi pico del API de arduino <https://arduino-pico.readthedocs.io/en/latest/#>`__.
  *  `Sitio oficial del raspberry pi pico <https://www.raspberrypi.com/products/raspberry-pi-pico/>`__.

  Ejercicio 6: montaje
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  El siguiente ejercicio es un reto. Te voy a dar dos cosas. Unos materiales y un programa 
  de prueba. El objetivo es que hagas el montaje de prueba correctamente y lo pruebes 
  con el programa de prueba. ¿Qué debes hacer? Busca en Internet cómo conectar 
  LEDs y pulsadores (push buttons) a un raspberry pi pico en un protoboard.

  El montaje tendrá 4 sensores y 4 actuadores que estarán conectados al 
  raspberry pi pico así:

  ====================== ====================
  Puerto del raspberry     dispositivo
  ====================== ====================
  GP2                     button1   
  GP3                     button2
  GP4                     button3
  GP5                     button4
  GP18                    LED RED
  GP19                    LED GREEN
  GP20                    LED BLUE
  GP21                    LED YELLOW    
  ====================== ====================

  Ten presente `este <https://datasheets.raspberrypi.com/pico/Pico-R3-A4-Pinout.pdf>`__ 
  documento para identificar los puertos del raspberry pi pico.

  .. code-block:: cpp

    void task1()
    {
        // Definición de estados y variable de estado
        enum class Task1States
        {
            INIT,
            WAIT_TIMEOUT
        };
        static Task1States task1State = Task1States::INIT;

        // Definición de variables static (conservan
        // su valor entre llamadas a task1)
        static uint32_t lasTime = 0;

        // Constantes
        constexpr uint32_t INTERVAL = 1000;
        constexpr uint8_t button1Pin = 2;
        constexpr uint8_t button2Pin = 3;
        constexpr uint8_t button3Pin = 4;
        constexpr uint8_t button4Pin = 5;
        constexpr uint8_t ledRed = 18;
        constexpr uint8_t ledGreen = 19;
        constexpr uint8_t ledBlue = 20;
        constexpr uint8_t ledYellow = 21;

        // MÁQUINA de ESTADOS

        switch (task1State)
        {
        case Task1States::INIT:
        {
            Serial.begin(115200);
            pinMode(button1Pin, INPUT_PULLUP);
            pinMode(button2Pin, INPUT_PULLUP);
            pinMode(button3Pin, INPUT_PULLUP);
            pinMode(button4Pin, INPUT_PULLUP);
            pinMode(ledRed, OUTPUT);
            pinMode(ledGreen, OUTPUT);
            pinMode(ledBlue, OUTPUT);
            pinMode(ledYellow, OUTPUT);
            lasTime = millis();
            task1State = Task1States::WAIT_TIMEOUT;

            break;
        }
        case Task1States::WAIT_TIMEOUT:
        {
            uint8_t btn1State = digitalRead(button1Pin);
            uint8_t btn2State = digitalRead(button2Pin);
            uint8_t btn3State = digitalRead(button3Pin);
            uint8_t btn4State = digitalRead(button4Pin);
            uint32_t currentTime = millis();

            // Evento 1:
            if ((currentTime - lasTime) >= INTERVAL)
            {   
                lasTime = currentTime;
                printf("btn1: %d,btn2: %d, btn3: %d, btn4: %d\n", btn1State, btn2State, btn3State, btn4State);
            }

            // Evento 2
            if (btn1State == LOW)
                digitalWrite(ledRed, HIGH);
            // Evento 3
            if (btn2State == LOW)
                digitalWrite(ledGreen, HIGH);
            // Evento 4
            if (btn3State == LOW)
                digitalWrite(ledBlue, HIGH);
            // Evento 5
            if (btn4State == LOW)
                digitalWrite(ledYellow, HIGH);

            break;
        }
        default:
        {
            Serial.println("Error");
        }
        }
    }

    void setup()
    {
        task1();
    }

    void loop()
    {
        task1();
    }

  Ejercicio 7: análisis del programa de prueba  
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  Miremos algunos aspectos del programa:

  * Los programas los dividiremos en tareas. En este caso 
    solo tenemos una. Las tareas son una manera de distribuir 
    el trabajo para poder realizar el programa en equipo. Lo 
    ideal es que las tareas sean independientes, pero no siempre 
    se logra. Por tanto, será necesario definir mecanismos de 
    comunicación entre ellas.
  * Este programa tiene un pseudo estado y un estado, pero 
    desde ahora diremos que tiene 2 estados: 

    .. code-block:: cpp
    
        enum class Task1States
        {
            INIT,
            WAIT_TIMEOUT
        };

  * ¿Qué son los estados? Son condiciones de espera. Son momentos 
    en los cuales tu programa está esperando a que algo ocurra. En este 
    caso en ``Task1States::INIT`` realmente no ``ESPERAMOS`` nada, por eso 
    decimos que es un pseudo estado. Este estado SIEMPRE lo usaremos 
    para configurar las condiciones INICIALES de tu programa.
  * Nota cómo se pasa de un estado a otro:: 
    
      task1State = Task1States::WAIT_TIMEOUT;

  * En el estado `Task1States::WAIT_TIMEOUT` estamos esperando a 
    que ocurran varios ``EVENTOS``. En este caso los eventos los 
    identificamos mediante los ``IF``. Por tanto, en un estado tu 
    programa estará siempre preguntando por la ocurrencia de algunos 
    eventos.
  * Cuando la condición de un evento se produce entonces tu programa 
    ejecuta ACCIONES. Por ejemplo aquí:

    .. code-block:: c

      if (btn4State == LOW)
        digitalWrite(ledYellow, HIGH);
    
    Si el evento ``if (btn4State == LOW)`` ocurre, el programa 
    ejecutará una sola acción que será ``digitalWrite(ledYellow, HIGH);``.
    Ten presente que si requieres ejecutar más acciones en este evento, 
    tendrás que encerrarlas con llaves ``{}``.

  Ejercicio 8: retrieval practice (evaluación formativa)
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  Lo primero que debes hacer es aceptar 
  `esta <https://classroom.github.com/a/m7LkASpg>`__ evaluación e 
  ingresar a tu equipo de trabajo. 

  * Entra al repositorio y copia la url para clonarlo en tu 
    computador local.
  * Realiza un programa que implemente la lógica que muestra la siguiente 
    tabla: 

    ==========  ==========  ==============
    button1     button2     LED
    ==========  ==========  ==============
    LOW         LOW         LED RED
    LOW         HIGH        LED GREEN
    HIGH        LOW         LED BLUE
    HIGH        HIGH        LED YELLOW
    ==========  ==========  ==============

  Antes de comenzar a programar:

  * ¿Entiendes el problema?
  * ¿Cuáles son los estados de tu programa?
  * ¿Cuáles serían los eventos?
  * ¿Cuáles serían las acciones?

  En el README.md del repositorio contesta las preguntas anteriores.

  Ejercicio 9: tareas concurrentes (evaluación formativa)
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  Para sacar el máximo provecho a la CPU de tu microcontrolador lo 
  ideal es dividir el problema en varias tareas que se puedan 
  ejecutar de manera concurrente. La arquitectura de software 
  que te voy a proponer es esta:

  .. code-block:: cpp

    #include "task1.h"
    #include "task2.h"
    #include "task3.h"

    void setup()
    {
        task1();
        task2();
        task3();
    }

    void loop()
    {
        task1();
        task2();
        task3();
    }

  Nota entonces que tu programa está dividido en tres tareas. La función setup 
  se ejecuta una sola vez y ahí se llama por primera vez cada tarea. La función 
  loop se ejecuta cada que las tareas terminan, es como un ciclo infinito.

  Te voy a mostrar el código para la task1 y luego con tu equipo vas 
  a construir las demás tareas. La frecuencia del LED rojo será de 5 Hz

  Acepta `esta <https://classroom.github.com/a/t-YZPz7J>`__ evaluación.

  El objetivo es que hagas un programa donde tengas 4 tareas y cada 
  una controle un LED a 0.5 Hz, 1 Hz, 2 Hz y 4 Hz.

  Te voy a dejar como el ejemplo el programa de una de las tareas 
  que controlará el LED ROJO a 0.5 Hz. Te queda entonces el retor de realizar 
  las tareas para los otros LEDs. No olvides sincronizar tu repositorio 
  local con el remoto donde está la evaluación.

  .. code-block:: cpp

    void task1(){
        enum class Task1States{
            INIT,
            WAIT_TO_TOGGLE_LED
        };
        static Task1States task1State = Task1States::INIT;
        static uint32_t lasTime;
        static constexpr uint32_t INTERVAL = 1000;
        static constexpr uint8_t ledRed = 18;
        static bool ledStatus = false;

        switch(task1State){
            case Task1States::INIT:{
                pinMode(ledRed,OUTPUT);
                lasTime = millis();
                task1State = Task1States::WAIT_TO_TOGGLE_LED;
                break;
            }

            case Task1States::WAIT_TO_TOGGLE_LED:{
                // evento 1:
                uint32_t currentTime = millis();
                if( (currentTime - lasTime) >= INTERVAL ){
                    lasTime = currentTime;
                    ledStatus = !ledStatus;
                    digitalWrite(ledRed,ledStatus);
                    
                }
                break;
            }

            default:{
                break;
            }
        }

    }  

  Ejercicio 10: monitor serial
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  Para profundizar un poco más en el funcionamiento de los programas 
  vas a usar una herramienta muy interesante llamada terminal serial.
  En este curso vas a utilizar ScriptCommunicator. La aplicación 
  la puedes descargar de `este <https://sourceforge.net/projects/scriptcommunicator/>`__
  sitio. Al instalarla en los computadores de la Universidad usa un directorio 
  del usuario y deshabilita la creación de accesos directos en el escritorio y 
  no asocies los archivos .js con ScriptCommunicator.

  Para lanzar la aplicación abre el directorio donde la instalaste y lanza 
  el programa ScriptCommunicator.exe

  Ingresa al menu Settings, selecciona la pestaña serial port y elige 
  el puerto (el puerto asignado por el sistema operativo a tu sistema 
  de desarrollo) y el BaudRate a 115200. Los demás parámetros los puedes 
  dejar igual.

  Selecciona la pestaña console options y allí marca ÚNICAMENTE las opciones: 
  utf8, receive, hex, mixed.

  En la pestaña serial port ve a la sección general, selecciona como 
  current interface ``serial port``. Cierra la ventana de configuración.

  .. warning:: IMPORTANTE

    No olvides que para DEBES TENER conectado el sistema de desarrollo 
    al computador para poder seleccionar el Port correcto.

  Para conectar ScriptCommunicator al microcontrolador, solo tienes que 
  dar click en Connect y para desconectar Disconnect.

  .. warning:: ESTO ES CRÍTICO

    SOLO UNA APLICACIÓN puede comunicarse a la vez con el microcontrolador.
    Por tanto SOLO una aplicación puede abrir o conectarse al puerto 
    serial que el sistema operativo le asigna al sistema de desarrollo.

    Esto quiere decir que no puedes programar el raspberry mientras tienes 
    abierto ScriptCommunicator conectado al puerto serial.

  Ejercicio 11: realiza algunas pruebas
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  Ahora vas a probar ScriptCommunicator con el sistema de desarrollo.

  Utiliza el siguiente programa:

  .. code-block:: cpp

    void task1()
    {
        enum class Task1States
        {
            INIT,
            WAIT_DATA
        };
        static Task1States task1State = Task1States::INIT;

        switch (task1State)
        {
        case Task1States::INIT:
        {
            Serial.begin(115200);
            task1State = Task1States::WAIT_DATA;
            break;
        }

        case Task1States::WAIT_DATA:
        {
            // evento 1:
            // Ha llegado al menos un dato por el puerto serial?
            if (Serial.available() > 0)
            {                  
                Serial.read();
                Serial.print("Hola computador\n"); 
            }
            break;
        }

        default:
        {
            break;
        }
        }
    }

  Ahora abre ScriptCommunicator:

  * Presiona el botón Connect.
  * Selecciona la pestaña Mixed.
  * Luego escribe una letra en la caja de texto que está debajo del botón 
    ``send``. Si quiere coloca la letra `s`.
  * Al lado del botón send selecciona la opción utf8.
  * Dale click a send.
  * Deberías recibir el mensaje ``Hola computador``.

  Ahora PIENSA:

  #. Analiza el programa.
  #. `Abre <https://www.asciitable.com/>`__ esta tabla.
  #. Analiza los números que se ven debajo de las letras. Nota 
    que luego de la r, abajo, hay un número. ¿Qué es ese número?
  #. ¿Qué relación encuentras entre las letras y los números?

  Ejercicio 12: punteros
  ^^^^^^^^^^^^^^^^^^^^^^^

  Vas a explorar un concepto fundamental de los lenguajes de programación 
  C y C++. Se trata de los punteros. Para ello, te voy a proponer que 
  escribas el siguiente programa (es una tarea). Para probarlo usa ScriptCommunicator. 

  .. code-block:: cpp

    void task1()
    {
        enum class Task1States
        {
            INIT,
            WAIT_DATA
        };
        static Task1States task1State = Task1States::INIT;

        switch (task1State)
        {
        case Task1States::INIT:
        {
            Serial.begin(115200);
            task1State = Task1States::WAIT_DATA;
            break;
        }

        case Task1States::WAIT_DATA:
        {
            // evento 1:
            // Ha llegado al menos un dato por el puerto serial?
            if (Serial.available() > 0)
            {                  
                // DEBES leer ese dato, sino se acumula y el buffer de recepción
                // del serial se llenará.            
                Serial.read(); 
                uint32_t var = 0;
                // Almacena en pvar la dirección de var.
                uint32_t *pvar = &var;         
                // Envía por el serial el contenido de var usando 
                // el apuntador pvar.
                printf("var content: %d\n", *pvar); 
                // ESCRIBE el valor de var usando pvar
                *pvar = 10;                    
                printf("var content: %d\n", *pvar); 
            }
            break;
        }

        default:
        {
            break;
        }
        }
    }

  La variable ``pvar`` se conoce como puntero. Simplemente es una variable 
  en la cual se almacenan direcciones de otras variables. En este caso, 
  en pvar se almacena la dirección de ``var``. Nota que debes decirle al 
  compilador el tipo de la variable (uint32_t en este caso) 
  cuya dirección será almacenada en pvar. 

  Ejecuta el programa. Observa lo que hace. Ahora responde las siguientes 
  preguntas mediante un ejercicio de ingeniería inversa:

  * ¿Cómo se declara un puntero?
  * ¿Cómo se define un puntero? (cómo se inicializa)
  * ¿Cómo se obtiene la dirección de una variable?
  * ¿Cómo se puede leer el contenido de una variable por medio de un 
    puntero?
  * ¿Cómo se puede escribir el contenido de una variable por medio 
    de un puntero?

  .. warning:: IMPORTANTE

    No avances hasta que este ejercicio no lo tengas claro.

  Ejercicio 13: punteros y funciones 
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  Vas a escribir el siguiente programa, pero antes de ejecutarlo vas 
  a tratar de lanzar una HIPÓTESIS de qué hace. Luego lo vas a 
  ejecutar y compararás el resultado con lo que creías. Si el 
  resultado no es el esperado, no deberías seguir al siguiente 
  ejercicio hasta que no experimentes y salgas de la duda.

  .. code-block:: cpp

    static void changeVar(uint32_t *pdata)
    {
        *pdata = 10;
    }

    static void printVar(uint32_t value)
    {
        printf("var content: %d\n", value);
    }

    void task1()
    {
        enum class Task1States
        {
            INIT,
            WAIT_DATA
        };
        static Task1States task1State = Task1States::INIT;

        switch (task1State)
        {
        case Task1States::INIT:
        {
            Serial.begin(115200);
            task1State = Task1States::WAIT_DATA;
            break;
        }

        case Task1States::WAIT_DATA:
        {
            // evento 1:
            // Ha llegado al menos un dato por el puerto serial?
            if (Serial.available() > 0)
            {
                Serial.read();
                uint32_t var = 0;
                uint32_t *pvar = &var;
                printVar(*pvar);
                changeVar(pvar);
                printVar(var);
            }
            break;
        }

        default:
        {
            break;
        }
        }
    }

  Ejercicio 14: retrieval practice (evaluación formativa)
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  Realiza un programa que intercambie mediante una función 
  el valor de dos variables. 

  `Aquí <https://classroom.github.com/a/pWkF_5LT>`__ está el enlace 
  de la evaluación.


  Ejercicio 15: punteros y arreglos
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  Escribe el siguiente programa (como siempre te doy la tarea). ``ANALIZA`` qué 
  hace, cómo funciona y qué necesitas para probarlo. No olvides revisar de nuevo 
  una tabla ASCII. Para hacer las pruebas usa ScriptCommunicator y abre la pestaña 
  Utf8. 

  .. code-block:: cpp

    static void processData(uint8_t *pData, uint8_t size, uint8_t *res)
    {

        uint8_t sum = 0;
        for (int i = 0; i < size; i++)
        {
            sum = sum + (pData[i] - 0x30);
        }
        *res = sum;
    }

    void task1()
    {
        enum class Task1States
        {
            INIT,
            WAIT_DATA
        };
        static Task1States task1State = Task1States::INIT;
        static uint8_t rxData[5];
        static uint8_t dataCounter = 0;

        switch (task1State)
        {
        case Task1States::INIT:
        {
            Serial.begin(115200);
            task1State = Task1States::WAIT_DATA;
            break;
        }

        case Task1States::WAIT_DATA:
        {
            // evento 1:

            if (Serial.available() > 0)
            {
                rxData[dataCounter] = Serial.read();
                dataCounter++;
                if (dataCounter == 5)
                {
                    uint8_t result = 0;
                    processData(rxData, dataCounter, &result);
                    dataCounter = 0;
                    printf("result: %d\n",result);
                }
            }
            break;
        }

        default:
        {
            break;
        }
        }
    }


  Piensa en las siguientes cuestiones:

  * ¿Por qué es necesario declarar ``rxData`` static?
  * dataCounter se define static y se inicializa en 0. Cada 
    vez que se ingrese a la función loop dataCounter se inicializa 
    a 0? ¿Por qué es necesario declararlo static?
  * Observa que el nombre del arreglo corresponde a la dirección 
    del primer elemento del arreglo. Por tanto, usar en una expresión 
    el nombre rxData (sin el operador []) equivale a &rxData[0].
  * En la expresión ``sum = sum + (pData[i] - 0x30);`` observa que 
    puedes usar el puntero pData para indexar cada elemento del 
    arreglo mediante el operador [].
  * Finalmente, la constante ``0x30`` en ``(pData[i] - 0x30)`` ¿Por qué 
    es necesaria? 
    
  .. tip:: ALERTA DE SPOILER

    Con respecto a la pregunta anterior. Al enviar un carácter numérico desde 
    ScriptCommunicator este se envía codificado, es decir, se envía 
    un byte codificado en ASCII que representa al número. Por tanto, 
    es necesario decodificar dicho valor. El código ASCII que 
    representa los valores del 0 al 9 es respectivamente: 0x30, 0x31, 
    0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39. De esta manera, 
    si envías el ``1`` recibirás el valor 0x31. Si restas de 0x31 el 
    0x30 obtendrás el número 1.

    Repite el ejercicio anterior pero esta vez usa la pestaña Mixed.

  Ejercicio 16: análisis del api serial (investigación: hipótesis-pruebas)
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  Qué crees que ocurre cuando:

  * ¿Qué pasa cuando hago un `Serial.available() <https://www.arduino.cc/reference/en/language/functions/communication/serial/available/>`__?
  * ¿Qué pasa cuando hago un `Serial.read() <https://www.arduino.cc/reference/en/language/functions/communication/serial/read/>`__?
  * ¿Qué pasa cuando hago un Serial.read() y no hay nada en el buffer de
    recepción?
  * Un patrón común al trabajar con el puerto serial es este:

  .. code-block:: cpp

      if(Serial.available() > 0){
          int dataRx = Serial.read() 
      }

  * ¿Cuántos datos lee Serial.read()?
  * ¿Y si quiero leer más de un dato? No olvides que no se pueden leer más datos
    de los disponibles en el buffer de recepción porque no hay
    más datos que los que tenga allí.
  * ¿Qué pasa si te envían datos por serial y se te olvida llamar Serial.read()?

  .. warning:: NO AVANCES SIN ACLARAR LAS PREGUNTAS ANTERIORES

    Te pido que resuelvas las preguntas anteriores antes de avanzar. 
    ES MUY IMPORTANTE.  

  Ejercicio 17: buffer de recepción
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  Así se pueden leer 3 datos que han llegado al puerto serial:

  .. code-block:: cpp

      if(Serial.available() >= 3){
          int dataRx1 = Serial.read()
          int dataRx2 = Serial.read() 
          int dataRx3 = Serial.read() 
      }

  ¿Qué escenarios podría tener en este caso?

  .. code-block:: cpp

      if(Serial.available() >= 2){
          int dataRx1 = Serial.read()
          int dataRx2 = Serial.read() 
          int dataRx3 = Serial.read() 
      }

  Para responder, es necesario que experimentes. ESTOS son los ejercicios 
  que realmente te ayudarán a aprender.

  Ejercicio 18: miniRETO
  ^^^^^^^^^^^^^^^^^^^^^^^

  Piense cómo podrías hacer lo siguiente:

  * Crea una aplicación con una tarea.
  * La tarea debe tener su propio buffer de recepción y una capacidad 
    para 32 bytes.
  * La tarea almacena los datos del serial en su propio buffer de recepción
    (el buffer será un arreglo).
  * El buffer debe estar encapsulado en la tarea.
  * Los datos almacenados en el buffer no se pueden perder
    entre llamados a la tarea.
  * La tarea debe tener algún mecanismo para ir contando 
    la cantidad de datos que han llegado. ¿Cómo lo harías?

  Inventa un programa que ilustre todo lo anterior.
