#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


void AbrirInv();
void MostrarProd();
void Actualizar();
void EliminarProd();
void MaStock();
void MenoStock();
int EsNumero(char num[]);
int OPM,j=1,i=0;
char N,M;

typedef struct EstructuraProd{
	int id;
	char nombre[100];
	char cod[10];
	float precio;
	int cant;
	float total;
}EstructuraProd;
	
EstructuraProd inventario[100];

EstructuraProd AgregarProd(int idp){
	EstructuraProd inventario;
	char stock[10];
	FILE *Invt;
	FILE *InvtFinal;
	
	//INVENTARIO
	InvtFinal=fopen("Datos/InventarioFinal.txt","a");
	
	//DECLARA ERROR AL ABRIR ARCHIVO
	if( InvtFinal )
		printf("\n\tLista InventarioFinal.txt (ABIERTO)\n");
	else{
		printf("\n\tERROR InventarioFinal.txt (NO ABIERTO)\n");	
	}
	//
	
	//INVENTARIO
	Invt=fopen("Datos/inventario.txt","a");
	
	//DECLARA ERROR AL ABRIR ARCHIVO
	if( Invt )
		printf("\n\tLista inventario.txt (ABIERTO)\n");
	else{
		printf("\n\tERROR inventario.txt (NO ABIERTO)\n");	
	}
	//
	
	//idp == ID DEL PRODUCTO
	inventario.id = idp;
	printf("\n\t\tIngrese los siguientes datos");
	printf("\n\t\tPRODUCTO: ");
	
	//Obtener Enter
	while(getchar()!='\n');
	fgets(inventario.nombre,100,stdin);
	strcpy(inventario.nombre,strtok(inventario.nombre,"\n"));
	printf("\n\t\tLOTE: ");
	scanf("%s",inventario.cod);
	do{
		printf("\n\t\tSTOCK: ");
		scanf("%s",stock);
		N = EsNumero(stock);
	}while(N==0);
	
	inventario.cant = atoi(stock);
	
	printf("\n\t\tPRECIO DE COMPRA: "); 
	scanf("%f",&inventario.precio);
	
	inventario.total = inventario.cant * inventario.precio;
	
	fprintf(Invt,"\n%d %s\n%d %f %f %s",inventario.id,inventario.nombre,inventario.cant,inventario.precio,inventario.total,inventario.cod);
	fprintf(InvtFinal,"\n%d %s %s %d %f %f",inventario.id,inventario.nombre,inventario.cod,inventario.cant,inventario.precio,inventario.total);
	
	//ERROR DURANTE LA ESCRITURA
	if(ferror(InvtFinal)){
		printf("Error de escritura InvtFinal.txt");
	}
	fclose(InvtFinal);
	//
	
	
	//ERROR DURANTE LA ESCRITURA
	if(ferror(doc)){
		printf("Error de escritura InvtFinal.txt");
	}
	fclose(InvtFinal);
	//
	
	fclose(Invt);
	
	return inventario;
}

