#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/estructuras.h"

//ptr globales, aquí se guardan las listas de usuarios, posts y vocabulario, para que puedan ser accedidos desde cualquier función. De esto se sostiene todo
Usuario* lista_usuarios = NULL;
Post* lista_posts = NULL;
Vocabulario* lista_vocabulario = NULL;


//funcion para encontrar un usuario dado su id
Usuario* buscarUsuario(int id_buscado){
    Usuario* actual = lista_usuarios; //nuestro primer usuario cargado
    while(actual != NULL){ //mientras no lleguemos al final de la lista de usuarios
      if(actual->id_usuario == id_buscado) //si el id del user actual coicide con el que buscamos, lo encontramos
      return actual;
      actual = actual->siguiente;
    }
    return NULL; //si llegamos al final sin encontrar nada, devuelve null
}

//nuestro indice invertido
void insertarVocabulario(char tag[], int id_post){
    Vocabulario *actual = lista_vocabulario; //revisamos el diccionario desde el inicio
    //(caso 1):busca si el hashtag ya existe en nuestro vocabulario, con strcmp comparamos strings, si son iguales devuelve un 0
    while(actual != NULL){
      if(strcmp(actual->hashtag,tag) ==0){
          //si el hashtag ya existe, se inserta el id del post a su lista de posteo, pero antes pedimos memoria para el nuevo nodo de posteo
          NodoPosteo* nuevo_posteo = (NodoPosteo*)malloc(sizeof(NodoPosteo));
          nuevo_posteo->id_post_global = id_post;
          //lo metemos al principio de la lista de posteo con esa palabra
          nuevo_posteo->siguiente = actual->lista_posteo;
          actual->lista_posteo = nuevo_posteo;
          return;
      }
      actual = actual->siguiente; //si no coincide esa palabra, pasamos a la sgte
    }
    //(caso 2):si se llega a terminar el while y no la encuentra, es una palabra nueva, por lo que nos toca pedir memoria para registrarla en el diccionario
    Vocabulario* nuevo_vocabulario = (Vocabulario*)malloc(sizeof(Vocabulario));
    strcpy(nuevo_vocabulario->hashtag, tag); //si el hashtag no existe, creamos un nuevo nodo en el vocabulario, con strcpy copiamos el string
    //al ser una palabra nueva, creamos su primer post/registro
    NodoPosteo* nuevo_posteo = (NodoPosteo*)malloc(sizeof(NodoPosteo));
    nuevo_posteo->id_post_global = id_post;
    nuevo_posteo->siguiente = NULL; //como es el primer posteo de esa palabra, su siguiente es null
    nuevo_vocabulario->lista_posteo = nuevo_posteo;//conectamos ese registro a la palabra recien creada

    //enlazamos esa palabra a la lista global de nuestro diccionario
    nuevo_vocabulario->siguiente = lista_vocabulario;
    lista_vocabulario = nuevo_vocabulario;
};

void cargarUsuarios(){
    printf("entrando a usuarios \n");
    FILE *archivo_usuarios = fopen("../data/usuarios.txt", "r");
    if (archivo_usuarios == NULL) {
        printf("Error: No se pudo abrir el archivo usuarios.txt\n");
        return;
    }
    int id_leido;
    char nombre_leido[1000];
    int usuarios_cargados = 0;

//como es texto formateado usamos fscanf hasta que termine el archivo
//el "%d;%[^\n]\n" indica que es un entero  luego se lee todo hassta encontrar un punto y coma o un salto de linea.
    while(fscanf(archivo_usuarios, "%d;%[^\n]\n",&id_leido,nombre_leido) ==2){
        //solicitamos memoria
        Usuario* nuevo_usuario = (Usuario*)malloc(sizeof(Usuario));
        nuevo_usuario->id_usuario = id_leido;
        strcpy(nuevo_usuario->nombre_usuario, nombre_leido);
        nuevo_usuario->lista_amigos = NULL;
        
        nuevo_usuario->siguiente = lista_usuarios;
        lista_usuarios = nuevo_usuario;

        usuarios_cargados++;

    }
    fclose(archivo_usuarios);
    printf("Exito: se cargaron los usuarios %d\n",usuarios_cargados);
     
};

Post* buscarPostGlobal(int id_buscado){
    Post* actual = lista_posts;
    while(actual != NULL){
      if(actual->id_post_global == id_buscado){
        return actual;
      }
      actual = actual->siguiente;
    }
    return NULL;
}


