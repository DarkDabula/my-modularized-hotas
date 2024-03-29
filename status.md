# Status
This file will be a kind of diary for the project, to document the progress

## 1. Aug 2023
After the current lever joint got weaker and weaker I was forced to continue the project and beind able to play Elite Dangerous ^^ I printed the tow new joint parts for the new base plate. While assembling the new parts I recognized the whole cable management within the lever body is a mess. To it will be on my list when I replace the 2nd Arduino with a GPIO expander.

![New base plate](./images/20230702_joint_v2.jpg)
![New base plate](./images/20230725_joint_part.jpg)
![New base plate](./images/20230725_lever_joint.jpg)
![New base plate](./images/20230725_lever_joint_2.jpg)

The screws are still too long, I will replace or shorten them. The advantage is that cou can adjust the vertical angle steplessly. The joint is pretty robust so far even in stressful situations like space comat.

## 28. Jun 2023
Designed and printed a new base plate for the upcoming new lever joint.
I tried to improve stability while reducing the needed material. I also increased the size of the tunnel within the vertical joint for better cable handling.

![New base plate](./images/20230628_BasePlateV2.jpg)

## 23. Apr 2023
I finished another major step, I replaced the lever head with the new version with Cherry MX switches. I am looking forward to play with them. I am not happy with the slight wiring chaos within the lever, I will try to fix it with one of the nest stages.

![New hull and secondary mount](./images/IMG_20230422_Hull_and_2nd_mount.jpg)
![Hull and secondary mount assembled](./images/IMG_20230422_half_assembled.jpg)
![HAT switches wired](./images/IMG_20230423_wired_hat_switches.jpg)
![Wired switches and attached caps](./images/IMG_20230423_wired_buttons_with_caps.jpg)
![Wiring from below](./images/IMG_20230423_wiring.jpg)
![Attached cover plate](./images/IMG_20230423_attached_plate.jpg)
![Fully assembled lever head](./images/IMG_20230423_assembled_head.jpg)
![New head attached to lever](./images/IMG_20230423_atteched_to_lever.jpg)

The next steps will be
* Replacing the weak mount to the base
* Replacing the inner Arduino and complex resistor board board by an I2C GPIO expander
* Improving wire management

## 06. Mar 2023
Yesterday I completed and assembled the new redesigned lever body. Now there will be Cherry switches for the rocker and the two main buttons. The new body is mostly compatible with the other legacy parts.

![Parts for lever body V2](./images/20230304_lever_v2_body_parts.jpg)
![Parts for lever body V2 assembled](./images/20230304_lever_v2_body_partly_assembled.jpg)
![Parts for lever body V2 assembled](./images/20230304_lever_v2_body_partly_assembled_2.jpg)
![Lever body V2 assembled](./images/20230304_lever_v2_body_assembled.jpg)

To connect the cherry keys I use thinner wires and female sockets as connector which fits into the original board connectors.

![Wired Cherry switches](./images/20230305_wired_cherry_switch.jpg)
![Parts for lever body V2](./images/20230305_connected_cherry_switch.jpg)

The next steps will be (maybe not in this order):

- Redesign of the lever joint
- Redesign of the HAT-button-panel
- Replacing the inner Arduino and connector board by an I2C GPIO expander

I played already several hours with the new lever and so far all in fine. The Cherry switches are softer and need less pressure. Hopefully the (used) Cherry switches will be more durable.

## 05. Feb 2023
Still playing a lot Elite Dangerous with the current HOTAS design and yes, the blue push buttons are crap. The most stressed button have to be replaced regularly and I am going to run low on replacements.

So I ordered an used Cherry keyboard and desolded the switches. The I designed an printed some prototypes as mount and key cap.

![Cherry MX switches with mount prototypes](./images/20230205_cherry_switches.jpg)

The next steps will be to redesign the lever and some other parts around the new switches.
 

## 23. Dec 2022
I printed a cable mount so there will be no mechanical force on the Arduino board anymore.

![Cable mount](./images/20221223_cable_mount.jpg)

I also located some weak points of the construction after several hours playing Elite Dangerous:

- The lever joint seems not strong enough to hold the lever in the adjusted position when pushed to hard
- Some of the push button are getting unreliable. Maybe they don't have the quality I thought. Maybe ne next time I will use real Cherry buttons when possible.
- The circuit with the resistant maybe isn't the best option with the tolerance of the buttons, maybe the next stage will be using a I2C GPIO expander to get an input for every button. 

