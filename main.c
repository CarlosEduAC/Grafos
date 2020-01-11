#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct lista
{
    int destino;
    float custo;
    struct lista *prox;
}Lista;
typedef struct menor
{
    int caminho[10];
    float custo[10];
    int indice;
}menor;

void Menu(void);
void Inicializa (Lista **g,int n);
Lista* Insere_Na_Lista (Lista* lst,int destino,float custo);
void Insere_Aresta(Lista** g,int origem,int destino,float custo);
Lista* Remove_Da_Lista(Lista* lst,int x);
void Remove_Aresta (Lista** g,int origem,int destino);
int Existe (Lista* lst,int x);
void Existe_Aresta (Lista **g,int origem,int destino);
void Imprime_Lista(Lista *lst);
void Imprime_Grafo (Lista **g, int n);
int Conta_Grau_Saida (Lista*lst);
void Grau_Saida(Lista** g,int origem);
int Conta_Grau_Entrada (Lista* lst,int x);
void Grau_Entrada(Lista** g,int destino,int n);
int Existe_Caminho (int* v,int pos,int x);
void Imprime_Caminho (Lista** g,int *v,int pos,int destino,int h);
void Grafo_Completo (Lista** g,int n);
void Completa_Grafo (Lista** g,int n);
void Imprime_Menor_Caminho (Lista** g,int *v,float *vet,int pos,int destino,menor* vmenor);

