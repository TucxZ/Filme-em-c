/* uniGB1
Gerenciador de filmes.
Nomes: Arthur Mota, Fernando, Eduarda, Isabella */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char titulo[100];
    char genero[50];
    int ano;
    float nota;
} Filme;

void cadastrarFilme()
{
    FILE *arquivo = fopen("filmes.dat", "ab");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    Filme f;

    printf("\n=== CADASTRAR FILME ===\n\n");
    printf("ID: ");
    scanf("%d", &f.id);

    getchar();

    printf("Titulo: ");
    fgets(f.titulo, 100, stdin);
    f.titulo[strcspn(f.titulo, "\n")] = '\0';

    printf("Genero: ");
    fgets(f.genero, 50, stdin);
    f.genero[strcspn(f.genero, "\n")] = '\0';

    printf("Ano: ");
    scanf("%d", &f.ano);

    printf("Nota: ");
    scanf("%f", &f.nota);

    fwrite(&f, sizeof(Filme), 1, arquivo);

    fclose(arquivo);

    printf("\nFilme cadastrado com sucesso!\n");
}

void listarFilmes()
{
    FILE *arquivo = fopen("filmes.dat", "rb");

    if (arquivo == NULL)
    {
        printf("Arquivo nao encontrado.\n");
        return;
    }

    Filme f;

    printf("\n=== LISTA DE FILMES ===\n");

    while (fread(&f, sizeof(Filme), 1, arquivo))
    {
        printf("ID: %d\n", f.id);
        printf("Titulo: %s\n", f.titulo);
        printf("Genero: %s\n", f.genero);
        printf("Ano: %d\n", f.ano);
        printf("Nota: %.1f\n", f.nota);
        printf("----------------------\n");
    }

    fclose(arquivo);
}

