#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H


typedef struct NodoAmigo {
    long long int id_amigo;
    struct NodoAmigo *siguiente;
} Amigo;
typedef struct NodoLike{
    int id_usuario_like;

    struct NodoLike* siguiente;
} Like;

typedef struct NodoPosteo{
    int id_post_global;
    struct NodoPosteo* siguiente;
} NodoPosteo;

typedef struct Post{
    int id_post_global;
    int id_usuario_post;
    char tags[1000];
    Like *lista_Like;
    struct Post *siguiente;
  
} Post; 

typedef struct NodoUsuario{
    int id_usuario;
    char nombre_usuario[1000];
    Post *lista_post;
    Amigo * lista_amigos;
    struct NodoUsuario* siguiente;
    
} Usuario;
//este es el indice invertido
//P.D. con "hashtag", nos referimos a una palabra
typedef struct NodoVocabulario{
    char hashtag[1000];

    NodoPosteo* lista_posteo;
    struct NodoVocabulario* siguiente;
} Vocabulario;

#endif
