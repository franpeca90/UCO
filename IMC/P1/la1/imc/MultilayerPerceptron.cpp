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
// Constructor: Default values for all the parameters
MultilayerPerceptron::MultilayerPerceptron()
{
	// Se ha completado el constructor con sus valores por defecto
	eta = 0.1;
	mu = 0.9;
	validationRatio = 0.0;
	decrementFactor = 1.0;
}

// ------------------------------
// Allocate memory for the data structures
// nl is the number of layers and npl is a vetor containing the number of neurons in every layer
// Give values to Layer* layers
int MultilayerPerceptron::initialize(int nl, int npl[]) {
	
	// Creamos un vector de capas, con el numero de capas que debera tener la red
	layers = new Layer[nl];

	for(int i = 0 ; i<nl ; i++){ // Recorremos todas las capas
		layers[i] = *new Layer; // Inicializamos el objeto
		layers[i].nOfNeurons = npl[i] // Indicamos el numero de neuronas para cada capa
		layers[i].neurons = new Neuron[npl[i]]; // Creamos todas las neuronas de esa capa
	}

	for(int i = 1 ; i<nl ; i++){ // Vamos a traves de las capas
		for(int j = 0 ; j<layers[i].nOfNeurons ; j++){ // Vamos a traves de cada neurona
			// Ahora inicializamos todas las variables de la clase neurona para todas las neuronas de todas las capas	
			layers[i].neurons[j].w = new double[layers[i-1].nOfNeurons + 1];
			layers[i].neurons[j].wCopy = new double[layers[i-1].nOfNeurons +1];
			layers[i].neurons[j].deltaW = new double[layers[i-1].nOfNeurons +1];
			layers[i].neurons[j].lastDeltaW = new double[layers[i-1].nOfNeurons +1];
		}
	}

	return 1;
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
// Feel all the weights (w) with random numbers between -1 and +1
void MultilayerPerceptron::randomWeights() {
	
	for(int i=1 ; i<nOfLayers ; i++){ // Comenzamos asignando pesos desde la primera capa oculta
		for (int j = 0; j < layers[i].nOfNeurons; j++){ // Para todas y cada una de las neuronas...
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) { // ... le asignamos valores a todos los pesos ...
				layers[i].neurons[j].w[k] = ((double)rand()/RAND_MAX)* pow(-1,rand()); //... entre -1 y +1
			}
		}
	}
}

// ------------------------------
// Feed the input neurons of the network with a vector passed as an argument
void MultilayerPerceptron::feedInputs(double* input) {
	for(int i=0 ; i<layers[0].nOfNeurons ; i++){
		layers[0].neurons[i].out = input[i];
	}
}

// ------------------------------
// Get the outputs predicted by the network (out vector the output layer) and save them in the vector passed as an argument
void MultilayerPerceptron::getOutputs(double* output)
{
	// Se muestran las salidas de la red
	for (int i = 0; i < layers[nOfLayers-1].nOfNeurons; i++) {
		output[i] = layers[nOfLayers-1].neurons[i].out;
	}
}

// ------------------------------
// Make a copy of all the weights (copy w in wCopy)
void MultilayerPerceptron::copyWeights() {
	//Vamos a acceder a los pesos de todas las neuronas con respecto a la capa anterior
	for (int i = 1; i < nOfLayers ; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
				// Las guardamos en la variable de la clase
				layers[i].neurons[j].wCopy[k] = layers[i].neurons[j].w[k];
			}
		}
	}
}

// ------------------------------
// Restore a copy of all the weights (copy wCopy in w)
void MultilayerPerceptron::restoreWeights() {
	// Es igual que copyWeights pero cambiando las variables
	for (int i = 1; i < nOfLayers ; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
				// Las guardamos en la variable de la clase
				layers[i].neurons[j].w[k] = layers[i].neurons[j].wCopy[k]; 
			}
		}
	}
}

