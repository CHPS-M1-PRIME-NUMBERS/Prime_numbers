#!/bin/bash
# Si permission non accordé : chmod u+x test.sh

echo "== Script de test et d'analyse des nombres premiers =="
# a : Effectuer chaque test.
# k : AKS.
# e : Euclide (Computation Bound).
# o : Modulo (Computation Bound).
# m : Cribble d'Eratosthene.
# p : Pocklington.
# i : Miller-Rabin.
# h : Nombre hautement composé naive.
# H : Nombre hautement composé def.
read -p " Quels sont les tests que vous voulez lancer ? " options
read -p " Combien d'itérations pour le test d'un nombre premier ? " iter
read -p " Combien de nombres (de préférence premier ou hautement composé)? " size

if [ $size != 0 ]
then
    echo "Veuillez les indiquer: "
    prime_numbers=()
    for ((i=0; i<$size; i++))
    do
        read prime_numbers[i]
    done
fi

# Par défaut on suppose que l'on a fait cmake et make et qu'on se trouve dans le dossier racine
cd build/

if  [ ! -e 'average.txt' ]
then
    touch average.txt # Si le fichier existe on le créé.
elif [ ! -e 'data.txt'  ]
then
    touch data.txt
elif [ ! -e 'result.txt'  ]
then
    touch result.txt
else   # On efface le contenu
    echo '' | tee average.txt
    echo '' | tee data.txt
    echo '' | tee result.txt
fi

# Dans le cas où l'option choisi est "a" pour faire tout les tests:
if [ $options = "a" ]
then
    options=('k' 'e' 'o' 'm' 'p' 'i' 'h' 'H')
    for ((j=0; j<8; j++))
    do
        for ((i=0; i<$size; i++))
        do
          ./prime_numbers -${options[$j]} $iter ${prime_numbers[$i]}
        done
        echo " " >> data.txt
    done
else # Cas avec l'option différent de "a"
    for ((i=0; i<$size; i++))
    do
      ./prime_numbers -$options $iter ${prime_numbers[$i]}
    done
fi

gnuplot -e "set xlabel 'Number'; set ylabel 'Times'; plot 'data.txt' using 1:2 with linespoints title 'Resultats'; pause -1" # Affiche le plot du résultat
cd ..

#gnuplot -e "set format y '10^{%S}';set format x '10^{%S}'; set xlabel 'Number'; set ylabel 'Times (ns)'; plot 'AKS.txt' using 1:2 with linespoints title 'AKS','Euclide.txt' using 1:2 with linespoints title 'Euclide', 'Modulo.txt' using 1:2 with linespoints title 'Modulo','pocklington.txt' using 1:2 with linespoints title 'Pocklington', 'miller.txt' using 1:2 with linespoints title 'Miller-Rabin', 'Eratosthene.txt' using 1:2 with linespoints title 'Eratosthène';pause -1"
#gnuplot -e "set format y '10^{%S}';set format x '10^{%S}'; set xlabel 'Number'; set ylabel 'Times (ns)'; plot 'Euclide.txt' using 1:2 with linespoints title 'Euclide', 'Modulo.txt' using 1:2 with linespoints title 'Modulo', 'miller.txt' using 1:2 with linespoints title 'Miller-Rabin', 'Eratosthene.txt' using 1:2 with linespoints title 'Eratosthène';pause -1"
