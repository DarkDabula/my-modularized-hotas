# My Modularized HOTAS
A modularized, mostly 3D printed HOTAS with HID emulation via Arduino

## Motivation
On Christmas 2020 I stumbled over [Elite Dangerous](https://www.elitedangerous.com/) and got hooked. After a while I began to play it in VR.
At this point I realized I would need a HOTAS system. The problem was that through the pademic all systems were mostly sold out. 
I had already a joystick so I built a throttle lever made of metal parts, wood and some electronics. And it served me pretty well.

![Prototype](./images/prototype.jpg)

But after hundreds of hours I recognized that the simple push buttons got weak and that I would need more buttons for effective playing in VR.
In 2021 I bought a 3D printer and the idea was born to contruct a new and better throttle lever and maybe after this a new joystick.

## Goals
- As much 3D printed parts as possible and reasonable
- Modularized design for easy printing, assembly, customization and repair

## Current state
See [here](./status.md)

## Concepts
See [here](./concepts.md)

## External parts
For this project additional parts/components are needed besides the 3D printed ones.

| ID     | Ammount   | Item                   | Picture                             | Example link for buying                                                                                                   |
|----------|---------|------------------------|-------------------------------------|---------------------------------------------------------------------------------------------------------------------------|
| CON3     |      3  | Connector 3 pins       | ![Connector 3 pins](./images/part_CON3.jpg) | |
| CON5     |      1  | Connector 5 pins       | ![Connector 5 pins](./images/part_CON5.jpg)| |
| MS       |      4  | Micro swith            | ![Micro switch](./images/part_MS.jpg) | [Link](https://www.ebay.com/sch/i.html?_from=R40&_trksid=p2380057.m570.l1313&_nkw=micro+limit+switch+125V+1A&_sacat=0) | 
| PB       |     10  | Push button            | ![Push button](./images/part_PB.jpg)  | [Link](https://www.ebay.com/sch/i.html?_from=R40&_trksid=p2380057.m570.l1313&_nkw=micro+button+7mm+non+latching&_sacat=0) |
| SC25     |      4  | Screw 2,5x13 (metric)  | ![Screw 2,5x13](./images/part_SC25.jpg) | |
| SCM3     |      1  | Screw M3x20 (metric)   | ![Screw M3x20](./images/part_SC30.jpg) | |
| SC35_7   |      1  | Screw 3,5x7 (metric)   | ![Screw 3,5x7](./images/part_SC35_7.jpg) | |
| SC35_95  |      4  | Screw 3,5x9,5 (metric) | ![Screw 3,5x9,6](./images/part_SC35.jpg) | |
| SCM4_10  |      8  | Screw M4x10 (metric)   | ![Screw M4x10](./images/part_SC40_10.jpg) | |
| SCM4_20  |      2  | Screw M4x20 (metric)   | ![Screw M4x20](./images/part_SC40_20.jpg) | |
| SCN4     |      2  | Stop nut M4 (metric)   | ![Stop nut M4](./images/part_SN40.jpg) | |


## Toolchain
- [FreeCAD](https://www.freecad.org/) 0.19
- [Cura](https://ultimaker.com/software/ultimaker-cura) 4.12.1 (or above)
- [Creality Ender 6](https://www.creality.com/goods-detail/ender-6-3d-printer) (modified)
- [Arduino IDE](https://www.arduino.cc/en/software)
- [KiCad](https://www.kicad.org/)

## License
This projects is licensed under the terms of [CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/)
