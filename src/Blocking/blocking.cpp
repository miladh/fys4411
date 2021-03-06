#include "blocking.h"

Blocking::Blocking(const int &nProcess):
    nNodes(nProcess)
{
}


/************************************************************
Name:
Description:
*/
void Blocking::doBlocking()
{
    vec data = readDataFromFile();
    int N = data.n_elem;
    int maxBlockSize = (int) N/10;

    if(maxBlockSize > maxBlockSizeTreshold)
        maxBlockSize = maxBlockSizeTreshold;

    mat results(3, maxBlockSize/deltaBlockSize);
    string outFile = dataPath + outFilename;

    for (int i = 1; i*deltaBlockSize <= maxBlockSize; i++) {
        int blockSize = i*deltaBlockSize;
        results.col(i-1) = computeBlock(data, blockSize);
    }

    results.save(outFile, arma_ascii);
}


/************************************************************
Name:
Description:
*/
vec Blocking::readDataFromFile()
{
    vec data;

    // Loading the first file
    stringstream file;
    file << dataPath << dataName << 0 << ".mat";
    data.load(file.str());

    // Loading the rest of the files
    vec data_i;
    for (int i = 1; i < nNodes; i++) {
        file.str("");
        file << dataPath << dataName << i << ".mat";
        data_i.load( file.str() );
        data = join_cols(data, data_i);
    }

    return data;
}


/************************************************************
Name:
Description:
*/
vec Blocking::computeBlock(const vec &data, int blockSize)
{
    int samples = data.size();
    int blocks = int(samples / blockSize);
    vec averageEnergyBlock = zeros(blocks);

    // Computing the mean value of every block
    double energySum;
    for (int i = 0; i < blocks; i++) {
        // Finding the average over one block
        energySum = 0;
        for (int j = i * blockSize; j < i * blockSize + blockSize; j++){
            energySum += data(j);
        }
        averageEnergyBlock(i) = energySum / blockSize;
    }

    // Calculating the mean and variance of all the blocks
    double E = 0;
    double E2 = 0;

    for (int i = 0; i < blocks; i++) {
        E += averageEnergyBlock(i);
        E2 += averageEnergyBlock(i) * averageEnergyBlock(i);
    }

    // Averaging
    E  /= blocks;
    E2 /= blocks;

    double sigma = E2 - E*E;
    sigma = sqrt(sigma/blocks);

    vec result(3);
    result(0) = blockSize;
    result(1) = E;
    result(2) = sigma;

    return result;
}



/************************************************************
Name:
Description:
*/

void Blocking::loadConfiguration(Config *cfg){
   cfg->lookupValue("setup.BlockingSettings.outFilename",outFilename);
   cfg->lookupValue("setup.BlockingSettings.dataPath",dataPath);
   cfg->lookupValue("setup.BlockingSettings.dataName",dataName);
   deltaBlockSize =cfg->lookup("setup.BlockingSettings.deltaBlockSize");
   maxBlockSizeTreshold = cfg->lookup("setup.BlockingSettings.maxBlockSizeTreshold");
   stepLength = cfg->lookup("setup.BlockingSettings.stepLength");
}























