#include "ofMain.h"
#include "ofApp.h"
#include "Public/Math/Matrix3.h"
#include "Public/Math/Matrix4.h"
#include "Public/Math/Quaternion.h"
#include <cassert>
#include "Public/Math/Vector3D.h"

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
		std::cout << "Matrix3 AddTest passed." << std::endl;
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
		std::cout << "Matrix3 SubTest passed." << std::endl;
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
		std::cout << "Matrix3 MultScalarTest passed." << std::endl;
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
		std::cout << "Matrix3 MultMatrixTest passed." << std::endl;
	}
	else
	{
		return false;
	}


	// Test the Matrix3 multiply with vector method
	Vector3D vector_3d(1, 2, 3);
	Vector3D resultMultVector = matrixA.Multiply(vector_3d);

	Vector3D expectedMultVector(14, 32, 50);

	// Compare the actual result with the expected result
	if(resultMultVector.GetX() != expectedMultVector.GetX() && resultMultVector.GetY() != expectedMultVector.GetY() && resultMultVector.GetZ() != expectedMultVector.GetZ())
	{
		std::cerr << "MultMatrixVectorTest failed " << std::endl;
		TestResult = false;
	}

	if (TestResult) {
		std::cout << "Matrix3 MultMatrixVectorTest passed." << std::endl;
	}
	else
	{
		return false;
	}

	
	// Test the Matrix3 determinant method
	double resultDeterminant = matrixA.determinant();
	double expectedDeterminant = 0;

	// Compare the actual result with the expected result
	assert(resultDeterminant == expectedDeterminant);
	std::cout << "TestMatrix3Determinant passed." << std::endl;

	
	// Test the Matrix3 transpose method
	Matrix3 resultTranspose = matrixA.Transpose();
	Matrix3 expectedTranspose(1, 4, 7, 2, 5, 8, 3, 6, 9);

	// Compare the actual result with the expected result
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (resultTranspose.GetMatrix3Element(i, j) != expectedTranspose.GetMatrix3Element(i, j)) {
				std::cerr << "MatrixTransposeTest failed " << std::endl;
				TestResult = false;
			}
		}
	}

	if (TestResult) {
		std::cout << "Matrix3TransposeTest passed." << std::endl;
	}
	else
	{
		return false;
	}

	
	// Test the Matrix3 reverse method
	Matrix3 matrixC(2, 1, 3, 1, 3, 2, 3, 2, 1);

	Matrix3 resultReverse = matrixC.Reverse();
	Matrix3 expectedReverse(
	0.05, -0.27, 0.38,
	-0.27, 0.38, 0.05,
	0.38, 0.05, -0.27
	);
	
	// Compare the actual result with the expected result
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (fabs(resultReverse.GetMatrix3Element(i, j) - expectedReverse.GetMatrix3Element(i, j)) > 0.01) {
				std::cerr << "Matrix3ReverseTest failed at element (" << i << ", " << j << ")" << std::endl;
				TestResult = false;
			}
		}
	}

	if (TestResult) {
		std::cout << "Matrix3ReverseTest passed." << std::endl;
	}
	else
	{
		return false;
	}
	
	//return true if all tests are passed
	return true;
}

