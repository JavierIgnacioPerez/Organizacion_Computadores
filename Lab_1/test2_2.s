#Nombre: Javier Pérez Cáceres
#Sección: L-1

.text
addi $t0, $zero, 2 #($t0 = 0 + 2)
addi $t1, $zero, 2 #($t1 = 0 + 2)
beq $t0, $t0, A   #(Si $t0 es igual a $t1, salta a “A”)
addi $t1, $zero, 1  #($t1 = 0 + 1, pero en este caso no se ejecuta) 
A:
add $t2,$t0,$t1

#Se debio crear el label "A" para probar el funcionamiento del programa.
#El Label A cambia de valor el registro $t2 para verificar que si se salto a dicho label.
#Al cambiar la isntrucción "beq $t0, $t1, A" a "beq $t0, $t0, A" el valor de los registros permanece igual,
#ya que la comparación sigue siendo verdadera y se salta al label "A".