// ------------------------------
// Calculate and propagate the outputs of the neurons, from the first layer until the last one -->-->
void MultilayerPerceptron::forwardPropagate() {
	for(int i=1 ; i<nOfLayers ; i++){ // Desde la primera capa oculta
		for(int j=0 ; j<layers[i].nOfNeurons ; j++){  
			double sum = 0.0;
			for(int k=0 ; k<layers[i-1].nOfNeurons ; k++){  // La salida depende de la anterior
				// Tomo la salida de la neurona anterior y su peso;
				sum = sum + (layers[i].neurons[j].w[k] * layers[i-1].neurons[j].out);
			}
		// Obtengo toda la suma
		sum = sum + (layers[i].neurons[j].w[layers[i-1].nOfNeurons])
		// Ya solo queda aplicar la sigmoide para ver la salida de la neurona
		layers[i].neurons[j].out = 1.0/(1.0 + -exp(-sum));
		}
	}
}

// ------------------------------
// Obtain the output error (MSE) of the out vector of the output layer wrt a target vector and return it
double MultilayerPerceptron::obtainError(double* target) {
	double single_error = 0.0;
	
	// Vammos por las neuronas de la capa final
	for (int i=0 ; i<layers[nOfLayers-1].nOfNeurons ; i++) {
		// Obtenemos el error en base a la salida
		single_error = single_error + (layers[nOfLayers-1].neurons[i].out-target[i]) * (layers[nOfLayers-1].neurons[i].out-target[i]);
	}
	
	return -1;
}


// ------------------------------
// Backpropagate the output error wrt a vector passed as an argument, from the last layer to the first one <--<--
void MultilayerPerceptron::backpropagateError(double* target) {

	double sum = 0.0;
	
	//Calculamos el delta de todas las neuronas de la capa de salida
	for(int i=0 ; i<layers[nOfLayers-1].nOfNeurons; j++){
		// Esto es la expresion de la derivada, se esta calculando el delta para la capa de salida (nOfLayers-1)
		layers[nOfLayers-1].neurons[i].delta = -1*(target[j]-layers[nOfLayers-1].neurons[j].out) * (layers[nOfLayers-1].neurons[j].out * (1-layers[nOfLayers-1].neurons[j].out));
	}

	// Ahora, recorremos las capas en orden descendente desde la anterior a la de salida
	for(int i=nOfLayers-2 ; i>0 ; i--){
		// Para la capa actual, recorremos sus neuronas
		for(int j=0 ; j<layers[i].nOfNeurons; j++){
			// Tomamos en cuenta tambien las neuronas de la capa siguiente, pues nos tomaremos datos de estas
			for(int k=0 ; k<layers[i+1].nOfNeurons ; k++){
				// Esto es la sumatoria de los pesos por el delta de la capa siguiente
				sum = sum + layers[i+1].neurons[k].w[j+1]*layers[i+1].neurons[k].delta;
			}
			// Ahora el delta de la capa actual es la sumatoria anterior por la salida de esa neurona por uno menos esa misma salida
			layers[i].neurons[j].delta = sum*layers[i].neurons[j].out*(1-layers[i].neurons[j].out));
			
			//Reseteamos la cuenta
			sum = 0.0;
		}
	}
}


// ------------------------------
// Accumulate the changes produced by one pattern and save them in deltaW
void MultilayerPerceptron::accumulateChange() {
	// Avanzamos por todas las capas desde la primera
	for(int i=1 ; i<nOfLayers; i++){
		// Recorremos todas las neuronas
		for(int j=0 ; j<layers[i].nOfNeurons ; j++){
			// Tomo las neuronas de la capa anterior
			for(int k=1 ; k<layers[i-1].nOfNeurons+1 ; k++){
				// El cambio viene dado por los deltas y la salida
				layers[i].neurons[j].deltaW[k] = layers[i].neurons[j].deltaW[k]+layers[i].neurons[j].delta*layers[i-1].neurons[k-1].out;
			}
			// Para la primera, el cambio es el propio delta, no depende de las salidas
			layers[i].neurons[j].deltaW[0] = layers[i].neurons[j].deltaW[0]+layers[i].neurons[j].delta;
		}
	}
}

