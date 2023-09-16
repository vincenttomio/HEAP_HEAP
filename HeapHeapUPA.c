/* --------------------------------------------------------------------------------------
    Programa: Trabalho Pratico 2 (2022): Heap, Heap, UPA!
    Link: https://www.inf.ufpr.br/vvsbt20

    Autores: Vincent Tomio
    Disciplina: Algoritmos II
    Data da ultima atualizacao: 2022/8
----------------------------------------------------------------------------------------*/

// Bibliotecas utilizadas
#include <stdio.h>
#include <time.h>

// Constantes
#define TamMaxFila 99
#define TamMaxNome 25

// Variavel Global para acumlar inspecoes que o algoritmo realiza
long inspecoes = 0; 


typedef struct Pacientes       // Estrutura Paciente solicitada no exercicio
{
    char nome[TamMaxNome + 1]; // nome[TamMaxNome] +1 para \0, manipulacao string basica
    int prioridade;            // Prioridade, elemento principal do exercicio
} Paciente;

typedef struct TipoFilaHeap           // Tipo Abstrato de Dados HEAP, vetor de pacientes
{
    Paciente paciente[TamMaxFila +1]; // Vetor Paciente, com tipo Paciente, de TamMax+1 posicoes
    int tamanho;                      // Tamanho usado, que sera manipulado e atualizado durante o ex.
} FilaHeap;

// Inicializa tamanho da fila
void InicHeap(FilaHeap *fila);

// Funcao de chacagem da fila, se Vazia
int Vazia(FilaHeap *fila);

// Funcao de chacagem da fila, se Cheia
int Cheia(FilaHeap *fila);

// Funcao de troca de elementos na fila de prioridades
void TrocaPosFila(int *xp, int *yp, char *xn, char *yn);

/* Funcao que corrige a fila de prioridades heap,
** recebe o a fila de prioridades heap, e o indice
** tal que as subarvores [2i] e [2i+1] sao heaps,
** devolvendo [i] heap ao final
*/
void CorrigeHeapDescendo(FilaHeap *fila, int i);

/* Funcao que corrige a fila de prioridades heap,
** recebe o a fila de prioridades heap, e o indice
** tal que [1..i-1] eh heap, devolvendo [1..i] heap
** ao final
*/
void CorrigeHeapSubindo(FilaHeap *fila, int i);

/* Funcao que insere um novo elemento na ultima
** posicao disponível e corrige, se necessário,
** fazendo troca com o pai (CorrigeHeapSubindo)
*/
void InsereHeap(FilaHeap *fila, char *n, int *p);

/* Funcao que remove o primeiro elemento da fila,
** troca-se o primeiro elemento com o ultimo,
** diminui o tamanho da fila, e corrige descendo
** de tal maneira que ao final se tem uma heap[1..Tam-1]
*/
void RemoveHeap(FilaHeap *fila);

/* Funcao que Recebe entrada de um Paciente, ou seja
** nome e prioridade, e o insere na ultima posicao,
** usando (insereheap) de tal forma, que ao final se
** tem o Paciente em seu lugar devido na heap
*/
void CadastraPaciente(FilaHeap *fila);

// Funcao que imprime a Fila, ja de maneira prioritaria (HEAP)
void ImprimeFila(FilaHeap fila);

/* Funcao que altera a prioridade de um elemento na
** fila, verifica se a conflito com o pai ou o filho,
** e dependendo da sua relacao de prioridade, corrige
** usando (corrigeHeapSubindo) ou (corrigeHeapDescendo)
*/
void AlteraHeap(FilaHeap *fila, int i, int *valor);

// Funcao que atualiza a Prioridade de um Paciente, usando (AteraHeap)
void AtualizarCadastro(FilaHeap *fila);

/*** Funcoes para uso durante SIMULACAO/TESTE ***/
// Funcao que monta uma fila com elementos nao ordenados
void ConstroiFilaDesordenada(FilaHeap *fila);

/* Corrige cada subarvore, da menor altura para a maior
** a partir do primeiro indice que nao eh folha
*/
void ConstroiHeap(FilaHeap *fila);

