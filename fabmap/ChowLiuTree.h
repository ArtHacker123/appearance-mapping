// implementation for the Chow Liu trees
// with the offline learning part
// and the online calculation part
// author: Richard

#ifndef CHOWLIUTREE_H_
#define CHOWLIUTREE_H_
#include <map>
#include <limits>
#include <cfloat>
#include <iostream>
#include <fstream>
#include <ctime>
#include "math.h"
#include "InterfaceObservationLikelihood.h"
#include "InterfaceDetectorModel.h"
#include "InterfacePlaceModel.h"

//const std::string CLTreeFilename = "ChowLiuTree.txt";

class ChowLiuTree : public InterfaceObservationLikelihood
{
public :
	// constructor which trains the model using the training_data and saves the model into pCLTreeFilename
	ChowLiuTree(std::vector<std::vector<int> > training_data, std::string pCLTreeFilename);
	// constructor which loads the model from pCLTreeFilename
	ChowLiuTree(std::string pCLTreeFilename);
	~ChowLiuTree();

	// returns p(Z_k | L_i) as defined in equations (9)-(14) for the Chow Liu trees, i=location, Z_k=observations
	virtual double evaluate(std::vector<int> observations, int location, InterfaceDetectorModel* detectorModel, InterfacePlaceModel* placeModel);

	// returns the marginal probability for observing a single attribute p(z_attr = val)
	virtual double getMarginalPriorProbability(int attr, int val);

	// returns the whole marginal probabilities vector
	virtual std::vector<std::vector<double> >& getMarginalPriorProbabilities() { return mMarginalPriorProbability; };

	// returns p(Z_k | L_u) for a randomly sampled place L_u with randomly sampled obervations Z_k as needed in equation (17)
	virtual double sampleNewPlaceObservation(InterfaceDetectorModel* detectorModel);

private:
	std::vector< std::vector<double> > calculateMutualInformation();

	void primMaximumSpanningTree(std::vector< std::vector<double> > mutualInf);

	// after calculating the first order dependencies this function calculates the generative model from the training data
	void generateChowLiuProbabilities();

	// saves the Chow Liu Tree model
	void saveModel(std::string pCLTreeFilename);
	
	// loads the Chow Liu Tree model from file
	void loadModel(std::string filename);

	//the training data in the form [image[histogram of image]] = [sample][attribute]
	std::vector<std::vector<int> > mTrainingData;

	//discrete attribute sizes
	std::vector<int> mAttributeSizes;

	// mParentIndex[i] = the index of the parent attribute to atrribute i
	std::vector<int> mParentIndex;

	// stores the ChowLiu approximation probabilities mProbabilityModel[attr][a][b] stands for p( attr=a | parent(attr)=b )
	std::vector<std::vector<std::vector<float> > > mProbabilityModel;

	// stores the marginal probability for observing a single attribute p(z_attr = val) as mMarginalPriorProbability[attr][val]
	std::vector<std::vector<double> > mMarginalPriorProbability;
};

#endif /* CHOWLIUTREE_H_ */
