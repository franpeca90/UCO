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
	return 0;
}

// ------------------------------
// Obtain a real random number in the range [Low,High]
double randomDouble(double Low, double High)
{
	return 0;
}

// ------------------------------
// Constructor: Default values for all the parameters
MultilayerPerceptron::MultilayerPerceptron()
{
	// Se ha completado el constructor con sus valores por defecto
	eta = 0.7;
	mu = 1;
	validationRatio = 0.0;
	decrementFactor = 1.0;
}

// ------------------------------
// Allocate memory for the data structures
// nl is the number of layers and npl is a vetor containing the number of neurons in every layer
// Give values to Layer* layers
int MultilayerPerceptron::initialize(int nl, int npl[]) {
	// La inicialización es similar a la practica anterior
	// Solo que tenemos que establecer a NULL en un caso especial
	// Esto es, cuando apliquemos SOFTMAX y nos encontremos en la ultima neurona de la ultima capa
	nOfLayers = nl;
	layers = new Layer [nOfLayers];

	for(int i=0;i<nOfLayers;i++){
		layers[i].nOfNeurons = npl[i];
		layers[i].neurons = new Neuron [layers[i].nOfNeurons];
	}

	for(int i=1 ; i<nOfLayers ; i++){
		for(int j=0 ; j<layers[i].nOfNeurons ; j++){
			if ((outputFunction == 1) && (i == nOfLayers-1) && (j == layers[i].nOfNeurons-1)){
				layers[i].neurons[j].w = NULL;
				layers[i].neurons[j].wCopy = NULL;
				layers[i].neurons[j].deltaW = NULL;
				layers[i].neurons[j].lastDeltaW = NULL;
			}else{
				layers[i].neurons[j].w = new double [layers[i-1].nOfNeurons+1];
				layers[i].neurons[j].wCopy = new double [layers[i-1].nOfNeurons+1];
				layers[i].neurons[j].deltaW = new double [layers[i-1].nOfNeurons+1];
				layers[i].neurons[j].lastDeltaW = new double [layers[i-1].nOfNeurons+1];
			}		
		}
	}
	return 0;
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

	for (int i = 1; i < nOfLayers ; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
				if (layers[i].neurons[j].w != NULL) {
					layers[i].neurons[j].w[k] = randomDouble(-1, 1);
				}
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
	for (int i=0 ; i<layers[nOfLayers-1].nOfNeurons ; i++) {
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
					layers[i].neurons[j].w[k] = layers[i].neurons[j].wCopy[k];
				} 
			}
		}
	}
}

// ------------------------------
// Calculate and propagate the outputs of the neurons, from the first layer until the last one -->-->
void MultilayerPerceptron::forwardPropagate() {
	// Se ha variado al forma de realizar la propagacion de la informacion
	for(int i=1 ; i<nOfLayers ; i++){ // Recorremos las capas desde la primera oculta
		double sum = 0.0; // Sumatoria del denominador de la softmax
		double sumNeuronas = 0.0;
		
		if(outputFunction == 1 && i==nOfLayers-1){// Caso en el que apliquemos la softmax
			// Solo contemplamos el caso en el que estemos en la ultima capa
			for(int j=0 ; j<layers[i].nOfNeurons ; j++){ // Recorremos todas esas neuronas
				if(layers[i].neurons[j].w!=NULL){ // Cuidado con las neuronas en NULL
					sum = 0.0; // Realizamos las operaciones para posteriormente usar la softmax
					sum = layers[i].neurons[j].w[0];
					for(int k=1 ; k<layers[i-1].nOfNeurons+1 ; k++){
						sum = sum + layers[i].neurons[j].w[k] * layers[i-1].neurons[k-1].out;
					}
					sumNeuronas = sumNeuronas + exp(sum);				
				}
			}
		}

		for(int j=0 ; j<layers[i].nOfNeurons ; j++){ // Ahora recorro todas las capas
			if(layers[i].neurons[j].w!=NULL){ // Vuelvo a comprobar que no sean NULL
				layers[i].neurons[j].out = layers[i].neurons[j].w[0];
				for(int k=1 ; k<layers[i-1].nOfNeurons+1 ; k++){
					layers[i].neurons[j].out = layers[i].neurons[j].out + (layers[i].neurons[j].w[k] * layers[i-1].neurons[k-1].out);
				}
			} else {
				layers[i].neurons[j].out = 0.0;
			}

			// Ahora realizo la ultima operacion de la salida de las neuronas
			if((outputFunction) && (i==nOfLayers-1) ){ // En caso de usar softmax
				layers[i].neurons[j].out = exp(layers[i].neurons[j].out)/(1+(sumNeuronas));			
			} else { // En el caso de no usar softmax
				layers[i].neurons[j].out = 1/(1+exp(-(layers[i].neurons[j].out)));
			}
			
		}
		
	}	

}

