#Nombre: Javier P�rez C�ceres
#Secci�n: L-1

.text
li $t0,3           #Se carga el valor 3 en el registro $t0.
sw $t0,0x10010000  #Se guarda el valor almacenado en el registro $t0 en la direccion de memoria 0x10010000 (Primera posici�n).
subi $t1,$t0,1     #Se guarda en el registro $t1 el valor de la resta $t0 - 1.
sw $t1,0x1001000c  #Se guarda el valor almacenado en el registro $t1 en la direccion de memoria 0x1001000c (Tercera posici�n).

#Se puede observar en la pesta�a de "Data Segment" despues de ensamblar el codigo que el valor de la posicion 0 es 3 y el valor de 
#la posicion 3 es 2.
#Concuerda con los resultados esperados.