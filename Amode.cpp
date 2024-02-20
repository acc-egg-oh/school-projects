#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
using namespace std;

float **createDataMatrix(int numElement, int numSample)
{
    // Create a 2D data matrix of size numElement and numSample
    float** RFData = new float*[numElement];
    //using a nested for loop to initialize the index of double pointer array
    for (int n = 0; n < numElement; n++) {
        RFData[n] = new float[numSample];
        for (int i = 0; i < numSample; i ++) {
            //initialize to 0 to prevent any possible errors when loading data later
            RFData[n][i] = 0;
        }
    }
    return RFData;
}

int loadRFData(float **RFData, const char *fileName, int numElement, int numSample)
{
    // Open the text file fileName, read the data and store into RFData
    ifstream input;
    input.open(fileName);
    //will kill program if there is problem with inputting the file
    if (!input) {
        //main file will print out error statement
        return -1; 
    }

    //using nested for loop to initialize array RFData
    for (int i = 0; i < numElement; i++) {
        for (int n = 0; n < numSample; n++) {
            //stores const char into store using getline() to get input
            string store;
            getline(input, store);
            istringstream stores(store);
            //stores into RFData
            stores >> RFData[i][n];
        }
    }

    input.close();
    
    return 0;
}

// Create an array containing the depth location (in z-direction) for each pixel on the scanline
float *genScanlineLocation(int &numPixel)
{
    //create variable to store the scanLineDepth
    float scanLineDepth = 0;

    //ask user for scanline depth and number of pixel
    cout<<"Please input how deep you would like the scanline to be: ";
    cin>>scanLineDepth;
    cout<<"Please input the number of pixels of scanline: ";
    cin>>numPixel;

    //create a float pointer array to store the scanine depth later
    float* scanLineLocation = new float[numPixel];

    //initilize range to be used for calculating how much the depth should increment
    int range = numPixel - 1;
    //calculates how much the depth will increment per each location
    float depth = scanLineDepth/range;

    for (int i = 0; i < numPixel; i ++){
        //calculates the depth per each location and stores it in scanlineLocation
        scanLineLocation[i] = depth*(i);
    }

    return scanLineLocation;
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *genElementLocation(int numElement, float PITCH)
{
    //define and declare an array to store the element's location
    float* eleLocation = new float[numElement];
    for (int n = 0; n < numElement; n++){
        //stores calculations for the nth element's location in eleLocation
        eleLocation[n] = (n - (numElement-1.0)/2.0)*PITCH;
    }

    return eleLocation;
}

// Allocate memory to store the beamformed scanline
float *createScanline(int numPixel)
{
    float *scanLine = new float[numPixel];
    for (int i = 0; i < numPixel; i++) {
        //initialize each index of scanline to 0 to minimize chance of future errors
        scanLine[i] = 0;
    }

    return scanLine;
}

// Beamform the A-mode scanline
void beamform(float *scanline, float **realRFData, float **imagRFData, float *scanlinePosition, float *elementPosition, int numElement, int numSample, int numPixel, float FS, float SoS)
{
    int** sample = new int*[numPixel];

    for (int i = 0; i < numPixel; i++) {
        sample[i] = new int[numElement];
        for (int n = 0; n < numElement; n ++) {
            //combines calculation for the forward and backward movement times of the beams to calculate total time
            // and use the total time to calculate for the sample
            sample[i][n] = floor(((scanlinePosition[i]/SoS) + (sqrt(pow(scanlinePosition[i],2) + pow(elementPosition[n],2)))/SoS)*FS);
        }
    }

    //define and declare float pointer arrays to store the real and imaginary parts of data
    float* real = new float[numPixel];
    float* imag = new float[numPixel];
    
    for (int i = 0; i < numPixel; i++) {
        for (int n = 0; n < numElement; n ++) {
            //storing data in real and imag to generate the real part and the imaginary part
            real[i] += realRFData[n][sample[i][n]];
            imag[i] += imagRFData[n][sample[i][n]];
        }
    }

    for (int i = 0; i < numPixel; i++) {
        //calculating the corresponding echo magnitude at the i scanline location and store in scanline
        scanline[i] = sqrt((pow(real[i],2)) + (pow(imag[i],2))); //
    }
}

// Write the scanline to a csv file
int outputScanline(const char *fileName, float *scanlinePosition, float *scanline, int numPixel)
{
    //create output file name after fileName in main file
    ofstream output;
    output.open(fileName);

    //if program fails to create/open an output file, return -1 and kill the program
    if (!output.good()) {
        //main file prints out error statement when returned -1
        return -1;
    }

    for (int i = 0; i < numPixel; i++) {
        //output the scanline location and the scanline to the cvs file
        output << scanlinePosition[i]<<", "<<scanline[i] << endl;
    }

    output.close();

    return 0;
}

// Destroy all the allocated memory
void destroyAllArrays(float *scanline, float **realRFData, float **imagRFData, float *scanlinePosition, float *elementPosition, int numElement, int numSample, int numPixel)
{
    //iterates through the double pointer arrays to delete the arrays in the array
    for (int i = 0; i < numElement; i++){
        delete[] realRFData[i];
        delete[] imagRFData[i];
    }

    //delete all arrays to free memory space that is no longer needed
    delete[] scanline;
    delete[] scanlinePosition;
    delete[] elementPosition;
    delete[] realRFData;
    delete[] imagRFData;
}
