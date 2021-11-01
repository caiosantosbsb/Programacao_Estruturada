/*PR�T. PROF. II - LINGUAGEM DE PROGRAMA��O ESTRUTURADA - GPE01N0147
Descri��o do Projeto 01:

Utilizando os conceitos de vetor e fun��o (est� proibido o uso de struct, ponteiros, aloca��o din�mica...), implemente um algoritmo que:

inclua um usu�rio por vez, limitado a 1000 usu�rios;
edite um usu�rio;
exclua um usu�rio;
busque um usu�rio pelo id (pesquisa bin�ria);
busque um usu�rio pelo email;
imprima todos os usu�rios cadastrados;
fa�a backup dos usu�rios cadastrados;
fa�a restaura��o dos dados;
Dados do usu�rio:

Id (int) => preenchido automaticamente por n�meros rand�micos
Nome completo (string)
Email (string) => valida��o do campo: verificar se o caractere "@" aparece
Sexo (string) => valida��o do campo: aceitar somente as palavras Feminino, Masculino e N�o declarar
Endere�o (string)
Altura (double) => valida��o do campo: aceitar valores entre 1 e 2 m. 
Vacina (tomou a vacina? boolean)
Apresenta��o: 27 de setembro

Duas equipes ser�o sorteadas para realizar a apresenta��o do projeto, tendo 15 min para cada apresenta��o.
Entrega:  28 de setembro

apenas um integrante da dupla deve postar o arquivo no formato .c ou .cpp
o nome completo dos integrantes da dupla deve constar na primeira linha do arquivo, como coment�rio, e no f�rum.
no f�rum tamb�m dever� ser postado o link do reposit�rio do projeto no GitHub (uso obrigat�rio)
a postagem final do projeto dever� ser feita at� 28/09 (voc�s poder�o realizar corre��es ap�s a apresenta��o dos projetos)*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


//Estrutura ativa
struct residencia{
    char logradouro[35], bairro[35],uf[2];
    int numero,cep;	
};

struct cadastroVacina{
    char nome[35], email[35], sexo[13];
    int id;
	double altura;
    bool vacina;
    struct residencia endereco;
};

//Estrutura bakcup
struct residenciaBkp{
    char logradouro[35], bairro[35],uf[2];
    int numero,cep;	
};

struct cadastroVacinaBkp{
    char nome[35], email[35], sexo[13];
    int id;
	double altura;
    bool vacina;
    struct residenciaBkp endereco;
};

//Declaracao de funcoes
void cadastrar(struct cadastroVacina *cadastro,int cont);
void ordenacaoInsercao(struct cadastroVacina *cadastro,int cont);
void listar(struct cadastroVacina *cadastro,int cont);
int consultar(struct cadastroVacina *cadastro,int esq, int dir, int idBusca);
void buscaEmail(struct cadastroVacina *cadastro,int cont);
void alterar(struct cadastroVacina *cadastro,int cont);
int backup(struct cadastroVacina *cadastro, struct cadastroVacinaBkp *cadastroBkp,int cont);

int main(){
	struct cadastroVacina cadastro[1000]; 
	struct cadastroVacinaBkp cadastroBkp[1000];
	int opcao, cont=0, bkpCont;
	int esq=0, dir, index1, idBusca, i; //variaveis consulta binaria
	
	do{
	opcao=menu();//chama Menu e grava em opcao
		switch (opcao){
		case 0:
		return;		
		break;
		case 1:
			//Gerar ID
			cadastrar(cadastro,cont);			
			cont++;
		break;
		case 2:
			//Listar nome
			listar(cadastro,cont);		
		break;
		case 3:
			//Consula o ID desejado
			printf("Informe o ID que deseja consultar: ");
			fflush(stdin);
			scanf("%d",&idBusca);
			dir=cont;			
			index1=consultar(cadastro,esq,dir-1,idBusca);
	    	(index1 == -1)?printf("Id nao encontrado."):printf("ID = %4d - Nome = %35s - Email = %35s - Sexo = %13s \nEndereco %35s, %d, %35s, %d, %2s - Altura = %.2f\n", cadastro[index1].id, cadastro[index1].nome, cadastro[index1].email, cadastro[index1].sexo, cadastro[index1].endereco.logradouro, cadastro[index1].endereco.numero, cadastro[index1].endereco.bairro, cadastro[index1].endereco.cep,cadastro[index1].endereco.uf, cadastro[index1].altura);printf(cadastro[index1].vacina ? "Tomou vacina" : "Nao tomou vacina");
			
		break;
		case 4:
			//Busca pelo email desejado
			buscaEmail(cadastro,cont);
		break;
		case 5:
			//Altera atraves do ID desejado
			alterar(cadastro,cont);
		break;
		case 6:
			//Excluir atraves do ID desejado
			printf("\n\n*** Excluir ***\n");
			printf("Digite o ID que deseja excluir: ");
			fflush(stdin);
			scanf("%d", &idBusca);
			dir=cont;
			index1=consultar(cadastro,esq,dir-1,idBusca);			
			(index1 == -1)?printf("Id nao encontrado."):printf("ID excluido"); 
            cadastro[index1].id=cadastro[cont-1].id;
			strcpy(cadastro[index1].nome,cadastro[cont-1].nome);
			strcpy(cadastro[index1].email,cadastro[cont-1].email);
			strcpy(cadastro[index1].sexo,cadastro[cont-1].sexo);
			strcpy(cadastro[index1].endereco.logradouro,cadastro[cont-1].endereco.logradouro);
			cadastro[index1].endereco.numero=cadastro[cont-1].endereco.numero;
			strcpy(cadastro[index1].endereco.bairro,cadastro[cont-1].endereco.bairro);
			cadastro[index1].endereco.cep=cadastro[cont-1].endereco.cep;
			strcpy(cadastro[index1].endereco.uf,cadastro[cont-1].endereco.uf);
			cadastro[index1].altura=cadastro[cont-1].altura;
			cadastro[index1].vacina=cadastro[cont-1].vacina;
			cont--;
			ordenacaoInsercao(cadastro,cont); //Ordenar apos exclusao												
		break;
		case 7:
			//Realiza backup
 			bkpCont=backup(cadastro,cadastroBkp,cont);
 			cont=bkpCont;
		break;						
		}	
	}while(cont<1000);	
}

/*----------------Func�es-------------------*/
//Mostrar menu
int menu(){
	int opcao;
	printf("\n\n*** MENU ***\n\n");
	printf("1. Inclusao\n");
	printf("2. Listagem\n");
	printf("3. Consulta ID\n");
	printf("4. Consulta email\n");	
	printf("5. Alteracao\n");
	printf("6. Exclusao\n");
	printf("7. Backup\n");	
	printf("0. Sair\n\n");
	printf("Digite sua opcao: ");
	fflush(stdin);
	scanf("%d", &opcao);
	return opcao;	
}

