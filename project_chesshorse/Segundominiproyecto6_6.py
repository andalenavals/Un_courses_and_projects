r,q=input('Teclee la posicion del caballo')

#~ Se define la funcion que encuentra las casillas a las que puede saltar el caballo dentro del tablero   
def saltosdentrotablero(x,y):
	p=[[x-1,y-2],[x+1,y-2],[x+2,y-1],[x+2,y+1],[x-2,y-1],[x-2,y+1],[x-1,y+2],[x+1,y+2]]
	n=0
	a=[]
	while n<=7:	
		i=p[n][0]
		j=p[n][1]
		if (i >0 and j >0) and (i <=6 and j <=6):
			a.append((i,j))
			c=a
		n+=1
	return c

#~ Se define la funcion saltos consecutivos que le adiciona a una
#lista establecida 'b' los primeros saltos posibles para ~ su ultima
#casilla (sin retroceder y tomando siempre el primer salto dentro del
#tablero que no este en los saltos determinado por la lista dada)
b=[(r,q)]
def saltosconsecutivos(x,y,b):
	n=0
	while n<35:
		for i in range(0,len(saltosdentrotablero(x,y))):
			if b.count(saltosdentrotablero(x,y)[i])==0:
				b.append(saltosdentrotablero(x,y)[i])
				x,y=saltosdentrotablero(x,y)[i]
				break
		n+=1	
	return b

#~ toma los saltos consecutivos hasta una casilla (w,z) y mira a que otras casillas puede saltar el caballo estando en la casilla (w,z)
def saltosvalidos(x,y,b,w,z):
	v=[]
	e=saltosconsecutivos(x,y,b).index((w,z))
	saltosconsecutivos(x,y,b)[(e+1):len(saltosconsecutivos(x,y,b))]=[]
	for i in range(0,len(saltosdentrotablero(w,z))):
		if b.count(saltosdentrotablero(w,z)[i])==0:
			v.append(saltosdentrotablero(w,z)[i])
	return v

#~ La funcion saltos consecutivos se atasca en una casilla,
#entonces,se define unos condicionales ~ para asignarle nuevas listas
#a la funcion saltosconsecutivos de modo que se atasque lo mas
#'lejos'posible ~ y si no completa los 64 movimientos escoger otra
#lista que no se halla tomado 'que regrese' de modo que encuentre los
#64 saltos

#~ dentro del while antes del if defino la ultima casilla 'u', la
#penultima 'p' y de los saltos validos de la penultima en que ~
#posicion estaba la ultima 'm', esta ultima definicion con el fin de
#que me busque el siguientevalido si no me vota un resultado ~
#satisfactorio. En el if pongo la condicion de que la posicion de la
#validad +1 sea menor que la cantidad de saltos validos ~ en otras
#palabras si hay saltos validos diferente a la ultima casilla que tome
#el primero y haga saltos consecutivos hasta que se atasque.

b=[(r,q)] 
x=r
y=q
Q=saltosconsecutivos(x,y,b)
while len(Q)!=36:
	u=Q.pop()
	p=Q[len(Q)-1]
	m=saltosvalidos(x,y,b,p[0],p[1]).index((u[0],u[1]))
	if m+1<len(saltosvalidos(x,y,b,p[0],p[1])):
		x=saltosvalidos(x,y,b,p[0],p[1])[m+1][0]
		y=saltosvalidos(x,y,b,p[0],p[1])[m+1][1]
		Q.append(saltosvalidos(x,y,b,p[0],p[1])[m+1])
		b=Q
		Q=saltosconsecutivos(x,y,b)	
print Q
		
#~ 'Una vez conocida la lista con la trayectoria que debe seguir el
#caballo ~ se organiza dicha lista como otra lista llamada Tablero que
#contiene las filas del tablero

trayectoria=Q
Tablero=[]
for i in range (1,7):
	for j in range (1,7):
		a=(i,j)
		Tablero.append (a)
		pos=trayectoria.index (a)
                Tablero[Tablero.index (a)]=pos
	print Tablero[6*(i-1):6*i]
