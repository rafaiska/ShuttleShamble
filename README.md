# Shuttle Shamble

Shuttle Shamble is an experiment in building a small game engine with SDL 1.2
for resource-constrained handhelds, with the PocketGo V1 as its initial target.
The goal is to make a small, efficient game rather than a general-purpose
engine.

## The game

Shuttle Shamble is inspired by *Asteroids*, but its main objective is to rescue
allied shuttles instead of simply destroying asteroids. Shooting the asteroids
is still an option.

## Technical direction

The game will use tile-based graphics and an 8-bit indexed framebuffer to keep
memory use and rendering costs predictable. The intended format uses:

- 8×8-pixel tiles;
- four colors per tile;
- sprites composed of one or more tiles;
- a shared 256-entry screen palette.

This design is a feasible fit for SDL 1.2 and the PocketGo V1, but it is still a
target architecture rather than the current state of the engine.

`GMTile` currently describes a square region of a `GMImage2D`, and `GMSprite`
arranges tiles in a rectangular grid. These classes provide a useful starting
point, but the compact 2-bit tile format, palette allocation, asset conversion,
and SDL drawing path still need to be implemented. In particular,
`VideoServiceSDL1::draw_tile` is currently a stub.

See [docs/tiled_graphics.md](docs/tiled_graphics.md) for the proposed graphics
model, its constraints, and a suggested implementation path.

## Current status

The repository contains early engine components for tiles, sprites, tile maps,
renderers, collision detection, file loading, and an SDL 1.2 video service.
Development is experimental, and the PocketGo build and deployment workflow
has not yet been documented or validated in this repository.

## Near-term milestones

1. Define an in-memory 2-bit tile and four-color palette representation.
2. Convert source artwork into the runtime format during asset loading or as an
   offline build step.
3. Implement frame-local palette allocation for the 8-bit SDL surface.
4. Implement and test tile drawing in `VideoServiceSDL1`.
5. Add transparency, sprite clipping, and palette-overflow handling.
6. Validate performance and output scaling on PocketGo V1 hardware.

