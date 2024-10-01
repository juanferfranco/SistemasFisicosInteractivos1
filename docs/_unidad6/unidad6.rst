Experiencia de aprendizaje 6. El puente entre dispositivos (Node.js)
=========================================================================

Introducción
--------------

En hora buena. Has llegado a la sexta experiencia de aprendizaje. En este punto 
ya has aprendido las técnicas básicas para integrar dispositivos externos a una 
aplicación interactiva usando protocolos de comunicación ASCII y binarios. Ahora 
es momento de poner a prueba lo aprendido y trasladarlo a un nuevo contexto. En 
esta experiencia vas a comunicar dos aplicaciones en tiempo real usando Node.js. 
Node.js será el puente entre esas dos aplicaciones, o como lo hemos llamado 
el puente entre dispositivos. En esta experiencia las aplicaciones estarán en 
el mismo computador, pero en la siguiente experiencia estarán en computadores 
diferentes.

Investigación
-----------------------

Para esta experiencia de aprendizaje te voy a proponer el análisis de un caso 
de estudio. Este caso de estudio te permitirá entender cómo se pueden comunicar 
dos aplicaciones en tiempo real usando Node.js. La idea del reto es que modifiques 
el caso de estudio y le des un giro creativo al concepto.

Este caso de estudio está inspirado en el trabajo de Sahand Babali publicado 
en youtube y github. Puedes encontrar el video `aquí <https://youtu.be/cBgxArOP4jg?si=AWuSDYzpGFIoQjud>`__.

El caso de estudio se divide en tres partes o aplicaciones: una aplicación para el servidor 
escrita en Node.js y dos aplicaciones cliente que usarán p5.js.

El código fuente completo lo puedes descargar de `aquí <https://github.com/juanferfranco/juanferfranco-entagledTest-sfi1-2024-20>`__.


* El código del server se llama server.js.
* En la carpeta views encontrarás un archivo html y otro javascript para cada cliente.

Para ejecutar las aplicaciones sigue estos pasos:

* Descarga el código fuente.
* Abre una terminal y ubícate en la carpeta donde descargaste el código.
* Ejecuta el comando `npm install` para instalar las dependencias.
* Ejecuta el comando `npm start` para ejecutar el servidor.
* Abre un navegador y escribe la dirección `http://localhost:3000/page1`.
* Abre otra ventana del mismo navegador y escribe la dirección `http://localhost:3000/page2`.

Una vez tengas funcionando la aplicación es momento que analices el código. Puede usar 
chatGPT para generar una explicación detallada de cada línea de código. Profundiza en los 
conceptos que desees.

Para asegurar que entiendes el funcionamiento de las aplicaciones realiza experimentos 
haciendo pequeñas modificaciones al código. 

Bitácora 
***********

Documenta de manera libre todo tu proceso de investigación en tu bitácora de aprendizaje. 
No olvides incluir el código fuente de tus experimentos y las conclusiones 
a las que llegues con estos.

Reto 
------

Ahora que ya entiendes cómo se pueden comunicar dos aplicaciones en tiempo real 
usando Node.js, te propongo que hagas una aplicación interactiva en tiempo real 
que modifique el caso de estudio propuesto. Mira por ejemplo cómo el 
artista generativo Bjørn Staal usa el concepto en su exposición 
`Entangled <https://www.fxhash.xyz/vertex/entangled>`__. Observa en este 
`video <https://x.com/_nonfigurativ_/status/1727322594570027343>`__ el concepto en 
acción.

Ahora es tu turno ¿Qué harás usando el concepto del caso estudiado?

Bitácora 
************

* Explicación del concepto diseñado.
* Códigos de las aplicaciones.
* Explica cómo funciona la aplicación.
* Enlace a un video de tu aplicación publicado en alguna red social.