// ------------------------------
// Obtain the output error (MSE) of the out vector of the output layer wrt a target vector and return it
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
double MultilayerPerceptron::obtainError(double* target, int errorFunction) {
	double single_error = 0.0;
	// Obtenemos las salidas
	double* salidas = new double[layers[nOfLayers-1].nOfNeurons];
	getOutputs(salidas);
	
	if(!errorFunction){ // Caso de MSE
		for (int i=0 ; i<layers[nOfLayers-1].nOfNeurons ; i++){		
			single_error = single_error + pow(salidas[i]-target[i],2);
		}
	} else { // Caso de la entropia
		for (int i=0 ; i<layers[nOfLayers-1].nOfNeurons ; i++){
			single_error = single_error + (target[i]*log(salidas[i]));
		}
	}
	single_error = single_error / layers[nOfLayers-1].nOfNeurons;
	return single_error;
}

// ------------------------------
// Backpropagate the output error wrt a vector passed as an argument, from the last layer to the first one <--<--
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::backpropagateError(double* target, int errorFunction) {
double acumulador;

	if(outputFunction == 0){//si no es softMax

		if(errorFunction == 0){
			for(int j=0;j<layers[nOfLayers-1].nOfNeurons;j++){//para 	 -2(d-out)out(1-out)para la sigmoide g()=out(1-out)
				this->layers[nOfLayers-1].neurons[j].delta = -2*(target[j]-layers[nOfLayers-1].neurons[j].out)*layers[nOfLayers-1].neurons[j].out*(1-layers[nOfLayers-1].neurons[j].out);//con el 2 disminuye el error
			}
		}else{
			for(int j=0;j<layers[nOfLayers-1].nOfNeurons;j++){//para cada neurona de salida calculamos su derivada entropia
				this->layers[nOfLayers-1].neurons[j].delta = -(target[j]/layers[nOfLayers-1].neurons[j].out)*layers[nOfLayers-1].neurons[j].out*(1-layers[nOfLayers-1].neurons[j].out);//con el 2 disminuye el error
			}
		}

	}else if(outputFunction == 1){//si es softMax

		if(errorFunction == 0){
			for(int j=0;j<layers[nOfLayers-1].nOfNeurons;j++){//para cada neurona de salida calculamos su derivada 
				this->layers[nOfLayers-1].neurons[j].delta = 0.0;
				for(int i=0;i<layers[nOfLayers-1].nOfNeurons;i++){//para cada neurona de salida calculamos su derivada 
					int Findicador;
					if(i==j){
						Findicador = 1;
					}else{
						Findicador = 0;
					}
					this->layers[nOfLayers-1].neurons[j].delta += (target[i]-layers[nOfLayers-1].neurons[i].out)*layers[nOfLayers-1].neurons[j].out*(Findicador-layers[nOfLayers-1].neurons[i].out);//con el 2 disminuye el error
				}
				this->layers[nOfLayers-1].neurons[j].delta=-2*this->layers[nOfLayers-1].neurons[j].delta;
			}
		}else{
			for(int j=0;j<layers[nOfLayers-1].nOfNeurons;j++){//para cada neurona de salida calculamos su derivada 
				this->layers[nOfLayers-1].neurons[j].delta = 0.0;
				for(int i=0;i<layers[nOfLayers-1].nOfNeurons;i++){//para cada neurona de salida calculamos su derivada 
					int Findicador;
					if(i==j){
						Findicador = 1;
					}else{
						Findicador = 0;
					}
					this->layers[nOfLayers-1].neurons[j].delta += (target[i]/layers[nOfLayers-1].neurons[i].out)*layers[nOfLayers-1].neurons[j].out*(Findicador-layers[nOfLayers-1].neurons[i].out);//con el 2 disminuye el error
				}
				this->layers[nOfLayers-1].neurons[j].delta=-(this->layers[nOfLayers-1].neurons[j].delta);
			}	
		}
	}
	//para las capas ocultas
	for(int i=this->nOfLayers-2;i>0;i--){//comienzo desde la capa final hasta la capa 1
		for(int j=0;j<layers[i].nOfNeurons+1;j++){//para todos los pesos despues añado 1 para no coger el sesgo
			acumulador = 0.0;		
			for(int x=0;x<layers[i+1].nOfNeurons;x++){//numero de neuronas de la capa siguiente
				if (not(outputFunction == 1 and layers[i+1].neurons[x].w==NULL)){
					acumulador += layers[i+1].neurons[x].w[j+1]*layers[i+1].neurons[x].delta;//almaceno el peso de la neurona siguiente con su respectivo delta
				}
			}		
			layers[i].neurons[j].delta = acumulador * layers[i].neurons[j].out * (1-layers[i].neurons[j].out);//calculo el delta de esta neurona con la derivada de la sigmoide con la sumatoria anterior
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
			if (layers[i].neurons[j].deltaW != NULL){ // Comprobamos que no tomemos el NULL. Necesario comprobar el outputFunction?
				for(int k=1 ; k<layers[i-1].nOfNeurons+1 ; k++){
					// El cambio viene dado por los deltas y la salida
					layers[i].neurons[j].deltaW[k] = layers[i].neurons[j].deltaW[k]+layers[i].neurons[j].delta*layers[i-1].neurons[k-1].out;
				}
				// Para la primera, el cambio es el propio delta, no depende de las salidas
				layers[i].neurons[j].deltaW[0] = layers[i].neurons[j].deltaW[0] + layers[i].neurons[j].delta;
			}
		}
	}
}

