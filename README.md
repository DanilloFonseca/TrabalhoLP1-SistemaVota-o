# Projeto de LP. Sistemas de votação.

## Autores:

Nome: Eduarda Rodrigues Chiesa
Email: eduardachiesa@gmail.com

Nome: Danillo Melo da Fonseca
Email: danillo.fonseca.129@ufrn.edu.br

## Sobre o projeto

Esse projeto simula os resultados de um sistema de votação majoritário. São apresentadas 3 formas diferentes de simular a votação em si:

1 - Distribuição discreta uniforma automática
2 - Distribuição discreta não uniforme automática
3 - Distribuição manual

- Na 1, todos os candidatos tem uma chance igual de receber votos, porém isso não significa que todos vão receber a mesma quantidade.

- Na 2, a chance de cada candidato de receber votos é calculada automáticamente e aleatóriamente, ou seja, as quantidades de votos para cada candidato podem variar bastante.

- Na 3, o usuário decide manualmente e individualmente a chance de cada candidato de receber votos, ou seja, as quantidades vão variar de acordo com os valores passados pelo usuário.

Como a simulação é feita com base em um sistema de votação majoritário, o primeiro turno pode ter um ganhador final (caso um candidato some 50% dos votos + 1) ou 2 ganhadores, aqueles que tiverem mais votos. Caso tenham 2 ganhadores, haverá um segundo turno, que no caso da distribuição 2 e 3, atualizará a chance que cada um deles terá de ganhar.

## TADS utilizadas

Foi implementada uma lista duplamente encadeada e um vector, porém a única que foi realmente utilizada foi o vector.

## Pastas:

bin: contém o executável do programa

build: contém os arquivos .o

docs: contém a documentação gerada e relatórios anteriores a esses projeto sobre algoritmos de busca e ordenação. O relatório sobre algoritmos de busca é um trabalho antigo e bem menos completo que o de ordenação, mas serve como prova de que o assunto já foi pesquisado antes. Além disso tem o Diagrama UML.

source: contém a pasta include e o main.

source/include: contém todos os arquivos .h com as classes, os algortimos de busca (binária iterativa e binária recursiva) e os algortimos de ordenação (insertion, selection, bubble, radix, shell, quick e merge)

makefile: é o makefile :/ (que controla a compilação e execução do programa)

## Diretivas de compilação:

Para compilar o aquivo main, é preciso somente digitar "make" no terminal e em seguida "make run" para executar.
