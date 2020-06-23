#Nombre: Javier Pérez Cáceres
#Sección: L-1

li $t6, 5   #Se guarda en el registro $t6 el valor 2 (Valor de A)
li $t7, 2  #Se guarda en el registro $t7 el valor 10 (Valor de B) 
li $t0, 0   #Se guarda en el registro $t0 el valor 0 (Valor de M)

Loop:
bgt $t6,0,SUMA_RESTA
li  $v0, 10 #Se carga el valor 10 en el registro $v0 para terminar la ejecución
syscall

SUMA_RESTA:
add $t0,$t0,$t7
subi $t6,$t6,1
j Loop

#Con el valor de A = 2 y el valor B = 1, el valor final de M es 2, que es el valor que debe tener ya que el valor de A se le debe
#restar de a 1 hasta llegar a 0 y eso necesita 2 restas. En esas mismas restas a M se le suma 2 veces el valor de B (El valor es 1)

#Con el valor de A = 5 y el valor B = 2, el valor final de M es a, que es el valor que debe tener ya que el valor de A se le debe
#restar de a 1 hasta llegar a 0 y eso necesita 5 restas. En esas mismas restas a M se le suma 6 veces el valor de B (El valor es 2)