// ------------------------------
// Update the network weights, from the first layer to the last one
void MultilayerPerceptron::weightAdjustment() {
	// Vamos a traves de las capas
	for (int i=1 ; i<nOfLayers ; i++) {
		// Para todas las neuronas
		for (int j=0 ; j<layers[i].nOfNeurons ; j++) {
			// El valor de mu cambia por cada capa
			auxMu = pow(decrementFactor, -((nOfLayers-1)-i)) * mu;
			// Tomamos las neuronas de la capa siguiente
			for (int k=1 ; k<layers[i-1].nOfNeurons+1 ; k++) {
				// El nuevo peso es el peso actual menos eta por la acumulacion de los pesos menos mu por eta por la acumulacion
				// Esto es aplicando el concepto de momentum
				layers[i].neurons[j].w[k] = layers[i].neurons[j].w[k]-(eta*layers[i].neurons[j].deltaW[k])-(muPerLayer*(eta*layers[i].neurons[j].lastDeltaW[k]));
			}
			layers[i].neurons[j].w[0] = layers[i].neurons[j].w[0]-(eta*layers[i].neurons[j].deltaW[0])-(muPerLayer*(eta*layers[i].neurons[j].lastDeltaW[0]))
		}
	}
}

// ------------------------------
// Print the network, i.e. all the weight matrices
void MultilayerPerceptron::printNetwork() {
	
	cout << "\n----------------------------";
	for (int i = 1; i < nOfLayers; i++){
		
		cout << "Layer " << i << std::endl;
		
		for (int j = 0; j < layers[i].nOfNeurons; j++){
			for (int k = 0; k < layers[i - 1].nOfNeurons + 1; k++)
				cout << layers[i].neurons[j].w[k] << " \n";
		}
		cout << "\n\n";
	}
	cout << "\n----------------------------";
}

// ------------------------------
// Perform an epoch: forward propagate the inputs, backpropagate the error and adjust the weights.
// input is the input vector of the pattern and target is the desired output vector of the pattern
void MultilayerPerceptron::performEpochOnline(double* input, double* target) {
	// Ahora relizamos todos los pasos para una sola epoca

	// Establecemos todos los deltas a 0
	for (int i=1; i<nOfLayers ; i++) {
		for (int j=0 ; j<layers[i].nOfNeurons; j++) {
			for (int k=0 ; k<layers[i-1].nOfNeurons+1; k++) {
				layers[i].neurons[j].deltaW[k] = 0;
			}
		}
	}

	// Realizamos la epoca con los mismos pasos que en las diapositivas de clase
	feedInputs(input);
	forwardPropagate();
	backpropagateError(target);
	accumulateChange();
	weightAdjustment();
}

// ------------------------------
// ------------------------------
// Read a dataset from a file name and return it
Dataset* MultilayerPerceptron::readData(const char *fileName) {
	// Lectura de datos. Funcion sacada de Moodle
	ifstream myFile(fileName);    // Create an input stream

    if (!myFile.is_open()) {
       cout << "ERROR: I cannot open the file " << fileName << endl;
       return NULL;
    }

	Dataset * dataset = new Dataset;
	if(dataset==NULL)
		return NULL;

	string line;
	int i,j;


	if( myFile.good()) {
		getline(myFile,line);   // Read a line
		istringstream iss(line);
		iss >> dataset->nOfInputs;
		iss >> dataset->nOfOutputs;
		iss >> dataset->nOfPatterns;
	}
	dataset->inputs = new double*[dataset->nOfPatterns];
	dataset->outputs = new double*[dataset->nOfPatterns];

	for(i=0; i<dataset->nOfPatterns; i++){
		dataset->inputs[i] = new double[dataset->nOfInputs];
		dataset->outputs[i] = new double[dataset->nOfOutputs];
	}

	i=0;
	while ( myFile.good()) {
		getline(myFile,line);   // Read a line
		if (! line.empty()) {
			istringstream iss(line);
			for(j=0; j< dataset->nOfInputs; j++){
				double value;
				iss >> value;
				if(!iss)
					return NULL;
				dataset->inputs[i][j] = value;
			}
			for(j=0; j< dataset->nOfOutputs; j++){
				double value;
				iss >> value;
				if(!iss)
					return NULL;
				dataset->outputs[i][j] = value;
			}
			i++;
		}
	}

	myFile.close();

	return dataset;
}

// ------------------------------
// Perform an online training for a specific trainDataset
void MultilayerPerceptron::trainOnline(Dataset* trainDataset) {
	int i;
	for(i=0; i<trainDataset->nOfPatterns; i++){
		performEpochOnline(trainDataset->inputs[i], trainDataset->outputs[i]);
	}
}

