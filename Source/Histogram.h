/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2013 Open Ephys

    ------------------------------------------------------------------

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef Histogram_H__
#define Histogram_H__

#include <VisualizerWindowHeaders.h>

#include <vector>

/**
 
    Displays the actual PSTH
 
 */
class Histogram :
    public Component,
    public Timer
{
public:
    
    /** Constructor */
    Histogram(const SpikeChannel* channel);
    
    /** Destructor */
    ~Histogram() { }
    
    /** Draws the histogram */
    void paint(Graphics& g);
    
    /** Called when histogram is resized */
    void resized();
    
    /** Adds a spike time */
    void addSpike(int64 sample_number, int sortedId);
    
    /** Adds an event time*/
    void addEvent(int64 sample_number);
    
    /** Clears the display*/
    void clear();
    
    /** Sets the =window size*/
    void setWindowSizeMs(int pre_ms, int post_ms);
    
    /** Sets the pre-event window size*/
    void setBinSizeMs(int ms);
    
    /** Listens for mouse movements */
    void mouseMove(const MouseEvent& event);
    
    /** Listens for mouse movements */
    void mouseExit(const MouseEvent& event);
    
    /** Called by OnlinePSTHDisplay after event window closes */
    void update();
    
    /** Stream ID for this histogram */
    uint16 streamId;

private:
    
    /** Updates histogram after event window closes*/
    void timerCallback();
    
    /** Recomputes temporal offsets */
    void recompute();
    
    /** Recomputes bin counts */
    void recount();
    
    ScopedPointer<Label> infoLabel;
    ScopedPointer<Label> channelLabel;
    ScopedPointer<Label> hoverLabel;
    
    Array<int64> newSpikeSampleNumbers;
    Array<int> newSpikeSortedIds;
    
    int64 latestEventSampleNumber;
    
    Array<int> uniqueSortedIds;
    
    Array<double> binEdges;
    
    int maxSortedId = 0;
    
    Array<double> relativeTimes;
    Array<int> relativeTimeSortedIds;
    Array<Colour> colours;
    
    Array<Array<int>> counts;
    
    int pre_ms;
    int post_ms;
    int bin_size_ms;
    
    int maxCount = 1;
    
    int hoverBin = -1;
    
    CriticalSection mutex;
    
    bool waitingForWindowToClose;
    
    float numEvents = 0;
    
    const double sample_rate;
    
};



#endif  // Histogram_H__
