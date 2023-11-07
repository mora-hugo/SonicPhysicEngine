#include "ofMain.h"
#include "ofApp.h"
#include "Public/Math/Matrix3.h"
#include "Public/Math/Matrix4.h"
#include "Public/Math/Quaternion.h"

bool testsUnitaire();
bool RunMatrix3Tests();
bool RunMatrix4Tests();
bool RunQuaternionTests();

//========================================================================
int main( ){

	if(testsUnitaire())
	{
		cout << "All the tests succeeded " << endl;
	}
	else
	{
		cout << "Unit test failed " << endl;
		return 1;
	}
	
	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();

}

bool testsUnitaire()
{
	if(!RunMatrix3Tests())
		return false;

	if(!RunMatrix4Tests())
		return false;

	if(!RunQuaternionTests())
		return false;
	
	return true;
}

bool RunMatrix3Tests() {
	// Test the Matrix3 Add method
	Matrix3 matrixA(1, 2, 3, 4, 5, 6, 7, 8, 9);
	Matrix3 matrixB(9, 8, 7, 6, 5, 4, 3, 2, 1);

	Matrix3 result = matrixA.Add(matrixB);

	// Define the expected result manually or calculate it
	Matrix3 expected(10, 10, 10, 10, 10, 10, 10, 10, 10);

	// Compare the actual result with the expected result
	bool TestResult = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (result.GetMatrix3Element(i, j) != expected.GetMatrix3Element(i, j)) {
				std::cerr << "AddTest failed at index (" << i << ", " << j << ")" << std::endl;
				TestResult = false;
			}
		}
	}

	if (TestResult) {
		std::cout << "AddTest passed." << std::endl;
	}
	else
	{
		return false;
	}

	
	// Test the Matrix3 substract method
	Matrix3 resultSubstract = matrixA.Substract(matrixB);

	Matrix3 expectedSubstract(-8, -6, -4, -2, 0, 2, 4, 6, 8);

	// Compare the actual result with the expected result
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (resultSubstract.GetMatrix3Element(i, j) != expectedSubstract.GetMatrix3Element(i, j)) {
				std::cerr << "SubTest failed at index (" << i << ", " << j << ")" << std::endl;
				TestResult = false;
			}
		}
	}

	if (TestResult) {
		std::cout << "SubTest passed." << std::endl;
	}
	else
	{
		return false;
	}
	
	// Test the Matrix3 multiply with scalar method
	Matrix3 resultMultScalar = matrixA.Multiply(2);

	Matrix3 expectedMultScalar(2, 4, 6, 8, 10, 12, 14, 16, 18);

	// Compare the actual result with the expected result
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (resultMultScalar.GetMatrix3Element(i, j) != expectedMultScalar.GetMatrix3Element(i, j)) {
				std::cerr << "MultScalarTest failed at index (" << i << ", " << j << ")" << std::endl;
				TestResult = false;
			}
		}
	}

	if (TestResult) {
		std::cout << "MultScalarTest passed." << std::endl;
	}
	else
	{
		return false;
	}

	
	// Test the Matrix3 multiply with Matrix3 method
	Matrix3 resultMultMatrix = matrixA.Multiply(matrixB);

	Matrix3 expectedMultMatrix(30, 24, 18, 84, 69, 54, 138, 114, 90);

	// Compare the actual result with the expected result
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (resultMultMatrix.GetMatrix3Element(i, j) != expectedMultMatrix.GetMatrix3Element(i, j)) {
				std::cerr << "MultMatrixTest failed at index (" << i << ", " << j << ")" << std::endl;
				TestResult = false;
			}
		}
	}

	if (TestResult) {
		std::cout << "MultMatrixTest passed." << std::endl;
	}
	else
	{
		return false;
	}


	//return true if all tests are passed
	return true;
}

bool RunMatrix4Tests() {

	return true;
}

bool RunQuaternionTests()
{

	return true;
}
