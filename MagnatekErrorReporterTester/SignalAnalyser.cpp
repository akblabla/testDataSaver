#include "stdafx.h"
#include "SignalAnalyser.h"
#define PI atan(1)*4

SignalAnalyser::SignalAnalyser()
{
}


SignalAnalyser::~SignalAnalyser()
{
}

std::vector<double> SignalAnalyser::convolution(const std::vector<double> a, const std::vector<double> b)
{
	return std::vector<double>();
}

std::vector<double> SignalAnalyser::crosscorrelation(const std::vector<double> a, const std::vector<double> b)
{
	const std::vector<double>* shortest;
	std::vector<double> longest;
	std::vector<double> result;
	if (a.size() < b.size()) {
		shortest = &a;
		longest = std::vector<double>(shortest->size(), 0.0);
		for (size_t i = 0; i<b.size(); i++) {
			longest.push_back(b.at(i));
		}
	}
	else {
		shortest = &b;
		longest = std::vector<double>(shortest->size(), 0.0);
		for (size_t i = 0; i<a.size(); i++) {
			longest.push_back(a.at(i));
		}
	}
	for (size_t i = 0; i<shortest->size(); i++) {
		longest.push_back(0.0);
	}
	for (size_t i = 0; i < longest.size() - shortest->size(); i++) {
		double convolutionValue = 0;
		for (size_t j = 0; j < shortest->size(); j++) {
			convolutionValue += shortest->at(j)*longest.at(i + j);
		}
		result.push_back(convolutionValue);
	}
	return result;
}

std::vector<double> SignalAnalyser::resample(std::vector<double>& a, unsigned int n, unsigned int m)
{
	std::vector<double> resultVector;
	resultVector = upsample(a, n);
	resultVector = sincFilter(resultVector, 1.0/(2*m*n),1000);

	resultVector = downsample(resultVector, m);
	return resultVector;
}

std::vector<double> SignalAnalyser::sincFilter(std::vector<double>& a, double cutOffFreq, unsigned int zeroPadding)
{
	std::vector<double> zeroPaddedVector;
	for (unsigned int i = 0; i<zeroPadding;i++){
		zeroPaddedVector.push_back(0);
	}
	for (unsigned int i = 0; i<a.size(); i++) {
		zeroPaddedVector.push_back(a[i]);
	}
	for (int i = 0; i<zeroPadding; i++) {
		zeroPaddedVector.push_back(0);
	}
	std::vector<double> resultVector;
	for (unsigned int i = 0; i<a.size(); i++) {
		resultVector.push_back(0);
	}
	for (unsigned int i = 0; i<resultVector.size(); i++) {
		for (unsigned int n = 0; n<2* zeroPadding; n++) {
			if (n!= zeroPadding){
				double sincValue = 2 * cutOffFreq*sin(2 * PI*cutOffFreq*(n- zeroPadding)) / (2 * PI*cutOffFreq*(n- zeroPadding));
				if (zeroPaddedVector[i + n] != 0) {
					int hest = 0;
				}
				resultVector[i] += zeroPaddedVector[i + n]*sincValue;
			}
			else
			{
				resultVector[i] += zeroPaddedVector[i + n];

			}
		}
	}
	return resultVector;
}


std::vector<double> SignalAnalyser::upsample(std::vector<double>& a, unsigned int n)
{
	std::vector<double> resultVector;
	for (std::vector<double>::iterator i = a.begin(); i < a.end(); i++) {
		resultVector.push_back((*i)*n);
		for (unsigned int j = 1; j < n; j++) {
			resultVector.push_back(0.0);
		}
	}
	return resultVector;
}

std::vector<double> SignalAnalyser::downsample(std::vector<double>& a, unsigned int n)
{
	std::vector<double> resultVector;
	for (std::vector<double>::iterator i = a.begin(); i < a.end(); i+=n) {
		resultVector.push_back((*i)/n);
	}
	return resultVector;
}

std::vector<double>& SignalAnalyser::decimate(std::vector<double>& a, double f)
{
	return decimate(a, f, 1);
}

std::vector<double>& SignalAnalyser::decimate(std::vector<double>& input, int bandwidthScala, double initialMulti)
{
	//double alpha = 1 - exp(-f);

	//double b0 = pow(alpha, 2);
	//double a1 = 2 * (1 - alpha);
	//double a2 = -pow(1 - alpha, 2);
	//0 = alpha;
	//a1 = 1-alpha;
	//a2 = 0;
	std::vector<double> output;
	for (std::vector<double>::iterator i = input.begin(); i < input.end(); i++) {
		double resultingOutput = 0;
		for (int j = 0; j < (bandwidthScala+1)/2; j++) {
			double valueToBeAdded = i > input.begin() + j ? *(i - j) : (*input.begin())*initialMulti;
			resultingOutput += valueToBeAdded / bandwidthScala;
		}
		for (int j = 0; j < bandwidthScala/2; j++) {
			double valueToBeAdded = i + j < input.end() ? *(i + j) : (*input.end())*initialMulti;
			resultingOutput += valueToBeAdded / bandwidthScala;
		}

		output.push_back(resultingOutput);
	}
	input = output;
	return input;
}