// ------------------------------
// Test the network with a dataset and return the MSE
double MultilayerPerceptron::test(Dataset* testDataset) {
	
	double mse = 0.0;

	// Usamos todos los patrones del dataset
	for(int i=0 ; i<testDataset->nOfPatterns ; i++){
		// Usamos las funciones ya creadas para obtener las salidas
		feedInputs(testDataset->inputs[i]);
		forwardPropagate();
		// En base a esas salidas, calculamos el error
		mse = mse + obtainError(testDataset->outputs[i]);
	}

	return mse / testDataset->nOfPatterns;

}


// Optional - KAGGLE
// Test the network with a dataset and return the MSE
// Your have to use the format from Kaggle: two columns (Id y predictied)
void MultilayerPerceptron::predict(Dataset* pDatosTest)
{
	int i;
	int j;
	int numSalidas = layers[nOfLayers-1].nOfNeurons;
	double * obtained = new double[numSalidas];
	
	cout << "Id,Predicted" << endl;
	
	for (i=0; i<pDatosTest->nOfPatterns; i++){

		feedInputs(pDatosTest->inputs[i]);
		forwardPropagate();
		getOutputs(obtained);
		
		cout << i;

		for (j = 0; j < numSalidas; j++)
			cout << "," << obtained[j];
		cout << endl;

	}
}

