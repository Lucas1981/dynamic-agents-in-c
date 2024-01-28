# Dynamic Agents in C

So, this was a problem I always tried to solve as a kid but could never get straight. I wanted a way to add agents to a game dynamically rather than have a number of agents specified up front. Especially bullets were agents I wanted to add to games. I think I would actually use linked lists in the end, I've done that in the past. But this idea of using a pool was fun to explore, so I went with that.

Again, all of it is arrived at with the help of ChatGPT 4 which is both great at explaining concepts and providing code that illustrates it, as well as providing boiler-plate code for a lot of these things. In contrast to my previous attempts to write game code in C, this has the agents pool and uses a single image to get the right animation frames.

I also add a sound queue, that stages sounds to be played and then at the end of the loop plays all the sounds that were staged during the loop - I like that pattern which doesn't interrupt the ongoing loop by already starting to play the sounds. I got that from the book Game Programming Patterns by Robert Nystrom.

I also hope to "skin" the game differently from the wireframe like stick figures I now use as placeholders. I have an idea for what the game could be like, but I'll still need to flesh that out. That will probably be another repository though.

Todo list:
- Add the logic for the title and pause screens.
- Tweak movement boundary and player speed