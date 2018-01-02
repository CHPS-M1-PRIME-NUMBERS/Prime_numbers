#!/bin/bash
# Si permission non accordé : chmod u+x test.sh

read -p " Comment d'itération pour le test d'un nombre premier ? " iter # Se sera argv[1]
read -p " Quel est ce nombre ? " nbr # Se sera argv[2]
read -p 'Combien de nombres (de préférence premier)? ' size # Se sera argv[3]
if [ $size != 0 ]
then
    echo "Veuillez les indiquer: "
    prime_numbers=()  # Se sera argv[4]
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

./prime_numbers $iter $nbr $size ${prime_numbers[*]}
#gnuplot -e "plot 'data.txt'; pause -1" # Affiche le plot du résultat
#gnuplot -e "plot 'average.txt'; pause -1" # Un histogramme qui compare la vitesse d'éxécution des algos pour un nombre?
cd ..