void buscarFilme()
{
    FILE *arquivo = fopen("filmes.dat", "rb");

    if (arquivo == NULL)
    {
        printf("Arquivo nao encontrado.\n");
        return;
    }

    int idBusca;
    int encontrado = 0;

    printf("\n=== BUSCAR FILME ===\n\n");
    printf("Digite o ID do filme: ");
    scanf("%d", &idBusca);

    Filme f;

    while (fread(&f, sizeof(Filme), 1, arquivo))
    {
        if (f.id == idBusca)
        {
            printf("\nFilme encontrado:\n");
            printf("----------------------\n");
            printf("Titulo: %s\n", f.titulo);
            printf("Genero: %s\n", f.genero);
            printf("Ano: %d\n", f.ano);
            printf("Nota: %.1f\n", f.nota);
            printf("----------------------\n");

            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("\n* Filme nao encontrado.\n");
    }

    fclose(arquivo);
}

void atualizarFilmes()
{
    FILE *arquivo = fopen("filmes.dat", "r+b");
    if (arquivo == NULL)
    {
        printf("Arquivo nao encontrado.\n");
        return;
    }

    Filme f;
    int id;
    int encontrado = 0;

    printf("\n=== ATUALIZAR FILME ===\n\n");
    printf("Digite o ID do filme que deseja atualizar: ");
    scanf("%d", &id);

    while (fread(&f, sizeof(Filme), 1, arquivo))
    {

        if (f.id == id)
        {

            encontrado = 1;

            printf("\nFilme encontrado!\n");
            printf("----------------------\n");
            printf("ID: %d\n", f.id);
            printf("Titulo: %s\n", f.titulo);
            printf("Genero: %s\n", f.genero);
            printf("Ano: %d\n", f.ano);
            printf("Nota: %.1f\n", f.nota);
            printf("----------------------\n");

            int opcao;

            printf("\nEscolha o campo para atualizar:\n");
            printf("1 - Titulo\n");
            printf("2 - Genero\n");
            printf("3 - Ano\n");
            printf("4 - Nota\n\n");
            printf("Escolha: ");
            scanf("%d", &opcao);

            getchar();

            switch (opcao)
            {

            case 1:
                printf("\nNovo titulo: ");
                fgets(f.titulo, 100, stdin);
                f.titulo[strcspn(f.titulo, "\n")] = '\0';
                break;

            case 2:
                printf("\nNovo genero: ");
                fgets(f.genero, 50, stdin);
                f.genero[strcspn(f.genero, "\n")] = '\0';
                break;

            case 3:
                printf("\nNovo ano: ");
                scanf("%d", &f.ano);
                break;

            case 4:
                printf("\nNova nota: ");
                scanf("%f", &f.nota);
                break;

            default:
                printf("\nOpcao invalida.\n");
                fclose(arquivo);
                return;
            }

            fseek(arquivo, -sizeof(Filme), SEEK_CUR);

            fwrite(&f, sizeof(Filme), 1, arquivo);

            printf("\nFilme atualizado com sucesso!\n");

            return;
        }
    }

    if (!encontrado)
    {
        printf("\n* Filme com ID %d nao encontrado.\n", id);
    }

    fclose(arquivo);
}

long long unsigned int contarFilmes()
{
    FILE *f = fopen("filmes.dat", "rb");
    if (f == NULL)
    {
        printf("\nFalha ao abrir o arquivo\n");
        return 0;
    }
    fseek(f, 0, SEEK_END);
    long long unsigned int count = ftell(f) / sizeof(Filme);
    fclose(f);
    return count;
}

Filme pegarFilme(long long unsigned int index)
{
    Filme f;
    FILE *fi = fopen("filmes.dat", "rb");
    fseek(fi, index * sizeof(Filme), SEEK_SET);
    fread(&f, sizeof(Filme), 1, fi);
    fclose(fi);
    return f;
}

void filtrarFilmes()
{
    int count = 0;
    char gen[50];
    int total_filmes = contarFilmes();

    printf("\n=== FILTRAR FILME ===\n");
    printf("\nDigite o Genero do filme: ");
    scanf("%s", gen);

    Filme f;

    for (int i = 0; i < total_filmes; i++)
    {
        f = pegarFilme(i);

        if (strcmp(f.genero, gen) == 0)
        {
            count++;
        }
    }

    if (count >= 2)
        printf("\n=== FILMES DE %s ===\n\nForam encontrados [%d Filmes] de %s!\n----------------------\n",
               gen, count, gen);
    else if (count == 1)
        printf("\n=== FILMES DE %s ===\n\nFoi encontrado [%d Filme] de %s!\n----------------------\n",
               gen, count, gen);
    else
        printf("\n=== FILMES DE %s ===\n\nNao foi possivel encontrar Filmes de %s.\n\n----------------------\n",
               gen, gen);

    for (int i = 0; i < total_filmes; i++)
    {
        f = pegarFilme(i);

        if (strcmp(f.genero, gen) == 0)
        {
            printf("ID: %d\nTitulo: %s\nGenero: %s\nAno: %d\nNota: %.1f\n----------------------\n", f.id, f.titulo, f.genero, f.ano, f.nota);
        }
    }

}

void end()
{
    int r = 0;

    do
    {
        printf("\n1 - Voltar para o menu\n2 - Sair\n\nResposta: ");

        while (scanf("%d", &r) != 1)
        {
            printf("\n* Entrada Invalida! Digite um numero (1 ou 2)\n");
            while (getchar() != '\n');
            printf("Resposta: ");
        }

        if (r < 1 || r > 2)
        {
            printf("\n* Opcao invalida! Tente novamente");
            while (getchar() != '\n');
        }

    } while (r < 1 || r > 2);

    if (r == 2)
    {
        printf("\nEncerrando...\n");
        exit(0);
    }

    return;
}

int main()
{
    int opcao;

    do
    {
        printf("\n=== MENU ===\n\n");
        printf("1 - Cadastrar filme\n");
        printf("2 - Listar filmes\n");
        printf("3 - Buscar filme\n");
        printf("4 - Atualizar filme\n");
        printf("5 - Filtrar filmes\n");
        printf("0 - Sair\n");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {

        case 1:
            cadastrarFilme();
            while (getchar() != '\n');
            end();
            break;

        case 2:
            listarFilmes();
            while (getchar() != '\n');
            end();
            break;

        case 3:
            buscarFilme();
            while (getchar() != '\n');
            end();
            break;

        case 4:
            atualizarFilmes();
            while (getchar() != '\n');
            end();
            break;

        case 5:
            filtrarFilmes();
            while (getchar() != '\n');
            end();
            break;

        case 0:
            printf("\nEncerrando...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }

        while ((getchar()) != '\n')
            ;

    } while (opcao != 0);

    return 0;
}