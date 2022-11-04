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

#ifndef OnlinePSTHDISPLAY_H_
#define OnlinePSTHDISPLAY_H_

#include <VisualizerWindowHeaders.h>

#include "Histogram.h"

#include <vector>

/*
    
    Component that holds the histogram displays
 
 */
class OnlinePSTHDisplay : public Component
{
    
public:
    
    /** Constructor */
    OnlinePSTHDisplay();
    
    /** Destructor */
    ~OnlinePSTHDisplay() { }
    
    /** Renders the Visualizer on each animation callback cycle
        Called instead of Juce's "repaint()" to avoid redrawing underlying components
        if not necessary.*/
    void refresh();
    
    /** Called when component changes size*/
    void resized();

    /** Sets the overall window size*/
    void setWindowSizeMs(int pre_ms, int post_ms);
    
    /** Sets the bin size*/
    void setBinSizeMs(int bin_size);
    
    /** Sets the bin size*/
    void setPlotType(int plotType);
    
    /** Add an event to the queue */
    void pushEvent(uint16 streamId, int64 sample_number);
    
    /** Add a spike to the queue */
    void pushSpike(const SpikeChannel* channel, int64 sample_number, int sortedId, int stimClass);
    
    /** Adds a spike channel */
    void addSpikeChannel(const SpikeChannel* channel, int numStimClasses);
    
    /** Prepare for update*/
    void prepareToUpdate();
    
    /** Returns the desired height for this component*/
    int getDesiredHeight();
    
    /** Clears the histograms */
    void clear();
    
private:
    
    OwnedArray<OwnedArray<Histogram>> histograms; // TODO: 2D array of histograms
    
    std::map<const SpikeChannel*, OwnedArray<Histogram>*> histogramMap; // TODO: array of histograms for each channel
    
    int totalHeight = 0;
    const int histogramHeight = 100;
    const int borderSize = 20;
    
    int post_ms;
    int plotType = 1;

    std::vector<Colour> colorList = {
    Colour(30,118,179), Colour(255,126,13), Colour(43,159,43),
    Colour(213,38,39), Colour(147,102,188), Colour(139,85,74),
    Colour(226,118,193), Colour(126,126,126), Colour(187,188,33),
    Colour(22,189,206) };
};


#endif  // OnlinePSTHDISPLAY_H_
