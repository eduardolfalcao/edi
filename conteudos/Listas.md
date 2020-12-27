# Listas

 Usamos listas com muita frequência no cotidiando, e por esta razão, é intrínseco a todos nós o conceito de listas. É muito comum fazermos uma lista de feira, lista de convidados, lista de presentes, lista de alunos, lista de ingredientes, etc.

 Lista de feira             |  Lista de convidados
:-------------------------:|:-------------------------:
![](imgs/listas/lista-de-feira.jpg)  |  ![](imgs/listas/lista-de-convidados.png)
 
 **Definição:**
 > Listas são coleções de elementos/objetos de um mesmo tipo.
 
 Para o nosso estudo, vamos iniciar com uma visão abstrata e superficial da ED lista. Vamos estudar listas sob a perspectiva de Tipos Abstratos de Dados (TADs), logo, neste primeiro momento não nos preocuparemos com implementação, mas queremos apenas ter um entendimento superficial de suas operações básicas.

 ## TAD: Listas

- Inserir um elemento no fim da lista.
- Ler um elemento em uma posição específica da lista.
- Inserir um elemento em uma posição específica na lista.
- Modificar um elemento em uma posição específica na lista.
- Contar os elementos de uma lista.
- Remover um elemento no fim da lista.
- Remover um elemento em uma posição específica na lista.

Um array é suficiente para implementar uma lista com estes requisitos! Uma outra estratégia é usar o que chamamos de listas ligadas, que são compostas por nós que contém o valor do elemento e ponteiros para outros nós. Cada abordagem possui seus pontos positivos e negativos, e são mais apropriadas em situações diferentes.

A seguir, veremos mais detalhes sobre a visão lógica de como cada operação funciona nas diferentes EDs, e discutiremos as diferentes formas de implementar Listas. Ao fim deste estudo, seremos capaz de analisar/comparar o desempenho das principais operações.