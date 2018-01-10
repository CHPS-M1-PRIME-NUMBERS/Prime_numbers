# Prime Numbers, Projet M1 CHPS - UVSQ 2017/2018

Prime Numbers est un projet réalisé au sein du Master M1 CHPS de l'Université de Versailles/Saint-Quentin.
Il a pour but de tester la primalité d'un nombre N via plusieurs algorithmes:
* Des algorithmes naifs (Crible d'Ératosthène, Euclide)
* Des algorithmes probabilistes (Miller-Rabin)
* Des algorithmes déterministes (Pocklington, AKS)

Ce projet contient également tout le nécéssaire pour tester une grande plage de nombre via un script SHELL et pour analyser les résultats en terme de performance.

Ce programme génère différents fichiers .txt qui permettent d'analyser les résultats via notamment l'utlisation de Gnuplot par exemple.

BONUS:
Nous avons également implementé la recherche des nombres hautements composés.

## Installation

### Exigences
* g++ 7.2.0 (ou tout autre compilateur de >=C++14)
* GMP 6.1.2
* NTL 10.5.0
* CMAKE 3.9.4

### Construction de l'executable
`$ cmake ..`
Une fois placé dans un dossier d'installation créé à l'interieur du dossier source.

## Usage

`./prime_numbers -options nb_iterations nbs_a_tester`

ou

`bash test.sh`

### Les options
* a : Effectuer chaque test.
* k : AKS.
* e : Euclide.
* o : Modulo.
* m : Cribble d'Eratosthene.
* p : Pocklington.
* i : Miller-Rabin.
* h : Nombre hautement composé naïve.
* H : Nombre hautement composé définition.

## Auteurs
* Jean-Didier Pailleux
* Damien Thénot
* Robin Feron
* Romain Robert
* Maxence Joulin

Ainsi que l'aimable aide apportée par notre encadrant S. Gougeaud.

## License
[MIT](https://choosealicense.com/licenses/mit/)
