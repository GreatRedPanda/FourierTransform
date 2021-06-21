#include "FFT.h"
#include <ccomplex>
#include <vector>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

// log (1) = 0, log(2) = 1, log(3) = 2, log(4) = 2 ...

#define PI (2.0 * asin(1.0))

FFT::FFT(int bufferSize, SoundBuffer& buffer)
{
    _mark = 0;
    _sampleRate = buffer.getSampleRate() *buffer.getChannelCount();
    _points = buffer.getSampleCount();
    soundSamples = buffer.getSamples();
    if (bufferSize < _points)
        _bufferSize = bufferSize;
    else
        _bufferSize = _points;

    for (int i(0); i < _bufferSize; i++) 
        _window.push_back(0.54 - 0.46 * cos(2 * PI * i / (float)_bufferSize));
    _samples.resize(_bufferSize);
    VA1.setPrimitiveType(PrimitiveType::LinesStrip);
   
    VA1.resize(_bufferSize);
    rectangles = new RectangleShape[_bufferSize];
}

void FFT::transform(valarray<complex<double>> &ffArray)
{

    const int N = ffArray.size();
    if (N <= 1) return;

    valarray<complex<double>> even = ffArray[slice(0, N / 2, 2)];
    valarray<complex<double>>  odd = ffArray[slice(1, N / 2, 2)];

    transform(even);
    transform(odd);

    for (int k = 0; k < N / 2; k++)
    {
        complex<double> t = polar(1.0, -2 * PI * k / N) * odd[k];
        ffArray[k] = even[k] + t;
        ffArray[k + N / 2] = even[k] - t;
    }
}

void FFT::updateCurrentSamples(const Sound& sound)
{

    _mark = sound.getPlayingOffset().asSeconds() * _sampleRate;
    if (_mark + _bufferSize < _points)
    {
        for (size_t i = _mark; i < _mark + _bufferSize; i++)
        {
            _samples[i - _mark] = complex<double>(soundSamples[i] , 0);
      /*      VA1[i - _mark] = Vertex(Vector2f(20, 250) + Vector2f((i - _mark) / (float)_bufferSize * 700, 
                _samples[i - _mark].real() * 0.005),
                Color::Color(255, 255, 255, 255));*/

            float percent = (i - _mark) / (float)_bufferSize;
            int p = percent *100*  255;
           // rectangles[i - _mark].setFillColor(Color::Color(p , p/2 , p /4, 255));
           //// rectangles[i - _mark].setPosition(Vector2f((i - _mark) * 320 / _bufferSize, 320));
           // rectangles[i - _mark].setPosition(Vector2f(160, 160));
           // rectangles[i - _mark].setSize(Vector2f(320 / _bufferSize, _samples[i - _mark].real() * 0.005));

           // rectangles[i - _mark].rotate(percent *360);

            float angle = percent * 6.28f;
            float radius = (_samples[i - _mark].real()+ 50000) * 0.0009;
            Vector2f pos = Vector2f(radius*cos(angle), radius *sin(angle));
            VA1[i - _mark] = Vertex(Vector2f(160, 160) +pos  ,
                Color::Color(p, p / 2, p / 4, 255));
        }
    }
}

void FFT::update()
{

    _bin = valarray<complex<double>>(_samples.data(), _bufferSize);
    transform(_bin);
}

VertexArray FFT::getPoints()
{
    return VA1;
}

void FFT::drawRects(RenderTarget& window)
{

    for (size_t i = 0; i < _bufferSize; i++)
    {
        window.draw(rectangles[i]);
    }
}
