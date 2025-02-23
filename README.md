0.35 ms avrage FrameTime (game loop)
____________________________________
0.05 ms avrage update time
0.14 ms avrage render time
0.19 ms avrage delay from benchmarker

if u wanna play around with difrent update fucntions follow the comments in PlatformerGame.cpp function GameLoop

to build up LvL's check out the functions LvL0 && LvL1 && LvL2 in LvLManager.cpp

to add more enemies simply create a class and have it enherit from enemy.h as it's the base enemy

(there is a slight problem with collition handleing atm alowwing player to phase through enemies sometimes)
(player still can't kill enemies...)
