#Nombre: Javier Pérez Cáceres
#Sección: L-1

.data
arr: .word 10 22 15 40
end:
.text
la $s0, arr # esta instrucción pone la dirección base de arr en $s0
la $s1, end
subu $s1, $s1, $s0
srl $s1, $s1, 2 # ahora $s1 = num elementos en arreglo.
################################################################################

li $t0,0    		#Se carga en el registro $t0 el valor 0 (EvenSum).
li $t3,0    		#Se carga en el registro $t0 el valor 0, funcionara como un contador (i)
li $t1,0x10010000 	#Se carga en el registro $t1 el valor de la direccion de memoria del primer elemento de una lista.
Loop:
	bgt $s1,$t3,Desarrollo  #En caso de que $s1 sea igual a $t0 se salta al label "Desarrollo".
	li  $v0, 10 		#Se carga el valor 10 en el registro $v0 para terminar la ejecución.
	syscall
Desarrollo:
	lw $t2, 0($t1)          #Se carga en el registro $t2 lo contenido en la direccion de memoria que tiene $t1
	and $t2,1               #Operacion bitwise and y guarda el valor en el registro $t2
	add $t0, $t0, $t2       #En el registro $t0 el resultado de la suma $t0 + $t2
	addiu $t1, $t1, 4	#Se guarda en el registro $t1 el resultado de la suma de memoria de $t1 y 4 
	addi $t3,$t3,1          #Se aumenta uno en el contador
	J Loop			#Se salta al label "Loop"

#Con el arreglo .word 1 2 3 4 -> $t0 (Evensum) da 2
#Con el arreglo .word 10 20 30 40 50 -> $t0 (Evensum) da 0
#Con el arreglo .word 11 22 33 44 -> $t0 (Evensum) da 0
#Con el arreglo .word 10 22 15 40 -> $t0 (Evensum) da 1