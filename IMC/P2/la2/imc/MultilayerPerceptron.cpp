/*********************************************************************
* File  : MultilayerPerceptron.cpp
* Date  : 2020
*********************************************************************/

#include "MultilayerPerceptron.h"

#include "util.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // To establish the seed srand() and generate pseudorandom numbers rand()
#include <limits>
#include <math.h>


using namespace imc;
using namespace std;
using namespace util;

// ------------------------------
// Obtain an integer random number in the range [Low,High]
int randomInt(int Low, int High)
{
}

// ------------------------------
// Obtain a real random number in the range [Low,High]
double randomDouble(double Low, double High)
{
}

// ------------------------------
// Constructor: Default values for all the parameters
MultilayerPerceptron::MultilayerPerceptron()
{

}

// ------------------------------
// Allocate memory for the data structures
// nl is the number of layers and npl is a vetor containing the number of neurons in every layer
// Give values to Layer* layers
int MultilayerPerceptron::initialize(int nl, int npl[]) {
	// La inicialización es similar a la practica anterior
	// Solo que tenemos que establecer a NULL en un caso especial
	// Esto es, cuando apliquemos SOFTMAX y nos encontremos en la ultima neurona de la ultima capa
	layers = new Layer[nl];
	nOfLayers = nl;

	for (int i = 0; i < nl; i++) {
		layers[i].nOfNeurons = npl[i];
		layers[i].neurons = new Neuron[npl[i]];
	}

	for (int i = 1; i < nl; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			if( (outputFunction == 1) && (i == nOfLayers-1) && (j == layers[i].nOfNeurons-1) ){
				layers[i].neurons[j].w = NULL;
				layers[i].neurons[j].wCopy = NULL;
				layers[i].neurons[j].deltaW = NULL;
				layers[i].neurons[j].lastDeltaW = NULL;
			} else { // En el caso de no aplicar la softmax o que no estemos en la ultima neurona
				layers[i].neurons[j].w = new double[layers[i-1].nOfNeurons +1];
				layers[i].neurons[j].wCopy = new double[layers[i-1].nOfNeurons +1];
				layers[i].neurons[j].deltaW = new double[layers[i-1].nOfNeurons +1];
				layers[i].neurons[j].lastDeltaW = new double[layers[i-1].nOfNeurons +1];
			}
		}
	}
}


// ------------------------------
// DESTRUCTOR: free memory
MultilayerPerceptron::~MultilayerPerceptron() {
	freeMemory();
}


// ------------------------------
// Free memory for the data structures
void MultilayerPerceptron::freeMemory() {
	delete[] layers;
}

// ------------------------------
// Fill all the weights (w) with random numbers between -1 and +1
void MultilayerPerceptron::randomWeights() {
	for(int i=1 ; i<nOfLayers ; i++){ // Comenzamos asignando pesos desde la primera capa oculta
		for (int j = 0; j < layers[i].nOfNeurons; j++){ // Para todas y cada una de las neuronas...
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) { // ... le asignamos valores a todos los pesos ...
				layers[i].neurons[j].w[k] = ((double)(rand()%20001) / 10000)-1; //... entre -1 y +1
			}
		}
	}
}

// ------------------------------
// Feed the input neurons of the network with a vector passed as an argument
void MultilayerPerceptron::feedInputs(double* input) {
	// No cambia respecto a la practica anterior
	for(int i=0 ; i<layers[0].nOfNeurons ; i++){
		layers[0].neurons[i].out = input[i];
	}
}

// ------------------------------
// Get the outputs predicted by the network (out vector of the output layer) and save them in the vector passed as an argument
void MultilayerPerceptron::getOutputs(double* output) {
	// No cambia respecto a la practica anterior
	// Se muestran las salidas de la red
	for (int i = 0; i < layers[nOfLayers-1].nOfNeurons; i++) {
		output[i] = layers[nOfLayers-1].neurons[i].out;
	}
}

// ------------------------------
// Make a copy of all the weights (copy w in wCopy)
void MultilayerPerceptron::copyWeights() {
	// Hay que tener cuidado con el caso de la neurona a NULL
	// Vamos a acceder a los pesos de todas las neuronas con respecto a la capa anterior
	for (int i = 1; i < nOfLayers ; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
				// Las guardamos en la variable de la clase
				if (layers[i].neurons[j].w != NULL) { // Nos ahorramos el peso
					layers[i].neurons[j].wCopy[k] = layers[i].neurons[j].w[k];
				}
			}
		}
	}
}