int main(void) {
	AbrirInv();
	int decision;
	do{
		char opcion[10];
		int Anum, Anum2;
		printf("\n\t---------- BIENVENIDO ----------");
		printf("\n\n\t1. Lista de productos ");
		printf("\n\t2. Carrito de compras ");
		printf("\n\t3. Agregar productos ");
		printf("\n\t4. Eliminar producto ");
		printf("\n\t5. Inventario ");
		printf("\n\t6. Modificar stock ");
		printf("\n\t7. Cerrar programa  ");
		printf("\n\n\t---------------------------------");
		do{
			printf("\n\n\tIngrese su eleccion: ");
			scanf("%s",opcion);
			N=EsNumero(opcion);
		}while(N==0);
		Anum=atoi(opcion);
		switch(Anum){
			case 1:{
				int Anum3,BusId;
				printf("\n\t---------- PRODUCTOS ----------");
				printf("\n\t1. Despensa y Bodega ");
				printf("\n\t2. Bebé ");
				printf("\n\t3. Cuidado del hogar ");
				printf("\n\t4. Cuidado personal ");
				printf("\n\t5. Bebidas ");
				printf("\n\t6. Refrigerados ");
				printf("\n\t7. Cerrar programa  ");
				printf("\n\n\t---------------------------------");
				do{
					printf("\n\tIngrese su eleccion: ");
					scanf("%s",opcion);
					N=EsNumero(opcion);
				}while(N==0);
				Anum2=atoi(opcion);
				MostrarProd(Anum2);
				printf("\n\tComprar=1");
				printf("\n\tAgregar a carrito=2\n");
				scanf("\n- %d",&decision);
				if(decision==1){
					do{
						printf("\n\tIngrese su eleccion: ");
						scanf("%s",opcion);
						N=EsNumero(opcion);
					}while(N==0);
					Anum3=atoi(opcion);
					for(i=1;i<j;i++){
						if(Anum3==inventario[i].id){BusId=i;} 
					}
					if(BusId==0){printf("\n\t\t\t ¡El producto no existe!");
					}else{
						printf("\n\n\t-------------------------------------------------");
						printf("\n\tID\tPRODUCTO\t\tCODIGO\tSTOCK\tPRECIO");
						printf("\n\t%d\t%s\t\t%s\t%d\t%.2f$\t%.2f$",inventario[BusId].id,inventario[BusId].nombre,inventario[BusId].cod,inventario[BusId].cant,inventario[BusId].precio);
						printf("\n\n\t-------------------------------------------------");
					}
					printf("\n\n\t\t¡¡GRACIAS POR SU COMPRA!!\n");
				}  
				break;
			}
			case 2:{
				break;
			}
			case 3:{
				printf("\n\t---------- AGREGAR PRODUCTO ----------");
				inventario[j]=AgregarProd(j);

				j++;
				break;
			}
			case 4:{
				printf("\n\t---------- ELIMINAR PRODUCTO ----------");
				EliminarProd();
				break;
			}
			case 5:{
				float tot=0;
				printf("\n\t---------- PRODUCTOS EXISTENTES EN BODEGA ----------");
				printf("\n\n\t-------------------------------------------------");
				printf("\n\tID\t PRODUCTO\t\tCODIGO\tSTOCK\tPRECIO\tTOTAL");
				printf("\n\n\t-------------------------------------------------");
				for(i=1;i<j;i++){
					printf("\n\t%d\t%s\t\t%s\t%d\t%.2f$\t%.2f$",inventario[i].id,inventario[i].nombre,inventario[i].cod,inventario[i].cant,inventario[i].precio,inventario[i].total);
					tot=tot+inventario[i].total;
				}
				printf("\n\n\t-------------------------------------------------");
				printf("\n\t\t\t\t\tTotal en bodega: %.2f$",tot);
				printf("\n\n\t-------------------------------------------------");
				printf("\n\tRegresar=1");
				printf("\n\tCerrar=2\n");
				scanf("\n- %d",&decision);
				break;
			}
			case 6:{
				char en[10];
				printf("\n\t---------- ENTRADAS  Y SALIDAS DE PRODUCTOS ----------");
				printf("\n\t1.-Ingresar cantidad");
				printf("\n\t2.-Restar cantidad");
				printf("\n\n\t-------------------------------------------------");
				do{
					printf("\n\tSelecciones una opcion: ");
					scanf("%s",en);
					N=EsNumero(en);
				}while(N==0);
				Anum2=atoi(en);
				if(Anum2==1){MaStock();
				}else if(Anum2==2){MenoStock();
				}else{printf("\n\t\t\t ***** La opcion no existe ****");}
				break;
			}
			case 7:{
				printf("\n\t---------- HASTA PRONTO ----------");
				exit(0);
				break;
			}
			case 8:{
				int buscar,BusId;
				printf("\n\t---------- BUSQUEDA DE PRODUCTOS ----------");
				printf("\n\tIngrese el id del Producto: ");
				scanf("%d",&buscar);
				for(i=1;i<j;i++){
					if(buscar==inventario[i].id){BusId=i;} 
				}
				if(BusId==0){printf("\n\t\t\t ¡El producto no existe!");
				}else{
					printf("\n\n\t-------------------------------------------------");
					printf("\n\tID\t\tPRODUCTO\t\tCODIGO\t\tSTOCK\t\tPRECIO\t\tTOTAL");
					printf("\n\t%d\t\t%s\t\t%s\t\t\t%d\t\t\t%.2f$\t\t%.2f$",inventario[BusId].id,inventario[BusId].nombre,inventario[BusId].cod,inventario[BusId].cant,inventario[BusId].precio,inventario[BusId].total);
					printf("\n\n\t-------------------------------------------------");
					printf("\n\t\tDesea regresar al menu anterior?");
					printf("\n\t1.-SI: ");
					scanf("%d",&decision);
				}
				break;
			}
			default:printf("\n\t\t ***** La opcion no existe *****");
		}
	}while(decision==1);
	return 0;
}
	
