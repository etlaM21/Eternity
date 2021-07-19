# Eternity

![Preview](eternity_canvas.png)

## Abstract

Eternity is an artistic piece trying to overcome humanity's oldest struggle: Time.

While everybody eventually has to go, algorithms in robust systems can run forever with a steady power supply. By creating two distinct brushes being drawn by two artists, my deceased grandparents, each with distinct behaviour, I want you to have a glimpse into eternity and watch them paint on a digital canvas for the rest of time.

How human can an algorithm become? Who is painting on the canvas?

## Project description

The main goal of this project was to create two different artists with their own brushes, which resemble my grandparents. Both should have their own canvas and paint on it forever.

To code a personality into a brush, I created parameters which would let me have a watercolor-type-brush as well as a more harsh, more resembling of caligraphy, type of brush. Both behave like you would expect from a normal brush, adapting to their direction, pressure used, etc..

An artistic style is obviously much more than just a brush, so having different painting behaviour was important. To achieve that, each artist has a random start and finish position for each brush stroke. How they get from a to b, depends on their personality. One goes directly to the end, while the other my take longer with a few more detours.

This results in two canvases, being painted on by two artists until the power is cut off.

## Implementation

The project was created using [openFramworks](https://openframeworks.cc/). At it's core it displays two FramebufferObjects where ofPaths get randomly created and drawn on. To achieve distinct looks, the "artist" is an autonomous agent with behavioural properties that can be changed and the brush can control the way the ofPath is drawn (the strokes).

A brushtroke consists of multiple strokes, depending on how many hairs the brush has. Each stroke drawn is an ofPath, at the point it is drawn on both of sides of the center point a point is added to the path with a distance dependant on the random pressure applied.

To achieve eternity, the strokes fade-away after a certain time and are wiped from memory. I'm not sure how to test the functionality, but I let it run for > 6 hours over night an the artists where still drawing on the canvas.

## Lessons learned

- ofPath is not really as performant, as it tesselates the path everytime it is updated. This really breaks my performance. I have to switch to an ofMesh and triangulate it myself to achieve a higher framerate.
- ofFbos handle transparency different than when drawing "directly on the screen" in openFrameworks. There are some [workarounds](https://forum.openframeworks.cc/t/solved-fbo-and-transparency/18835/9), but I have to dive into FBOs again to understand what is actually going on
- Autonomous agents are really great for creating "natural" behaviour
- I should start sooner with the documentation and presentation.