// Funcao que atualiza a Prioridade de alguns pacientes aleatoriamente
void AtualizaPrioridadesAleat(FilaHeap *fila);

// Funcao que pega uma fila heap e ordena de forma nao decrescente
void HeapSort(FilaHeap *fila);

// Funcao que chama todos os pacientes, da maior prioridade para menor
void ChamandoTodosPacientes(FilaHeap *fila);

// Checa se uma filha de prioridades obedece a definicao de prioridade
void ChecaHeap(FilaHeap *fila);

// Funcao que aleatoriza um numero entre min e max passados
int aleat(int min, int max);

void main()
{
    // Var para 'escolha' usuario para menu
    int choice = -1;
    // TAD FilaHeap
    FilaHeap fila;

    // Abertura do programa
    puts("\t=============================================================================");
    puts("\t\tTrabalho: Trabalho Pratico 2 (2022): Heap, Heap, UPA! ");
    puts("\t\tAutores:  Vincent Tomio");
    puts("\t\tLink:     https://www.inf.ufpr.br/vvsbt20 ");
    puts("\t=============================================================================");
    puts("\n");

    // Inicia Heap
    InicHeap(&fila);

    while (1)
    {
        // Menu do jogo
        puts(".....................");
        puts("\tMENU\n");
        puts("(1) Cadastrar Paciente");
        puts("(2) Atualizar Cadastro");
        puts("(3) Imprimir Fila");
        puts("(4) Chamar Paciente");
        puts("(5) SIMULACAO/TESTE");
        puts("(0) Sair\n");
        puts(".....................");
        // Recebe entrada do usuario
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 0: // Saida do programa
        {
            puts("\n\tTchau, ateh a proxima! \n \t\t ;) \n");
            exit(0);
        }
        case 1: // Cadastra Paceite caso a fila nao esteja Cheia
        {
            if (Cheia(&fila))
                puts("FILA CHEIA! Cadastre apenas quando alguem for chamado!");
            else
                CadastraPaciente(&fila);
            break;
        }
        case 2: // Atualiza Prioridade de Paciente, caso haja paciente na fila
        {
            if (Vazia(&fila))
                puts("Fila Vazia!");
            else
            {
                ImprimeFila(fila);
                AtualizarCadastro(&fila);
            }
            break;
        }
        case 3: // Imprime fila
        {
            if (Vazia(&fila))
                puts("Fila Vazia!");
            else
                ImprimeFila(fila);
            break;
        }
        case 4: // Chama paciente, ou seja remove primeiro elemento (O de maior prioridade)
        {
            if (Vazia(&fila))
                puts("Fila Vazia!");
            else
            {
                puts("\tChamando:");
                printf("Paciente: %s \nPrioridade: %02d\n\n", fila.paciente[1].nome, fila.paciente[1].prioridade);
                RemoveHeap(&fila);
                ImprimeFila(fila);
            }
            break;
        }
        case 5: // Simula entrada de dados, afim de testar programa
        {
            // Semente para uso da funcao aleat
            srand(time(NULL));
            // Limpando Tela
            system("clear");
            // Imprimindo msg de simulacao
            puts("\t=================================================");
            puts("\t\t\tMODO SIMULACAO");
            puts("\t=================================================");
            puts("\n");

            InicHeap(&fila);

            ConstroiFilaDesordenada(&fila);
            ImprimeFila(fila);
            ChecaHeap(&fila);

            ConstroiHeap(&fila);
            printf("\n|%d|INSPECOES para Funcao ConstroiHeap \n\n",inspecoes);
            inspecoes = 0;
            ImprimeFila(fila);
            ChecaHeap(&fila);

            AtualizaPrioridadesAleat(&fila);
            printf("\n|%d|INSPECOES para Atualizar os elementos\n\n",inspecoes);
            inspecoes = 0;
            ChecaHeap(&fila);
            ImprimeFila(fila);

            HeapSort(&fila);
            printf("\n|%d|INSPECOES para Funcao HEAPSORT\n\n",inspecoes);
            inspecoes = 0;
            ImprimeFila(fila);
            ChecaHeap(&fila);

            ConstroiHeap(&fila);
            ImprimeFila(fila);
            ChecaHeap(&fila);

            ChamandoTodosPacientes(&fila);
            if (Vazia(&fila))
                puts("\nFila Vazia!");
            else
                ImprimeFila(fila);

            puts("\n\tFim da Simulacao!");
            break;
        }
        default: // Msg Padrao
            puts("Entrada Incorreta\n");
        }
    }
}

