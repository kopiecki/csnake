# csnake

Yet another [snake](https://en.wikipedia.org/wiki/Snake_(video_game_genre)) clone.
Dead simple, no bells and whistles, made out of boredom.

![](support/github/play.gif)

## Dependencies

- `cmake` and `make` for building
- `ncurses` for terminal stuff
- [ncge](https://github.com/kopiecki/ncge) git submodule

## Bulding

Tested only on GNU/Linux.

Update submodule:
```console
git submodule update --init
```

Release build:
```console
make
```

Debug build:
```console
make debug=y
```

## Running

```console
make run
```
## Configuration

Game is mostly configured by constants in `app/src/config.h`. You can change
some stuff there and recompile the program to see results.