void MostrarProd(int Anum2){
	AbrirInv();
	if (Anum2==7){
	printf("\n\t\t\t***** HASTA PRONTO *****");
	exit(0);
	}else if ((Anum2>0)&&(Anum2<7)){
	int d,h;
	switch(Anum2){
	case 1:{
		d=1;
		h=10;
		printf("\n\t---------- PRODUCTOS DESPENSA Y BODEGA ----------");
		break;
	}
	case 2:{
		d=10;
		h=15;
		printf("\n\t---------- PRODUCTOS BEBÉ ----------");
		break;
	}
	case 3:{
		d=15;
		h=20;
		printf("\n\t---------- PRODUCTOS CUIDADO DEL HOGAR ----------");
		break;
	}		
	case 4:{
		d=20;
		h=25;
		printf("\n\t---------- PRODUCTOS CUIDADO PERSONAL ----------");
		break;
	}
	case 5:{
		d=25;
		h=30;
		printf("\n\t---------- PRODUCTOS BEBIDAS ----------");
		break;
	}
	case 6:{
		d=30;
		h=35;
		printf("\n\t---------- PRODUCTOS REFRIGERADOS ----------");
		break;
	}	
	}
	printf("\n\n\t-------------------------------------------------");
	printf("\n\tCOD\tPRODUCTO\t\tLOTE\tSTOCK\tPRECIO\tTOTAL");
	printf("\n\n\t-------------------------------------------------");
	for(i=d;i<h;i++){
	printf("\n\t%d\t%s\t\t%s\t%d\t%.2f$\t%.2f$",inventario[i].id,inventario[i].nombre,inventario[i].cod,inventario[i].cant,inventario[i].precio,inventario[i].total);
	}
	printf("\n\n\t-------------------------------------------------");
	}else { printf("\n\t\t ***** La opcion no existe *****");}
}

void AbrirInv(){
	FILE *abrir;
	abrir=fopen("Datos/inventario.txt","r");
	if (abrir!=NULL){
	while(feof(abrir)==0){
	fscanf(abrir,"%d",&inventario[j].id);
	fgets(inventario[j].nombre,100,abrir);
	strcpy(inventario[j].nombre,strtok(inventario[j].nombre,"\n"));
	fscanf(abrir,"%d",&inventario[j].cant);
	fscanf(abrir,"%f",&inventario[j].precio);
	fscanf(abrir,"%f",&inventario[j].total);
	fscanf(abrir,"%s",inventario[j].cod);

	j++;
	}
	fclose(abrir);
	} 
}


void MaStock(){
	int I;
	char mas[10];
	printf("\n\t---------- PRODUCTOS EXISTENTES EN BODEGA ----------");
	printf("\n\n\t-------------------------------------------------");
	printf("\n\tCOD\tPRODUCTO\t\tLOTE\tSTOCK\tPRECIO\tTOTAL");
	for(i=1;i<j;i++){
		printf("\n\t%d\t\t%s\t%s\t%d\t%.2f$\t%.2f$",inventario[i].id,inventario[i].nombre,inventario[i].cod,inventario[i].cant,inventario[i].precio,inventario[i].total);
	}
	printf("\n\n\t-------------------------------------------------");
	printf("\n\t\tIngrese el id del Producto a agregar stock: ");
	scanf("%d",&I);
	printf("\n\t\tProducto seleccionado: %s",inventario[I].nombre);
	do{
		printf("\n\t\tIngrese la cantidad a agregar: ");
		scanf("%s",mas);
		N=EsNumero(mas);
	}while(N==0);
	inventario[I].cant=inventario[I].cant+atoi(mas);
	inventario[I].total=inventario[I].cant*inventario[I].precio;
	Actualizar();
}

