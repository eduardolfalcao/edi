# Tabelas de Dispersão

Tabelas de dispersão têm como base a ideia de que a leitura e o acesso a qualquer posição de um array são extremamente rápidos. 
A razão para isso é bem conhecida. 
Ao ler ou escrever em um vetor em uma posição como 10¹², o sistema operacional determinará o endereço de memória por meio de um cálculo simples, que se baseia na premissa de que todas as posições de um vetor têm o mesmo tamanho em bytes: endereço de memória = endereço base + (10¹² * sizeof(type)). 
Por exemplo, dependendo do tipo de dado do vetor, sizeof(type) pode retornar 4 bytes se o tipo for um inteiro, ou 8 bytes se for um long.

Observe que, até este ponto, não estudamos um Tipo Abstrato de Dados (TAD) ou Estrutura de Dados (ED) que ofereça um desempenho de tempo O(1) para todas as suas operações. 
Até agora, as árvores balanceadas (AVL) demonstraram o melhor desempenho, com complexidade O(log n) para operações de leitura, escrita e remoção. 
Tabelas de dispersão, por outro lado, oferecem um desempenho O(1) (ou muito próximo disso) para operações de leitura, escrita e remoção. 
Portanto, é fundamental familiarizarmo-nos com essa estrutura e compreender o seu funcionamento.

## Estrutura e Funcionamento Básico

Tabelas de dispersão utilizam **chaves** para realizar o mapeamento de entidades para a tabela.
Imagine que no censo do IBGE mapeamos todas as pessoas e precisamos armazená-las em um BD e eventualmente realizar algum processamento.
Para isso, considere o seguinte struct resumido:
```go
type Pessoa struct {
	cpf   int
	nome string
}
```

No Brasil, um CPF possui 11 dígitos.
Se escolhermos o cpf como chave para mapear todos os brasileiros para um vetor, o problema é que precisaremos de um vetor muito grande para poder armazenar todos os alunos.
Precisaríamos de um vetor no seguinte formato [00000000000,99999999999].
Note que para armazenar 11 dígitos, um int (4 bytes) não seria suficiente; precisaríamos usar o tipo long (8 bytes).
Portanto, o nosso vetor consumiria aproximadamente 727GB.
Além de consumir uma quantidade de memória RAM elevada, há uma alta probabilidade de haver espaços ociosos.

No entanto, o mapeamento seria trivial.
Como há um espaço no array para cada possibilidade, se eu quiser informações de uma pessoa com CPF = 23897429874, sei que suas informações estarão em v[23897429874].
Portanto, leitura, escrita e remoção aconteceriam em O(1).

Por outro lado, como não é razoável alocar 727GB em um computador, somos forçados a diminuir o tamanho do vetor.
O Brasil hoje possui cerca de 214,3 milhões de pessoas.
Então, poderíamos tentar alocar um vetor com 215 milhões de posições, por exemplo, resultando em 1,6GB de RAM alocado, algo ainda extremamente alto, mas factível.

## Função de Mapeamento (Função de Hashing)

Uma função de mapeamento ajuda a descobrir a posição correta para um dado elemento conhecida a sua chave.
Quando o vetor tem tamanho suficiente para armazenar todas as chaves, como no primeiro caso do exemplo anterior, a função de hashing é super simples: o índice do elemento no vetor será o próprio valor da chave, i.e., **hash(chave) = chave**.
Uma pessoa com CPF = 23897429874 terá suas informações armazenadas em v[23897429874], pois **hash(23897429874) = 23897429874**.
Mas quando o tamanho do vetor não permite fazer o mapeamento usando a própria chave, pois causaria extrapolação dos limites do vetor, então é preciso criar uma função de mapeamento que lide com esse problema.
A forma mais simples de evitar que chaves sejam mapeadas para índices fora dos limites é aplicar uma operação de módulo que considera o tamanho do vetor: **hash(chave) = chave % n**, onde n é o tamanho do vetor.
No entanto, essa situação cria a possibilidade de colisões.

## Colisões

Uma colisão acontece quando duas chaves de valores diferentes são mapeadas para a mesma posição no vetor: **hash(chave1) = hash(chave2)**.

### Solução de Colisões


Tabelas de dispersão possuem uma propriedade chamada fator de carga (não confundir com fator de balanço em AVLs).
O fator de carga é computado pela divisão entre a quantidade de elementos inseridos pelo tamanho do vetor.
Note que quanto maior o fator de carga, maior a probabilidade de colisão.
Aumentam o fator de carga: diminuir o tamanho do vetor, e inserir elementos no vetor.
O problema de diminuir o tamanho do vetor é que aumentamos a possibilidade de colisão.
