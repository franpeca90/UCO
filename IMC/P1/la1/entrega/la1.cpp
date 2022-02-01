//============================================================================
// Introduction to computational models
// Name        : la1.cpp
// Author      : Pedro A. Gutiérrez
// Version     :
// Copyright   : Universidad de Córdoba
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ctime>    // To obtain current time time()
#include <cstdlib>  // To establish the seed srand() and generate pseudorandom numbers rand()
#include <string.h>
#include <math.h>

#include "imc/MultilayerPerceptron.h"


using namespace imc;
using namespace std;

int main(int argc, char **argv) {
    // Process arguments of the command line
    
    bool tflag = 0, Tflag = 0, wflag = 0, pflag = 0;
    char *Tvalue = NULL, *wvalue = NULL;
    int c;

    opterr = 0;

    // Declaracion de variables necesarias
    int niter = 1000;
    int nOfLayers = 1;
    int nOfNeurons = 5;
    double eta = 0.1;
    double mu = 0.9;
    double valRatio = 0.0;
    double decrementFactor = 1;
    char* trainFileName = NULL;

    // a: Option that requires an argument
    // a:: The argument required is optional
    while ((c = getopt(argc, argv, "t:i:l:n:e:m:v:h:d:T:w:p")) != -1)
    {
        // The parameters needed for using the optional prediction mode of Kaggle have been included.
        // You should add the rest of parameters needed for the lab assignment.
        switch(c){
            // Argumentos de la parte obligatoria
            case 't': // Datos de entrenamiento
                tflag = true;
                trainFileName = optarg;
                break;
            case 'T': // Datos de test
                Tflag = true;
                Tvalue = optarg;
                break;
            case 'i': // Numero de iteraciones, por defecto 1000
                niter = atoi(optarg);
                break;
            case 'l': // Numero de capas ocultas, por defecto 1
                nOfLayers = atoi(optarg);
                break;
            case 'h': // Numero de neuronas por capa, por defecto 5
                nOfNeurons = atoi(optarg);
                break;
            case 'e': // Tasa de aprendizaje, por defecto 0.1
                eta = atof(optarg);
                break;
            case 'm': // Valor del parametro mu, por defecto 0.9
                mu = atof(optarg);
                break;
            case 'v': // Ratio de patrones para validacion, por defecto 0.0
                valRatio = atof(optarg);
                break;
            case 'd': // Factor de decremento para cada capa, por defecto 1
                decrementFactor = atof(optarg);
                break;

            // Argumentos de la parte opcional
            case 'w':
                wflag = true;
                wvalue = optarg;
                break;
            case 'p':
                pflag = true;
                break;
            // ---------
            case '?': // Caso en el que se necesite mostrar ayuda por el terminal
                if (optopt == 't' || optopt == 'i' || optopt == 'l' || optopt == 'h' || optopt == 'e' ||
                    optopt == 'm' || optopt == 'v' || optopt == 'd' ||
                    optopt == 'T' || optopt == 'w' || optopt == 'p')
                    fprintf (stderr, "The option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                             "Unknown character `\\x%x'.\n",
                             optopt);
                return EXIT_FAILURE;
            default:
                return EXIT_FAILURE;
        }
    }

    // El programa termina en caso de que no se introduzcan los argumentos minimos necesarios
    if(!tflag || !Tflag){
        cout<<"Error: Incorrect arguments"<<endl;
        return EXIT_FAILURE;
    }

    if (!pflag) {
        //////////////////////////////////
        // TRAINING AND EVALUATION MODE //
        //////////////////////////////////

        // Multilayer perceptron object
    	MultilayerPerceptron mlp;

        // Parameters of the mlp. For example, mlp.eta = value;
    	int iterations = niter; // This should be corrected (Corrected)
        // Ahora cambiamos todas las variables del objeto mlp
        mlp.eta = eta;
        mlp.mu = mu;
        mlp.decrementFactor = decrementFactor;
        mlp.validationRatio = valRatio;

        // Ahora indicamos las rutas de los datasets
        // Read training and test data: call to mlp.readData(...)

    	Dataset* trainDataset = mlp.readData(trainFileName); // This should be corrected (Corrected)
    	Dataset* testDataset = mlp.readData(Tvalue); // This should be corrected (Corrected)

        // Mi variable layers tiene TODAS las capas, entrada, salida y ocultas
        int layers = nOfLayers+2;
    	int * topology = new int[nOfLayers+2]; // This should be corrected

        topology[0] = trainDataset->nOfInputs;
        for (int i = 1; i < layers-1; i++) {
            topology[i] = nOfNeurons;
        }
        topology[layers-1] = trainDataset->nOfOutputs;

        // Initialize the network using the topology vector
        mlp.initialize(layers,topology);

        // Seed for random numbers
        int seeds[] = {1,2,3,4,5};
        double *testErrors = new double[5];
        double *trainErrors = new double[5];
        double bestTestError = 1;
        for(int i=0; i<5; i++){
            cout << "**********" << endl;
            cout << "SEED " << seeds[i] << endl;
            cout << "**********" << endl;
            srand(seeds[i]);

            mlp.runOnlineBackPropagation(trainDataset,testDataset,iterations,&(trainErrors[i]),&(testErrors[i]));

            cout << "We end!! => Final test error: " << testErrors[i] << endl;

            // We save the weights every time we find a better model
            if(wflag && testErrors[i] <= bestTestError)
            {
                mlp.saveWeights(wvalue);
                bestTestError = testErrors[i];
            }
        }

        cout << "WE HAVE FINISHED WITH ALL THE SEEDS" << endl;

        double averageTrainError = 0, stdTrainError = 0;
        double averageTestError = 0, stdTestError = 0;

        // Obtain training and test averages and standard deviations
        double sumAverageTrain = 0, sumAverageTest = 0;
        double sumStdTrain = 0,  sumStdTest = 0;

        // Obtenemos la sumatoria de los errores tanto para train como para test
        for (int i = 0; i < 5; i++) {
            sumAverageTrain = sumAverageTrain + trainErrors[i];
            sumAverageTest = sumAverageTest + testErrors[i];
        }
        
        // Calculamos la media. Ser usara tambien para la desviacion tipica
        averageTrainError = sumAverageTrain / 5; // Dividimos entre el total de semillas
        averageTestError = sumAverageTest / 5;

        // Calculamos la desviacion tipica

        for (int i = 0; i < 5; i++) {
          sumStdTrain = sumStdTest + (trainErrors[i] - averageTrainError) * (trainErrors[i] - averageTrainError);
          sumStdTest = sumStdTest + (testErrors[i] - averageTestError) * (testErrors[i] - averageTestError);
        }

        stdTrainError = sqrt(sumStdTrain/5);
        stdTestError = sqrt(sumStdTest/5);
        

        cout << "FINAL REPORT" << endl;
        cout << "************" << endl;
        cout << "Train error (Mean +- SD): " << averageTrainError << " +- " << stdTrainError << endl;
        cout << "Test error (Mean +- SD):          " << averageTestError << " +- " << stdTestError << endl;
        return EXIT_SUCCESS;
    }
    else {

        //////////////////////////////
        // PREDICTION MODE (KAGGLE) //
        //////////////////////////////
        
        // Multilayer perceptron object
        MultilayerPerceptron mlp;

        // Initializing the network with the topology vector
        if(!wflag || !mlp.readWeights(wvalue))
        {
            cerr << "Error while reading weights, we can not continue" << endl;
            exit(-1);
        }

        // Reading training and test data: call to mlp.readData(...)
        Dataset *testDataset;
        testDataset = mlp.readData(Tvalue);
        if(testDataset == NULL)
        {
            cerr << "The test file is not valid, we can not continue" << endl;
            exit(-1);
        }

        mlp.predict(testDataset);

        return EXIT_SUCCESS;
    }

    
}

