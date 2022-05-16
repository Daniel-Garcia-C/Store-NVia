#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define LISTAPRODUCTOS 1
#define CARRITO 2
#define AGREGARPRODUCTO 3
#define ELIMINARPRODUCTO 4
#define CERRAR 6

//Se manejara los datos en modo binario en lugar de modo texto
FILE *inventario;

//Estructura de datos de cada producto
typedef struct structProduct{
	int ID;
	char    nombre[30];
	int     cantidad;		
	float 	precio;
}structProduct;

//Funcion: Mostrar Menu de Opciones
//Programador: Ian Aguilar Ramirez
//Fecha: 25/Marzo/2022
/*Objetivo: Que la funcion despliegue en la consola el menu de opciones que va
	a ofrecer el programa al usuario y dar a escoger la opcion para retornarla
	al funcion main() para hacer la llamada a otras funciones*/

int mostrarMenuDeOpciones(int validar){
	// MENU DE OPCIONES DE ARTICULOS
	int opcion;
	
	//MENU USUARIO (USO LIBRE)
	if(validar == 0){
		printf("\n     -----------------------------");
		
		printf("\n\t     Tienda NVia\n");
		printf("\n\t1. Lista de productos ");
		printf("\n\t2. Carrito de compras ");
		printf("\n\t3. Cerrar programa  ");
		
		printf("\n     -----------------------------");
		
		do{
		printf("\n\tEscoja el servicio: ");
		scanf("%d", &opcion);
		}while(opcion < 1 && opcion > 3);
	}
	//MENU ADMINISTRADOR (USO PRIVADO)
	else{
		printf("\n     -----------------------------");
		
		printf("\n\t     ADMINISTRADOR");
		printf("\n\t     Tienda NVia\n");
		printf("\n\t1. Lista de productos ");
		printf("\n\t2. Carrito de compras ");
		printf("\n\t3. Agregar productos ");
		printf("\n\t4. Eliminar producto ");
		
		printf("\n\t5. Cerrar programa  ");
		
		printf("\n     -----------------------------");
		
		do{
		printf("\n\tEscoja el servicio: ");
		scanf("%d", &opcion);
		}while(opcion < 1 && opcion > 5);
	}
	
	if(opcion > 1 && opcion < 5){
		return opcion;
	}
	
	return CERRAR;
}

//Funcion: Asignar ID
//Programador: Daniel Garcia Cetina
//Fecha: 28/Abril/2022
/*Objetivo: Que la funcion lea todos los productos almacenado, y recoja las ID
	de cada producto hasta llegar al ultimo para asignar a una variable aumentado
	en +1 y retornar a funcion agregarProducto(). En caso de que no haya ningun producto
	retornar el valor de 1*/
	
int asignarID(){
	
	//Variables
	FILE* buscar;
	struct structProduct producto;
	int id = 0;
	
	//ELIMINA LA BASURA QUE ALMACENA EN .dat 
	memset(&producto, 0, sizeof(struct structProduct));
	
	//Se abre lista de productos modo "rb" = Lectura en modo binario
	buscar = fopen("ListaProductos.dat","rb");
	
	//Verifica si esta vacio el documento o no esta creado aun.
	if( NULL != buscar){
		
		//Romper el ciclo while hasta que feof() [Fin de linea] sea verdad.
		while(!feof(buscar)){
			//Leer asignando a estructura producto, de tamanio producto, un solo producto del archivo
			fread(&producto, sizeof(producto), 1, buscar);
	
			//Asigna id por cada producto, en caso de que no haya permanece en id = 0
			id = producto.ID;
			
			}
		
		//Se asigna valor id = 1 si no hay productos registrados, caso contrario aumenta en +1
		if(id == 0){
			id = 1;
		}
		else{
			id++;
		}
	}
	//COMPROBACION DE ERRORES
	else{
		printf("Error al abrir archivo(ID)");
	}
	
	if( !fclose( buscar ) ){
	   printf( "\nFichero cerrado(ID)\n" );
	}
	else{
		printf( "\nError: fichero NO CERRADO(ID)\n" );
	}
	
	return id;
}

//Funcion: Agregar Producto
//Programador: Burguete Pech Eyli
//Fecha: 20/Mayo/2022
/*Objetivo: Que la funcion agregue un producto al archivo.dat(Lista de Productos)
	de tal manera que sea ingresado los datos por el usuario excepto la ID*/
	
