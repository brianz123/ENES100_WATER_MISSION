# ENES100_WATER_MISSION

For this project, we were tasked with creating an OTV that was fully autonomous that could complete its desired mission. We received the water mission and to complete this, the OTV had to:

navigate to within 150 mm of the edge of the water pool, measure and correctly transmit whether the pool has freshwater, saltwater polluted freshwater, or polluted saltwater
measure and transmit the depth of the water in the pool to within 4 mm
collect a sample of at least 20 ml of water from the pool
navigate completely past the three obstacles
navigate completely into the destination zone (path: under the limbo)
There were a few restrictions placed on our design, which included:

OTV mass must be between 0-3 kilograms
Mission must be completed within 5 minutes
OTV will have random orientation and positioning at the start
Water salinity, quality, and level will be randomly selected
Sample must be taken from a 71 mm tall pool
Our Design

We first made a chassis system. The front, side, and bottom panel were laser cut out of plywood and the top was cut out of acrylic. It had a rectangular (with box-like design). The approximate dimensions were 250mm x 300mm. Some things we took into consideration in creating our design was its low center of gravity and it robust/sturdy design.

Completing the Mission

To complete the mission specific objectives, we created an arm that attached to the center of the chassis. To test the water height, we used an ultrasonic sensor since it uses sound waves to detect distance and we would be given clear distance numbers based on our code. we coded the ultrasonic sensor so that it would convert the time it takes for sound waves to bounce off of an object in front of it (in this case it being the water) and convert it to distance by multiplying it to the speed of sound divided by 2. After this, we had the Arduino output the distance reading in centimeters so that we could test if the readings would change after changing the height of the water. After placing the arm at the level of the chassis height above the tank, we changed the height of the water multiple times, and the readings of the ultrasonic sensor so far have been accurate (have changed in relation to the change in water height) meaning our ultrasonic sensor will do the trick in completing the first part of the mission. After we decided that this was a good permanent solution, we 3D printed a new mount for the end of the arm, creating a housing for this second ultrasonic sensor.

To measure the pollution of the water, we installed a water pump connected to a 3D printed reservoir tank. One end of the tube was placed into reservoir and the other was run up the arm and hung from the end. Once height was measured with the ultrasonic sensor, a single channel relay was pressed to activate the water pump. The water in contact with the tube in the pool will be vacuumed through the tubes into the reservoir. We then created a circuit with a photoresistor used to determine pollution with LED shining through the tube. This measured intensity of light. If water is polluted then light intensity will be lower.

To test the salinity of the water, we used a TDS sensor. The TDS sensor indicates how many milligrams of dissolved solids are in water. A high TDS level indicates salt water and a low value indicates freshwater. The TDS sensor was placed into the reservoir and tested the water when it was collected by the pump.

Propulsion

We created a 4 wheel drive system that used:

4 DC 6-12V Motors with a torque of 66 N-cm at 7.2 Volts
The battery we selected was the POVWAY NiMH Battery

Material: nickel metal hydride
Voltage: 7.2V
Cell: 6-Cell
Capacity: 3600mAH
Plug: Tmiya Connector
Dimension(L*W*H): 137 x 47 x24mm
Battery Weight: 371 g
We decided on 4 wheels which were 3D printed. The approximate dimensions were 152.4 mm in diameter and 19 mm thickness. Each wheel was about 90 grams.

Navigation

For navigation, we used and ultrasonic sensor that was attached to top of the arm. This was able to detect obstacles to avoid collisions. Our arena used a vision system that had a camera above to scan barcodes for OTV location (aruco markers)
