# Notas sobre Alocação de Memória

Na linguagem C, podemos alocar memória dinamicamente com as seguintes funções: malloc, calloc, realloc, e free. 

```c
#include<stdio.h>
#include<stdlib.h>

int main(){
    int a;  
    int *p;
    p = (int *) malloc(sizeof(int)); 
    *p = 10;
    free(p);
    p = (int *) malloc(sizeof(20*int)); 
}
```

- Primitivos são alocados na pilha (stack)
- Ponteiros são alocados na Heap (pilha recebe ponteiro para endereço alocado na heap)
- Precisamos do casting pois malloc retorna void \*, e o que solicitamos foi int \*
- O ponteiro armazena endereço de memória... logo, se quisermos alterar o valor do endereço apontado por p, precisaremos usar \*p
- A função free desaloca o endereço previamente alocado, tornando-o alocável para outras aplicações
- O segundo malloc aloca um array com 20 posições para inteiros (20*4bytes)
- É possível usar a forma convencional de acessar arrays: p[0], p[1], p[2], etc.
    - p[0] é o mesmo que *p
    - p[1] é o mesmo que *(p+1)
    - p[2] é o mesmo que *(p+2)
- Se malloc não conseguir alocar espaço em memória ele retornará NULL
- *p retorna o conteúdo apontado por um ponteiro
- &a retorna o endereço onde o valor de a está armazenado
    - p = &a  é o mesmo que fazer p sempre conter o valor que estiver em a 
    - p é diferente de &p
        - p armazena um endereço para um espaço que contém o valor
        - &p denota o espaço de memória usado para armazenar um ponteiro


### Refs interessantes
- https://stackoverflow.com/questions/1296843/what-is-the-difference-between-null-0-and-0#:~:text=NULL%20is%20a%20macro%2C%20defined,used%20to%20terminate%20a%20string.&text=pointer%20context%20%2D%20NULL%20is%20used,other%208%20bytes%20of%20zeroes).
- MyCodeSchool:
    - https://www.youtube.com/watch?v=h-HBipu_1P0
    - https://www.youtube.com/watch?v=_8-ht2AKyH4