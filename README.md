# Game_Frogger

**Made with <3 by [Amazing Cow](http://www.amazingcow.com).**



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Websites:

* [Game Frogger Website](http://opensource.amazingcow.com/game/game_frogger/)
* [Games Website](http://opensource.amazingcow.com/game/) - 
The Amazing Cow's Games site.



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Description:

```Game_Frogger``` is a small _"quasi"_-remake of the Konami's Frogger.   
You can find more info about the original game in 
[Wikipedia](https://en.wikipedia.org/wiki/Frogger)

It was developed in C++11 using 
[Lore](https://github.com/AmazingCow-Game-Framework/Lore), 
[CoreGame](https://github.com/AmazingCow-Game-Core/CoreGame), 
[CoreClock](https://github.com/AmazingCow-Game-Core/CoreClock) and 
[CoreRandom](https://github.com/AmazingCow-Game-Core/CoreRandom).


<br>
As usual, you are **very welcomed** to **share** and **hack** it.


<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Dedication

This game is dedicated to 
[AACD](http://www.aacd.org.br/).   
They .

AACD do a WONDERFUL job helping people with motor disability. :D

Thanks! 


<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Screen Shots:

<a href="http://amazingcow.com/opensource/game/game_frogger/img/1.png"> <img src="http://amazingcow.com/opensource/game/game_frogger/img/1.png" width="20%" height="20%"> </a>
<a href="http://amazingcow.com/opensource/game/game_frogger/img/2.png"> <img src="http://amazingcow.com/opensource/game/game_frogger/img/2.png" width="20%" height="20%"> </a>
<a href="http://amazingcow.com/opensource/game/game_frogger/img/3.png"> <img src="http://amazingcow.com/opensource/game/game_frogger/img/3.png" width="20%" height="20%"> </a>
<a href="http://amazingcow.com/opensource/game/game_frogger/img/4.png"> <img src="http://amazingcow.com/opensource/game/game_frogger/img/4.png" width="20%" height="20%"> </a>


<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Download & Install:

#### Option 1 - Compiled packages, just download and play :D

You can just download the _"compiled"_ packages from 
[Amazing Cow website](http://opensource.amazingcow.com/game/game_frogger/).

There are _"compiled"_ version for Linux - Sorry Windows/OSX users, we 
don't have a Windows/OSX box currently to make a package for it.

**Notice[1] that the assets folder MUST be in the same directory of the executable.**   
**Notice[2] you will need the SDL2 runtime libraries**

* [SDL2 - Runtime](https://www.libsdl.org/download-2.0.php)
* [SDL2_Image - Runtime](https://www.libsdl.org/projects/SDL_image/)
* [SDL2_TTF   - Runtime](https://www.libsdl.org/projects/SDL_ttf/)
* [SDL2_Mixer - Runtime](https://www.libsdl.org/projects/SDL_mixer/)


#### Option 2 - Source packages, _almost_ just download and play.

You can either grab a copy of the sources from 
[Amazing Cow website](http://opensource.amazingcow.com/game/game_frogger/) 
or download directly from github.

**Check notes bellow about source install.**


#### Option 3 - Clone / Fork the repo and hack it.

Also you can just ```git clone https://github.com/AmazingCow-Game/Game_Frogger``` 
to grab the latest version of sources.    
You should (and probably will) be good to go!

**Check notes bellow about source install.**


#### Notes for Option 2 and 3:

For those that prefer the source packaging, the **development** libraries 
for SDL2 are required. 

Assuming that you have the runtime libs installed, we made a Makefile 
that installs the game into your system.    

So just type:   
``` 
    make install 
``` 

With the appropriated privileges and start gaming :D



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Dependencies:

```Game_Frogger``` depends on:

* [Lore](https://github.com/AmazingCow-Game-Framework/Lore)  
* [CoreGame](https://github.com/AmazingCow-Game-Core/CoreGame)
* [CoreClock](https://github.com/AmazingCow-Game-Core/CoreClock)
* [CoreRandom](https://github.com/AmazingCow-Game-Core/CoreRandom)

and 

* [SDL2](https://www.libsdl.org/download-2.0.php)
* [SDL2_Image](https://www.libsdl.org/projects/SDL_image/)
* [SDL2_TTF](https://www.libsdl.org/projects/SDL_ttf/)
* [SDL2_Mixer](https://www.libsdl.org/projects/SDL_mixer/)


To generate the archives using the Makefile target ```gen-archives```
the [git-archive-all](https://github.com/Kentzo/git-archive-all) is also needed


<!-- ####################################################################### -->
<!-- ####################################################################### -->

## License:

This software is released under GPLv3.



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## TODO:

Check the TODO file for general things.

This projects uses the COWTODO tags.   
So install [cowtodo](http://www.github.com/AmazingCow-Tools/COWTODO) and run:

``` bash
$ cd path/to/the/project
$ cowtodo 
```

That's gonna give you all things to do :D.



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Others:

Check our repos and take a look at our 
[open source site](http://opensource.amazingcow.com).