//Realizar cadastro de vacinacao
void cadastrar(struct cadastroVacina *cadastro,int cont){
	//Gerar ID 
	int num;
	
	srand(time(NULL));   // Initialization, should only be called once.
	num=rand();      // Returns a pseudo-random integer between 0 and RAND_MAX.	
	printf("\nID = %d\n", num);
	cadastro[cont].id=num;
	
	//Gravar nome
	do{
	printf("\nInforme o nome: ");
	fflush(stdin);
	gets(cadastro[cont].nome);
	}while (strlen(cadastro[cont].nome)==0);
	//Gravar email	
	char *ptr;
	
	do{
		printf("\nInforme o email: ");
		fflush(stdin);
		gets(cadastro[cont].email);
		ptr = strstr(cadastro[cont].email, "@");
		if (ptr != NULL)
			printf("'%s' Contem '@'\n", cadastro[cont].email);			
	}while(ptr==NULL);
	
	//Gravar sexo
	do{
		printf("\nInforme o sexo: ");
		fflush(stdin);
		gets(cadastro[cont].sexo);
	}while((stricmp(cadastro[cont].sexo,"Masculino")!=0) && (stricmp(cadastro[cont].sexo,"Feminino")!=0) && (stricmp(cadastro[cont].sexo,"Nao declarar")!=0));		

	//Gravar endere�o
	do{
		printf("\nInforme o endereco: ");
		fflush(stdin);
		gets(cadastro[cont].endereco.logradouro);	
	}while (strlen(cadastro[cont].endereco.logradouro)==0);

	do{
		printf("\nInforme o numero da residencia: ");
		fflush(stdin);
		scanf("%d",&cadastro[cont].endereco.numero);	
	}while (cadastro[cont].endereco.numero<=0);
	
	do{
		printf("\nInforme o bairro: ");
		fflush(stdin);
		gets(cadastro[cont].endereco.bairro);	
	}while (strlen(cadastro[cont].endereco.bairro)==0);

	do{
		printf("\nInforme o CEP: ");
		fflush(stdin);
		scanf("%d",&cadastro[cont].endereco.cep);	
	}while (cadastro[cont].endereco.cep<=0);
	
	do{
		printf("\nInforme a unidade federativa: ");
		fflush(stdin);
		gets(cadastro[cont].endereco.uf);
	}while ((strlen(cadastro[cont].endereco.uf)==0)||(strlen(cadastro[cont].endereco.uf)>2));		
		
	//Gravar altura
	do{
	printf("\nDigite a altura:");
	fflush(stdin);
	scanf("%lf",&cadastro[cont].altura);
	}while((cadastro[cont].altura<1)||(cadastro[cont].altura>2));
	
	//Se tomou vacina
    int escolha;
    
    do{
    printf("\nTomou vacina? 1 - sim, 0 - nao \n");
    fflush(stdin);
    scanf("%d",&escolha);
    }while((escolha!=0)&&(escolha!=1));
    
    if(escolha==1)
    	cadastro[cont].vacina=true;
    if(escolha==0)	
    	cadastro[cont].vacina=false;
	ordenacaoInsercao(cadastro,cont); //Ordenar apos cadastro		    		
}

