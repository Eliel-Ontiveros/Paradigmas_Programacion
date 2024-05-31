# Universidad Autonoma de Baja California

### Eliel Alfonso Ontiveros Ojeda
### 368746 

# Introducción
Prolog es un lenguaje de programación lógico, utilizado principalmente en el ámbito de la inteligencia artificial y la computación simbólica. Su nombre proviene de "Programming in Logic" y se caracteriza por un enfoque declarativo, donde se especifica qué se quiere lograr en lugar de cómo lograrlo. En este reporte, se explorará el funcionamiento de Prolog, ilustrando su sintaxis y lógica mediante ejemplos prácticos, y se presentará una conclusión sobre sus aplicaciones y beneficios en la programación.

# Desarrollo
## Fundamentos de Prolog

Prolog se basa en la lógica de predicados de primer orden, donde el conocimiento se representa mediante hechos, reglas y consultas.

**Hechos**: Declaran relaciones entre objetos o propiedades de objetos.

    madre(maria, ana).
    padre(jose, ana).

**Reglas**: Definen relaciones lógicas basadas en hechos.

    progenitor(X, Y) :- madre(X, Y).
    progenitor(X, Y) :- padre(X, Y).

**Consultas**: Permiten interrogar la base de conocimientos.

    ?- progenitor(maria, ana).

## Ejemplo 1: Árbol Genealógico
Definamos una base de conocimientos simple para un árbol genealógico.

    % Hechos
    madre(maria, ana).
    madre(ana, juan).
    padre(jose, ana).
    padre(carlos, juan).

    % Reglas
    abuelo(X, Y) :- padre(X, Z), progenitor(Z, Y).
    abuela(X, Y) :- madre(X, Z), progenitor(Z, Y).
    progenitor(X, Y) :- madre(X, Y).
    progenitor(X, Y) :- padre(X, Y).

    % Consultas
    ?- abuelo(jose, juan).
    % Respuesta: No
    ?- abuelo(carlos, juan).
    % Respuesta: Sí

En este ejemplo, se definen hechos para madres y padres, y se introducen reglas para determinar si alguien es abuelo o abuela de otra persona. Luego se pueden realizar consultas para obtener información.

## Ejemplo 2: Relaciones Familiares
Para ilustrar la flexibilidad de Prolog, consideremos las siguientes reglas para definir hermanos y tíos.

    % Hechos adicionales
    madre(sofia, pedro).
    padre(juan, pedro).

    % Reglas adicionales
    hermano(X, Y) :- progenitor(Z, X), progenitor(Z, Y), X \= Y.
    tio(X, Y) :- hermano(X, Z), progenitor(Z, Y).

    % Consultas
    ?- hermano(juan, ana).
    % Respuesta: No
    ?- hermano(ana, juan).
    % Respuesta: No
    ?- tio(ana, pedro).
    % Respuesta: No
    ?- tio(juan, pedro).
    % Respuesta: Sí

Aquí, se extienden las reglas para identificar relaciones más complejas como hermanos y tíos, demostrando la capacidad de Prolog para manejar estructuras de datos relacionadas.

## Ejemplo 3: Listas y Recursión
Prolog maneja listas y permite realizar operaciones recursivas sobre ellas. A continuación, un ejemplo de cómo calcular la longitud de una lista.

    % Regla para calcular la longitud de una lista
    longitud([], 0).
    longitud([_|Cola], L) :- longitud(Cola, N), L is N + 1.

    % Consultas
    ?- longitud([a, b, c, d], L).
    % Respuesta: L = 4.
    ?- longitud([], L).
    % Respuesta: L = 0.

En este ejemplo, se utiliza la recursión para calcular la longitud de una lista. La regla base establece que la longitud de una lista vacía es 0, y la regla recursiva suma 1 por cada elemento en la lista.

## Ejemplo 4: Búsqueda en un Grafo
Prolog también puede usarse para buscar caminos en un grafo. A continuación, un ejemplo de cómo encontrar un camino entre dos nodos en un grafo.

    % Hechos que representan las aristas del grafo
    arista(a, b).
    arista(b, c).
    arista(c, d).
    arista(d, e).
    arista(a, e).

    % Regla para encontrar un camino entre dos nodos
    camino(X, Y, [X,Y]) :- arista(X, Y).
    camino(X, Y, [X|Camino]) :- arista(X, Z), camino(Z, Y, Camino).

    % Consultas
    ?- camino(a, d, Camino).
    % Respuesta: Camino = [a, b, c, d] ; Camino = [a, e, d].
    ?- camino(b, e, Camino).
    % Respuesta: Camino = [b, c, d, e].

En este ejemplo, se define un conjunto de aristas que representan un grafo y se utiliza la recursión para encontrar un camino entre dos nodos.    

# Conclusión

Prolog es una herramienta poderosa en el campo de la programación lógica, ofreciendo un enfoque declarativo que difiere significativamente de los lenguajes imperativos tradicionales. Su capacidad para manejar problemas de lógica complejos y trabajar con bases de conocimientos lo hace especialmente útil en la inteligencia artificial y la investigación académica. Aunque puede tener una curva de aprendizaje pronunciada, su habilidad para modelar y resolver problemas lógicos de manera eficiente lo convierte en una opción valiosa para los programadores que buscan explorar nuevos paradigmas de programación.