// ------------------------------
// Update the network weights, from the first layer to the last one
void MultilayerPerceptron::weightAdjustment() {
	// Vamos a traves de las capas
	//double auxMu = 0.0;
	double auxEta = 0.0;
	int N;

	if(online){
		N = 1; // En el caso online se queda tal como esta
	} else {
		N = nOfTrainingPatterns; // En offline, hay que dividir entre el total de patrones usados
	}
	for(int i=1 ; i < nOfLayers ; i++){ // Voy por todas las capas
		auxEta = pow(decrementFactor, -1*((nOfLayers-1)-i))*eta; // Para cada capa, cambio el valor de eta
		for(int j=0 ; j<layers[i].nOfNeurons ; j++){
			if (layers[i].neurons[j].w != NULL) { // Con cuidado de no usar una neurona NULL
				for(int k=1 ; k<layers[i-1].nOfNeurons+1 ; k++){ // Voy a traves de las neuronas
					// Realizo el cambio de pesos segun la expresion del "momento" 
					layers[i].neurons[j].w[k] = layers[i].neurons[j].w[k]-((auxEta * layers[i].neurons[j].deltaW[k])/N)-((mu * (auxEta * layers[i].neurons[j].lastDeltaW[k]))/N);
				}
				layers[i].neurons[j].w[0] = layers[i].neurons[j].w[0]-((auxEta * layers[i].neurons[j].deltaW[0])/N)-((mu * (auxEta * layers[i].neurons[j].lastDeltaW[0]))/N);
			}
		}
	}
}