## 20. Nov 2022
I optimized the code of the master Arduino to improve the throttle control, now it works fine.

I also redesigned the magnet mount for the metal base plate. Unluckily I broke some uncritical parts of it while inserting the magnet.
The new mount have a better adhesion to the plate.

![New magnet plate mount](./images/20221120_new_magnet_mount.jpg)

I printed a mount for the front board and attached it to the metal base plate.

![Front board and mount](./images/20221120_front_board_and_mount.jpg)

Next step will be to create a case for the whole thing and finalize the cable management.

## 17. Nov 2022
I fixed some issues which occurs while playing.

1. Broken cable at one of the rocker switches
2. Replaced one rocker switch which had more than 30 Ohm while pressed
3. Fixed software bug in slave program which reports invalid values to master via I2C

I also finished the front board with the connectors for cable, time-of-flight sensor and master Arduino

![Front board top](./images/20221117_front_board_top.jpg)
![Front board bottom](./images/20221117_front_board_bottom.jpg)

Next step is to print a mount for the front board.

## 14. Nov 2022
I wired and assembled the lever

![Lever interior](./images/20221114_lever_interior.jpg)
![Lever assemlbed](./images/20221114_lever_assembled.jpg)

I also printed the last parts for the magnets which "mark" the zero position

![Lever interior](./images/20221114_magnets.jpg)

and the reflector for the time-of-flight sensor using a small piece of aluminum

![Lever interior](./images/20221114_reflector.jpg)

I finished the programming of the Arduinos. A strange thing is that sometimes the master gets values over I2C which the slave don't send. 
But luckily I was able to compensate it via programming.

Finally I finished my first session Elite Dangerous with the new lever and configured the key bindings.

## 11. Nov 2022
I finished the connector board

![Connector board front](./images/20221111_connector_board_front.jpg)
![Connector board back](./images/20221111_connector_board_back.jpg)

But despite all digital planning I had to modify some parts because the Arduino collided with the 4-pin connector on the side

![Connector board modified](./images/20221111_connector_board_modified.jpg)

1. Removed the plastic spacer to lower the height
2. Cable connection instead pins
3. Increased angle of connector

With that all fits together well

![Connector board assembled](./images/20221111_connector_board_assembled.jpg)

I also tested the whole setup with both Arduino boards.

![Two Arduinos connected](./images/20221111_two_arduinos_connected.jpg)

Next steps will be:

* Finish programming
* Assemble thrust lever
* Create electric connections

## 04. Nov 2022
I designed a placeholder for the boards within the lever to get a feeling for the available space.

![Board placeholder](./images/20221104_board_placeholder.png)

Then I imported the shape into KiCad and puzzled to get all parts arranged within it.

![Connector board front](./images/20221104_connector_board_front.png)
![Connector board back](./images/20221104_connector_board_back.png)

Now I wait for some parts that I ordered to assemble the connector board.
I also continued developing the Arduino sketch for the slave controller.

## 26. Oct 2002
I designed the connector boards with KiCad. These boards will be connected to the buttons and will translate them into analogue signals for the slave Arduino. Maybe this will not be the final design.

![Connector boards front](./images/20221026_CBs_front.png)
![Connector boards back](./images/20221026_CBs_back.png)

I also created a physical version, but its not perfect. So I consider to call it prototype.

![Connector one board front](./images/20221025_CB1prot_front.jpg)
![Connector one back front](./images/20221025_CB1prot_back.jpg)

Besides that I began to program the slave Arduino. Results are promising so far.

## 19. Oct 2022
I reached a major milestone within this project. All basic parts of the lever are designed and printed. 

![Lever front](./images/20221019_lever_1.jpg)
![Lever back](./images/20221019_lever_2.jpg)
![Lever opened](./images/20221019_lever_open.jpg)

Not all is perfect but I think it will go through some iterations while using it, but for now I am happy wight the result.

The next phase will be wiring all the buttons, create connector boards and programming the controller. Challenging will be the limited space within the lever.

## 18. Oct 2022
I finally printed the two parts of the lever hull. I printed them separately in two runs. At the first part I struggled to strip the support structure away. So at the second
part I used tree support.

![Lever hull parts](./images/20221017_lever_hull.jpg)

There a still some little tasks ahead: 
- reprint of the lever angle stopper -> seems to be too small
- print the final version of the rocker
- print the final version of the rocker module
- designing and printing the front buttons of the lever

