########################## librerias ###########################################
import pygame

pygame.init()

######################### "constantes" ################################
ANCHO = 1280
ALTO =720
NEGRO = (0, 0, 0)
VERDE = (0, 255, 0)
ALTO_MURO = 89
ANCHO_MURO = 79

########################## clases ###############################################

class Pared(pygame.sprite.Sprite): #Sprite es una clase padre para que este sea un objeto visual, con cuerpo, imagen, movimiento, etc
    def __init__(self):              #__init__ es el nombre default para los constructores
        super().__init__()            #creo variables image y rect
        self.image = pygame.image.load("c:\\Users\\Mateo\\Documents\\laberinto\\muro.png").convert_alpha() #convert alpha hace que la imagen sea mas optima al ejecutar
        self.rect=self.image.get_rect() #lo que delimita a la imagen son sus mismos limites visuales
        
class Bola(pygame.sprite.Sprite): #similar a la clase anterior
    def __init__(self, cx, cy, cwidth, cheight):
        super().__init__()
        self.image = pygame.image.load("c:\\Users\\Mateo\\Documents\\laberinto\\bola2.png").convert_alpha()
        self.rect = self.image.get_rect()
        self.rect.x=cx
        self.rect.y=cy
        self.rect.width=cwidth
        self.rect.height=cheight
        
class Corazon(pygame.sprite.Sprite):
    def __init__(self, cx, cy, cwidth, cheight):
        super().__init__()
        self.image = pygame.image.load("c:\\Users\\Mateo\\Documents\\laberinto\\corazon.png").convert_alpha()
        self.rect = self.image.get_rect()
        self.rect.x=cx
        self.rect.y=cy
        self.rect.width=cwidth
        self.rect.height=cheight

########################### funciones #########################################
#construir muros
def construir_mapa(mapa): #le llega un arreglo de strings

    listaMuros=[]
    x=0
    y=0
    for fila in mapa: #fila va usando un string del mapa = fila va tomando cada fila del mapa
        for muro in fila: #muro va tomando cada caracter, " " o "X"
            if muro == "X":
                listaMuros.append(pygame.Rect(x,y,ANCHO_MURO,ALTO_MURO)) #defino un area de juego rectangular. si en el dibujo del mapa hay una X, carga un muro en las coordenadas x,y con alto 80 y ancho 80
            x+=ANCHO_MURO
        x=0
        y+=ALTO_MURO
    return listaMuros

def dibujar_mapa(ventanaPrincipal, listaMuros): #Dibujamos listaMuros con los rectangulo muro
    for muro in listaMuros: # 1ro dibujo cuadrados para colisionar
        pygame.draw.rect(ventanaPrincipal, NEGRO, muro)

    x=0 #2do cargo las imagenes arriba
    y=0
    for fila in mapa:
        for muro in fila:
            if muro=="X":
                pared.rect.x=x
                pared.rect.y=y
                listaPared.add(pared)
                listaPared.draw(ventanaPrincipal)
            x+=ANCHO_MURO   
        x=0
        y+=ALTO_MURO

def actualizar_pantalla(vidas):
    ventanaPrincipal.fill(NEGRO) #creamos el fondo de nuestro juego nuevamente para borrar las imagenes anteriores de la bola
    dibujar_mapa(ventanaPrincipal, listaMuros) #tengo que volver a dibujar los muros
    listaBola.draw(ventanaPrincipal)
    agregarCorazones(vidas)
    listaCorazon.draw(ventanaPrincipal)
    actualizar_vidas(vidas)
    

def actualizar_vidas(vidas):
    if vidas==5:
        texto="vidas: 5"
    elif vidas==4:
        texto="vidas: 4"
    elif vidas ==3:
        texto="vidas: 3"
    elif vidas ==2:
        texto="vidas: 2"
    elif vidas ==1:
        texto="vidas: 1"
    elif vidas ==0:
        texto="vidas: 0"

    fuente=pygame.font.Font(None, 36)          
    superficie_texto= fuente.render(texto, True, VERDE)
    posicion_texto=(ANCHO // 2 - superficie_texto.get_width() // 2, ALTO // 2 - superficie_texto.get_height() // 2)

    ventanaPrincipal.blit(superficie_texto, posicion_texto)
    
def agregarCorazones(vidas): #carga tantos corazones como vidas tenga
    for i in range(vidas):
        corazon = Corazon(i*60, 0, 50, 50) # 50 es el ancho del corazon, a ellos los separo por 60 pixeles para que no aparexcan pegados
        listaCorazon.add(corazon)

###################### inicia main ######################################

#variables primitivas
vidas = 5
ancho=0
alto=0
x=0
y=0
gameOver=False 
mapa = [

    "XXXXXXXXXXXXXXXX",
    "X              X",
    "X XXX XXXXXXXX X",
    "X X   X         ",
    "X XX XXXXX XXX X",
    "X              X",
    "XXXXXXX XXXX  XX",
    "X              X",
    "XXXXXXXXXXX XXXX"
]

#objetos
ventanaPrincipal = pygame.display.set_mode((ANCHO, ALTO)) #creo ventana de juego, donde se va a ver el mapa
pygame.display.set_caption('Muro') #inserto titulo de la ventana
reloj = pygame.time.Clock() #para controlar la velocidad de actualizacion del juego

listaPared=pygame.sprite.Group() #admistro sprites del mismo tipo en grupos, para actualizarlos, saber si chocaron y otros análisis en conjunto
pared=Pared()
listaPared.add(pared)

listaBola=pygame.sprite.Group()#si bien tengo una sola bola, como es un group puedo aplicar funciones como la de draw
bola=Bola(570, 550, 33, 33)
listaBola.add(bola)

listaMuros=construir_mapa(mapa) #hago mapa con los cuadrados violetas

rectanguloVidas = pygame.Rect(10,10,100,20)
ventanaVidas = pygame.draw.rect(ventanaPrincipal, NEGRO, rectanguloVidas)

listaCorazon=pygame.sprite.Group()

#inicio juego
while not gameOver:
    
    reloj.tick(60) # controlo los fps, actualizo todo 60 veces por segundo
    
    for event in pygame.event.get(): #obtengo todas las acciones que hico el usuario, en este caso me importan las flechas y otras teclas
        if event.type == pygame.QUIT:
            gameOver=True
        
        if event.type==pygame.KEYDOWN: # si presiono una tecla
            if event.key == pygame.K_LEFT:
                ancho=-5
            elif event.key == pygame.K_RIGHT:
                ancho=+5
            elif event.key == pygame.K_UP:
                alto=-5
            elif event.key == pygame.K_DOWN:
                alto=+5
        else:
            ancho=0
            alto=0

    bola.rect.x += ancho
    bola.rect.y += alto

    colision_previa=False

    reloj.tick(0) #para que no saque varias vidas si mantengo presionado
    for muro in listaMuros: #   Recorremos cada cuadro de la lista para comprobar las colisiones
        if bola.rect.colliderect(muro):
            bola.rect.x -= ancho #para que no reste varias vidas 
            bola.rect.y -= alto
            vidas = vidas - 1
    reloj.tick(60)
     
    actualizar_pantalla(vidas)

    if vidas == 0:
        gameOver=True
        
    pygame.display.flip()
pygame.quit()