void agregarProducto(){
	
	//Variables
	FILE* inventario;
	struct structProduct producto;
	
	//Se abre lista de productos modo "ab" = Crea Archivo y escribe al final del archivo
	inventario = fopen("ListaProductos.dat", "ab");
	//ELIMINA LA BASURA QUE ALMACENA EN .dat 
	memset(&producto, 0, sizeof(struct structProduct));
		
	//DECLARA ERROR AL ABRIR ARCHIVO
	if( inventario )
		printf("\n\tLista ListaProductos.txt (ABIERTO)\n");
	else{
		printf("\n\tERROR ListaProductos.txt (NO ABIERTO)\n");	
	}
	
	//Se asigna el ultimo ID registrado
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
	
	//Escribiendo en modo binario
	fwrite(&producto, sizeof(producto), 1, inventario);
	
	//COMPROBACION DE ERRORES
	if( !fclose( inventario ) )
		printf( "\nFichero cerrado\n" );
	else{
		printf( "\nError: fichero NO CERRADO\n" );
	}
}

	
//Funcion: Mostrar Inventario
//Programador: Ian Aguilar Ramirez
//Fecha: 20/Mayo/2022
/*Objetivo: Que la funcion se encargue de desplegar los productos almacenados del archivo.dat
	(Lista de Productos) en la consola de manera que sea visualmente atractiva
	para el usuario*/

int mostrarInventario(){
	//Variables
	FILE* inventario;
	structProduct producto;
	
	//Se abre lista de productos modo "rb" = Lectura en modo binario
	inventario = fopen("ListaProductos.dat", "rb");
	
	//ERROR EN CASO DE QUE NO HABRA EL ARCHIVO
	if(inventario == NULL){
		printf("Error: No se ha podido abrir el archivo\n");
		return 0;
	}
	else{
		//Mostrar todos los productos
		printf("\n    ------------------------------------------------------");
		printf("------------------------");
		printf("\n\tID\t\tNombre\t\t\tCantidad\t\tPrecio\n");
		printf("\n    ------------------------------------------------------");
		printf("------------------------");
	}
	
		//Romper el ciclo while hasta que feof() [Fin de l�nea] sea verdad
		while(1){
		
		//Leer asignando a estructura producto, de tamanio producto, un solo producto del archivo
		fread(&producto, sizeof(producto), 1, inventario);
		
		if(feof(inventario)){
			break;
		}
		//Mostrar en pantalla cada producto
		printf("\n\t%d\t\t", producto.ID);
		
		printf("%s\t\t\t", producto.nombre);
	
		printf("   %d\t", producto.cantidad);
		
		printf("\t\t%0.2f\n\n", producto.precio);
		}
	
		printf("\n    ------------------------------------------------------");
		printf("------------------------");
		
		//Comprobar si se cierra el fichero
		if( !fclose( inventario ) ){
			printf( "\nFichero cerrado\n" );
		}
		else{
			printf( "\nError: fichero NO CERRADO\n" );
		}
	return 0;
}
	
//Funcion: Eliminar Producto
//Programador: Burguete Pech Eyli y Daniel Garcia Cetina
//Fecha: 4/Abril/2022
/*Objetivo: Que la funcion elimine un producto del archivo.dat(Lista de Productos)
	de tal manera que no se vea afectado la secuencia ID*/