void InicHeap(FilaHeap *fila)
{
    fila->tamanho = 0;
    printf("Iniciei a Fila de Pacientes, que pode ter no maximo %d elementos.\n", TamMaxFila);
}

int Vazia(FilaHeap *fila)
{
    return (fila->tamanho == 0);
}

int Cheia(FilaHeap *fila)
{
    return (fila->tamanho == TamMaxFila);
}

void TrocaPosFila(int *xp, int *yp, char *xn, char *yn)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;

    char aux_nome[TamMaxNome];
    strcpy(aux_nome, xn);
    strcpy(xn, yn);
    strcpy(yn, aux_nome);
}

void CorrigeHeapDescendo(FilaHeap *fila, int i)
{
    int maior = i;

    inspecoes++;
    if ((2 * i <= fila->tamanho) && (fila->paciente[2 * i].prioridade > fila->paciente[maior].prioridade))
        maior = 2 * i;

    inspecoes++;
    if ((2 * i + 1 <= fila->tamanho) && (fila->paciente[2 * i + 1].prioridade > fila->paciente[maior].prioridade))
        maior = 2 * i + 1;

    if (maior != i)
    {
        TrocaPosFila(&fila->paciente[i].prioridade, &fila->paciente[maior].prioridade,
                     &fila->paciente[i].nome, &fila->paciente[maior].nome);
        CorrigeHeapDescendo(fila, maior);
    }
}

void CorrigeHeapSubindo(FilaHeap *fila, int i)
{
    int pai = i / 2;
    
    inspecoes++;
    if ((i >= 2) && (fila->paciente[i].prioridade > fila->paciente[pai].prioridade))
    {
        TrocaPosFila(&fila->paciente[i].prioridade, &fila->paciente[pai].prioridade,
                     &fila->paciente[i].nome, &fila->paciente[pai].nome);
        CorrigeHeapSubindo(fila, pai);
    }
}

void InsereHeap(FilaHeap *fila, char *n, int *p)
{
    fila->tamanho++;

    strcpy(&fila->paciente[fila->tamanho].nome, n);
    fila->paciente[fila->tamanho].prioridade = p;

    CorrigeHeapSubindo(fila, fila->tamanho);
}

void RemoveHeap(FilaHeap *fila)
{
    TrocaPosFila(&fila->paciente[1].prioridade, &fila->paciente[fila->tamanho].prioridade,
                 &fila->paciente[1].nome, &fila->paciente[fila->tamanho].nome);

    fila->tamanho--;
    CorrigeHeapDescendo(fila, 1);
}

void CadastraPaciente(FilaHeap *fila)
{
    char entrada_nome[TamMaxNome];
    int entrada_idade;

    puts("Insira um nome: ");
    fgets(entrada_nome, TamMaxNome, stdin);
    entrada_nome[strcspn(entrada_nome, "\n")] = '\0';

    while (1)
    {
        puts("Insira a Prioridade (Entre 1 e 99): ");
        scanf("%i", &entrada_idade);
        getchar();
        if ((entrada_idade >= 1) && (entrada_idade <= 99))
            break;
    }

    InsereHeap(fila, &entrada_nome, entrada_idade);
}

void ImprimeFila(FilaHeap fila)
{
    puts("\t-=Imprimindo Fila=-");
    for (int i = 1; i <= fila.tamanho; i++)
    {
        printf("Paciente [%02d] = Prioridade: %02d || Nome: %s \n",
               i, fila.paciente[i].prioridade, fila.paciente[i].nome);
    }
    puts("");
}

void AlteraHeap(FilaHeap *fila, int i, int *valor)
{
    int aux = fila->paciente[i].prioridade;
    fila->paciente[i].prioridade = valor;

    if (aux < valor)
        CorrigeHeapSubindo(fila, i);
    else
        CorrigeHeapDescendo(fila, i);
}

