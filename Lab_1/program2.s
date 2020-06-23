#Nombre: Javier Pérez Cáceres
#Sección: L-1

.text
li $t3,12 #En el registro $t3 se guarda el valor X
li $t4,0 #En el registro $t4 se guarda el valor 0
beq $t3,0,Y_MAS 
beq $t3,1,Y_MENOS
li $t4, 100  
li  $v0, 10 #Se carga el valor 10 en el registro $v0 para terminar la ejecución
syscall
Y_MAS:
addi $t4,$t4,1
li  $v0, 10 #Se carga el valor 10 en el registro $v0 para terminar la ejecución
syscall
Y_MENOS:
subi $t4,$t4,1
li  $v0, 10 #Se carga el valor 10 en el registro $v0 para terminar la ejecución
syscall

#Para cambiar el valor de X se debe cambiar el valor del registro $t3.
#Con $t3 = 0 -> el registro $t4 tiene un valor de 1
#Con $t3 = 1 -> el registro $t4 tiene un valor de 0xffffffff
#Con $t3 = 12 -> el registro $t4 tiene un valor de 64
