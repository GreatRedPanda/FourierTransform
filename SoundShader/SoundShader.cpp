// SoundShader.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "FFT.h"
using namespace sf;

int main()
{
    RenderWindow rw(VideoMode(320, 320,32), "Recording");
    if(!SoundBufferRecorder::isAvailable())
    std::cout << "No mic\n";

    SoundBufferRecorder bufRecorder;
    SoundBuffer buffer;
    Sound sound;
    
    float sounds[2000] ;

    buffer.loadFromFile("bubble.wav");
    int count = (buffer.getSampleCount() < 2000) ? buffer.getSampleCount() : 2000;
    std::cout << buffer.getChannelCount()<<"   "<<buffer.getSampleRate()<<"  "<<buffer.getDuration().asSeconds();


    float rateMS = buffer.getSampleRate() / 1000.0f/1000.0f;
    float durationMS = buffer.getDuration().asMicroseconds() ;
    int sampleCount = buffer.getSampleCount();
    int channels = buffer.getChannelCount();


    //sound.setPitch(0.1f);
    sound.setLoop(true);
    sound.setVolume(1);
    sound.setBuffer(buffer);

  // sound.setPitch(0.01f);
    sound.play();
    Shader s;
    s.loadFromFile("Box.frag", Shader::Fragment);
    RectangleShape rect;
    rect.setPosition(Vector2f(0, 0));
    rect.setSize(Vector2f(320, 320));
    rect.setFillColor(Color::Red);
    float time = 0;
    float prevTime = 0;
    float amplitude = 0;
    bool isRecording = false;
    Time t;
    Clock clock;

    FFT fft = FFT(4096, buffer);
    //Texture tex;
    //tex.create(320, 320);
    
    const unsigned int sampleFrequency{ buffer.getSampleRate() };
    const unsigned int numberOfChannels{ buffer.getChannelCount() };
    while (rw.isOpen())
    {
       
        t = clock.getElapsedTime();
       
     
        Event e;
        //amplitude += 0.001f;
        while (rw.pollEvent(e))
        {


            switch (e.type)
            {
            case  Event::EventType::KeyReleased:
                if (e.key.code == Keyboard::R)
                {
                    
                    //bufRecorder.start();                 
                  }
                else if (e.key.code == Keyboard::S)
                {
                 //   isRecording = false;
                 //   bufRecorder.stop();
                 //   buffer = bufRecorder.getBuffer();

                 //const Int16 *samples=  buffer.getSamples();
                
                 //Image im;
                 //im.create(1, 16000);
                 //for (size_t i = 0; i < 16000; i++)
                 //{
                 //    im.setPixel(0, i, Color(samples[i], samples[i], samples[i]));
                 //}
                 //tex.loadFromImage(im);
                 // //  int samples[] =buffe
                 //   sound.setBuffer(buffer);
                 //   sound.play();
                 //clock.restart();

                }
            }
        }
      
      //  float time = sound.getPlayingOffset().asSeconds()*1.0f  / buffer.getDuration().asSeconds()/4000;      
       // float currentSample = buffer.getSamples()[int(time * buffer.getSampleCount())];

        rw.clear();

        //if (sound.getStatus() == SoundSource::Status::Playing)
        //{
        //    float curTImr = sound.getPlayingOffset().asMicroseconds();
        //    
        //  //  curTImr = t.asMicroseconds();
        //    int index = int(rateMS * curTImr *channels);
        //    float lch = buffer.getSamples()[index];
        //    float rch = buffer.getSamples()[index  + 1];


        //    std::cout << lch << "     " << rch << "\n";
        //    s.setUniform("currentSample", lch / 500.0f);
        //    s.setUniform("rightChannel", rch / 500.0f);



        //    rw.draw(rect, &s);
        //}
        //else
        //{
        //  //  clock.restart();
        //   // sound.play();
        //}

        fft.updateCurrentSamples(sound);
        fft.update();
        VertexArray va = fft.getPoints();
       rw.draw(va);
        //fft.drawRects(rw);
        rw.display();
    }

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