// ------------------------------
// Restore a copy of all the weights (copy wCopy in w)
void MultilayerPerceptron::restoreWeights() {
	// Nuevamente, hay que tener cuidado con la neurona a NULL
	// Es igual que copyWeights pero cambiando las variables
	for (int i = 1; i < nOfLayers ; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
				// Las guardamos en la variable de la clase
				if (layers[i].neurons[j].w != NULL) { // Nos ahorramos el peso
					layers[i].neurons[j].wCopy[k] = layers[i].neurons[j].w[k];
				} 
			}
		}
	}
}

// ------------------------------
// Calculate and propagate the outputs of the neurons, from the first layer until the last one -->-->
void MultilayerPerceptron::forwardPropagate() {
	// Hay que diferenciar los dos casos, normal o softmax
	if(outputFunction == 0){ // Caso de online
		for(int i=1 ; i<nOfLayers ; i++){ // Desde la primera capa oculta
			for(int j=0 ; j<layers[i].nOfNeurons ; j++){  // Vamos por todas las neuronas
				
				// Sumatorio
				double sum = 0.0;
				sum = sum + layers[i].neurons[j].w[0];
				for(int k=0 ; k<layers[i-1].nOfNeurons+1 ; k++){  // La salida depende de la anterior
					// Tomo la salida de la neurona anterior y su peso;
					sum = sum + layers[i].neurons[j].w[k] * layers[i-1].neurons[k-1].out;
				}
		
				// Ya solo queda aplicar la sigmoide para ver la salida de la neurona
				layers[i].neurons[j].out = 1.0/(1.0 + exp(-sum));
			}
		}
	} else { // Caso softmax
		double sum = 0.0;
		double sumSoftmax = 0.0; // Sumatoria del denominador
		double auxSum = 0.0; // Auxiliar para conseguir la sumatoria para el Softmax
		for(int i=1 ; i<nOfLayers ; i++){ // Desde la primera capa oculta
			for(int j=0;j<layers[i].nOfNeurons;j++){
				if(layers[i].neurons[j].w!=NULL){
					
					sum = sum + layers[i].neurons[j].w[0];
					for(int k=0 ; k<layers[i-1].nOfNeurons+1 ; k++){  // La salida depende de la anterior
					// Tomo la salida de la neurona anterior y su peso;
						sum = sum + layers[i].neurons[j].w[k] * layers[i-1].neurons[k-1].out;
					}
				} else {
					layers[i].neurons[j].out = 0.0;
				}

				// Ahora compruebo en que capa estoy y dependiendo de la misma, realizo la sigmoide o la softmax
				if(i == nOfLayers-1) { // En el caso de estar en la ultima capa, realizamos la sumatoria
					auxSum = 0;
					auxSum = auxSum + layers[nOfLayers-1].neurons[j].w[0];
					for(int k=1 ; k<layers[nOfLayers-2].nOfNeurons+1; k++){ // Vemos los pesos de la capa anterior a la final
						auxSum = auxSum + layers[nOfLayers-1].neurons[j].w[k] * layers[nOfLayers-2].neurons[k-1].out;
					}
					sumSoftmax = sumSoftmax + auxSum;

					layers[nOfLayers-1].neurons[j].out = exp(sum)/(1+sumSoftmax);
				} else { // En el caso de estar en el resto de capas
					layers[i].neurons[j].out = 1.0/(1.0 + exp(-sum));
				}
			}
		}
	}
}

// ------------------------------
// Obtain the output error (MSE) of the out vector of the output layer wrt a target vector and return it
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
double MultilayerPerceptron::obtainError(double* target, int errorFunction) {
}


// ------------------------------
// Backpropagate the output error wrt a vector passed as an argument, from the last layer to the first one <--<--
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::backpropagateError(double* target, int errorFunction) {
}

// ------------------------------
// Accumulate the changes produced by one pattern and save them in deltaW
void MultilayerPerceptron::accumulateChange() {
}

// ------------------------------
// Update the network weights, from the first layer to the last one
void MultilayerPerceptron::weightAdjustment() {
}

// ------------------------------
// Print the network, i.e. all the weight matrices
void MultilayerPerceptron::printNetwork() {
}

// ------------------------------
// Perform an epoch: forward propagate the inputs, backpropagate the error and adjust the weights
// input is the input vector of the pattern and target is the desired output vector of the pattern
// The step of adjusting the weights must be performed only in the online case
// If the algorithm is offline, the weightAdjustment must be performed in the "train" function
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::performEpoch(double* input, double* target, int errorFunction) {
	// Ahora relizamos todos los pasos para una sola epoca

	// Establecemos todos los deltas a 0
	for (int i=1; i<nOfLayers ; i++) {
		for (int j=0 ; j<layers[i].nOfNeurons; j++) {
			for (int k=0 ; k<layers[i-1].nOfNeurons+1; k++) {
				layers[i].neurons[j].deltaW[k] = 0.0;
			}
		}
	}

	feedInputs(input);
	forwardPropagate();
	backpropagateError(target, errorFunction);
	accumulateChange();
	if (online) { // Solo actualizo los pesos al terminar una epoca en online
		weightAdjustment();
	}
}

