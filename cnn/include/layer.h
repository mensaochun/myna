#include "blob.h"
using namespace std;
struct Param {
	//conv parameter
	int convStride;
	int convPad;
	int convWidth;
	int convHeight;
	int numKernals;

	//kernal param
	int kernalWidth;
	int kernalHeight;
	inline void setConvParam(int convStride, int convPad, int convWidth, int convHeight,int numKernals) {
		convStride = convStride;
		convPad=convPad;
		convWidth=convWidth;
		convHeight=convHeight;
		numKernals=numKernals;
	}

	//...
};
class ConvolutionLayer {
	ConvolutionLayer() {};
	~ConvolutionLayer() {};
	static void forward(const vector<Blob> &in,Blob &out,Param &param );
	static void backword();
};