int main()
{
    setlocale(LC_ALL,"Portuguese");
    Menu();
    return 0;
}
/// Função Menu, mostra na tela as opções e chama as funções correspondentes
void Menu (void)
{
    int op_menu,n,origem,destino,noh,*caminho,i;
    float custo,*caminho_custo;
    menor vmenor;
    Lista **g;
    printf("Qual o tamanho do seu grafo? ");
    scanf("%d",&n);
    system("cls");
    g = (Lista **)malloc((n+1) * sizeof(Lista *));
    caminho = (int *)malloc(n * sizeof(int));
    caminho_custo = (float *)malloc(n * sizeof(float));
    Inicializa(g,n);
    do
    {
        printf("\t\tMENU\n\n");
        printf("1. Inserir uma nova aresta no grafo\n");
        printf("2. Remover uma aresta do grafo\n");
        printf("3. Verificar se uma aresta existe n\n");
        printf("4. Verificar grau de saída de um vértice \n");
        printf("5. Verificar grau de entrada de um vértice\n");
        printf("6. Verificar se o grafo é completo\n");
        printf("7. Imprimir todos os caminhos entre origem e destino que passam por um nó intermediário\n");
        printf("8. Imprimir caminho e o custo, do caminho de menor custo entre origem e destino\n");
        printf("9. Complete o Grafo\n");
        printf("12. Sair\n\nO que devo fazer: ");
        scanf("%d", &op_menu);
        system("cls");
        switch(op_menu)
        {

            case 1: printf("Onde você deseja inserir: ");
                    scanf("%d", &origem);
                    printf("\nQual o seu destino: ");
                    scanf("%d", &destino);
                    printf("\nQual será o custo: ");
                    scanf("%f", &custo);
                    if (origem<=n && origem!=destino && origem != 0 && destino<=n && destino != 0)
                    {
                        Insere_Aresta(g,origem,destino,custo);
                    }
                    else
                    {
                        printf("Erro!");
                    }
                    break;

            case 2: printf("Qual a origem da aresta que deve ser removida: ");
                    scanf("%d", &origem);
                    printf("\nQual o destino: ");
                    scanf("%d", &destino);
                    if (origem<=n && origem!=destino && origem != 0 && destino<=n && destino != 0)
                    {
                        Remove_Aresta(g,origem,destino);
                    }
                    else
                    {
                        printf("Erro!");
                    }
                    break;

            case 3: printf("Qual a origem da aresta: ");
                    scanf("%d", &origem);
                    printf("\nQual o destino: ");
                    scanf("%d", &destino);
                    system("cls");
                    if (origem<=n && origem!=destino && origem != 0 && destino<=n && destino != 0)
                    {
                        Existe_Aresta(g,origem,destino);
                    }
                    else
                    {
                        printf("Não existe aresta!");
                    }
                    break;

            case 4: printf("Qual a origem da aresta: ");
                    scanf("%d", &origem);
                    system("cls");
                    if (origem<=n && origem != 0)
                    {
                        Grau_Saida(g,origem);
                    }
                    else
                    {
                        printf("Não existe aresta!");
                    }
                    break;

            case 5: printf("Digite o destino: ");
                    scanf("%d", &destino);
                    if (destino != 0 && destino<=n)
                    {
                        Grau_Entrada(g,destino,n);
                    }
                    else
                    {
                        printf("Não existe aresta!");
                    }
                    break;

            case 6: Grafo_Completo(g,n);
                    break;

            case 7: printf("Qual a origem: ");
                    scanf("%d", &origem);
                    printf("\nQual o seu destino: ");
                    scanf("%d", &destino);
                    printf("\nQual o seu nó intermediário: ");
                    scanf("%d", &noh);
                    caminho[0]=origem;
                    if (origem<=n && origem!=destino && origem != 0 && destino<=n && destino != 0)
                    {
                        Imprime_Caminho(g,caminho,1,destino,noh);
                    }
                    else
                    {
                        printf("Não existe aresta!");
                    }
                    break;

            case 8: printf("Qual a origem: ");
                    scanf("%d", &origem);
                    printf("\nQual o seu destino: ");
                    scanf("%d", &destino);
                    caminho[0]=origem;
                    for(i=0;i<=n;i++)
                    {
                        vmenor.custo[i]=1000;
                        vmenor.caminho[i]=0;
                        vmenor.indice=n;
                    }
                    if (origem<=n && origem!=destino && origem != 0 && destino<=n && destino != 0)
                    {
                        Imprime_Menor_Caminho(g,caminho,caminho_custo,1,destino,&vmenor);
                        printf("Menor Caminho: ");
                        custo=0;
                        for(i=0;i<vmenor.indice;i++)
                        {
                            printf("%d ",vmenor.caminho[i]);
                            custo += vmenor.custo[i];
                        }
                        printf("\nCusto total: %f",custo);
                    }
                    else
                    {
                        printf("Não existe aresta!");
                    }
                    break;

            case 9: Completa_Grafo(g,n);
                    break;

            case 10:printf("Digite a origem: ");
                    scanf("%d", &origem);
                    if (origem<=n && origem != 0)
                    {
                        Imprime_Lista(g[origem]);
                    }
                    else
                    {
                        printf("Não existe aresta!");
                    }
                    break;

            case 11: Imprime_Grafo(g,n);
                     break;

            case 12: printf("Finalizando programa! \n\n");
                     exit(1);
                     break;

            default:printf("Digite uma opção válida!\n\n");
                    break;

        }
        printf("\n\n");
        system("pause");
        system("cls");
    }while(op_menu!=12);
}
void Inicializa (Lista **g,int n)
{
    int i;
    for (i=0;i<=n;i++)
    {
        g[i]=NULL;
    }
}
Lista* Insere_Na_Lista (Lista* lst,int destino,float custo)
{
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->destino=destino;
    novo->custo=custo;
    novo->prox=lst;
    return novo;
}
void Insere_Aresta(Lista** g,int origem,int destino,float custo)
{
    if(!Existe (g[origem],destino))
    {
        g[origem] = Insere_Na_Lista(g[origem],destino,custo);
    }
    else
    {
       printf("\n\nAresta já existente");
    }
}
Lista* Remove_Da_Lista(Lista* lst,int x)
{
    Lista* novo;
    if (lst!=NULL)
    {
        if (lst->destino == x)
        {
            novo = lst;
            lst = lst->prox;
            free(novo);
            return lst;
        }
        else
        {
            lst->prox = Remove_Da_Lista(lst->prox,x);
            return lst;
        }
    }
    else
    {
        return NULL;
    }
}
void Remove_Aresta (Lista** g,int origem,int destino)
{
    if(Existe (g[origem],destino))
    {
        g[origem] = Remove_Da_Lista (g[origem],destino);
    }
    else
    {
       printf("\n\nAresta inxistente");
    }
}
int Existe (Lista* lst,int x)
{
    if(lst==NULL)
    {
        return 0;
    }
    else
    {
        if (lst->destino==x)
        {
            return 1;
        }
        else
        {
            return Existe (lst->prox,x);
        }
    }
}
void Existe_Aresta (Lista **g,int origem,int destino)
{
    if(Existe(g[origem],destino))
    {
        printf("Existe aresta\n\n");
    }
    else
    {
        printf("Não existe");
    }
}
void Imprime_Lista(Lista *lst)
{
    if(lst != NULL){
        printf("%d | %.2f -> ",lst->destino,lst->custo);
        Imprime_Lista(lst->prox);
    }
}
void Imprime_Grafo (Lista **g, int n)
{
    int i;
    for(i=1;i<=n;i++)
    {
        printf("g[%d] = ",i);
        Imprime_Lista(g[i]);
        printf("\n");
    }
}
int Conta_Grau_Saida (Lista* lst)
{
    if (lst == NULL)
    {
        return 0;
    }
    else
    {
        return 1+Conta_Grau_Saida(lst->prox);
    }
}
void Grau_Saida(Lista** g,int origem)
{
    int cont = Conta_Grau_Saida(g[origem]);
    printf("O grau de saída de %d é %d\n\n",origem,cont);
}
int Conta_Grau_Entrada (Lista* lst,int x)
{
    if (lst == NULL)
    {
        return 0;
    }
    else
    {
        if (lst->destino==x)
        {
            return 1+Conta_Grau_Entrada(lst->prox,x);
        }
        else
        {
            return 0+Conta_Grau_Entrada(lst->prox,x);
        }
    }
}
void Grau_Entrada(Lista** g,int destino,int n)
{
    int i, cont=0;
    for(i=1;i<=n;i++)
    {
        cont += Conta_Grau_Entrada(g[i],destino);
    }
    printf("O grau de entrada de %d é %d\n\n",destino,cont);
}
int Existe_Caminho (int* v,int pos,int x)
{
    int i;
    for(i=0;i<pos;i++)
    {
        if(v[i]==x)
        {
            return 1;
        }
    }
    return 0;
}
void Imprime_Caminho (Lista** g,int* v,int pos,int destino,int h)
{
    int i,flag=0;
    if(v[pos-1]==destino)
    {
        for(i=0;i<pos;i++)
        {
            if (v[i]==h)
            {
                flag=1;
            }
        }
        if(flag==1)
        {
            printf("\n");
            for(i=0;i<pos;i++)
            {
                printf("%d",v[i]);
            }
        }
    }
    else
    {
        Lista* p = g[v[pos-1]];
        while(p!=NULL)
        {
            if (!Existe_Caminho(v,pos,p->destino))
            {
                v[pos] = p->destino;
                Imprime_Caminho(g,v,pos+1,destino,h);
            }
            p=p->prox;
        }
    }
}
void Grafo_Completo (Lista** g,int n)
{
    int arestas=0,i;
    for (i=1;i<=n;i++)
    {
        arestas += Conta_Grau_Saida(g[i]);
    }
    if(arestas == ((n)*(n-1))/2)
    {
        printf("\n\nGrafo Completo\n\n");
    }
    else
    {
        printf("\n\nGrafo Incompleto\n\n");
    }
}
void Completa_Grafo (Lista** g,int n)
{
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i!=j){
                if(!Existe (g[i],j)){
                    g[i] = Insere_Na_Lista(g[i],j,1);
                }
            }
        }

    }
}
void Imprime_Menor_Caminho (Lista** g,int *v,float *vet,int pos,int destino,menor* vmenor)
{
    int i,tam;
    float menor1=0,menor2=0;
    if(v[pos-1]==destino)
    {
        if (pos>=(vmenor->indice))
        {
            tam = pos;
        }
        else
        {
            tam = (vmenor->indice);
        }
        for(i=0;i<tam;i++)
        {
            if(i<pos)
                menor1 += vet[i];
            if(i<(vmenor->indice))
                menor2 += vmenor->custo[i];
        }
        if(menor1 < menor2)
        {
            for(i=0;i<pos;i++)
            {
                vmenor->custo[i] = vet[i];
                vmenor->caminho[i] = v[i];
                vmenor->indice = pos;
            }
        }
    }
    else
    {
        Lista* p = g[v[pos-1]];
        while(p!=NULL)
        {

            if(!Existe_Caminho(v,pos,p->destino))
            {
                v[pos] = p->destino;
                vet[pos] = p->custo;
                Imprime_Menor_Caminho(g,v,vet,pos+1,destino,vmenor);
            }
            p=p->prox;
        }
    }
}