// ------------------------------
// Read a dataset from a file name and return it
Dataset* MultilayerPerceptron::readData(const char *fileName) {
}


// ------------------------------
// Train the network for a dataset (one iteration of the external loop)
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::train(Dataset* trainDataset, int errorFunction) {
	
	// Realizo las epocas
	for(int i=0; i<trainDataset->nOfPatterns; i++){
		performEpoch(trainDataset->inputs[i], trainDataset->outputs[i], errorFunction);
	}
	
	if(!online){ // Solo cambio los pesos tras todas las epocas en offline
		weightAdjustment();
	}
}

// ------------------------------
// Test the network with a dataset and return the error
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
double MultilayerPerceptron::test(Dataset* dataset, int errorFunction) {
}


// ------------------------------
// Test the network with a dataset and return the CCR
double MultilayerPerceptron::testClassification(Dataset* dataset) {
}


// ------------------------------
// Optional Kaggle: Obtain the predicted outputs for a dataset
void MultilayerPerceptron::predict(Dataset* dataset)
{
	int i;
	int j;
	int numSalidas = layers[nOfLayers-1].nOfNeurons;
	double * salidas = new double[numSalidas];
	
	cout << "Id,Category" << endl;
	
	for (i=0; i<dataset->nOfPatterns; i++){

		feedInputs(dataset->inputs[i]);
		forwardPropagate();
		getOutputs(salidas);

		int maxIndex = 0;
		for (j = 0; j < numSalidas; j++)
			if (salidas[j] >= salidas[maxIndex])
				maxIndex = j;
		
		cout << i << "," << maxIndex << endl;

	}
}



