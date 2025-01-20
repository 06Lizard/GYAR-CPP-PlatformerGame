#pragma once
#include <chrono>
#include <array>
#include <numeric>
#include <iostream>

class DeltaTimeCounter
{
private:
    static const int sampleSize = 100;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime;
    std::array<double, sampleSize> frameTimes;
    int frameIndex;
    double averageDelta;
    int validSamples;

public:
    DeltaTimeCounter() 
        : lastFrameTime(std::chrono::high_resolution_clock::now()),
        frameTimes{},
        frameIndex(0),
        averageDelta(0.0),
        validSamples(0)
    {
    }

    void Reset() {
        lastFrameTime = std::chrono::high_resolution_clock::now();
        frameTimes.fill(0.0);
        frameIndex = 0;
        averageDelta = 0.0;
        validSamples = 0;
    }

    void Count() {
        using namespace std::chrono;
        auto currentFrameTime = high_resolution_clock::now();
        duration<double> delta = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // store the frameTime to the array
        frameTimes[frameIndex] = delta.count();
        frameIndex = (frameIndex + 1) % frameTimes.size();

        // increment valid samples withour exceeding the sample size
        if (validSamples < sampleSize)
            validSamples++;

        // calculate average frameTime
        averageDelta = std::accumulate(frameTimes.begin(), frameTimes.end(), 0.0) / frameTimes.size();
    }

    void Display(short x, short y, std::string whatCounting) {
        if (validSamples < sampleSize) {
            // displays how far till valid sampleSize
            std::cout << "\033[" << y << ";" << x << "H\033[2KLoading " << whatCounting << ": " << validSamples << "/" << sampleSize << " samples";
        }
        else {
            // display deltaTime avrage (ms)
            std::cout << "\033[" << y << ";" << x << "H\033[2KAverage " << whatCounting << " Time: "
                << (averageDelta > 0.0 ? averageDelta * 1000.0 : 0.0)
                << " ms" << std::endl;
        }
    }

    double GetDelta() const {
        if (validSamples < sampleSize)
            return NAN; // return NAN when not enough samples
        // returns the avrageDeltaTime
        return averageDelta;
    }
};
