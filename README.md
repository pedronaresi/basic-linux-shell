**UC Sistemas Operacionais
ICT/UNIFESP**


**Prof. Bruno Kimura
bruno.kimura@unifesp.br
15/03/18**

**LAB_1: Implementação de um Shell**

**Metodologia:**
Trabalho individual ou em grupo de no máximo 3 (três) alunos a ser desenvolvido em laboratório de
informática através de codificação na linguagem C.

**Data de entrega:
29/03/2018**

**Forma de entrega:**
Código .c deve ser enviado no SEAD. Insira como comentário no código o nome e matrícula de
cada integrante do grupo.

**Observação:**
Somente serão aceitos trabalhos **autênticos**. Cópias (entre grupos e/ou de fontes da Internet) serão
anuladas.

**Descrição:**
Implemente um interpretador de comandos para Linux na linguagem C. Utilize o material das aulas
e a bibliografia recomendada.

**Requisitos:**
O interpretador de comandos deverá:

1. Executar comandos simples, de comando único.
    Exemplo: ```# ls -la```
2. Executar comandos compostos, utilizando o pipe ```|``` para combinar saída e entrada padrão em
cadeias de comandos.
    Exemplo: ```# ls -la | grep “teste”
       # ls -la | grep “teste” | more```
3. Redirecionar entrada e saída padrão de comandos para arquivos, utilizando ```<``` para entrada
padrão e ```>``` para saída padrão. No caso caso do operador ```>```, se o arquivo apontado para a saída já
existir, o operador trunca a saída do comando sobre o conteúdo do arquivo, ou seja, sobrescreve o
arquivo existente com o novo conteúdo.
    Exemplos: ```# sort < teste.txt > novo_teste.txt```
4. Redirecionar a saída padrão de comandos para arquivos, utilizando ```>>```. Diferente do operador
```>```, caso o arquivo de saída exista, o operador ```>>``` acrescenta a saída do comando ao fim do
conteúdo do arquivo existente.
    Exemplos: ```# sort < teste.txt >> novo_teste.txt```
5. Combinar operadores.
    Exemplos: ```# sort < teste.txt | grep “x” > novo_teste.txt```
    Exemplos: ```# sort < teste.txt | grep “x” >> novo_teste.txt```