//Ordenacao Metodo Insercao
void ordenacaoInsercao(struct cadastroVacina *cadastro,int cont){
    int i, chave, j;
    for (i=1;i<cont;i++) {
        chave=cadastro[i].id;
        j=i-1;
 
        while (j>=0&&cadastro[j].id>chave){
            cadastro[j+1].id=cadastro[j].id;
			strcpy(cadastro[j+1].nome,cadastro[j].nome);
			strcpy(cadastro[j+1].email,cadastro[j].email);
			strcpy(cadastro[j+1].sexo,cadastro[j].sexo);
			strcpy(cadastro[j+1].endereco.logradouro,cadastro[j].endereco.logradouro);
			cadastro[j+1].endereco.numero=cadastro[j].endereco.numero;
			strcpy(cadastro[j+1].endereco.bairro,cadastro[j].endereco.bairro);
			cadastro[j+1].endereco.cep=cadastro[j].endereco.cep;
			strcpy(cadastro[j+1].endereco.uf,cadastro[j].endereco.uf);
			cadastro[j+1].altura=cadastro[j].altura;
			cadastro[j+1].vacina=cadastro[j].vacina;			         
            j=j-1;
        }
        cadastro[j+1].id=chave;
    }
}

//Listar 
void listar(struct cadastroVacina *cadastro,int cont){
	int i;
	for (i=0; i<cont; i++){
		printf("ID = %4d - Nome = %35s - Email = %35s - Sexo = %13s \nEndereco %35s, %d, %35s, %d, %2s - Altura = %.2f\n", cadastro[i].id, cadastro[i].nome, cadastro[i].email, cadastro[i].sexo, cadastro[i].endereco.logradouro, cadastro[i].endereco.numero, cadastro[i].endereco.bairro, cadastro[i].endereco.cep,cadastro[i].endereco.uf, cadastro[i].altura);
		printf(cadastro[i].vacina ? "Tomou vacina\n" : "Nao tomou vacina\n");	
	}
}

