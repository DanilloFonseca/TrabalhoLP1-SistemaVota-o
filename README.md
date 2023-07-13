# Projeto de LP. Sistemas de votação.

## Autores:

Nome: Eduarda Rodrigues Chiesa
Email: eduardachiesa@gmail.com

Nome: Danillo Melo da Fonseca
Email: danillo.fonseca.129@ufrn.edu.br

## Sobre o projeto

A ideia é que seja possível simular diferentes diferentes sistemas de votação (majoritário, misto, proporcional e semi proporcional), em diferentes cenários controlados pelo usuário. No momento, apenas com algumas assinaturas e classes muito básicas para representar a ideia geral, outras coisas serão acrescentadas conforme a necessidade prática. Ainda pretendemos adicionar muito mais conforme a implementação do projeto.

## TADS utilizadas

No momento, pretendemos implementar uma lista duplamente encadeada e uma fila.
A fila poderá ser utilizada para armazenar o montante de votos a serem contabilizados por cada sistema de votação.
A lista poderá ser utilizada na manipulação dos dados dentro das classes que serão utilizadas pelos sistemas de votação.

## Pastas:

bin: contém o executável do programa
build: contém os arquivos .o
docs: contém a documentação gerada (no caso, que vai ser gerada quando tiver algo de fato) e relatórios anteriores a esses projeto sobre algoritmos de busca e ordenação. O relatório sobre algoritmos de busca é um trabalho antigo e bem menos completo que o de ordenação, mas serve como prova de que o assunto já foi pesquisado antes.
Além disso tem o Diagrama UML.
source: contém a pasta include e o main.
source/include: contém todos os arquivos .h com as classes, os algortimos de busca (binária iterativa e binária recursiva) e os algortimos de ordenação (insertion, selection, bubble, radix, shell, quick e merge)
makefile: é o makefile :/ (que controla a compilação e execução do programa)

## Diretivas de compilação:

Para compilar o aquivo main, é preciso somente digitar "make" no terminal e em seguida "make run" para executar.