void eliminarProducto(){
	
	//Variables
	FILE* inventario;
	FILE* temporal;
	
	structProduct producto;
	int id;
	
	//Elimina la basura que pueda generar el agregar informacion a estructura
	memset(&producto, 0, sizeof(struct structProduct));
	

	//Se abre lista de productos modo "rb" = Lectura en modo binario
	inventario = fopen("ListaProductos.dat", "rb");
	//Se abre lista de productos modo "wb" = Crea un archivo binario o sobreescribe todos los datos, trucando a 0.
	temporal = fopen("temp.dat","wb");
	
	//Muestra el inventario
	mostrarInventario();
	printf("\nSeleccione el ID del producto a eliminar: ");
	scanf("%d", &id);
	
	//Funcion while: Leer todos los productos almacenados
	while(1){
		
		fread(&producto, sizeof(producto), 1, inventario);
		
		if(feof(inventario)){
			break;
		}
		
		//Si el producto con el ID buscado se encuentra:
		if(id == producto.ID){
			printf("\nArticulo Encontrado: %s", producto.nombre);
		}
		//Se escribe en un archivo temporal los productos excepto el seleccionado
		else{
			//Se reduce el id del producto seleccionado en -1
			if(producto.ID > id){
				producto.ID--;
			}
			//Se escribe en el archivo temporal todos los productos
			fwrite(&producto, sizeof(producto), 1, temporal);
		}
		
	}
	
	//Comprobacion de cierre de archivos
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
	
	//Se rompe el ciclo si feof() Fin de linea sea verdad
	while(1){
		//Se lee cada producto del archivo temporal
		fread(&producto, sizeof(producto), 1, temporal);
		
		if(feof(temporal)){
			break;
		}
		
		//Se sobreescribe cada producto de temporal a inventario
		fwrite(&producto, sizeof(producto), 1, inventario);
		
	}
	
	//Se comprueba que hayan cerrado los archivos
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

//Funcion: Eliminar Redundancia
//Programador: Daniel Garcia Cetina
//Fecha: 4/Mayo/2022
/*Objetivo: Al ingresar un arreglo de IDs solicitados de la funci�n carritoDeCompras
	se elimine la redundancia de ID's que existen en el arreglo y retornarlo
	sin repeticiones*/
	
int eliminarRedundancia(int* id, int elementsID, int limiteArray){
	
	//Variables
	int aux;
	
	//Se realizar la eliminacion de  de cada valor repetido
	for(int i = 0; i < elementsID - 1; i++){
		
		for(int j = i + 1; j < elementsID; j++){
			
			//En caso de repeticion se realiza un ordenamiento y sobreescritura
			if(*(id+i) == *(id+j)){
				
				aux = *(id + j);
				*(id + j) = *(id + elementsID - 1);
				*(id + elementsID - 1) = aux;
				elementsID--;
			}
		
		}
	}

	//Para aquellas variables no eliminadas por algun error logico se inicializa en 0
	for(int m = elementsID; m < limiteArray; m++){
		*(id + m) = 0;
	}
	
	//Retorna los elementos ya que el apuntador altera la id en la funcion
	return elementsID;
}

	
//Funcion: ordenarIDs
//Programador: Ian Aguilar Ramirez
//Fecha: 6/Mayo/2022
/*Objetivo: Se recibe un arreglo y el tamanio de las ID's de la funcion carritoDeCompras
	y se ordenan de tal manera que sea de menor a mayor, se retorna con repeticiones
	pero ordenados*/	

void ordenarIDs(int* id, int TAM){
	//Variables
	int temp;
	
	for (int i = 1; i < TAM; i++){
		for  (int j = 0 ; j < TAM - 1; j++){
			if (*(id + j) > *(id + (j+1))){
				temp = *(id + j);
				*(id + j) = *(id + (j+1));
				*(id + (j+1)) = temp;
			}
		}
	}
	//No retorna debido a que el apuntador reescribe los datos en la direccion de la variable
}

//Funcion: actualizarCantidad
//Programador: Daniel Garcia Cetina
//Fecha: 10/Mayo/2022
/*Objetivo: Se recibe la estructura de producto de la funcion carritoDeCompras
	y se pasa como apuntador, asi como la cantidad de Productos contados del carritoDeCompras
	Se hace una lectura al inventario y escritura a un archivo temporal para sobreescribirlo
	nuevamente en el inventario con los datos del archivo temporal siendo los cambios
	modificados (cantidad)*/
	
void actualizarCantidad(structProduct* carrito, int cantidadP){
	//Variables
	FILE* inventario;
	FILE* temporal;
	
	struct structProduct producto;
	struct structProduct p;
	
	/*Elimina la basura que pueda generar el agregar informacion a estructura*/
	memset(&producto, 0, sizeof(struct structProduct));
	int i = 0;
	
	carrito = &carrito[0];
/*	Se abre lista de productos modo "rb" = Lectura en modo binario*/
	inventario = fopen("ListaProductos.dat", "rb");
/*	Se abre lista de productos modo "wb" = Crea un archivo binario o sobreescribe todos los datos, trucando a 0.*/
	temporal = fopen("temp.dat","wb");
	
	i = 0;
	
/*	Funcion while: Leer todos los productos almacenados*/
	while(1){
		
		//Se lee cada producto
		fread(&p, sizeof(p), 1, inventario);
		
		if(feof(inventario)){
			break;
		}

	/*	Si el producto con el ID buscado se encuentra:*/
		if(carrito -> ID == p.ID){

			p.cantidad -= carrito -> cantidad;
		
			carrito++;
		}
			i++;
		//Se escribe en el archivo temporal con los cambios
		fwrite(&p, sizeof(p), 1, temporal);
	}
	
	//Se comprueba que los archivos hayan cerrado
	if( !fclose( inventario ) ){
		  printf( "\nFichero cerrado PASO 1\n" );
	}
	else{
		printf( "\nError: fichero NO CERRADO PASO 1\n" );
	}
	
	if( !fclose( temporal ) ){
		printf( "\nFichero cerrado PASO 1\n" );
	}
	else{
		printf( "\nError: fichero NO CERRADO PASO 1\n" );
	}
	
	/*Se abre lista de productos modo "wb" = Crea un archivo binario o sobreescribe todos los datos, trucando a 0.*/
	inventario = fopen("ListaProductos.dat", "wb");
	/*Se abre lista de productos modo "rb" = Lectura en modo binario*/
	temporal = fopen("temp.dat","rb");
	
	while(1){
		//Se lee cada producto modificado del archivo temporal
		fread(&p, sizeof(p), 1, temporal);

		if(feof(temporal)){
			break;
		}
		//Se sobreescribe la informacion de temporal al inventario
		fwrite(&p, sizeof(p), 1, inventario);

	}
	
	//Se comprueba que haya cerrado el inventario
	if( !fclose( inventario ) ){
		  printf( "\nFichero cerrado PASO 2\n" );
	}
	else{
		printf( "\nError: fichero NO CERRADO PASO 2\n" );
	}
	
	if( !fclose( temporal ) ){
		printf( "\nFichero cerrado PASO 2\n" );
	}
	else{
		printf( "\nError: fichero NO CERRADO PASO 2\n" );
	}
}


//Funcion: Carrito de Compras
//Programador: Daniel Garcia Cetina e Ian Aguilar Ramirez
//Fecha: 26/Abril/2022
/*Objetivo: Permitir al usuario o cliente anadir de la lista de productos a su
	carrito de compras, de tal manera que se manipulara la informacion para 
	estimar el valor de costo total, los articulos solicitados, la cantidad solicitada
	Se imprime en la consola el ticket de venta una vez realizada la compra con los
	todos los datos impresos*/
void carritoDeCompras(){
	//Variables
	FILE* inventario;
	
	//Variables para el carrito de compras
	struct structProduct producto;
	struct structProduct carrito[20];
	
	int limiteProductos = 20;
	int id[limiteProductos], cantidad[limiteProductos];
	char answer;
	int i = 0, count = 0, total = 0;
	
	//Variables para obtener la fecha y hora del dia
	time_t t;
	struct tm *tm;
	char fecha[100];
	
	t = time(NULL);
	tm = localtime(&t);
	strftime(fecha, 100, "%d/%m/%Y", tm);
	int segundos = tm -> tm_sec;
	int hora = tm -> tm_hour;
	int minutos = tm -> tm_min;
	
	//Elimina la basura que pueda generar el agregar informacion a estructura
	memset(&producto, 0, sizeof(struct structProduct));
	
	//Se abre fichero en modo binario para "actualizacion base de datos" y lectura.
	inventario = fopen("ListaProductos.dat", "rb+");
	
	//Inicializar en 0 el arreglo
	for(i = 0; i < limiteProductos; i++){
		id[i] = 0;
		cantidad[i] = 0;
	}
	
	i = 0;
	
	//Entrada de datos [ID]
	do{
		printf("\nSeleccione el producto (ID): ");
		scanf("%d", &id[i]);
		fflush(stdin);
		
		printf("\nCancelar[Cualquier tecla]");
		printf("     Continuar[Enter]: ");
		scanf("%c", &answer);
		fflush(stdin);
		
		i++;
		count++;
	}while(answer == '\n');
	
	//ORDENAMIENTO DE ID para su lectura
	ordenarIDs(id, count);
	
	count = eliminarRedundancia(id, count, limiteProductos);
	
	ordenarIDs(id, count);
	
	i = 0;
	
	count = 0;
	
	while(1){
		//Se lee cada producto del archivo inventario
		fread(&producto, sizeof(producto), 1, inventario);
		
		//Rompe el ciclo en caso de que sea verdad el fin de linea
		if(feof(inventario)){
			break;
		}
		
		//Se filtran los productos que hayan sido solicitados en ID's
		if((id[i] == producto.ID)){
			//Muestra el producto seleccionado
			printf("\t\nProducto Seleccionado");
			printf("\t\nNombre: %s", producto.nombre);
			printf("\t\nCantidad: %d", producto.cantidad);
			printf("\t\nPrecio: %0.2f", producto.precio);
			
			//En caso de que la cantidad del producto solicitado sea distinto de 0 (STOCK disponible)
			if(producto.cantidad != 0){
				do{
					//Entrada de datos (Cantidad)
					printf("\n\tSeleccione la cantidad: ");
					printf("\n\tCancelar registro[0]");
					scanf("%d", &cantidad[i]);
				}while(cantidad[i] > producto.cantidad || cantidad[i] < 0);
				
				//En caso de que no se cancele el registro del producto hacer:
				if(cantidad[i] != 0){
					carrito[i] = producto;
					carrito[i].cantidad = cantidad[i];
					carrito[i].precio = carrito[i].precio * carrito[i].cantidad;
			
					count++;
					}
			}
			//Para cancelar la compra es posible si la cantidad es 0
			else{
				printf("\n\tProducto NO registrado");
			}
			i++;
			//Comprobar si hubo error de escritura
			if(ferror(inventario)){
				printf("\n\tERROR ESCRITURA");
			}
			
		}
	}
	
	/*Si hay productos registrados con count(contador)[distinto de 0] entonces mandar mensaje
	 de confirmacion de compra*/
	if(count != 0){
	do{
		fflush(stdin);
		printf("\n\tConfirmar la compra: [Y][N]");
		scanf("%c", &answer);
	}while((answer != 'Y') && (answer != 'N'));
	
	//Si se confirma la compra: IMPRIMIR TICKET DE VENTA
	if(answer == 'Y'){
		printf("\t----------------------------------------------");
		printf("\n\t\t\tTicket de venta\n");
		printf("\t----------------------------------------------");
		printf("\n\t\t\t   Tienda NVia\n");
		//Hora y fecha
		printf ("\n\t\t\tFecha: %s\n", fecha);
		printf ("\n\t\t\t   Hora: %d:%d:%d\n", hora, minutos, segundos);
		printf("\t----------------------------------------------");
		printf("\n\tID\tNombre\t\tCantidad\tPrecio\n");
		printf("\t----------------------------------------------");
		
		//Productos solicitados
		for(int i = 0; i < count; i++){
			printf(" \n\t%d", carrito[i].ID);
			printf("\t%s", carrito[i].nombre);
			printf("\t\t  %d", carrito[i].cantidad);
			printf("\t   %0.2f", carrito[i].precio);
			total = carrito[i].precio + total;
		}
		
		//Total de la compra
		printf("\n\t----------------------------------------------");
		printf("\n\tTotal: $%d\n\t\t", total);
		//Total (escrito y numeros)
		printf("\n\t----------------------------------------------");
		printf("\n\t\tGracias por comprar con nosotros!\n");
		printf("\n\t----------------------------------------------");
		
		//Actualizar la cantidad del inventario indicando la reducci�n de STOCK
		actualizarCantidad(carrito, count);
		}
	}
	//En caso de que sea answer = "N" (Cancelar Compra)
	else{
		printf("\n\t--------------------------------------");
		printf("\n\tCompra Cancelada");
		printf("\n\t--------------------------------------");
	}
	
	//Verificar que cierre correctamente
	if( !fclose(inventario) ){
		printf( "\nFichero cerrado\n" );
	}
	else{
		printf( "\nError: fichero NO CERRADO\n" );
	}
}

//Funcion: main
//Objetivo: Hacer de llamada de las funciones con un switch por cada opcion al programa

int main(int argc, char *argv[]) {
	
	int cerrar;
	char usuario[7] = "MoonPie", user[7];
	char contrasena[7] = "NVIA712", contr[7];
	
	int validacion = 1;
	
	do{
		switch(mostrarMenuDeOpciones(validacion)){
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
			
			mostrarInventario();
			carritoDeCompras();
		
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