void cargarPosts(){
  printf("entrando a post\n");
  FILE *archivo_post = fopen("../data/posts.txt","r");
  if (archivo_post == NULL){
    printf("Error: No se pudo abrir el archivo post.txt\n");
    return;
  }
  int id_global_leido;
  char tags_leida[1000];
  int usuario_leido;
  while(fscanf(archivo_post,"%d;%d;%[^\n]\n",&id_global_leido,&usuario_leido,tags_leida)== 3){
      Post *nuevo_post = (Post*)malloc(sizeof(Post));
      nuevo_post -> id_post_global = id_global_leido; // nuevo post apunta a id global para darle el valor del id leido
      nuevo_post -> id_usuario_post = usuario_leido;  //igual que lo anterior pero en este caso se aplica en id usuario

      strcpy(nuevo_post -> tags,tags_leida); //con la funcion strcpy se guarda el valor de "tags leida" en tags
      nuevo_post -> lista_Like = NULL; 
      nuevo_post -> siguiente = lista_posts;  //se ingresa el dato al inicio de la lista 
      lista_posts = nuevo_post; //ahora la lista empieza en el nuevo post
      insertarVocabulario(tags_leida, id_global_leido); //se llama a la funcion InsertarVocabulario para ingresar el hashtag a la lista
      
  }
  fclose(archivo_post);
  printf("Exito: se cargaron los post\n");
};

void cargarAmigos(){
  printf("entrando a amigos\n");
  FILE *archivo_amigos = fopen("../data/amigos.txt","r");
  if (archivo_amigos == NULL){
    printf("Error: No se pudo abrir el archivo amigos.txt\n");
    return;
  }
  
  long long id_usuario_leido, id_amigo_leido;
  while(fscanf(archivo_amigos,"%d;%d\n",&id_usuario_leido,&id_amigo_leido) ==2){
    Usuario* usuario = buscarUsuario(id_usuario_leido); //se llama a la funcion buscarUsuario
    if(usuario == NULL){
      printf("usuario no encontrado %d\n",id_usuario_leido);
      continue;
    }
    Amigo* nuevo_amigo = (Amigo*)malloc(sizeof(Amigo));
    nuevo_amigo-> id_amigo = id_amigo_leido;
    nuevo_amigo -> siguiente = usuario -> lista_amigos; // usuario accede a la lista de amigos
    usuario -> lista_amigos = nuevo_amigo;
  }
  fclose(archivo_amigos);
  printf("Exito: se cargaron los amigos\n");
};

void cargarLikes(){
  printf("entrando a likes\n");
    FILE *archivo_likes = fopen("../data/likes.txt","r");
    if (archivo_likes == NULL){
      printf("ERROR: no se pudo abrir el archivo likes.txt\n");
      return; 
    }
    int id_post;
    int id_amigo;
    int likes_cargados = 0;//contador para saber cuantos likes se cargaron
    //lee linea por linea hasta que el archivo termine
    while(fscanf(archivo_likes, "%d;%d\n",&id_post,&id_amigo)==2){
        //primero busca el post al que le dieron like
        Post* actual = lista_posts; //ptr global a la lista de posts, quiere decir que estamos al inicio de todos los post
        while(actual != NULL && actual->id_post_global != id_post){ //recorre la lista mientras el final no sea null y el id no sea el que buscamos
            actual = actual->siguiente; //avanza a la sgte post
        }
        //insertamos el like
        //si el while anterior terminó y el "actual" no es null, quiere decir que encontramos el post al que le dieron like, entonces insertamos el like a su lista de likes
        if(actual != NULL){
            //pedimos memoria del tamaño de un like
            Like* nuevo = (Like*)malloc(sizeof(Like));
            nuevo->id_usuario_like = id_amigo; //el id del amigo que dio like se guarda en el nodo like
            nuevo->siguiente = actual->lista_Like; //enlazamos ese like a la lista de likes del post, es como otra lista que vive dentro del post
            actual->lista_Like = nuevo;
            likes_cargados++;
        }
    }
    fclose(archivo_likes);
    printf("Exito: likes cargados %d\n",likes_cargados);
    
};

void liberarMemoriaAmigos(Amigo *lista_amigo){
  while(lista_amigo != NULL){
    Amigo *nodo = lista_amigo;
    lista_amigo = lista_amigo -> siguiente;
    free(nodo);
  }
};
void liberarMemoriaUsuario(){
  Usuario *actual = lista_usuarios;

  while(actual != NULL){
    Usuario *nodo = actual;
    liberarMemoriaAmigos(actual -> lista_amigos);
    
    actual = actual -> siguiente;
    free(nodo);
  }
  lista_usuarios = NULL;
};
void liberarMemoriaLike(Like *lista_likes){
  while(lista_likes != NULL){
    Like *nodo = lista_likes;
    lista_likes = lista_likes -> siguiente;
    free(nodo);
  }
};

