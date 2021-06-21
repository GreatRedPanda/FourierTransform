#pragma once
#include <ccomplex>
#include <vector>
#include <SFML/Audio.hpp>
#include <valarray>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class FFT
{
private:
	long		_sampleRate;
	//int			_logPoints;
	//double		_sqrtPoints;
	int     _points;
	int _bufferSize;
	int _mark;

	const Int16 *soundSamples;
	vector<complex<double>> _samples= vector<complex<double>>();
	valarray<complex<double>> _bin = valarray<complex<double>>();
	vector<float> _window= vector<float>();

	VertexArray VA1;
	//std::complex<double> **_W;
	//int * _aBitRev;
	//double * _aTape;

	/*void PutAt(int i, double val)
	{
		_X[_aBitRev[i]] = std::complex<double>(val);
	}*/
	
	RectangleShape *rectangles;
public:
	FFT(int points, SoundBuffer &buffer);
	void transform(valarray<complex<double>> &ffArray);
	void updateCurrentSamples(const Sound& sound);
	void update();
	VertexArray getPoints();
	void drawRects(RenderTarget& window);
};

