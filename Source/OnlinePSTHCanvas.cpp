/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2022 Open Ephys

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

#include "OnlinePSTHCanvas.h"

OnlinePSTHCanvas::OnlinePSTHCanvas()
{
    
    clearButton = new UtilityButton("CLEAR", Font("Default", 12, Font::plain));
    clearButton->addListener(this);
    clearButton->setRadius(3.0f);
    clearButton->setClickingTogglesState(false);
    addAndMakeVisible(clearButton);

    viewport = new Viewport();
    viewport->setScrollBarsShown(true, true);

    display = new OnlinePSTHDisplay();
    viewport->setViewedComponent(display, false);
    addAndMakeVisible(viewport);
    display->setBounds(0, 50, 500, 100);

    scale = new Timescale();
    addAndMakeVisible(scale);

}


void OnlinePSTHCanvas::refreshState()
{
    resized();
}

void OnlinePSTHCanvas::resized()
{

    int scrollBarThickness = viewport->getScrollBarThickness();
    int yOffset = 50;
    
    clearButton->setBounds(getWidth()-120, 12, 100, 25);
    
    viewport->setBounds(0, yOffset, getWidth(), getHeight()-yOffset);
    
    display->setBounds(0, yOffset, getWidth()-scrollBarThickness, display->getDesiredHeight());

    scale->setBounds(10, getHeight()-40, getWidth()-scrollBarThickness-190, 40);

}

void OnlinePSTHCanvas::paint(Graphics& g)
{
    g.fillAll(Colour(0,18,43));

}

void OnlinePSTHCanvas::setWindowSizeMs(int pre_ms, int post_ms)
{
    display->setWindowSizeMs(pre_ms, post_ms);
    scale->setWindowSizeMs(pre_ms, post_ms);
}

void OnlinePSTHCanvas::setBinSizeMs(int bin_size)
{
    display->setBinSizeMs(bin_size);
}

void OnlinePSTHCanvas::pushEvent(uint16 streamId, int64 sample_number)
{
    display->pushEvent(streamId, sample_number);
}


void OnlinePSTHCanvas::pushSpike(const SpikeChannel* channel, int64 sample_number, int sortedId)
{
    display->pushSpike(channel, sample_number, sortedId);
}

void OnlinePSTHCanvas::addSpikeChannel(const SpikeChannel* channel)
{
    display->addSpikeChannel(channel);
}

void OnlinePSTHCanvas::prepareToUpdate()
{
    display->prepareToUpdate();
}

void OnlinePSTHCanvas::buttonClicked(Button* button)
{
    if (button == clearButton)
    {
        display->clear();
    }
}