void MenoStock(){
	int I;
	char menos[10];
	printf("\n\t---------- PRODUCTOS EXISTENTES EN BODEGA ----------");
	printf("\n\n\t-------------------------------------------------");
	printf("\n\tCOD\t\tPRODUCTO\t\tLOTE\t\tSTOCK\t\tPRECIO\t\tTOTAL");
	for(i=1;i<j;i++){
		printf("\n\t%d\t\t%s\t\t%s\t\t\t%d\t\t\t%.2f$\t\t%.2f$",inventario[i].id,inventario[i].nombre,inventario[i].cod,inventario[i].cant,inventario[i].precio,inventario[i].total);
	}
	printf("\n\n\t-------------------------------------------------");
	printf("\n\t\tIngrese el codigo del Producto a restar stock: ");
	scanf("%d",&I);
	printf("\n\t\tProducto seleccionado: %s",inventario[I].nombre);
	do{
		printf("\n\t\tIngrese la cantidad a restar: ");
		scanf("%s",menos);
		N=EsNumero(menos);
	}while(N==0);
	inventario[I].cant=inventario[I].cant-atoi(menos);
	inventario[I].total=inventario[I].cant*inventario[I].precio;
	Actualizar();
}

void Actualizar(){
	int A;
	FILE *ActualInvt;
	FILE *NuevoInvt;
	if(remove("Datos/inventario.txt")==0){
		ActualInvt=fopen("Datos/inventario.txt","a");
	remove("Datos/InventarioFinal.txt");
	NuevoInvt=fopen("Datos/InventarioFinal.txt","a");
	for(A=1;A<j;A++){
	  fprintf(ActualInvt," %d %s\n%d %f %f %s",inventario[A].id,inventario[A].nombre,inventario[A].cant,inventario[A].precio,inventario[A].total,inventario[A].cod);
	  fprintf(NuevoInvt,"\n%d %s %s %d %f %f",inventario[A].id,inventario[A].nombre,inventario[A].cod,inventario[A].cant,inventario[A].precio,inventario[A].total);
	}}
	fclose(NuevoInvt);
	fclose(ActualInvt);
}

void EliminarProd(){
	int A,B;
	printf("\n\t---------- PRODUCTOS EXISTENTES EN BODEGA ----------");
	printf("\n\n\t-------------------------------------------------");
	printf("\n\tID\tPRODUCTO\t\tLOTE\tSTOCK\tPRECIO\tTOTAL");
	for(i=1;i<j;i++){
	printf("\n\t%d\t%s\t\t%s\t%d\t%.2f$\t%.2f$",inventario[i].id,inventario[i].nombre,inventario[i].cod,inventario[i].cant,inventario[i].precio,inventario[i].total);
	}
	printf("\n\n\t-------------------------------------------------");
	printf("\n\tIngrese el codigo del producto a eliminar: ");
	scanf("%d",&A);
	printf("\n\tProducto seleccionado: %s",inventario[A].nombre);
	printf("\n\tEsta segudo de eliminar el producto? 1.-Si 2.-No: ");
	scanf("%d",&B);
	if(B==1){
	for(i=1;i<j;i++){
	  if(i==A){
		while(i<=j-1){
			inventario[i].id=inventario[i].id;
		  strcpy(inventario[i].nombre,inventario[i+1].nombre);
		  inventario[i].cant=inventario[i+1].cant;
		  inventario[i].total=inventario[i+1].total;
		  strcpy(inventario[i].cod,inventario[i+1].cod);
		  inventario[i].precio=inventario[i+1].precio;
		  i++;
		}
		break;
	  }
	}
	j=j-1;
	printf("\n\t\t\t***** PRODUCTOS EXISTENTES EN BODEGA *****");
	printf("\n\n\t-------------------------------------------------");
	printf("\n\tID\t\tPRODUCTO\t\tLOTE\t\tSTOCK\t\tPRECIO\t\tTOTAL");
	for(i=1;i<j;i++){
	printf("\n\t%d\t\t%s\t\t%s\t\t%d\t\t%.2f$\t\t%.2f$",inventario[i].id,inventario[i].nombre,inventario[i].cod,inventario[i].cant,inventario[i].precio,inventario[i].total);
	}
	printf("\n\n\t-------------------------------------------------");
	}else{
	  printf("\n\t\tNo se elimino el Producto");
	}
	Actualizar();
}

int EsNumero(char num[])
{
	int i;
	for(i=0; i<strlen(num); i++)
	{
		if(!(isdigit(num[i])))
		{
			printf("\n\t¡Ingresa solo NUMEROS!\n");
			return 0;
		}
	}
	return 1;
}
