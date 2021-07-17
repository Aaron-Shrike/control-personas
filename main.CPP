#include "basicas.CPP"

#define MAXdni 9
#define MAXsexo 2
#define MAXregion 3
#define DELTA 10

struct Persona
{
	char DNI[MAXdni];
   char nombre[LIM];
   char apellidop[LIM];
   char apellidom[LIM];
   int edad;
   int sexo;
   int region;
   int nacimiento;
   int vencimiento;
   char padre[LIM];
   char madre[LIM];
};

char Tsexo[MAXsexo][LIM]={"Masculino","Femenino"};
char Tregion[MAXregion][LIM]={"Norte","Centro","Sur"};

void iniciaPersona(Persona &P)
{
	P.DNI[0]=NULL;
   P.nombre[0]=NULL;
   P.apellidop[0]=NULL;
   P.apellidom[0]=NULL;
   P.edad=0;
   P.sexo=0;
   P.region=0;
   P.nacimiento=0;
   P.vencimiento=0;
   P.padre[0]=NULL;
   P.madre[0]=NULL;
}

void leePersona(Persona &P)
{
	do{
   	printf("\nIngrese numero de DNI(8 caracteres): ");
      fflush(stdin);
      gets(P.DNI);
   }while(!(strlen(P.DNI)==MAXdni-1));
   printf("\nIngrese nombre: ");
   fflush(stdin);
   gets(P.nombre);
   printf("\nIngrese apellido paterno: ");
   fflush(stdin);
   gets(P.apellidop);
   printf("\nIngrese apellido materno: ");
   fflush(stdin);
   gets(P.apellidom);
   P.edad=leeEntero("\nIngrese edad[1-150]: ",1,150);
   P.sexo=validaTabla("\nIngrese sexo: ",Tsexo,MAXsexo);
   P.region=validaTabla("\nIngrese region: ",Tregion,MAXregion);
   P.nacimiento=leeEntero("\nIngrese anio de nacimiento[1900-2018]: ",1900,2018);
   P.vencimiento=leeEntero("\nIngrese anio de vencimiento(DNI)[1920-2030]: ",1920,2038);
   printf("\nIngrese nombre del padre: ");
   fflush(stdin);
   gets(P.padre);
   printf("\nIngrese nombre de la madre: ");
   fflush(stdin);
   gets(P.madre);
}

void mostrarPersona(Persona &P)
{
	printf("\nNumero de DNI: %s",P.DNI);
   printf("\nNombre: %s",P.nombre);
   printf("\nApellido paterno: %s",P.apellidop);
   printf("\nApellido materno: %s",P.apellidom);
   printf("\nEdad: %d",P.edad);
   printf("\nSexo: %s",Tsexo[P.sexo-1]);
   printf("\nRegion: %s",Tregion[P.region-1]);
   printf("\nAnio de nacimiento: %d",P.nacimiento);
   printf("\nAnio de vencimiento: %d",P.vencimiento);
   printf("\nNombre del padre: %s",P.padre);
   printf("\nNombre de la madre: %s",P.madre);
}

struct listaPersona
{
	Persona *DATA;
   int N;
   int Max;
};

void iniciaListaPersonas(listaPersona &LP)
{
	LP.DATA=NULL;
   LP.N=0;
   LP.Max=0;
}

void crece(listaPersona &LP)
{
	Persona *Temp;

   Temp=new Persona[LP.Max+DELTA];
   for(int i=0;i<LP.N;i++)
   	Temp[i]=LP.DATA[i];
   delete[] LP.DATA;
   LP.DATA=Temp;
   LP.Max+=DELTA;
}

void insertar(listaPersona &LP,Persona &P)
{
	if(LP.N==LP.Max)
		crece(LP);
	LP.DATA[LP.N]=P;
	LP.N++;
}

void leeListaPersonas(listaPersona &LP)
{
   Persona P;
	do{
      iniciaPersona(P);
   	leePersona(P);
      insertar(LP,P);
   }while(!(continuar("\nDesea continuar(S/N): ")=='N'));
}

void mostrarListaPersonas(listaPersona &LP)
{
	if(LP.N>0)
   {
   	for(int i=0;i<LP.N;i++)
      {
      	printf("\nPersona [%d]",i+1);
         mostrarPersona(LP.DATA[i]);
      }
   }
   else
   	printf("\nNo hay datos...");
}

void liberarListaPersona(listaPersona &LP)
{
 	delete[] LP.DATA;
}

