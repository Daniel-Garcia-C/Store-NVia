#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define LISTAPRODUCTOS 1
#define CARRITO 2
#define AGREGARPRODUCTO 3
#define CERRAR 6

FILE *doc;

typedef struct producto{
	char    nombre[30];
	int     cantidad;
	float   precio;
}PRODUCTO;

int mostrarMenuDeOpciones(){
	// MENU DE OPCIONES DE ARTICULOS
	int opcion;
	
	printf("\nTienda NVia");
	printf("\n1. Lista de productos ");
	printf("\n2. Carrito de compras ");
	printf("\n3. Agregar productos ");
	printf("\n4. Eliminar producto ");
	printf("\n5. Agregar nuevo catalogo ");
	printf("\n6. Cerrar programa  ");
	
	printf("\nEscoja el servicio: ");
	scanf("%d", &opcion);
	
	return opcion;
}
	
int agregarProducto(FILE *doc){

	PRODUCTO elm;

	if( doc )
		printf("\nLista (ABIERTO)\n");
	else{
		printf("\nERROR (NO ABIERTO)\n");	//ERROR AL ABRIR ARCHIVO
		return FALSE;
	}

	//ENTRADA DE DATOS DEL PRODUCTO
	printf("\nNombre: ");
	fflush(stdin);
	scanf("%s", elm.nombre);

	printf("\nCantidad: ");
	fflush(stdin);
	scanf("%d", &elm.cantidad);

	printf("\nPrecio: ");
	fflush(stdin);
	scanf("%f", &elm.precio);

	fseek(doc, 0L, SEEK_END); //POSICIONA AL FINAL DEL CARÁCTER
	fprintf(doc, "%s\t", elm.nombre);
	fseek(doc, 0L, SEEK_END);
	fprintf(doc, "%d\t", elm.cantidad); //ESCRITURA AL .txt
	fseek(doc, 0L, SEEK_END);
	fprintf(doc, "%f\n", elm.precio);

	/*printf("1: %d",sizeof(PRODUCTO));*/

	fflush(stdin);

	if(ferror(doc)){
	printf("Error de escritura");//ERROR DURANTE LA ESCRITURA
	}
	return TRUE;

	if( !fclose(doc) ){
		printf( "\nFichero cerrado\n" ); //CIERRE CORRECTAMENTE
	}
	else{
		printf( "\nError: fichero NO CERRADO\n" );
		return FALSE; //ERROR DURANTE CIERRE DOCUMENTO
	}
}

	int mostrarNotas(){

	char cadena[100];
	int nLinea = 0;

	doc = fopen("ListaProductos.txt", "rb+");
		printf("\nLista Productos:");
		
		if( doc ){
			printf( "\nExiste (ABIERTO)\n" );
			return TRUE;
		}
		else{
			printf( "\nError (NO ABIERTO)\n" ); //ERROR AL ABRIR ARCHIVO
			return FALSE;
		}

		printf("Producto:\tCantidad\tPrecio");

		while(fgets(cadena, sizeof(cadena), doc)){
			printf("\t%d",nLinea);
			nLinea++;
		}	

		if(ferror(doc)){
			printf("Error de escritura");
			return FALSE;//ERROR DURANTE LA ESCRITURA
		}
		return TRUE; 

	}

int carritoDeCompras(){

	char response;
	PRODUCTO art;

	doc = fopen("ListaProductos.txt", "rb+");
	printf("\nLista Productos:");
	if( doc )
		printf( "\nExiste (ABIERTO)\n" );
	else{
		printf( "\nError (NO ABIERTO)\n" );
		return 1;
		}
	
	mostrarNotas();

	/*fread(PRODUCTO,sizeof(PRODUCTO),1,doc);*/

	/*printf("%s\n %d\n %f\n", fgets(art.nombre, , doc));*/

	/*fprintf("%s",fgets(art.nombre,20,doc));*/

	fclose(doc);
	
	doc = fopen("CarritoUsuario.txt", "a+");
	
	printf("\nCreado el carrito de compras");
	
        fprintf(doc, "%s ", art.nombre);
		fprintf(doc, "%d ", art.cantidad);
		fprintf(doc, "%f", art.precio);

		printf("\n¿Ingresar otro articulo? [s/n]");
		response = getchar();
		fflush(stdin);

		if(response == 's' || response == 'S'){
			
		}
		else{
			printf("\nPagar Ahora [s/n]");
			response = getchar();
		}

		if(response == 'n' || response == 'N'){

			return FALSE;
		}

		fclose(doc);

			return TRUE;
		}

int main(int argc, char *argv[]) {

	int cerrar;

	do{
		switch(mostrarMenuDeOpciones()){
			case LISTAPRODUCTOS:
				mostrarNotas();
			break;
			case AGREGARPRODUCTO:
				printf("\nAgregar Producto");
				doc = fopen("ListaProductos.txt", "rb+");

				agregarProducto(doc);

				if( !fclose(doc) )
					printf( "\nFichero cerrado\n" );
				else{
					printf( "\nError: fichero NO CERRADO\n" );
					return 1; //ERROR DURANTE CIERRE DOCUMENTO
					}
			break;
			case CARRITO:
				printf("\nCarrito de Compras");
					doc = fopen("ListaProductos.txt", "rb+");
					
					carritoDeCompras(doc);
					
			break;
			case CERRAR:
				cerrar = TRUE;
			break;
		}
	}while(cerrar = TRUE);

return 0;
}
