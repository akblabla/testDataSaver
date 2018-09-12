#pragma once
#include <vector>
class SignalAnalyser
{
public:
	SignalAnalyser();
	~SignalAnalyser();
	static std::vector<double> convolution(const std::vector<double> a, const std::vector<double> b);
	static std::vector<double> crosscorrelation(const std::vector<double> a, const std::vector<double> b);
	static std::vector<double> upsample(std::vector<double> &a, unsigned int n);
	static std::vector<double> downsample(std::vector<double> &a, unsigned int n);
	std::vector<double> resample(std::vector<double>& a, unsigned int n, unsigned int m);
	std::vector<double> sincFilter(std::vector<double>& a, double cutOffFreq, unsigned int order);
	static std::vector<double>& decimate(std::vector<double>& a, double f);
	static std::vector<double>& decimate(std::vector<double>& a, int n, double initialMulti);

};