// ------------------------------
// Run the traning algorithm for a given number of epochs, using trainDataset
// Once finished, check the performance of the network in testDataset
// Both training and test MSEs should be obtained and stored in errorTrain and errorTest
void MultilayerPerceptron::runOnlineBackPropagation(Dataset * trainDataset, Dataset * pDatosTest, int maxiter, double *errorTrain, double *errorTest)
{
	int countTrain = 0;

	// Random assignment of weights (starting point)
	randomWeights();

	double minTrainError = 0;
	int iterWithoutImproving;
	double testError = 0;

	double validationError = 1;

	double previusValidationError = 0; // Variables para controlar cuando se debe de parar el programa,
	int iterWithoutImproving = 0; // esta especificado en el guion de las practicas
	int iterWithoutImprovingValidation = 0;

	Dataset* dataset_aux = NULL; //Dataset auxiliar que contendra temporalmente el dataset train original
	Dataset* validation_part = NULL; // y la otra particion sera para la validacion


	// Ahora realizamos la particion del dataset inicial de train para poder usar la validacion
	// Generate validation data
	if(validationRatio > 0 && validationRatio < 1){
		dataset_aux = trainDataset; // La informacion original la contendra esta variable auxiliar

		// Damos los valores al nuevo dataset de validacion
		// El numero de entradas y de salidas no varia
		validation_part->nOfInputs = dataset_aux->nOfInputs;
		validation_part->nOfOutputs = dataset_aux->nOfOutputs;
		
		// Lo que si cambia es la proporcion de patrones usada
		validation_part->nOfPatterns = dataset_aux->nOfPatterns*validationRatio;
		 
		validation_part->inputs = new double*[validation_part->nOfPatterns];
		validation_part->outputs = new double*[validation_part->nOfPatterns];
		for(int i=0 ; i<validation_part.nOfPatterns ; i++){
			validation_part->inputs[i] = new double[validation_part->nOfInputs];
			validation_part->outputs[i] = new double[validation_part->nOfOutputs];
		}


		// Ahora formamos el nuevo dataset de entrenamiento
		// Las entradas y salidas son las mismas
		trainDataset->nOfInputs = dataset_aux->nOfInputs;
		trainDataset->nOfOutputs = dataset_aux->nOfOutputs;

		// Cambia la proporcion de patrones usados
		trainDataset->nOfPatterns = dataset_aux->nOfPatterns - validation_part->nOfPatterns;
		
		trainDataset->inputs = new double*[trainDataset->nOfPatterns];
		trainDataset->outputs = new double*[trainDataset->nOfPatterns];

		for (int i = 0; i < trainDataset->nOfPatterns; i++) {
			trainDataset->inputs[i] = new double[trainDataset->nOfInputs];
			trainDataset->outputs[i] = new double[trainDataset->nOfOutputs];
		}

		// Ahora seleccionamos de forma aleatoria los patrones que habra en cada dataset
		// Usamos un vector auxiliar para guardar los resultados de las posiciones aleatorias que seran usadas
		int* aux = integerRandomVectoWithoutRepeating(0,dataset_aux->nOfPatterns-1,dataset_aux->nOfPatterns);
		int* index = 0;

		for(int i = 0; i<validation_part->nOfPatterns; i++) {
			validation_part->inputs[i] = dataset_aux->inputs[aux[i]];
			validation_part->outputs[i] = dataset_aux->outputs[aux[i]];
			index = i; // Serviara para ver "por donde se ha quedado" el vector
		}

		// Ahora, la parte de train, empezara por la posicion donde se encontraba el vector al final del bucle anterior
		for (int j = 0 ; j<trainDataset->nOfPatterns ; j++) {
			trainDataset->inputs[j] = dataset_aux->inputs[aux[i+j]]; // Empiezo desde la posicion donde me he quedado
			trainDataset->outputs[j] = dataset_aux->outputs[aux[i+j]]; // De esta forma solo tengo que aumentar j
		}
	} 


	// Learning
	do {

		trainOnline(trainDataset);
		double trainError = test(trainDataset);
		if(countTrain==0 || trainError < minTrainError){ // Segunda condicion de parada
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

		// Check validation stopping condition and force it
		// BE CAREFUL: in this case, we have to save the last validation error, not the minimum one
		// Apart from this, the way the stopping condition is checked is the same than that
		// applied for the training set
		
		// Tercera condicion de parada
		// Solo se comprueba si el usuario ha decidido usar validacion cruzada
		if(validationRatio > 0 && validationRatio < 1){
			// Testeamos el conjunto de validacion
			validationError = test(validationError);
			// Realizamos la copia cada vez que el error es menor que el anterior
			if(countTrain=0 || validationError < previusValidationError){
				copyWeights();
				iterWithoutImprovingValidation = 0;
			} else if ((validationError-previusValidationError) < 0.00001){// Tolerancia
				iterWithoutImprovingValidation = 0;
			} else {
				iterWithoutImprovingValidation++;
			}

			// Si tras 50 iteraciones no ha disminuido el error, restauramos
			if(iterWithoutImprovingValidation == 50){
				// Similar a la parada anterior
				cout << "We exit because the validation is not improving!!"<< endl;
				restoreWeights();
				countTrain = maxiter;
			}
			// El error en la siguiente iteracion sera considerado como el previo
			previusValidationError = validationError
		}

		cout << "Iteration " << countTrain << "\t Training error: " << trainError << "\t Validation error: " << validationError << endl;

	} while ( countTrain<maxiter ); // Primera condicion de parada

	cout << "NETWORK WEIGHTS" << endl;
	cout << "===============" << endl;
	printNetwork();

	cout << "Desired output Vs Obtained output (test)" << endl;
	cout << "=========================================" << endl;
	for(int i=0; i<pDatosTest->nOfPatterns; i++){
		double* prediction = new double[pDatosTest->nOfOutputs];

		// Feed the inputs and propagate the values
		feedInputs(pDatosTest->inputs[i]);
		forwardPropagate();
		getOutputs(prediction);
		for(int j=0; j<pDatosTest->nOfOutputs; j++)
			cout << pDatosTest->outputs[i][j] << " -- " << prediction[j] << " ";
		cout << endl;
		delete[] prediction;

	}

	testError = test(pDatosTest);
	*errorTest=testError;
	*errorTrain=minTrainError;

}

// Optional Kaggle: Save the model weights in a textfile
bool MultilayerPerceptron::saveWeights(const char * archivo)
{
	// Object for writing the file
	ofstream f(archivo);

	if(!f.is_open())
		return false;

	// Write the number of layers and the number of layers in every layer
	f << nOfLayers;

	for(int i = 0; i < nOfLayers; i++)
		f << " " << layers[i].nOfNeurons;
	f << endl;

	// Write the weight matrix of every layer
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				f << layers[i].neurons[j].w[k] << " ";

	f.close();

	return true;

}


// Optional Kaggle: Load the model weights from a textfile
bool MultilayerPerceptron::readWeights(const char * archivo)
{
	// Object for reading a file
	ifstream f(archivo);

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
		f >> npl[i];

	// Initialize vectors and data structures
	initialize(nl, npl);

	// Read weights
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				f >> layers[i].neurons[j].w[k];

	f.close();
	delete[] npl;

	return true;
}