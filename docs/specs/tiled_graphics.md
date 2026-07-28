# Tiled graphics

This document describes the intended graphics architecture for Shuttle
Shamble. Unless stated otherwise, it is a design proposal and not a description
of features that are already implemented.

## Video mode

The renderer should use an 8-bit indexed SDL surface. Each framebuffer pixel is
therefore a one-byte index into a single, screen-wide palette of up to 256
colors.

The engine will treat that palette as 64 four-color slots:

```text
screen index = palette slot × 4 + tile color
```

Here, `palette slot` is in the range 0–63 and `tile color` is in the range 0–3.
This organization makes remapping a 2-bit tile straightforward, but the 64
slots are an engine convention—not separate palettes provided by SDL.

Changing an SDL surface's palette changes the meaning of every framebuffer
pixel that uses the affected indices. Consequently, palette slots must remain
stable until the frame has been presented. A simple first implementation can
reset the slot allocator at the beginning of each frame, assign a slot the
first time a palette is used, and reuse that assignment for the rest of the
frame.

If a frame needs more than 64 distinct palettes, drawing must remain safe and
the engine should emit a diagnostic. The exact visual fallback still needs to
be chosen; reasonable options include a reserved error palette or the closest
palette already allocated.

## Tiles

A logical tile is 8×8 pixels and uses four local color values. Each pixel needs
two bits, so the packed pixel data requires:

```text
8 × 8 × 2 bits = 128 bits = 16 bytes
```

If the tile stores a one-byte palette identifier, its serialized payload is 17
bytes. This is a file-format or packed-data size, not necessarily the size of a
C++ object: alignment, image metadata, and container overhead can make the
runtime representation larger.

The four local values are mapped to four entries in the tile's assigned screen
palette slot while rendering. For sprites, one local value will probably need
to be reserved for transparency; the precise transparency rule should be part
of the asset format.

### Current `GMTile` representation

The existing `GMTile` class does not yet contain packed pixels or a palette
identifier. It stores:

- a `GMImage2D`;
- square source boundaries within that image;
- the tile size derived from those boundaries.

It accepts square tiles of different sizes, whereas the proposed runtime format
fixes the size at 8×8. This makes `GMTile` a useful source-image abstraction,
but implementing the proposed design will require either extending it with
compact pixel and palette data or introducing a separate runtime tile type.

## Sprites

A sprite is a rectangular, row-major grid of tiles. Unlike Game Boy hardware
sprites, Shuttle Shamble sprites are not restricted to one fixed pair of
dimensions. Their width and height are expressed as tile counts, and all tiles
in a sprite must have the size declared by the sprite.

Different tiles in one sprite may use different palettes, subject to the
frame-wide limit of 64 simultaneously allocated palette slots. Sprite
transparency must be handled without overwriting destination pixels.

### Current `GMSprite` representation

The existing `GMSprite` class already provides most of the grid abstraction:

- it declares a column count, row count, and tile size;
- `add_tile` appends tiles in row-major order;
- it rejects excess tiles and tiles of the wrong size;
- `get_tile(column, row)` retrieves a tile by grid position.

Callers must currently add exactly `columns × rows` tiles before every valid
grid position can be read. The class checks coordinates, but it does not
separately report an incompletely populated sprite.

## Proposed rendering flow

For each frame:

1. Clear the framebuffer and reset the frame's palette-slot allocator.
2. Traverse visible sprites and tiles.
3. Look up or allocate a screen slot for each tile palette.
4. Install newly allocated colors in the SDL surface palette.
5. Translate each 2-bit tile pixel into an 8-bit screen index.
6. Skip transparent sprite pixels and clip writes to the viewport.
7. Present the completed framebuffer.

Palette equality should be based on the four color values, not merely on an
asset-local palette number. This allows identical palettes from different
assets to share a slot.

For the first implementation, correctness and deterministic overflow behavior
are more important than sophisticated caching. Once the drawing path works,
converted tiles or per-palette lookup tables can be cached to reduce per-pixel
work.

## Implementation gap

The main pieces still required are:

- a packed tile and palette format;
- an asset conversion or loading path;
- a per-frame palette-slot allocator;
- a transparency convention;
- an implementation of `VideoServiceSDL1::draw_tile`;
- tests for pixel unpacking, palette reuse and overflow, clipping, and
  transparency;
- validation of the final video mode, scaling strategy, and performance on
  PocketGo V1 hardware.

