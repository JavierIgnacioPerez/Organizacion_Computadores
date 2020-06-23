#Nombre: Javier Pérez Cáceres
#Sección: L-1

.text
addiu $t0, $zero, 0x10010000 #($t0 = 0 + 0x10010000)
addi $t1, $zero, 5           #($t1 = 0 + 5)
sw $t1, 0($t0)               #(Guardar en 0x10010000 ($t0) el valor de 5 ($t1)) 
lw $t2, 0($t0)               #(Cargar el valor en 0x10010000 ($t0) y guardarlo en $t2)
addiu $t0, $t0, 4            #($t0 = 0x10010000 + 4)
sw $t2, 0($t0)               #(Guardar en 0x10010004 ($t0) el valor de 5 ($t2))

#Los valores señalados en el pre-informe para los registros $t1 y $t2 son los verificados por el programa.
#Los valores almacenados en las direcciones de memoria 0x10010000 y 0x10010004 es 5 como se espera.