void liberarMermoriaPost(){
  Post *actual = lista_posts;

  while (actual != NULL){
    Post *nodo = actual ;
    liberarMemoriaLike(actual->lista_Like); //se llama a la funcion para liberar la memoria de likes ya que esta esta conectada a la lista post

    actual = actual -> siguiente;
    free(nodo);
    
  }
  lista_posts = NULL;
};
void liberarMemoriaVocabulario(){
  Vocabulario *actual = lista_vocabulario;

  while (actual != NULL){
    Vocabulario *nodo = actual;
    actual = actual -> siguiente;
    free(nodo);
  }
  lista_vocabulario = NULL;
};


int main(){
  printf("--------------------------------\n");
  printf("------Iniciando Buscador--------\n");
  printf("--------------------------------\n");

  cargarUsuarios();
  cargarPosts();
  cargarAmigos();
  cargarLikes();

  printf("Datos cargados exitosamente.\n");

  int opcion = 0;
    
  while(opcion != 3){

    printf("--------------------------------\n");
    printf("1. Informacion de usuario\n");
    printf("2. Busqueda por hashtag\n");
    printf("3. Salir\n");
    printf("--------------------------------\n");
    printf("Ingrese una opcion: ");

    if(scanf("%d", &opcion) != 1){
      
      printf("Opcion invalida. Por favor ingrese un numero nuevamente.\n");
      break;
    }
        
    switch(opcion){

      case 1:{
        int id_buscar;
        printf("Ingrese el ID del usuario: ");
        scanf("%d", &id_buscar);
            
        Usuario* usr = buscarUsuario(id_buscar);
        if(usr != NULL){
          printf("---SE ENCONTRO EL PERFIL---\n");
          printf("Nombre:   %s\n", usr->nombre_usuario);
          printf("ID:       %d\n", usr->id_usuario);
          printf("Amigos:   ");

          Amigo* amigo_actual = usr->lista_amigos;
          int contador_amigos = 0;

          //recorremos la sub-lista de amigos del usuario encontrado
          while(amigo_actual != NULL){
            printf("ID Amigo: %d", amigo_actual->id_amigo);
            amigo_actual = amigo_actual->siguiente;
            contador_amigos++;
          }
          if(contador_amigos ==0){
            printf("No tiene amigos registrados.\n");
          }
          else{
            printf("Usuario con ID %d no encontrado.\n", id_buscar);
          }          
        }
        break;
      }
      case 2:{
          char hashtag_buscar[1000];
          printf("Ingrese el hastag a buscar\n");
          scanf("%s",hashtag_buscar);

          Vocabulario* vocabulario_actual = lista_vocabulario;
          int encontrados = 0;

          //se busca la palabra en el diccionario
          while(vocabulario_actual != NULL){
              if(strcmp(vocabulario_actual->hashtag, hashtag_buscar) == 0){
                encontrados = 1;
                printf("---SE ENCONTRARON LOS POST---\n" );
                //si existe la palabara, se recorre la lista posteo
                NodoPosteo* posteo_actual = vocabulario_actual->lista_posteo;
                int elementos = 0;

                while(posteo_actual != NULL){
                    Post* info_post = buscarPostGlobal(posteo_actual->id_post_global);
                    if(info_post != NULL){
                    printf("ID Post: %s\n", info_post->id_post_global);

                    Like* like_actual = info_post->lista_Like;
                    int contador_likes = 0;
                    while(like_actual != NULL){
                        contador_likes++;
                        like_actual = like_actual->siguiente;
                    }
                    printf("Likes: %d\n", contador_likes);
                }
                posteo_actual = posteo_actual->siguiente;
                encontrados++;
          }
          printf("Total de post encontrados con el hashtag %s: %d\n", hashtag_buscar, elementos);
          break;
        }
        vocabulario_actual = vocabulario_actual->siguiente;
        }
        if(encontrados ==0){
          printf("No se encontraron post con el hashtag %s\n", hashtag_buscar);
        }
        break;
      }
      case 3:{
          liberarMermoriaPost();
          liberarMemoriaUsuario();
          liberarMemoriaVocabulario();
          printf("Cerrando el programa\n");
          opcion = 3;
          break;
      }

    } 
  }       
  return 0;
}
//1.arreglar errores. 2.comentar las lineas 3.grabar video 4.hacer ppt