// ------------------------------
// Print the network, i.e. all the weight matrices
void MultilayerPerceptron::printNetwork() {
	
	for (int i = 1; i < nOfLayers; i++){
		// Indicamos de que capa vamos a mostrar los pesos
		cout << "Layer " << i << std::endl;
		// Mostramos los pesos de la neurona
		for (int j = 0; j < layers[i].nOfNeurons; j++){
			if (layers[i].neurons[j].w!=NULL){ // Caso de la neurona a NULL
				for (int k = 0; k < layers[i - 1].nOfNeurons + 1; k++){
					cout << layers[i].neurons[j].w[k] << " \n";
				}
			}
		}
		cout << "\n\n";
	}
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
	if(online){
		for (int i=1; i<nOfLayers ; i++) {
			for (int j=0 ; j<layers[i].nOfNeurons; j++) {
				for (int k=0 ; k<layers[i-1].nOfNeurons+1; k++) {
					if(layers[i].neurons[j].deltaW!=NULL){
						layers[i].neurons[j].deltaW[k] = 0.0;
					}
				}
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
// Train the network for a dataset (one iteration of the external loop)
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::train(Dataset* trainDataset, int errorFunction) {
	
	if (!online){ // Para el caso off-line, los deltas deben de establecerse aqui a 0
		for (int i = 1; i < nOfLayers; i++) {
			for (int j = 0; j < layers[i].nOfNeurons; j++) {
				for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
					if (layers[i].neurons[j].deltaW != NULL) {
						layers[i].neurons[j].deltaW[k] = 0;
					}
				}
			}
		}
	}


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
	// Se podria haber usado una funcion como la 'predict'
	double total_error = 0.0;

	// Usamos todos los patrones del dataset
	for(int i=0 ; i<dataset->nOfPatterns ; i++){
		// Usamos las funciones ya creadas para obtener las salidas
		feedInputs(dataset->inputs[i]);
		forwardPropagate();
		// En base a esas salidas, calculamos el error
		total_error = total_error + obtainError(dataset->outputs[i], errorFunction);
	}
	// Calculamos el error cuadratico medio final y lo de volvemos
	total_error = total_error / dataset->nOfPatterns;
	return total_error;

}


// ------------------------------
// Test the network with a dataset and return the CCR
double MultilayerPerceptron::testClassification(Dataset* dataset) {
		double acumulador = 0.0;
	//cout<<"tamaño"<<dataset->nOfOutputs<<endl;
	/*double ** MatrizConfusion = new double * [dataset->nOfOutputs];
	for(int i = 0; i < dataset->nOfOutputs; i++){
		MatrizConfusion[i] = new double [dataset->nOfOutputs];
	}
	for(int i=0; i<dataset->nOfOutputs; i++){
		for(int j=0; j<dataset->nOfOutputs; j++){
			MatrizConfusion[i][j]=0;
		}
	}*/


	for(int i=0; i<dataset->nOfPatterns; i++){
		feedInputs(dataset->inputs[i]);
		forwardPropagate();
		
		int maxIndEsp = 0;
		int maxIndDes = 0;
		double * VectorSalidas = new double [dataset->nOfOutputs];
		this->getOutputs(VectorSalidas);

		for(int j=1; j<dataset->nOfOutputs; j++){				
			if(VectorSalidas[maxIndEsp]<VectorSalidas[j]){
				maxIndEsp = j;
			}
			if(dataset->outputs[i][maxIndDes]<dataset->outputs[i][j]){
				maxIndDes = j;
			}
		}


		//MatrizConfusion[maxIndDes][maxIndEsp]=MatrizConfusion[maxIndDes][maxIndEsp]+1;

		//cout<<VectorSalidas[maxIndEsp]<<"--"<<dataset->outputs[i][maxIndDes]<<endl;
		//cout<<maxIndEsp<<"--"<<maxIndDes<<endl;
		if(maxIndEsp==maxIndDes){
			
			acumulador++;
		}/*else{
			cout<<"Error encontrado en -> "<<i<<endl;
		}*/
	}
	/*for(int i=0; i<dataset->nOfOutputs; i++){
		for(int j=0; j<dataset->nOfOutputs; j++){
			cout<< MatrizConfusion[i][j]<<"   ";
		}
		cout<<endl;
	}*/

	return (100*acumulador/(double)dataset->nOfPatterns);

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

		train(TrainData,errorFunction);

		double trainError = test(TrainData,errorFunction);
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

	if ((iterWithoutImprovingValidation!=50) && (iterWithoutImproving!=50))
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
