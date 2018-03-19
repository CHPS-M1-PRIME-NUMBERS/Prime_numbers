#!/bin/bash
# Si permission non accordé : chmod u+x test.sh

echo "== Script de test et d'analyse des nombres premiers =="
# a : Effectuer chaque test.
# k : AKS.
# e : Euclide.
# o : Modulo.
# m : Cribble d'Eratosthene.
# p : Pocklington.
# i : Miller-Rabin.
# h : Nombre hautement composé naïve.
# H : Nombre hautement composé définition.
echo "Quel type de test voulez-vous effectuer?" type_test
echo "txt: Analyse une liste de nombres présents dans un fichier."
echo "range: Analyse tout les nombres présents entre A et B."
echo "normal: Analyse une liste de nombre donnés par l'utlisateur."
read type_test
read -p "Quels sont les tests que vous voulez lancer ? " options
read -p "Combien d'itérations pour le test d'un nombre premier ? " iter

# Par défaut on suppose que l'on a fait cmake et make et qu'on se trouve dans le dossier racine
cd build/

if  [ ! -e 'memory.txt' ]
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

if [ "$type_test" = "txt" ]
then
cd ..
    read -p "A partir de quel fichier souhaitez-vous faire l'analyse?" inputfile
    while read line; do
      prime_numbers[index]="${line}"
      ((++index))
    done < $inputfile
    cd build/
    for ((i=0; i<$index; i++))
    do
      ./prime_numbers -$options $iter ${prime_numbers[$i]}
    done
fi


if [ "$type_test" = "range" ]
then
      read -p "A partir de quel nombre souhaitez-vous commencer l'intervalle d'analyse?" A
      read -p "Par quel nombre souhaitez-vous finir l'intervalle d'analyse?" B
      for ((i=$A; i<=$B; i++))
      do
        ./prime_numbers -$options $iter $i
      done
fi

if [ "$type_test" = "normal" ]
then
    read -p "Combien de nombres (de préférence premier)? " size
    if [ $size != 0 ]
    then
        echo "Veuillez indiquer les nombres à analyser: "
        prime_numbers=()
        for ((i=0; i<$size; i++))
        do
            read prime_numbers[i]
        done

        for ((i=0; i<$size; i++))
        do
          ./prime_numbers -$options $iter ${prime_numbers[$i]}
        done
    fi
fi

#gnuplot -e "plot 'data.txt'; pause -1" # Affiche le plot du résultat
#gnuplot -e "plot 'average.txt'; pause -1" # Un histogramme qui compare la vitesse d'éxécution des algos pour un nombre?
cd ..