bool RunMatrix4Tests() {
	// Test the Matrix4 Add method
	Matrix4 matrixA(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	Matrix4 matrixB(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);

	Matrix4 result = matrixA.Add(matrixB);

	// Define the expected result manually or calculate it
	Matrix4 expected(17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17);

	// Compare the actual result with the expected result
	bool TestResult = true;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (result.GetMatrix4Element(i, j) != expected.GetMatrix4Element(i, j)) {
				std::cerr << "AddTest failed at index (" << i << ", " << j << ")" << std::endl;
				TestResult = false;
			}
		}
	}

	if (TestResult) {
		std::cout << " Matrix4 AddTest passed." << std::endl;
	}
	else
	{
		return false;
	}


	// Test the Matrix4 substract method
	Matrix4 resultSubstract = matrixA.Substract(matrixB);

	Matrix4 expectedSubstract(-15, -13, -11, -9, -7, -5, -3, -1, 1, 3, 5, 7, 9, 11, 13, 15);

	// Compare the actual result with the expected result
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (resultSubstract.GetMatrix4Element(i, j) != expectedSubstract.GetMatrix4Element(i, j)) {
				std::cerr << "SubTest failed at index (" << i << ", " << j << ")" << std::endl;
				TestResult = false;
			}
		}
	}

	if (TestResult) {
		std::cout << "Matrix4 SubTest passed." << std::endl;
	}
	else
	{
		return false;
	}
	
	// Test the Matrix4 multiply with scalar method
	Matrix4 resultMultScalar = matrixA.Multiply(2);

	Matrix4 expectedMultScalar(2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32);

	// Compare the actual result with the expected result
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (resultMultScalar.GetMatrix4Element(i, j) != expectedMultScalar.GetMatrix4Element(i, j)) {
				std::cerr << "MultScalarTest failed at index (" << i << ", " << j << ")" << std::endl;
				TestResult = false;
			}
		}
	}

	if (TestResult) {
		std::cout << "Matrix4 MultScalarTest passed." << std::endl;
	}
	else
	{
		return false;
	}

	
	// Test the Matrix4 multiply with Matrix4 method
	Matrix4 resultMultMatrix = matrixA.Multiply(matrixB);

	Matrix4 expectedMultMatrix(80, 70, 60, 50, 240, 214, 188, 162, 400, 358, 316, 274, 560, 502, 444, 386);

	// Compare the actual result with the expected result
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (resultMultMatrix.GetMatrix4Element(i, j) != expectedMultMatrix.GetMatrix4Element(i, j)) {
				std::cerr << "MultMatrixTest failed at index (" << i << ", " << j << ")" << std::endl;
				TestResult = false;
			}
		}
	}

	if (TestResult) {
		std::cout << "Matrix4 MultMatrixTest passed." << std::endl;
	}
	else
	{
		return false;
	}


	// Test the Matrix4 determinant method
	double resultDeterminant = matrixA.determinant();
	double expectedDeterminant = 0;

	// Compare the actual result with the expected result
	assert(resultDeterminant == expectedDeterminant);
	std::cout << "TestMatrix4Determinant passed." << std::endl;

	
	// Test the Matrix4 transpose method
	Matrix4 resultTranspose = matrixA.Transpose();
	Matrix4 expectedTranspose(1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16);

	// Compare the actual result with the expected result
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (resultTranspose.GetMatrix4Element(i, j) != expectedTranspose.GetMatrix4Element(i, j)) {
				std::cerr << "Matrix4TransposeTest failed " << std::endl;
				TestResult = false;
			}
		}
	}

	if (TestResult) {
		std::cout << "Matrix4TransposeTest passed." << std::endl;
	}
	else
	{
		return false;
	}
	
	// Test the Matrix4 reverse method
	Matrix4 matrixC(
	0.5, 0.3, 0.7, 0.9,
	0.1, 0.6, 0.2, 0.8,
	0.7, 0.5, 0.3, 0.9,
	0.3, 0.2, 0.1, 0.5
);
/*
	Matrix4 resultReverse = matrixC.Reverse();
	Matrix4 expectedReverse(
	-0.51, -1.45, 2.68, -1.59,
	-0.94, 1.59, 3.55, -7.25,
	1.78, 0.07, 0.62, -4.42,
	0.33, 0.22, -3.15, 6.74
);
	
	// Compare the actual result with the expected result
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (fabs(resultReverse.GetMatrix4Element(i, j) - expectedReverse.GetMatrix4Element(i, j)) > 0.01) {
				std::cerr << "Matrix4ReverseTest failed at element (" << i << ", " << j << ")" << std::endl;
				TestResult = false;
			}
		}
	}

	if (TestResult) {
		std::cout << "Matrix4ReverseTest passed." << std::endl;
	}
	else
	{
		return false;
	}
	*/
	//return true if all tests are passed
	return true;
}

bool RunQuaternionTests() {
	//Test the Quaternion multiply method
	Quaternion q1(1, 2, 3, 4);
	Quaternion q2(5, 6, 7, 8);

	Quaternion result = q1 * q2;

	// Define the expected result manually or calculate it
	Quaternion expected(-60, 12, 30, 24);

	// Compare the actual result with the expected result
	assert(result.w == expected.w);
	assert(result.x == expected.x);
	assert(result.y == expected.y);
	assert(result.z == expected.z);
	std::cout << "TestQuaternionMultiplication passed." << std::endl;
	

	//Test the Quaternion conjugate method
	Quaternion q(1, 2, 3, 4);

	Quaternion resultConjugate = q.conjugate();

	// Define the expected result manually
	Quaternion expectedConjugate(1, -2, -3, -4);

	// Compare the actual result with the expected result
	assert(resultConjugate.w == expectedConjugate.w);
	assert(resultConjugate.x == expectedConjugate.x);
	assert(resultConjugate.y == expectedConjugate.y);
	assert(resultConjugate.z == expectedConjugate.z);
	std::cout << "TestQuaternionConjugate passed." << std::endl;
	

	//Test the Quaternion norm method
	Quaternion q3(1, 2, 3, 4);

	double resultNorm = q3.norm();

	// Define the expected result manually
	double expectedNorm = 5.477225575051661;

	// Compare the actual result with the expected result, using a small tolerance
	double tolerance = 1e-9;
	assert(std::abs(resultNorm - expectedNorm) < tolerance);
	std::cout << "TestQuaternionNorm passed." << std::endl;

	
	//Test the Quaternion normalize method
	Quaternion q4(1, 2, 3, 4);

	q4.normalize();

	// Define the expected result manually
	Quaternion expectedNormalize(0.18257418583505539, 0.36514837167011077, 0.5477225575051661, 0.7302967433402215);

	// Compare the actual result with the expected result, using a small tolerance
	double toleranceNormalize = 1e-9;
	assert(std::abs(q4.w - expectedNormalize.w) < toleranceNormalize);
	assert(std::abs(q4.x - expectedNormalize.x) < toleranceNormalize);
	assert(std::abs(q4.y - expectedNormalize.y) < toleranceNormalize);
	assert(std::abs(q4.z - expectedNormalize.z) < toleranceNormalize);
	std::cout << "TestQuaternionNormalize passed." << std::endl;
	

	//return true if all tests are passed
	return true;
}
