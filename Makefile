##----------------------------------------------------------------------------##
##               █      █                                                     ##
##               ████████                                                     ##
##             ██        ██                                                   ##
##            ███  █  █  ███        Makefile                                  ##
##            █ █        █ █        Game_Frogger                              ##
##             ████████████                                                   ##
##           █              █       Copyright (c) 2016                        ##
##          █     █    █     █      AmazingCow - www.AmazingCow.com           ##
##          █     █    █     █                                                ##
##           █              █       N2OMatt - n2omatt@amazingcow.com          ##
##             ████████████         www.amazingcow.com/n2omatt                ##
##                                                                            ##
##                  This software is licensed as GPLv3                        ##
##                 CHECK THE COPYING FILE TO MORE DETAILS                     ##
##                                                                            ##
##    Permission is granted to anyone to use this software for any purpose,   ##
##   including commercial applications, and to alter it and redistribute it   ##
##               freely, subject to the following restrictions:               ##
##                                                                            ##
##     0. You **CANNOT** change the type of the license.                      ##
##     1. The origin of this software must not be misrepresented;             ##
##        you must not claim that you wrote the original software.            ##
##     2. If you use this software in a product, an acknowledgment in the     ##
##        product IS HIGHLY APPRECIATED, both in source and binary forms.     ##
##        (See opensource.AmazingCow.com/acknowledgment.html for details).    ##
##        If you will not acknowledge, just send us a email. We'll be         ##
##        *VERY* happy to see our work being used by other people. :)         ##
##        The email is: acknowledgment_opensource@AmazingCow.com              ##
##     3. Altered source versions must be plainly marked as such,             ##
##        and must not be misrepresented as being the original software.      ##
##     4. This notice may not be removed or altered from any source           ##
##        distribution.                                                       ##
##     5. Most important, you must have fun. ;)                               ##
##                                                                            ##
##      Visit opensource.amazingcow.com for more open-source projects.        ##
##                                                                            ##
##                                  Enjoy :)                                  ##
##----------------------------------------------------------------------------##

################################################################################
## Public Vars                                                                ##
################################################################################
HOST="linux_x64"


################################################################################
## Private Vars                                                               ##
################################################################################
_GAME_NAME=frogger


_COW_BIN=/usr/local/bin
_COW_SHARE=/usr/local/share/amazingcow_game_$(_GAME_NAME)
_GIT_TAG=`git describe --tags --abbrev=0 | tr . _`


_LORE_DIR=./lib/Lore
_CORECLOCK_DIR=$(_LORE_DIR)/lib/CoreClock
_COREGAME_DIR=$(_LORE_DIR)/lib/CoreGame
_CORERANDOM_DIR=$(_LORE_DIR)/lib/CoreRandom
_GAME_DIR=./game

_SDLFLAGS=`sdl2-config --libs --cflags` -lSDL2_image -lSDL2_ttf -lSDL2_mixer
_CC=g++ -Ofast -std=c++11 -Wall -Wextra -Wno-comment  -DCOREGAME_RELEASE -DLORE_RELEASE
_CC_DEBUG=g++ -g -std=c++11 -Wall -Wextra -Wno-comment


################################################################################
## End user                                                                   ##
################################################################################
install: dev-build
	@ echo "---> Installing...".

	@ ## Deleting old stuff...
	@ rm -rf $(_COW_SHARE)
	@ rm -rf $(_COW_BIN)/$(_GAME_NAME)

	@ ## Install new stuff...
	@ mkdir -p $(_COW_SHARE)/assets/

	@ cp -rf ./build/$(_GAME_NAME) $(_COW_BIN)/$(_GAME_NAME) ## Binary
	@ cp -rf ./assets              $(_COW_SHARE)             ## Assets

	@ echo "---> Done... We **really** hope that you have fun :D"


################################################################################
## Release                                                                    ##
################################################################################
gen-binary:

	mkdir -p ./bin/$(_GAME_NAME)

	cp -r ./assets/             ./bin/$(_GAME_NAME)/assets
	cp    ./build/$(_GAME_NAME) ./bin/$(_GAME_NAME)/$(_GAME_NAME)
	cp AUTHORS.txt   \
	   CHANGELOG.txt \
	   COPYING.txt   \
	   README.md     \
	   TODO.txt      \
	./bin/$(_GAME_NAME)

	cd ./bin && zip -r ./$(HOST)_$(_GIT_TAG).zip ./$(_GAME_NAME)
	rm -rf ./bin/$(_GAME_NAME)


gen-archive:
	rm -rf   ./archives
	mkdir -p ./archives

	git-archive-all ./archives/source_$(_GAME_NAME)_$(_GIT_TAG).zip
	git-archive-all  ./archives/source_$(_GAME_NAME)_$(_GIT_TAG).tar.gz


################################################################################
## Dev                                                                        ##
################################################################################
dev-build:
	rm -rf ./build/
	mkdir -p ./build/

	$(_CC) -o ./build/$(_GAME_NAME)           \
	       -I $(_LORE_DIR)                    \
	       -I $(_CORECLOCK_DIR)/include       \
	       -I $(_COREGAME_DIR)/include        \
	       -I $(_CORERANDOM_DIR)/include      \
	       -I $(_GAME_DIR)/include            \
	                                          \
	       $(_LORE_DIR)/src/*.cpp             \
	       $(_LORE_DIR)/src/private/src/*.cpp \
	       $(_CORECLOCK_DIR)/src/*.cpp        \
	       $(_COREGAME_DIR)/src/*.cpp         \
	       $(_CORERANDOM_DIR)/src/*.cpp       \
	       $(_GAME_DIR)/src/*.cpp             \
	$(_SDLFLAGS)


dev-debug:
	rm -rf ./build/
	mkdir -p ./build/

	$(_CC_DEBUG) -o ./build/$(_GAME_NAME)     \
	       -I $(_LORE_DIR)                    \
	       -I $(_CORECLOCK_DIR)/include       \
	       -I $(_COREGAME_DIR)/include        \
	       -I $(_CORERANDOM_DIR)/include      \
	       -I $(_GAME_DIR)/include            \
	                                          \
	       $(_LORE_DIR)/src/*.cpp             \
	       $(_LORE_DIR)/src/private/src/*.cpp \
	       $(_CORECLOCK_DIR)/src/*.cpp        \
	       $(_COREGAME_DIR)/src/*.cpp         \
	       $(_CORERANDOM_DIR)/src/*.cpp       \
	       $(_GAME_DIR)/src/*.cpp             \
	$(_SDLFLAGS)
