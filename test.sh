#!/bin/bash
# Si permission non accordé : chmod u+x test.sh

echo "== Script de test et d'analyse des nombres premiers =="
# a : Effectuer chaque test.
# k : AKS.
# e : Euclide.
# m : Cribble d'Eratosthene.
# p : Pocklington.
# i : Miller-Rabin.
# h : Nombre hautement composé.
read -p " Quels sont les tests que vous voulez lancer ? " options
read -p " Combien d'itérations pour le test d'un nombre premier ? " iter
read -p " Combien de nombres (de préférence premier)? " size

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

for ((i=0; i<$size; i++))
do
  ./prime_numbers -$options $iter ${prime_numbers[$i]}
done

#gnuplot -e "plot 'data.txt'; pause -1" # Affiche le plot du résultat
#gnuplot -e "plot 'average.txt'; pause -1" # Un histogramme qui compare la vitesse d'éxécution des algos pour un nombre?
cd ..