void AtualizarCadastro(FilaHeap *fila)
{
    int i_paciente, nova_prioridade;

    while (1)
    {
        printf("Qual paciente deseja atualizar? (Entre 1 e %d):\n", fila->tamanho);
        scanf("%i", &i_paciente);
        getchar();

        if ((i_paciente >= 1) && (i_paciente <= fila->tamanho))
            break;
    }

    printf("Paciente %s Selecionado!\n", fila->paciente[i_paciente].nome);

    while (1)
    {
        puts("Digite nova prioridade");
        scanf("%i", &nova_prioridade);
        getchar();

        if ((nova_prioridade >= 1) && (nova_prioridade <= 99))
            break;
    }

    AlteraHeap(fila, i_paciente, nova_prioridade);
}

void ConstroiFilaDesordenada(FilaHeap *fila)
{
    char nomes_aleat[350][40] = {"Lisa Schwartz", "Benjamin Parker", "Kimberly Sanchez", "Kimberly Carpenter", "Brian Alvarado", "Elizabeth Tran", "Billy Espinoza", "Bradley Rosales", "Todd Floyd", "Michael Hunter", "Yvonne Kemp", "Sheila Jefferson", "Mr. Nathan Martin", "Jennifer Arnold", "Gary Macias", "Cynthia Barnes", "Megan Moore", "Blake Wilcox", "Julie Landry", "Sharon Sims", "Daniel Black", "Anthony Butler", "Brianna Flores", "William Sims", "Richard Jimenez", "Lance Owens", "Samantha Torres", "Shane Butler", "Jack Lee", "Amanda Charles", "Barbara Wood", "Anne Perry", "Natalie Tyler", "James Charles", "Michael Brock", "Chase Smith", "Sara Hill", "Chris Marquez", "Kathryn Adams", "Crystal Gonzalez", "Jason Owens", "Sabrina Holt", "Vincent Fuller", "David Hines", "Austin Green MD", "Madison Mills", "Terry Carrillo", "Sarah Merritt", "Michael Lopez", "Charlotte Wright", "Steven Cortez", "Sarah Meyer", "Karen Rodriguez", "Theresa Perez", "Michelle Castillo", "Nicholas Kelly", "Maurice Jones", "Megan Zhang", "Sarah Fisher", "Bryan Vega", "Stacie Thompson", "John Hartman", "Bryan Parker", "Kelsey Oliver", "Wendy Davila DDS", "Kayla Smith", "Alan Vance", "Elizabeth Webb", "Christine Harris", "Scott Lawrence", "Jason Ibarra", "Zachary Spencer", "Anne Johnson", "Linda Bishop", "Peter Jones", "Katherine Ayers", "Stephanie Brock", "Angela Pearson", "Shelly Brandt", "Brenda Moore", "Joshua Cook", "Cody Hoffman", "Brandon Farrell", "Alan Matthews", "Sarah Freeman", "James Garcia", "Christopher Smith", "Christine Baird", "Krista Long", "Deborah Ramos", "Xavier Hood", "Christopher Foster", "Michael Flores", "Veronica Lopez", "Thomas Greene", "Evan Saunders", "Lori Jennings", "Eddie Cole", "Elizabeth Chandler", "Christopher Sullivan", "Tyler Arellano", "Charles Manning", "Laura Gay", "Christopher Solis", "Shelley Campbell", "Jessica Lee", "Bryan Warren", "Natalie Calhoun", "Amy Washington", "Michael Davis", "Susan Ward", "Larry Mcguire", "Dominique Fuller", "Robert Alexander", "Todd Harris", "Brian Santiago", "Cody Cannon", "Courtney Lutz", "Cody Washington", "Mark Massey", "Kenneth Reid", "Patricia Davis", "Benjamin Goodman", "Mikayla Anderson", "Anthony Weber", "Stephanie Navarro", "Tina Harris", "Dr. Sydney Gregory", "John Stewart", "Briana Scott", "Luis Maldonado", "Benjamin Robinson", "Willie Ross", "Maria Zimmerman", "Cindy Garcia", "Mary Bridges", "Nicole Morrison", "Stacy Thompson", "Charles Hill", "Karen Vasquez", "George Salas", "Sarah Webb", "Robert Simmons", "Jeffrey Powell", "Sarah Duffy", "Rebecca Fleming", "Jesse Taylor", "Matthew Young", "Christian Hernandez", "James Russo", "Cynthia Dillon", "Jenna Miller", "Andrew White", "Amy Choi", "Sara Payne", "Jason Bass", "Joseph Pena", "Don Williams", "Peter Watson", "Karen Vargas", "Mary Brewer", "Julia Williams", "Corey Hernandez", "Patrick Hester", "Bryan Johnson", "Javier Smith", "Karen Warren", "Mary Lopez", "Kaitlyn Christian", "Caitlyn Thompson", "Steven Jacobs", "Kristi Vargas", "Joseph Brock", "Robin Fry", "James Roman", "Olivia Baker", "Edward Baker", "Ryan Smith", "Alicia Barr", "Raymond Christensen", "Shane Harmon", "Hannah Barker", "Dylan York", "Mrs. Rhonda Cooper", "Jason Ayala", "Sandra Rodriguez", "Kevin Moss", "Jack Hogan", "Nicholas Robinson PhD", "Connor Thomas", "Brianna Spencer", "Crystal Curry", "Anthony Ramirez", "Amanda Terry", "Kyle Rowe", "Scott Aguilar", "Zachary Shah", "Thomas Cannon", "Mark Rowland", "Sandra Miles", "Brandy Bishop", "Miranda Carlson", "Danielle Carter", "Brenda Morrison", "Jerry Garcia", "Stacey Hayes", "Brandi Sheppard DDS", "Kenneth Johnson", "Joshua Acosta", "Tammy Sanchez", "Bethany Logan", "Sheila Vargas", "Savannah Crawford", "Kathy Petersen", "Kayla Romero", "Jeanette Jones", "Robert Moore", "David Jenkins", "John Smith", "Ronald Bentley", "Robert Kelly", "Douglas Snyder", "Donald Cuevas", "James Howard", "Tracy Williams", "Lydia Shepherd", "Erica Wilkinson", "Kayla Russell", "Michelle Lucas", "Matthew Vargas", "Mary Garrison", "Marc Brooks", "Cassie Norton", "Bobby Foster", "Derek Hamilton", "Erin Santos", "Eric Parks", "Christopher Cook", "Jason Buck", "Kathleen Chandler", "Amy Wilson", "Deborah Perez", "Matthew Smith", "Zoe Medina", "Kelsey Daniels", "Tyrone Sheppard", "Ryan Mora", "Heather Shelton", "Eric Jackson", "Dennis Howard", "Shawn Solis", "Nicole Holloway", "Rachel West", "Kenneth Mclaughlin Jr.", "Rebecca Contreras", "Sean James", "Paige Miller", "Meghan Shaffer", "Michael Fletcher", "Crystal Ferguson", "Mark Smith", "William Lawson", "Stephanie Gould", "Michelle Wiley", "Ashley Holmes", "Amy Joseph", "John Lindsey", "Victoria George", "Ernest Kemp", "Stephen Schwartz", "David Blair", "Craig Osborne", "Amanda Rocha", "Dustin Romero", "James Duran", "Gregory Wong", "Vincent Cisneros", "Carolyn Green", "Rachel Pearson", "Rebecca Norton", "Maria Williams", "Seth Moore", "Diane Cole", "Laurie Freeman", "Timothy Torres", "Nicole Perez", "Matthew Weaver", "Brittany Shepherd", "William Smith", "Robert Jones", "Joshua Watkins", "Dwayne Ward", "Ernest Figueroa", "Derek Fowler", "Sheila Jones", "Michelle Mckee", "Steven Olson", "Michael Johnson", "Patricia Mckenzie", "Joseph Scott", "Jessica Fowler", "Kari Leblanc", "Shane Montoya", "Ashley Bradley", "Matthew Weber", "Chad Gutierrez", "Vanessa Fernandez", "Kent Austin", "Zachary Smith", "Steven Allen", "Jennifer Webb", "Jordan Morales", "Sarah Shaw", "Shawna Patrick", "Bailey Strickland", "Christopher Velazquez", "Alexa Griffith", "Joseph Johnson", "Nicholas Bell", "Stephanie Cooper", "Ryan Lopez", "Anne Hale", "Michelle Castaneda", "Gina Freeman", "Kelly Monroe", "Eric White", "Bradley Roberts", "Javier Martinez", "Dennis Allen", "Jeffrey Vaughn", "Brent Kelly", "Jeremiah Greene", "Melissa Rodriguez", "Linda Davis", "Christina Walter", "Brandy Gray", "William Snow", "Daniel Moore", "Mark Mcdonald", "Jose Griffin", "Kathleen Gonzales", "Heather Valdez", "Alejandro Lee", "Spencer Perkins", "Sheila Nguyen", "Cynthia Roberts", "Kimberly Evans", "James Durham", "Chad Jackson", "Jay Smith"};
    int num = aleat(1, 99), nome = aleat(1, 350);

    puts("\nCriando fila com 99 elementos com propriedades aleatorias\n");
    for (int i = 1; i <= TamMaxFila; i++)
    {
        fila->tamanho++;

        strcpy(&fila->paciente[fila->tamanho].nome, nomes_aleat[nome]);
        fila->paciente[fila->tamanho].prioridade = num;

        num = aleat(1, 99);
        nome = aleat(1, 350);
    }
}

