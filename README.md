# Introdução: #

Este projeto tem a intenção de implementar uma lista duplamente encadeada personalizada similar a std::list
Para execução, batar dar o comando make pelo terminal no arquivo
Alguns comentário foram colocados para fins de feedback didático e explicação do código

# Classes Utilizadas/Implementadas: #

- Classe list que guarda os métodos e o início e fim da lista;
- Classe node que guarda os dados em si;
- Classe iterator que percorre a lista;
- Classe const_iterator que é basicamente um iterator com os métodos const.

# Métodos das classes customizadas: #

## Classe list: ##

- Construtores copy, range, default, lista inicializadora;
- operator=;
- size;
- clear;
- empty;
- push_front;
- push_back;
- pop_front;
- pop_back;
- back;
- front;
- assign;
- operator ==;
- operatos !=.

## Classe Node: ##

- Construtor default e com construído de acordo com o size.

## Classe iterator: ##

- Construtor com Node e default;
- print;
- operator++;
- operator--;
- operator =;
- operador de valor;
- operator ==;
- operator !=;
- Funções assign;
- Funções erase;
- Funções insert.
- Sobrecarga no operator <<;

## Classe const_iterator ##

- Construtor com Node e default;
- print;
- operator++;
- operator--;
- operator =;
- operador de valor;
- operator ==;
- operator !=;
- Funções assign;
- Funções erase;
- Funções insert.
 
# Autoria: #

Todos os códigos foram implementados por  [Giovanne da Silva Santos](https://github.com/GSDante) (Email de contato: <giovannedssantos@gmail.com>)

&copy; IMD/UFRN 2018-2019
