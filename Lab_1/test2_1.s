#Nombre: Javier Pérez Cáceres
#Sección: L-1

.text
addi $t0, $zero, 2 #($t0 = 0 + 2)
addi $t1, $zero, 2 #($t1 = 0 + 2)
beq $t0, $t1, A    #(Si $t0 es igual a $t1, salta a “A”)
addi $t1, $zero, 1 #($t1 = 0 + 1, pero en este caso no se ejecuta) 
.data
A:
add $t2,$t0,$t1

#Se debio crear el label "A" para probar el funcionamiento del programa.
#El Label A cambia de valor el registro $t2 para verificar que si se salto a dicho label.
#Los valores de $t0 y $t1 son los señalados en el pre-informe.
