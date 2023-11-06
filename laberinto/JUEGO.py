import pygame
pygame.init()

class Pared(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pygame.image.load("c:\\Users\\Mateo\\Documents\\JUEGO FINAL - sabi y emi\\muro.png").convert_alpha()
        self.rect=self.image.get_rect()

class bola(pygame.sprite.Sprite): #Cargamos imagen para el Sprite
    def __init__(self):
        super().__init__()
        self.image = pygame.image.load("c:\\Users\\Mateo\\Documents\\JUEGO FINAL - sabi y emi\\bola.png").convert_alpha()
        self.rect = self.image.get_rect()

#construir muros
def construir_mapa(mapa): #se creó una lista de resctangulos a partir de la listaMuros "mapa"
    listaMuros=[]
    x=0
    y=0
    for fila in mapa:
        for muro in fila:
            if muro == "X":
                listaMuros.append(pygame.Rect(x,y,80,80))
            x+=80
        x=0
        y+=80
    return listaMuros

def dibujar_muro(superficie, rectangulo): #dibujamos un rectangulo
    pygame.draw.rect(superficie, TRANSPARENT, rectangulo)

def dibujar_mapa(superficie, listaMuros): #Dibujamos listaMuros con los rectangulo muro
    for muro in listaMuros:
        dibujar_muro(superficie, muro)

ANCHO = 1280
ALTO =720
movil = pygame.Rect(600, 400, 40, 40)
x=0
y=0
vel=0
alt=0

NEGRO = (0, 0, 0)
VERDE = (0, 255, 0)
TRANSPARENT = pygame.Color(150, 15, 255, 0) # Red with alpha=0

ventana = pygame.display.set_mode((ANCHO, ALTO))
pygame.display.set_caption('Muro')
reloj = pygame.time.Clock()

listaPared=pygame.sprite.Group()
pared=Pared()
listaPared.add(pared)

listaBola=pygame.sprite.Group()
bola=bola()
listaBola.add(bola)

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

listaMuros=construir_mapa(mapa)

gameOver=False 
while not gameOver:
    
    reloj.tick(60)
    
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            gameOver=True
        
        if event.type==pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                vel=-5
            elif event.key == pygame.K_RIGHT:
                vel=+5
            elif event.key == pygame.K_UP:
                alt=-5
            elif event.key == pygame.K_DOWN:
                alt=+5
            
        else:
            vel=0
            alt=0
    movil.x += vel
    movil.y += alt
    
    bola.rect.x = movil.x
    bola.rect.y = movil.y
    
    for muro in listaMuros: #   Recorremos cada cuadro de la lista para comprobar las colisiones
        if movil.colliderect(muro):
            movil.x -= vel
            movil.y -= alt
    
    #creamos el fondo de nuestro juego
    
    ventana.fill(NEGRO)
    
    #dibujo
    
    x=0
    y=0
    for fila in mapa:
        for muro in fila:
            if muro=="X":
                pared.rect.x=x
                pared.rect.y=y
                listaPared.add(pared)
                listaPared.draw(ventana)
            x+=80   
        x=0
        y+=80


    listaBola.draw(ventana)
    dibujar_mapa(ventana, listaMuros)
    pygame.display.flip()
pygame.quit()
