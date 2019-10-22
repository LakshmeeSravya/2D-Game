# 2D Game

## Running the code:
- Create build folder and cd into it
- Run cmake ..
- Run make
- Run ./graphics_asgn_1

## Controls:
- left arrow key to move lef
- right arrow key to move right
- up arrow key to jump

## Score:
-  15 points for hitting very small balls
-  10 points for hitting medium sized balls
-  5 points for hitting large balls
- -20 points for touching the porcupine

## Levels:
- Level 1  	score is less than 50       water, trampoline
- Level 2  	reach a score of 50         water, trampoline, porcupine
- Level 3  	reach a score of 100        water, trampoline, porcupine, magnet

## About the game:
- On hitting a ball, the ball diappears and the score increases based on the size of the ball. 
- Some balls have inclined slope on them. If the player lands on the slopes, it will be launched based on the laws of reflection.
- Whenever the player falls into water it follows the curve until the lowermost point is reached unless the player is explicitly moving sideways. 
- The height reached by the player when it jumps is less in water. 
- If the player jumps onto the trampoline, it will cause the player jump higher than usual.
- Whenever the player is in the field of the magnet, it will be attracted towards it. 
- On touching the moving porcupine, the player loses 20 points. 
- The score and level are displayed on the titlebar of the game window.
