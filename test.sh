#!/bin/bash
# Si permission non accordé : chmod u+x test.sh

read -p " Comment d'itération pour le test d'un nombre premier ? " iter # Se sera argv[1]
read -p " Quel est ce nombre ? " nbr # Se sera argv[2]
read -p 'Combien de nombres (de préférence premier)? ' size # Se sera argv[3]

prime_numbers=()  # Se sera argv[4]
for ((i=0; i<$size; i++))
do
    read prime_numbers[i]
done

echo ${prime_numbers[*]} # Affiche le tableau

# Par défaut on suppose que l'on a fait cmake et make
cd build/

if  [ ! -e 'moyenne.txt' ]
then
    touch moyenne.txt # Si le fichier existe on le créé.
elif [! -e 'data.txt']; then
    touch data.txt
else
    echo '' | tee moyenne.txt # On efface le contenu
    echo '' | tee data.txt # On efface le contenu
fi

./prime_numbers $iter $nbr $size $prime_numbers
#gnuplot -e "plot 'res.txt'; pause -1" # Affiche le plot du résultat
cd ..