## 08. Oct 2022
I redesigned the rocker module to use the new push buttons and omitting the springs.

![New rocker module in parts](./images/20221008_new_rocker_module_parts.jpg)
![New rocker module assembled](./images/20221008_new_rocker_module.jpg)

## 03. Oct 2022
The right panel is now fully assembled and wired. One major step is done.

![Right panel assembled](./images/20221003_right_panel_assembled.jpg)

Next phase is the final design for the lever corpus.

## 28. Sep 2022
It took four attempts to print a perfect fitting HAT. I am pretty happy how it worked out finally. The next step will be to create an assembly description with the needed screws and other parts.

![Right panel with HAT](./images/20220928_HAT.jpg)

## 27. Sep 2022
The right panel makes progress. I printed the cover plate an the double button caps. The next step will be printing the HAT and add the missing wires.

![Right panel and button caps](./images/20220927_right_panel.jpg)

## 26. Sep 2022
At the moment I am eager to play Elite Dangerous again, so I am pretty motivated to push this project forward ;)
Today I printed the (maybe final) panel for the buttons and the HAT module. I also printed a button cap prototype.
A small problem will be wiring the HAT module because there isn't much space.

![Right panel and button cap prototype](./images/20220926_button_panel.jpg) 

## 25. Sep 2022
I am designing the right main button panel of the thrust lever at the moment. I plan to put there 6 buttons and a HAT.
The HAT module gave me a pretty hard time. First I wanted to use the new blue button but I didn't get the mechanics to work.
So I went back to the first micro switches and with that I got a promising prototype.

![Right panel parts prototypes](./images/20220925_panel_part_prototype.jpg)

The next step will be to integrate the HAT module into the panel construction.


## 20. Aug 2022
I designed the right part of the lever where many of the buttons and the HAT will be located. The print went pretty well.

![Left part of the lever](./images/20220820_right_part.png)

I am also struggling designing the button modules. The problem is that the switches I wanted to use aren't pretty compact. So I ordered some others at EBAY hoping that they are as reliable as the old ones.

![Switches](./images/20220820_switches.png)

## 11. Aug 2022
I designed and printed additional parts for test reasons.

![New parts](./images/20220811_New_parts.jpg)

The consists of:
- Two stoppers to set horizontal angle
- Connector and connection plate to connect the lever with the joint with possible rotation around a additional axis
- Partial printed lever hull, which consists of two parts but I put them too close while printing this time
- Stopper to adjust rotation angle of the lever around its inner axis, not completely assembled

The result is promising but I also identified some weak points.

![New parts assembled](./images/20220811_Parts_assembled.jpg)

There is also room for some optimizations like the amount of needed material.

## 07. Aug 2022
I did a second prototype for a part of the joint that will connect lever and base plate. With the screw the joint can be fixed in its position. The print wasn't 100% accurate but luckily it was at a non-critical point.

![2nd prototype base joint](./images/20220807_basejoint.jpg)
![2nd prototype base joint on baseplate](./images/20220807_basejoint2.jpg)

## 06. Jun 2022
I redesigned the base plate to reduce need of filament. Additionally I replaced the original lock-in position by a kind of gear to allow finer angles of adjustment around the vertical axis.
I also do a test print ob the counterpart for it.

![2nd prototype of base plate](./images/20220606_baseplate_2nd_prototype.jpg)  

## 07. Feb 2022
Printed the first version of the base plate with joint. We will see if the joint is strong and stiff enough.

![Base plate](./images/baseplate.jpg)

## 06. Feb 2022
Replaced the original metal base plate by a thin printed prototype to check if the holes where at the right position. On the base plate there will a joint to connect it with the lever.

![Base plate prototype](./images/baseplate-prototype.jpg)

## 31. Jan 2022
I created the first test pieces for the adjustable joint. With that it should possible to adjust the angle of the lever in relation to the horizontal line. This was my third try after evaluating other designs.

![Joint prototype](./images/joint-prototype.jpg)

## 20. Jan 2022
I did a small revision of the rocker switch module. Its slightly smaller and have holes to reduce material. The rocker itself is black because I was too lazy to change the filament for the test print. ^^

![Rocker switch revision 1](./images/rocker-switch-rev-1.jpg)

## 14. Jan 2022
Today I printed the early version of parts for the rocker switch and assembled them with the switches and springs.

![First rocker switch](./images/first-assembled-rocker-switch.jpg)
