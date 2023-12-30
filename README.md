# Membre du groupe : OUALI ROZA et DAHMANI LILIA du G1
->Dans ce code, le nombre de sémaphores initial est configuré pour que le producteur commence à produire et le consommateur commence à consommer. Le consommateur attend que le producteur produise une ligne, puis le producteur attend que le consommateur consomme cette ligne avant de passer à la suivante.
# les reponses sur les questions :
Q1: Quelles sont les structures de données à utiliser ?

Matrices B, C, et A pour stocker les données.
Tampon T pour stocker les résultats intermédiaires.
Sémaphores (sem_producteur et sem_consommateur) pour synchroniser l'accès aux données partagées.

Q2: Comment allez-vous protéger l'accès à ces données ?

Utilisation de sémaphores pour synchroniser les threads producteurs et consommateurs. Le sémaphore sem_producteur est utilisé pour contrôler l'accès au tampon par les threads producteurs, et sem_consommateur est utilisé pour contrôler l'accès au tampon par le thread consommateur.

Q3: Quels sont les risques ?

Risques de conditions de concurrence : Les accès concurrents au tampon T par les threads producteurs peuvent causer des problèmes si la synchronisation n'est pas correctement mise en place. L'utilisation de sémaphores aide à éviter ces conditions de concurrence en régulant l'accès aux données partagées.
Risques de deadlock : Si la synchronisation n'est pas correctement gérée, il peut y avoir des situations de deadlock où les threads restent bloqués indéfiniment. Cependant, dans ce code, la synchronisation semble correctement mise en œuvre avec les sémaphores, réduisant ainsi le risque de deadlock.
