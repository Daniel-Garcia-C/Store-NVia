#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Definido valores para orientar mejor función main() el switch 
#define TRUE 1
#define FALSE 0
#define LISTAPRODUCTOS 1
#define CARRITO 2
#define AGREGARPRODUCTO 3
#define ELIMINARPRODUCTO 4
#define CERRAR 6

//Se manejara los datos en modo binario en lugar de modo texto
FILE *inventario;

//Estructura de datos del producto
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
	
	//ENTRADA DE DATOS
	printf("\n\tEscoja el servicio: ");
	scanf("%d", &opcion);
	
	//SALIDA DE DATOS
	if(opcion <= 6 && opcion >= 1){
		return opcion;
	}
	return CERRAR;
}

//Función: asignarID
/*Objetivo: Asignar la ID sucesiva de un artículo previamente registrado o registrar una ID = 1 en caso de que
no haya ningún artículo registrado. De tal manera que posean una ID única cada producto.
*/
int asignarID(){
	
	FILE* buscar;
	
	struct structProduct producto;
	
	int id = 0;
	
	//ELIMINA LA BASURA QUE ALMACENA EN .dat 
	memset(&producto, 0, sizeof(struct structProduct));
	
	buscar = fopen("ListaProductos.dat","rb");
	
	//Verifica si está vacío el documento o no está creado aún.
	if( NULL != buscar){
		//Modo de lectura: Producto uno por uno hasta llegar al último registrado
		while(1){
			//fread: Lee hasta cierta cantidad de datos definidos por la estructura, en base a 1 producto.
			fread(&producto, sizeof(producto), 1, buscar);
			
			if(feof(buscar)){
				break;
			}

			//Asignar la id de cada producto hasta que sea asignado la última ID de la lista.
			id = producto.ID;
			
			}
		
		//Si no se inicializa nada y la id = 0, entonces se le asigna el valor de 1
		if(id == 0){
			id = 1;
		}
		//En dado caso de que se haya capturado la ID del último producto, aumentar valor 1.
		else{
			id++;
		}
	}
	else{
		printf("Error al abrir archivo(ID)");
	}
	
	if( !fclose( buscar ) ){
	   printf( "\nFichero cerrado(ID)\n" );
	}
	else{
		printf( "\nError: fichero NO CERRADO(ID)\n" );
	}
	
	//Salida de Datos: ID del siguiente producto
	return id;
}

void agregarProducto(){
		
	FILE* inventario;
	struct structProduct producto;
	
	//Se abre lista de productos modo "ab" = Escribe al final del archivo
	inventario = fopen("ListaProductos.dat", "ab");
	//ELIMINA LA BASURA QUE ALMACENA EN .dat 
	memset(&producto, 0, sizeof(struct structProduct));
		
	//DECLARA ERROR AL ABRIR ARCHIVO
	if( inventario )
		printf("\n\tLista ListaProductos.txt (ABIERTO)\n");
	else{
		printf("\n\tERROR ListaProductos.txt (NO ABIERTO)\n");	
	}
	
	//Se asigna el último ID registrado
	producto.ID = asignarID();

	//ENTRADA DE DATOS
	printf("\nIngrese Nombre:");
	scanf("%s", producto.nombre);
		
	do{
		printf("\nIngrese Cantidad:");
		scanf("%d", &producto.cantidad);
	}while(producto.cantidad == 0);

	printf("\nIngrese Precio:");
	scanf("%f", &producto.precio);
	
	//ESCRITURA EN EL ARCHIVO "inventario" 
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
		//ESCRITURA EN CONSOLA
		printf("\n\t%d\t", producto.ID);
		
		printf("%s\t\t", producto.nombre);
	
		printf("   %d\t", producto.cantidad);
		
		printf("\t%0.2f\n\n", producto.precio);
		}
		printf("\n    ------------------------------------------------------");
		
		if( !fclose( inventario ) )
			printf( "\nFichero cerrado\n" );
		else{
			printf( "\nError: fichero NO CERRADO\n" );
		}
	}
	
}
	
void eliminarProducto(){
	
	FILE* inventario;
	FILE* temporal;
	
	structProduct producto;
	
	//Elimina la basura que pueda generar el agregar información a estructura
	memset(&producto, 0, sizeof(struct structProduct));
	
	int id;
	//Se abre lista de productos modo "rb" = Lectura en modo binario
	inventario = fopen("ListaProductos.dat", "rb");
	//Se abre lista de productos modo "wb" = Crea un archivo binario o sobreescribe todos los datos, trucando a 0.
	temporal = fopen("temp.dat","wb");
	
	mostrarInventario();
	printf("\nSeleccione el ID del producto a eliminar: ");
	scanf("%d", &id);
	
	//Función while: Leer todos los productos almacenados
	while(1){

		fread(&producto, sizeof(producto), 1, inventario);
		
		if(feof(inventario)){
			break;
		}
		
		//Si el producto con el ID buscado se encuentra:
		if(id == producto.ID){
			printf("\nArtículo Encontrado: %s", producto.nombre);
		}
		else{
			//En caso de que la "id actual" leído sea mayor a la id seleccionada por el usuario
			if(producto.ID > id){
				//Restar el valor de la ID en -1 posterior a la "id actual"
				producto.ID--;
			}
			//Se escribe en un archivo temporal los productos excepto el seleccionado a eliminar
			fwrite(&producto, sizeof(producto), 1, temporal);
		}
		
	}
	
	if( !fclose( inventario ) )
		  printf( "\nFichero cerrado PASO 1\n" );
	else{
		printf( "\nError: fichero NO CERRADO PASO 1\n" );
	}
	
	if( !fclose( temporal ) )
		printf( "\nFichero cerrado PASO 1\n" );
	else{
		printf( "\nError: fichero NO CERRADO PASO 1\n" );
	}
	
	//Se abre lista de productos modo "wb" = Crea un archivo binario o sobreescribe todos los datos, trucando a 0.
	inventario = fopen("ListaProductos.dat", "wb");
	//Se abre lista de productos modo "rb" = Lectura en modo binario
	temporal = fopen("temp.dat","rb");
	
	
	while(1){
		fread(&producto, sizeof(producto), 1, temporal);
		
		if(feof(temporal)){
			break;
		}
		//Pasar toda la información del archivo temporal al archivo "inventario original"
		fwrite(&producto, sizeof(producto), 1, inventario);
		
	}
	
	if( !fclose( inventario ) )
		  printf( "\nFichero cerrado PASO 2\n" );
	else{
		printf( "\nError: fichero NO CERRADO PASO 2\n" );
	}
	
	if( !fclose( temporal ) )
		printf( "\nFichero cerrado PASO 2\n" );
	else{
		printf( "\nError: fichero NO CERRADO PASO 2\n" );
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
		case ELIMINARPRODUCTO:
			printf("\nEliminar Producto");
			
			eliminarProducto();
			
			break;
		case CERRAR:
			cerrar = TRUE;
			break;
		}
	}while((cerrar != TRUE));

	return 0;
}
		