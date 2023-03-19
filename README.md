
# Rapport du projet de systèmes d’exploitation


### Louis-César Pagès, CMI S4-P, Université de Strasbourg, 27/04/2018

Pour la manipulation et la représentation du carré magique, j’ai défini une structure « Square » contenant 4 tableaux à 2 dimensions.

Chacun de ces tableaux sont aussi désignés dans mon code comme des matrices. La structure « Square » contient aussi un entier « size » qui représente la taille totale de mon carré magique. Chacun des tableaux et de taille « size/2 » * « size/
2 ».

La fonction « initializeSquare » permet d’allouer dynamiquement de l’espace pour ma structure pour une taille donnée. La fonction « freeSquare » elle, libère la mémoire occupée par cette structure à la fin du code. Les fonctions suivantes permettent de sois calculé un carré magique :

« generateSquare » , soit de procéder aux changements entre cadrant : « transformSquare » ou encore affiché ma structure Square : « printSquare ».

Plusieurs conditions au début du main permet de vérifier que le l’entier donné en entré du programme n’est pas négatif, impaire et divisible par 4 ; une fois ces conditions vérifiées, j’initialise la structure du carré magique. J ‘initialise aussi une matrice qui nous servira lors du calcule d’un cadrant dans les fils. Le pipe doit être appelé et la structure sigaction « sa » va nous permettre de recevoir les signales émis par le père. La fonction « handler » implémenter avant le main va gérer l’action à effectuer lors de cette réception. Dans l’ensemble du programme , le code de retour des primitifs systèmes est vérifier. La fonction « raler » est appelée pour sortir proprement du programme au cas où.

 Enfin vient le lancement des fils. Pour pouvoir identifier les fils, on range leur pid dans un tableau, après les avoir lancé un par un. Cela va permet de lancer dans l’ordre le calcule de chaque cadrant et aussi au père d’envoyer le signal au cadrant voulu. Pour chaque fils :

1. On calcule un des cadrants de la structure en envoyant la matrice « support »

2. On transforme cette matrice en tableau à une dimension afin de faciliter l’écriture dans le
tube

3. On applique un coefficient au tableau qui correspond au numéro du cadrant

4. On attend la réception du signal du père avant d’écrire dans le tube

5. Le fils écrit dans le tube, libère la mémoire, puis se termine.

On procède ensuite à la réception du tableau envoyé par les fils dans le père. Pour chaque fils on envoie un signal et on attend son extinction. Un tableau est initialisé afin de recevoir les donnés envoyées. On transforme ensuite ce tableau en matrice à l’aide de la fonction « arrayToMatrix » et
on initialise chacun des quadrant de la structure en fonction de la position du fils.
  Fils1 →quadrant1
  Fils2→quadrant2 etc
On procède ensuite au changement de valeur entre quadrant afin d’obtenir notre carré magique.
On affiche la structure et libère la mémoire allouée avant de quitter le programme.