//Consultar Pesquisa Binaria
int consultar(struct cadastroVacina *cadastro,int esq, int dir, int idBusca){
    int meio;
	
	if(esq>dir)// Nao encontrado
		return -1;
	
	meio=(esq+dir)/2;
    
    if (cadastro[meio].id==idBusca) // Id busca esta no nomeio
        return meio;  
    else if (cadastro[meio].id > idBusca)
       return consultar(cadastro, esq, meio - 1, idBusca);// Idbusca esta na esquerda
	else
	   return consultar(cadastro, meio + 1, dir, idBusca);// Idbusca esta na direita   	
}

//Buscar email
void buscaEmail(struct cadastroVacina *cadastro,int cont){
	char string[35];
	int i;
	
	printf("Digite o email que deseja consultar: ");
	fflush(stdin);
	gets(string);

	for (i = 0; i <= cont; i++){
		if(strcmp(cadastro[i].email,string)==0){
			printf("ID = %4d - Nome = %35s - Email = %35s - Sexo = %13s \nEndereco %35s, %d, %35s, %d,%2s - Altura = %.2f\n", cadastro[i].id, cadastro[i].nome, cadastro[i].email, cadastro[i].sexo, cadastro[i].endereco.logradouro, cadastro[i].endereco.numero, cadastro[i].endereco.bairro, cadastro[i].endereco.cep, cadastro[i].endereco.uf, cadastro[i].altura);
			printf(cadastro[i].vacina ? "Tomou vacina\n" : "Nao tomou vacina\n");		
		}
	}
}

//Alterar cadastro
void alterar(struct cadastroVacina *cadastro,int cont){
	int esq=0, dir, index1, idBusca, i; //variaveis consulta binaria
	
	printf("Informe o ID que deseja alterar: ");
	fflush(stdin);
	scanf("%d",&idBusca);
	dir=cont;
	index1=consultar(cadastro,esq,dir-1,idBusca);
	(index1 == -1)?printf("Id nao encontrado."):cadastrar(cadastro,index1);
}

//Realizar Backup e Restore
int backup(struct cadastroVacina *cadastro, struct cadastroVacinaBkp *cadastroBkp,int cont){
	int opcao, bkpCont;
	
	printf("\n\n*** MENU DE BACKUP***\n\n");
	printf("1. Realizar Backup\n");
	printf("2. Realizar Restore\n");		
	printf("0. Sair\n\n");
	printf("Digite sua opcao: ");
	fflush(stdin);
	scanf("%d", &opcao);
	
	switch (opcao){
		case 0:
		return;		
		break;
		case 1:
			//Realiza backup
			cadastroBkp->id=cadastro->id;
			cadastroBkp->endereco.numero=cadastro->endereco.numero;
			cadastroBkp->endereco.cep=cadastro->endereco.cep;
			cadastroBkp->altura=cadastro->altura;
			cadastroBkp->vacina=cadastro->vacina;
			strcpy(cadastro->nome,cadastroBkp->nome);
			strcpy(cadastro->email,cadastroBkp->email);
			strcpy(cadastro->sexo,cadastroBkp->sexo);
			strcpy(cadastro->endereco.logradouro,cadastroBkp->endereco.logradouro);		
			strcpy(cadastro->endereco.bairro,cadastroBkp->endereco.bairro);
			strcpy(cadastro->endereco.uf,cadastroBkp->endereco.uf);			
			bkpCont=cont;				
		break;
		case 2:
			//Realiza restore
			cadastro->id=cadastroBkp->id;
			cadastro->endereco.numero=cadastroBkp->endereco.numero;
			cadastro->endereco.cep=cadastroBkp->endereco.cep;
			cadastro->altura=cadastroBkp->altura;
			cadastro->vacina=cadastroBkp->vacina;
			strcpy(cadastroBkp->nome,cadastro->nome);
			strcpy(cadastroBkp->email,cadastro->email);
			strcpy(cadastroBkp->sexo,cadastro->sexo);
			strcpy(cadastroBkp->endereco.logradouro,cadastro->endereco.logradouro);		
			strcpy(cadastroBkp->endereco.bairro,cadastro->endereco.bairro);
			strcpy(cadastroBkp->endereco.uf,cadastro->endereco.uf);						
			return bkpCont;
		break;
	}
}

