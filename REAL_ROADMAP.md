# ma_photoshop roadmap

## ver 0.1: simple button

```
[Button]

state = PRESS | UNPRESS
position
size
color

	funcs:

process_click()
press()
unpress()
is_in_area()
```

results:
* button changes state (and color) with click
* mutex button manager (only one button can be pressed)

## ver 0.2: simple canvas

results:
* point is drawn when click on button

## ver 0.3: connect canvas-buttons [@currently here]

results:
* draw on canvas with active color
* draw on canvas with active instrument

Buttons:
- red, green, blue - set canvas active color 
- brush, eraser [const white brush], pouring - set canvas active instrument

Parameterize canvas with instrument (make class from instrument).

```
[Instrument]

propertiesL size...

	funcs:

apply(position)
```


## ver 0.4: filters
results:
* Drop-down menu when click on filter button
* Apply filter to every pixel when click on concrete filter

Filters:
- B&W [R=G=B = average(R,G,B)]
- inverse [R=255-R ...]

## ver ??: serialization

Tree traverse and dump
Restore from dump

## ver ??: raytracer

2 mods:
* canvas works as screen for raytracer
* paint

Objects can be added to the scene on air

## features:

* undo opearation
* save picture
* load picture
* help panel
* plugins
* instruments to toolbox: line, rectangle
* set properties for instruments (size for brush)
* filters with curves
