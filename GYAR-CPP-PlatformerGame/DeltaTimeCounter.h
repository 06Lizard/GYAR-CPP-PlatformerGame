#pragma once
#include <chrono>
#include <array>
#include <iostream>

class DeltaTimeCounter
{
private:
    static const int sampleSize = 100;
    std::array<double, sampleSize> frameTimes;
    int frameIndex;
    double runningSum;
    int validSamples;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime;

public:
    DeltaTimeCounter()
        : lastFrameTime(std::chrono::high_resolution_clock::now()),
        frameTimes{},
        frameIndex(0),
        runningSum(0.0),
        validSamples(0)
    {
        frameTimes.fill(0.0);
    }

    void Reset() {
        lastFrameTime = std::chrono::high_resolution_clock::now();
        frameTimes.fill(0.0);
        frameIndex = 0;
        runningSum = 0.0;
        validSamples = 0;
    }

    void Count() {
        using namespace std::chrono;
        auto currentFrameTime = high_resolution_clock::now();
        duration<double> delta = currentFrameTime - lastFrameTime;

        // remove the old value from the runningSum
        runningSum -= frameTimes[frameIndex];

        // store the frameTime to the array and add the new time to runningSum
        frameTimes[frameIndex] = delta.count();
        runningSum += frameTimes[frameIndex];

        // increment frameIndex
        frameIndex = (frameIndex + 1) % sampleSize;

        // Increase validSamples untill it reatches sampleSize
        if (validSamples < sampleSize) {
            ++validSamples;
        }

        lastFrameTime = currentFrameTime;
    }

    void CountAndDisplay(short x, short y, std::string whatCounting) {
        using namespace std::chrono;
        auto currentFrameTime = high_resolution_clock::now();
        duration<double> delta = currentFrameTime - lastFrameTime;

        // remove the old value from the runningSum
        runningSum -= frameTimes[frameIndex];

        // store the frameTime to the array and add the new time to runningSum
        frameTimes[frameIndex] = delta.count();
        runningSum += frameTimes[frameIndex];

        // increment frameIndex
        frameIndex = (frameIndex + 1) % sampleSize;

        // Increase validSamples untill it reatches sampleSize
        if (validSamples < sampleSize) {
            ++validSamples;
        }

        Display(x, y, whatCounting);
        lastFrameTime = high_resolution_clock::now();
    }

    void Display(short x, short y, std::string whatCounting) {
        if (validSamples < sampleSize) {
            // displays how far till valid sampleSize
            std::cout << "\033[" << y << ";" << x << "H\033[2KLoading " << whatCounting
                << ": " << validSamples << "/" << sampleSize << " samples";
        }
        else {
            // display deltaTime avrage (ms)
            double avg = GetDelta();
            std::cout << "\033[" << y << ";" << x << "H\033[2KAverage " << whatCounting << " Time: "
                << (avg > 0.0 ? avg * 1000.0 : 0.0)
                << " ms";
        }
    }

    double GetDelta() const {
        if (validSamples == 0)
            return 0.0;
        // if still collecting samples, average over validSamples, otherwise use full sampleSize
        //return runningSum / (validSamples < sampleSize ? validSamples : sampleSize);
        return runningSum / sampleSize;
    }
};
