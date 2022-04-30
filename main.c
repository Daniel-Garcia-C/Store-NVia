#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define LISTAPRODUCTOS 1
#define CARRITO 2
#define AGREGARPRODUCTO 3
#define CERRAR 6

FILE *inventario;

typedef struct structProduct{
	int ID;
	char    nombre[30];
	int     cantidad;		
	float 	precio;
}structProduct;

structProduct cProducto[100];

int mostrarMenuDeOpciones(){
	// MENU DE OPCIONES DE ARTICULOS
	int opcion;
	
	printf("\n     -----------------------------");
	
	printf("\n\t     Tienda NVia\n");
	printf("\n\t1. Lista de productos ");
	printf("\n\t2. Carrito de compras ");
	printf("\n\t3. Agregar productos ");
	printf("\n\t4. Eliminar producto ");
	printf("\n\t5. Agregar nuevo catalogo ");
	printf("\n\t6. Cerrar programa  ");
	
	printf("\n     -----------------------------");
	
	printf("\n\tEscoja el servicio: ");
	scanf("%d", &opcion);
	
	if(opcion <= 6 && opcion >= 1){
		return opcion;
	}
	return CERRAR;
}
	
void agregarProducto(){
		
	FILE* inventario;
	struct structProduct producto;
	inventario = fopen("ListaProductos.dat", "ab");
	//ELIMINA LA BASURA QUE ALMACENA EN .dat 
	memset(&producto, 0, sizeof(struct structProduct));
		
	//DECLARA ERROR AL ABRIR ARCHIVO
	if( inventario )
		printf("\n\tLista ListaProductos.txt (ABIERTO)\n");
	else{
		printf("\n\tERROR ListaProductos.txt (NO ABIERTO)\n");	
	}

	fflush(stdin);
	printf("\nIngrese ID:");
	scanf("%d", &producto.ID); //TOMAR ID DEL ÚLTIMO PRODUCTO

	printf("\nIngrese Nombre:");
	scanf("%s", producto.nombre);
		
	do{
		printf("\nIngrese Cantidad:");
		scanf("%d", &producto.cantidad);
	}while(producto.cantidad == 0);

	printf("\nIngrese Precio:");
	scanf("%f", &producto.precio);
	
	fwrite(&producto, sizeof(producto), 1, inventario);

	if( !fclose( inventario ) )
		printf( "\nFichero cerrado\n" );
	else{
		printf( "\nError: fichero NO CERRADO\n" );
	}
}
	
	
void mostrarInventario(){
	
	FILE* inventario;
	
	structProduct producto;
	
	inventario = fopen("ListaProductos.dat", "rb");
	
	if(inventario == NULL){
		printf("Error: No se ha podido abrir el archivo\n");
	}
	else{
		//Mostrar todos los productos
		printf("\n    ------------------------------------------------------");
		printf("\n\tID\tNombre\t\tCantidad\tPrecio\n");
		printf("\n    ------------------------------------------------------");
		while(1){
		fread(&producto, sizeof(producto), 1, inventario);
		
		if(feof(inventario)){
			break;
		}
		printf("\n\t%d\t", producto.ID);
		
		printf("%s\t\t", producto.nombre);
	
		printf("   %d\t", producto.cantidad);
		
		printf("\t%0.2f\n\n", producto.precio);
		}
		printf("\n    ------------------------------------------------------");
		fclose(inventario);
	}
	
}
		
int main(int argc, char *argv[]) {
	
	int cerrar;
	
	do{
		switch(mostrarMenuDeOpciones()){
		case LISTAPRODUCTOS:
			
			printf("\n\t\t\tLista de Productos\n");
			
			mostrarInventario();
			
			break;
		case AGREGARPRODUCTO:
			printf("\n\tAgregar Producto");
			
			agregarProducto();
			
			break;
		case CARRITO:
			printf("\nCarrito de Compras");
			
			inventario = fopen("ListaProductos.txt", "rb+");
			
			/*carritoDeCompras(doc);*/
			
			if( !fclose(inventario) ){
				printf( "\nFichero cerrado\n" ); //CIERRE CORRECTAMENTE
			}
			else{
				printf( "\nError: fichero NO CERRADO\n" );
				return FALSE; //ERROR DURANTE CIERRE DOCUMENTO
			}
			
			break;
		case CERRAR:
			cerrar = TRUE;
			break;
		}
	}while((cerrar != TRUE));

	return 0;
}
		