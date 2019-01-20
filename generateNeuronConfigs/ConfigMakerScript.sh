gcc circleMakerIC.c -o makeNeuralConfig #Compiles circleMaker to latest version

#Begin making the varied number of neurons tests
coupling=( 1 25 50 75 100)
numOfNeurons=( 2 10 50 100 250 500 1000 10000)
q="And"
r="Neurons.json"

#beginloop
for i in "${coupling[@]}"
do
for j in "${numOfNeurons[@]}"
do
./makeNeuralConfig $i $j configWithCoupling$i$q$j$r
done
done