void ConstroiHeap(FilaHeap *fila)
{
    puts("\nTransformando em HEAP (definindo prioridades)\n");
    for (int i = fila->tamanho / 2; i >= 1; i--)
        CorrigeHeapDescendo(fila, i);
}

void AtualizaPrioridadesAleat(FilaHeap *fila)
{
    int num = aleat(1, 99),
        paciente = aleat(1, 99),
        propriedade = aleat(1, 99);

    printf("\nAtualizando prioridade de %d Pacientes\nPacientes com prioridade alterada:", num);

    for (int i = 0; i <= num; i++)
    {
        printf(" %d", paciente);
        AlteraHeap(fila, paciente, propriedade);
        paciente = aleat(1, 99);
        propriedade = aleat(1, 99);
    }
    puts("...\n");
}

void HeapSort(FilaHeap *fila)
{
    int aux = fila->tamanho;
    puts("\nHEAPSORT - Transformando a fila de prioridades HEAP em uma fila Ordenada Nao Decrescente\n");
    for (int i = fila->tamanho; i > 1; i--)
    {
        TrocaPosFila(&fila->paciente[1].prioridade, &fila->paciente[i].prioridade,
                     &fila->paciente[1].nome, &fila->paciente[i].nome);
        fila->tamanho--;
        CorrigeHeapDescendo(fila, 1);
    }
    fila->tamanho = aux;
}

void ChamandoTodosPacientes(FilaHeap *fila)
{
    puts("\n\tChamando todos os pacientes:");
    for (int i = fila->tamanho; i >= 1; i--)
    {
        printf("Prioridade: %02d || Nome: %s \n",
               fila->paciente[1].prioridade, fila->paciente[1].nome);
        TrocaPosFila(&fila->paciente[1].prioridade, &fila->paciente[fila->tamanho].prioridade,
                     &fila->paciente[1].nome, &fila->paciente[fila->tamanho].nome);

        fila->tamanho--;
        CorrigeHeapDescendo(fila, 1);
    }
}

void ChecaHeap(FilaHeap *fila)
{
    puts("Checando se Fila eh um HEAP...");
    for (int i = fila->tamanho; i > 1; i--)
    {
        if (fila->paciente[i].prioridade > fila->paciente[i / 2].prioridade)
        {
            printf("|ERRO| PACIENTE [%d] nao obedece criterio de prioridade\n", i);
            return;
        }
    }
    puts("|OK| Fila obedece o criterio de prioridade!");
}

int aleat(int min, int max)
{
    int n;

    n = (rand() % (min - max + 1) + min);

    return n;
}