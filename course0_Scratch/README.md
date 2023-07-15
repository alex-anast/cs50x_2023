# Scratch Project: Multiplayer Ricochet Game

This is a Scratch project that implements a multiplayer ricochet game where two players move their respective paddles to keep the ball in play.

## Specifications

The project meets the following requirements:

- It uses two sprites: the paddles and the ball.
- It has more than three scripts in total.
- It uses at least one conditional, loop, and variable.
- It uses at least one custom block that takes at least one input.
- It is more complex than most of the projects demonstrated in lecture, but less complex than Oscartime and Ivy’s Hardest Game.

## Game Rules

1. Player 1 moves the paddle on the left with the "w" and "s" keys.
2. Player 2 moves the paddle on the right with the up and down arrow keys.
3. The ball bounces off the paddles and the walls of the game area.
4. If a player misses the ball, the other player scores a point.
5. The game ends when one player scores and then restarts. The ball will be in the center and towards a random direction.

## Code Design

The project is well-designed, with each script doing a specific task. The project leverages abstraction by using custom blocks for complex sequences of blocks. The project is implemented using a few dozen puzzle pieces overall. Lastly, the ball includes a randomized angle added to the new direction of the ball after every hit, so that it makes the game less predictable and more fun.

---

For any details, go and try it out. I promise it's a bit fun :)