//Reportes
void reporteuno(listaPersona &LP)
{
   int flag=0;
   char nombrepadre[LIM],nombremadre[LIM];

   nombrepadre[0]=NULL;
   nombremadre[0]=NULL;
	if(LP.N>0)
   {
      printf("\nIngrese nombre del padre: ");
   	gets(nombrepadre);
      printf("\nIngrese nombre de la madre: ");
      gets(nombremadre);
      for(int i=0;i<LP.N;i++)
      	if(stricmp(LP.DATA[i].padre,nombrepadre)==0 && stricmp(LP.DATA[i].madre,nombremadre)==0)
         {
         	printf("\nPersona [i]",i+1);
         	mostrarPersona(LP.DATA[i]);
            flag=1;
         }
      if(flag==0)
      	printf("\nNo tiene hijos registrados.");
   }
   else
   	printf("\nNo hay datos...");
}

void reportedos(listaPersona &LP)
{
   int flag=0;
   
	if(LP.N>0)
   {
   	for(int i=0;i<LP.N;i++)
      	if(LP.DATA[i].vencimiento==2018)
         {
         	printf("\nPersona [%d]",i+1);
         	mostrarPersona(LP.DATA[i]);
            flag=1;
         }
      if(flag==0)
      	printf("\nNo hay personas.");
   }
   else
   	printf("\nNo hay datos...");
}

void reportetres(listaPersona &LP)
{
   int suma[MAXsexo],cont[MAXsexo];
   float prom[MAXsexo];
   iniciaVE(cont,MAXsexo);
   iniciaVE(suma,MAXsexo);
   iniciaVR(prom,MAXsexo);

	if(LP.N>0)
   {
   	for(int i=0;i<LP.N;i++)
      {
      	suma[LP.DATA[i].sexo-1]+=LP.DATA[i].edad;
      	cont[LP.DATA[i].sexo-1]++;
      }
      for(int i=0;i<MAXsexo;i++)
      	if(cont[i]>0)
         	prom[i]=(float)suma[i]/cont[i];
      for(int i=0;i<MAXsexo;i++)
      	printf("Promedio de edad %s: %f",Tsexo[i],prom[i]);
   }
   else
   	printf("\nNo hay datos...");
}

void reportecuatro(listaPersona &LP)
{
   int cont[MAXregion],flag=0;
   iniciaVE(cont,MAXregion);

	if(LP.N>0)
   {
   	for(int i=0;i<LP.N;i++)
      {
      	cont[LP.DATA[i].region-1]++;
      	flag=1;
      }
      for(int i=0;i<MAXregion;i++)
      	if(flag==1)
      		printf("\nNumero de personas(%s): %d",Tregion[i],cont[i]);
      	else
      		printf("\nNo hay personas(%s).",Tregion[i]);
   }
   else
   	printf("\nNo hay datos...");
}

void reportecinco(listaPersona &LP)
{
   int region,flag=0;
   Persona aux;

	if(LP.N>0)
   {
      region=validaTabla("\nIngrese region: ",Tregion,MAXregion);
      for(int i=0;i<LP.N-1;i++)
        for(int j=i+1;j<LP.N;j++)
				if(strcmp(LP.DATA[i].nombre,LP.DATA[j].nombre)>0)
        		{
            	aux=LP.DATA[i];
            	LP.DATA[i]=LP.DATA[j];
            	LP.DATA[j]=aux;
        		}
   	for(int i=0;i<LP.N;i++)
      	if(LP.DATA[i].region==region)
         {
         	printf("\nPersona [i]",i+1);
         	mostrarPersona(LP.DATA[i]);
            flag=1;
         }
      if(flag==0)
      	printf("\nNo hay personas de la region ingresada");
   }
   else
   	printf("\nNo hay datos...");
}

void menu(listaPersona &LP)
{
	int opc;
   do{
	printf("\n\n\n*** MENU ***");
   	printf("\n1. Lectura");
   	printf("\n2. Mostrar");
   	printf("\n3. Dado el nombre del padre y de la madre mostrar sus hijos registrados.");
   	printf("\n4. Mostrar las personas de las que vence su DNI este anio(2018).");
   	printf("\n5. Mostrar el promedio de edad por sexo.");
   	printf("\n6. Mostrar el numero de personas por region.");
   	printf("\n7. Dada la region mostrar las personas ordenadas por nombre.");
   	printf("\n8. Salir");
      opc=leeEntero("\nIngrese opcion: ",1,8);
      switch(opc)
      {
      	case 1:	leeListaPersonas(LP);
         	break;
         case 2:	mostrarListaPersonas(LP);
         	break;
         case 3:	reporteuno(LP);
         	break;
         case 4:	reportedos(LP);
         	break;
         case 5:  reportetres(LP);
         	break;
         case 6:  reportecuatro(LP);
         	break;
         case 7: 	reportecinco(LP);
         	break;
         case 8: 	liberarListaPersona(LP);
         	break;
      }
   }while(opc!=9);
}

int main()
{
	listaPersona LP;

   iniciaListaPersonas(LP);
   menu(LP);
   return 1;
}
