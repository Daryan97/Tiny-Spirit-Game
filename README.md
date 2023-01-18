# Tiny Spirit Game

Welcome to the Tiny Spirit game!
Here you face multiple challenges from your enemies and levels!

 1. ![Tiny Spirit Character](https://github.com/Daryan97/Tiny-Spirit-Game/raw/master/Assets/Player/player_right.gif) Your character: A blue alien like.
 2. ![Tiny Spirit Enemy](https://github.com/Daryan97/Tiny-Spirit-Game/raw/master/Assets/Enemy/monster_1_left.gif) Your enemy: A crab
3. ![Tiny Spirit Health](https://github.com/Daryan97/Tiny-Spirit-Game/raw/master/Assets/Map/Collectibles/heart.gif) Regenerate health: Using this collectible will grant you **+1** health back.
4. ![Tiny Spirit coin](https://github.com/Daryan97/Tiny-Spirit-Game/raw/master/Assets/Map/Collectibles/coin.gif) This will grant you to go to the `next level`.

## Programming Language & Libraries
- Language used: **C++**
- Library: [Borland Graphics Interface (BGI) for Windows](https://home.cs.colorado.edu/~main/bgi/doc/)

## Assets:
1. [Free Tiny Hero Sprites Pixel Art](https://free-game-assets.itch.io/free-tiny-hero-sprites-pixel-art)
2. [Castor's Forest Pixelpack Tileset](https://castorcreations.itch.io/castors-forest-pixelpack-tileset)
3. [COIN - 2D ANIMATION](https://gabriel-ceppas.itch.io/coin)
4. [RPG Characters Pack](https://ze0nni.itch.io/rpg-characters-pack)

### How maps are generated?
I have used [Tiled Map Editor](https://www.mapeditor.org/) to create maps on one layer, then extract it as ```JSON```, get the data out of the file, and put it in a **Multidimensional Array**  called *maps*.

This is not the most efficient way to generate maps, but it makes it 10 times easier for my university project.

### What do the numbers represent?
| Number | Represents |
|--|--|
| 0 | Air |
| 1 | Dirt Tile |
| 2 | Grass Tile |
| 3 | Heart Collectible |
| 4 | Player Spawn |
| 5 | Enemy Spawn |
| 6 | Next Level |

The project full map creation files can be found at [this repository](https://github.com/Daryan97/Tiny_Spirits_Map).