// ------------------------------
// Run the traning algorithm for a given number of epochs, using trainDataset
// Once finished, check the performance of the network in testDataset
// Both training and test MSEs should be obtained and stored in errorTrain and errorTest
// Both training and test CCRs should be obtained and stored in ccrTrain and ccrTest
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::runBackPropagation(Dataset * trainDataset, Dataset * testDataset, int maxiter, double *errorTrain, double *errorTest, double *ccrTrain, double *ccrTest, int errorFunction)
{
	int countTrain = 0;

	// Random assignment of weights (starting point)
	randomWeights();

	double minTrainError = 0;
	int iterWithoutImproving = 0;
	nOfTrainingPatterns = trainDataset->nOfPatterns;

	Dataset * validationDataset = NULL;
	double validationError = 0, previousValidationError = 0;
	int iterWithoutImprovingValidation = 0;

	Dataset* TrainData = new Dataset; // Datasets que contendra parte del original
	Dataset* validationData = new Dataset;

	// Generate validation data
	if(validationRatio > 0 && validationRatio < 1){
		
		// Para ambos datasets, el numero de entrada y de salidas es el mismo
		validationData->nOfInputs = trainDataset->nOfInputs;
		validationData->nOfOutputs = trainDataset->nOfOutputs;
		// Indicamos el numero de patrones con la proporcion dada por el usuario
		validationData->nOfPatterns = trainDataset->nOfPatterns*validationRatio;
		// Ahora indicamos cuantos patrones habra 
		validationData->inputs = new double*[validationData->nOfPatterns];
		validationData->outputs = new double*[validationData->nOfPatterns];
		for (int i = 0; i < validationData->nOfPatterns; i++) {
			validationData->inputs[i] = new double[validationData->nOfInputs];
			validationData->outputs[i] = new double[validationData->nOfOutputs];
		}
		
		// Mismo numero de entrada y de salidas
		TrainData->nOfInputs = trainDataset->nOfInputs;
		TrainData->nOfOutputs = trainDataset->nOfOutputs;
		// El resto de patrones perteneceran al conjunto de train
		TrainData->nOfPatterns = trainDataset->nOfPatterns - validationData->nOfPatterns;
		// Igual que antes pero para train
		TrainData->inputs = new double*[TrainData->nOfPatterns];
		TrainData->outputs = new double*[TrainData->nOfPatterns];
		for (int i = 0; i < TrainData->nOfPatterns; i++) {
			TrainData->inputs[i] = new double[TrainData->nOfInputs];
			TrainData->outputs[i] = new double[TrainData->nOfOutputs];
		}

		// Ahora obtenemos los patrones de forma aleatoria
		int *randomVector = integerRandomVectorWithoutRepeating(0,trainDataset->nOfPatterns-1,trainDataset->nOfPatterns);
		int index;

		// Los introducimos en los vectores correspondientes para cada dataset
		for(int i = 0; i < validationData->nOfPatterns; i++) {
			validationData->inputs[i] = trainDataset->inputs[randomVector[i]];
			validationData->outputs[i] = trainDataset->outputs[randomVector[i]];
			index = i;
		}
		// Los mimo pero para trian
		for (int j = 0; j < TrainData->nOfPatterns; j++) {
			TrainData->inputs[j] = trainDataset->inputs[randomVector[index]];
			TrainData->outputs[j] = trainDataset->outputs[randomVector[index]];
			index++;
		}
	}else{ // En el caso de que no se use train
		TrainData = trainDataset;
	} /* Se ha probado a usar un dataset auxiliar igual que train para no tener que modificar los argumentos de funciones posteriores,
		 pero no funcionaba correctamente el programa, por tanto, se ha dejado asi. Es por ello que funciones como 'test' tienen cambiado
		 el argumento con respecto a lo ficheros originales subidos en Moodle. */

	// Learning
	do {

		train(trainDataset,errorFunction);

		double trainError = test(trainDataset,errorFunction);
		if(countTrain==0 || trainError < minTrainError){
			minTrainError = trainError;
			copyWeights();
			iterWithoutImproving = 0;
		}
		else if( (trainError-minTrainError) < 0.00001)
			iterWithoutImproving = 0;
		else
			iterWithoutImproving++;

		if(iterWithoutImproving==50){
			cout << "We exit because the training is not improving!!"<< endl;
			restoreWeights();
			countTrain = maxiter;
		}

		countTrain++;

		if(validationDataset!=NULL){
			if(previousValidationError==0)
				previousValidationError = 999999999.9999999999;
			else
				previousValidationError = validationError;
			validationError = test(validationDataset,errorFunction);
			if(validationError < previousValidationError)
				iterWithoutImprovingValidation = 0;
			else if((validationError-previousValidationError) < 0.00001)
				iterWithoutImprovingValidation = 0;
			else
				iterWithoutImprovingValidation++;
			if(iterWithoutImprovingValidation==50){
				cout << "We exit because validation is not improving!!"<< endl;
				restoreWeights();
				countTrain = maxiter;
			}
		}

		cout << "Iteration " << countTrain << "\t Training error: " << trainError << "\t Validation error: " << validationError << endl;

	} while ( countTrain<maxiter );

	if ( (iterWithoutImprovingValidation!=50) && (iterWithoutImproving!=50))
		restoreWeights();

	cout << "NETWORK WEIGHTS" << endl;
	cout << "===============" << endl;
	printNetwork();

	cout << "Desired output Vs Obtained output (test)" << endl;
	cout << "=========================================" << endl;
	for(int i=0; i<testDataset->nOfPatterns; i++){
		double* prediction = new double[testDataset->nOfOutputs];

		// Feed the inputs and propagate the values
		feedInputs(testDataset->inputs[i]);
		forwardPropagate();
		getOutputs(prediction);
		for(int j=0; j<testDataset->nOfOutputs; j++)
			cout << testDataset->outputs[i][j] << " -- " << prediction[j] << " ";
		cout << endl;
		delete[] prediction;

	}

	*errorTest=test(testDataset,errorFunction);;
	*errorTrain=minTrainError;
	*ccrTest = testClassification(testDataset);
	*ccrTrain = testClassification(trainDataset);

}

// -------------------------
// Optional Kaggle: Save the model weights in a textfile
bool MultilayerPerceptron::saveWeights(const char * fileName)
{
	// Object for writing the file
	ofstream f(fileName);

	if(!f.is_open())
		return false;

	// Write the number of layers and the number of layers in every layer
	f << nOfLayers;

	for(int i = 0; i < nOfLayers; i++)
	{
		f << " " << layers[i].nOfNeurons;
	}
	f << " " << outputFunction;
	f << endl;

	// Write the weight matrix of every layer
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				if(layers[i].neurons[j].w!=NULL)
				    f << layers[i].neurons[j].w[k] << " ";

	f.close();

	return true;

}


// -----------------------
// Optional Kaggle: Load the model weights from a textfile
bool MultilayerPerceptron::readWeights(const char * fileName)
{
	// Object for reading a file
	ifstream f(fileName);

	if(!f.is_open())
		return false;

	// Number of layers and number of neurons in every layer
	int nl;
	int *npl;

	// Read number of layers
	f >> nl;

	npl = new int[nl];

	// Read number of neurons in every layer
	for(int i = 0; i < nl; i++)
	{
		f >> npl[i];
	}
	f >> outputFunction;

	// Initialize vectors and data structures
	initialize(nl, npl);

	// Read weights
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				if(!(outputFunction==1 && (i==(nOfLayers-1)) && (k==(layers[i].nOfNeurons-1))))
					f >> layers[i].neurons[j].w[k];

	f.close();
	delete[] npl;

	return true;
}
