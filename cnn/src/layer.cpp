#include"layer.h"
/*
in: in[0]-->X_in,in[1]-->w,in[2]-->b
out: out-->X_out
param: layer parameters

*/
void ConvolutionLayer::forward(const vector<Blob> &in, Blob &out, Param &param) {
	int convStride = param.convStride;
	int convPad = param.convPad;
	int convWidth = param.convWidth;
	int convHeight = param.convHeight;
	int numKernals = param.numKernals;

	Blob inX = in[0];
	Blob W = in[1];
	Blob b = in[2];
	int numSamples = inX.getNumSamples();
	int inWidth = inX.getWidth();
	int inHeight = inX.getHeight();
	int kernalWidth = param.kernalWidth;
	int kernalHeight = param.kernalHeight;


	int outWidth = (inWidth + convPad - kernalWidth) / convStride + 1;
	int outHeight = (inHeight + convPad - kernalHeight) / convStride + 1;
	out = Blob(numSamples, outHeight, outWidth,  numKernals, FILLTYPE::ZEROS);

	Blob inXPad = inX.pad(convPad, 0.0);

	for (int n = 0;n < numSamples;n++) {
		arma::cube XCube = inXPad[n];
		for (int c = 0;c < numKernals;c++) {
			for (int h = 0;h < outHeight;h++) {
				for (int w = 0;w < outWidth;w++){
					arma::cube subCube= XCube(span(h, h + kernalHeight), span(w, w + kernalWidth), span(span::all);
					W[]
				}
			}
		}
	}
	
}
void ConvolutionLayer::backword() {

}