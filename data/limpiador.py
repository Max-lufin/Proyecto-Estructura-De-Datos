#id[0],screenName[1],tags[2],avatar[3],followersCount[4],friendsCount[5],lang[6],lastSeen[7],tweetId[8],friends[9] 10 datos se deben separar en archivo txt


import csv
#Rutas de los archivos
archivo = "data/dataset_recortadoPrincipal.csv"  
archivo_usuarios = "data/usuarios.txt"
archivo_posts = "data/posts.txt"
archivo_amigos = "data/amigos.txt"
archivo_likes = "data/likes.txt"


with open(archivo, 'r') as archivo, \
     open(archivo_usuarios, 'w') as salida_usuarios, \
     open(archivo_posts, 'w') as salida_posts, \
     open(archivo_amigos, 'w') as salida_amigos, \
     open(archivo_likes, 'w') as salida_likes: #abre los archivos
                                                                    


   
    lector = csv.reader(archivo, delimiter=',', quotechar='"')  #csv.reader lee fila por fila y las separa 
    next(lector)  #salta la primera fila (encabezados)
    id_post_global = 1
    for fila in lector: #recorre el archivo agregando a los archivos correspondientes 
       
       id_usuario = fila[0]
       nombre_usuario = fila[1]
       posts =  fila[2]
       amigos = fila[9]
       posts_sucios = fila[2]  #limpieza de caracteres no deseados en los posts
       posts_limpios = posts_sucios.replace('[', '').replace(']', '').replace('"', '').strip()  #limpia los posts quitando los caracteres no deseados
    

       amigos_sucios = ",".join(fila[9:])  #limpieza de caracteres no deseados en los amigos
       amigos_limpios = amigos_sucios.replace('[', '').replace(']', '').replace('"', '').replace(' ', '')

       lista_amigos = amigos_limpios.split(',')  #separa los amigos en una lista

       for amigo in lista_amigos: #ciclo para guardar el usuario y el amigo que tenga
           if amigo != "":
               salida_amigos.write(f"{id_usuario};{amigo}\n")
            


             
       salida_usuarios.write(f"{id_usuario};{nombre_usuario}\n")  #escribe el id y el nombre del usuario en el archivo de usuarios

       salida_posts.write(f"{id_post_global};{id_usuario};{posts_limpios}\n")

       if len(lista_amigos) > 0 and lista_amigos[0] != "":
           primer_amigo = lista_amigos[0]  #toma el primer amigo de la lista para asignar el like
           salida_likes.write(f"{id_post_global};{primer_amigo}\n")

       id_post_global += 1

print("Archivos separados correctamente")


#Arreglar el tema de los ID y el contador
#Separar los 4 archivos
#Meterle mano a C