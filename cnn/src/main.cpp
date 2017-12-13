#include "blob.h"5 v

using namespace std;
using std::vector;

#include <armadillo>
using namespace arma;

int main() {
	//Blob a(1, 2, 3, 4, FILLTYPE::ZEROS);
	//Blob b(1, 2, 3, 4, FILLTYPE::ONES);
	//Blob c(1, 2, 3, 4, FILLTYPE::RANDN);
	////Blob d(1, 2, 3, 4, FILLTYPE::RANDU);
	////Blob e(1, 2, 3, 4);
	////Blob sum_blob = a + b;
	//double num = 3.1;
	//Blob numBlob = c + num;
	//numBlob.print();
	////cube cc = arma::randn(2, 3, 4);
	arma::mat m = randn(3, 4);
	cout << "m" << m;
	arma::mat dd = m(span(1, 2), span(1, 3));
	cout << dd;
	////sum_blob.print();
	//numBlob.print();

	/*vector<int> vec{ 1,2,3,4,5 };
	for (int i = 0;i < vec.size();i++) {
		cout << vec[i];
	}
	for (int i = 0;i < vec.size();i++) {
		vec[i] = 3;
	}
	for (int i = 0;i < vec.size();i++) {
		cout << vec[i];
	}*/

	/*a.print();
	b.print();
	c.print();
	d.print();
	e.print();*/
}