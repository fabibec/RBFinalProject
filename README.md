# Final Project - Introduction to Robotics
### by Fabian Becker, Florian Remberger & Quang Thanh Lai

## Project Description
The aim of this project is for the robot to make it's way through a predefinied map and navigate to two destinations.

## Task Importing
Simple for loop is necessary to copy characters from string into a 2D array with dimensions 14x14.

## Pathfinding and Route Creation
Dijkstra's Algorithm is used for pathfinding

## Driving Controls

## Individual Contributions
### Fabian Becker (Pathfinding & Route Creation
TODO

### Florian Remberger (Importing & Driving Controls)
## Importing
Importing the map is quite easy, because we do not have to read it directly from a text file. 
The map string is stored in a const char* variable called mapString.
It is located in main.c file and has to be changed manually if you want the robot to use another map.

The 2D array mapStringMatrix is also declared in main.c and can be filled with the characters from mapString via a simple for-loop.

We have to run from i = 0 up to i < 196 incrementing i after each loop, because the 14x14 map stored in the string contains 196 character (14 * 14 = 196).
For every character we have to calculate the right Row and Column where it should be stored in the 2D Array.

The Row can be determined by dividing i by 14. This calculation will be evaluated as a integral number due to the datatypes of i (uint8_t) and 14 (int by default). 
There for the result will be a whole number between 0 and 13 which will determine in which Row of the Array the character on position i in mapString should be stored.

The Column will be calculated by the operation i % 14. This will also return a whole number between 0 and 13 representing the Column.

Using both calculations we can now compose them to get the following equation.
mapStringMatrix[i/14][i%14] = mapString[i]

## Driving Controls
### function driveTiles(uint8_t tiles) 
Located in motion.c file this function makes the robot drive forward in a straight line.
The input parameter tiles represents the amount of tiles (each tile 25cm long) the robot should drive forward.
Using a 14x14 map the data type of tiles uint8_t will be definitely sufficient because we can not drive more than 12 tiles forward at once before hitting a wall.

The first thing this function does is calculating the distance it should drive.
This calculation is quite easy because we only have to multiply the tiles with 25 (cm) to get the total distance we want to drive.
Because we do not want to use floating point values later on we also multiply the distance we already calculated with 1000.

After calculating the distane we declare two variables which we will use to calculate the difference of degree.

Now we get the current degree of the wheels and store this value in prev_deg variable.

The general logic of this drive function is, that we first start the motors and then check how much distance we traveled since we last checked.
We the subtract the traveled distance from the total distance we have to travel.
If the total distance will be less then 2cm (represented as 2000 in our code due to the multiplication with 1000 earlier)
we stop the motors and via Motor_stop_float.

So the first thing within the while-loop has to be a delay so we do not get the same degree value as we got just before the while-loop.
We let the motors drive for 200ms so we can be certain that we get a bigger degree value.

After getting the new degree value and storing it inside deg variable we now have to calculate the distance 
the robot traveled.
This calculation is quite complex so i want to break it down into smaller steps:
1) **Calculate difference between old degree value and new degree value**. This can be done by subtracting the old value stored in prev_deg from the current degree value stored in deg. In our code we use the function getAbsDiff which calculated the absolute difference so we do not get any negative numbers.
2) **Multiply** the number we just calculated **by 2**. The function Motor_Tacho_GetCounter will return 1 for every two degrees the motor rotated. 
3) **Divide it by 360.0**. 360 degree would be a full spin of the motor and therefore also of the wheel. What we want to calculate here is how often the wheel rotated. The .0 guarantees, that the result will be of type double so we do not lose precision.
4) **Multiply by CIRCUMFERENCE**. CIRCUMFERENCE represents the circumference of the wheel. After this step we now excactly how much centimeter the robot traveled since we last checked. 
5) **Multiply by 1000**. If we would not multiply by 1000 here we could lose the decimal places because we subtract a double from a int here. Because of this step we also had to multiply by 1000 when we first calculated the total distance.

After we calculated the distance we can simply subtract it from the total distance and set prev_deg to deg.

This procedure will be followed until the distance is less or equal to 2cm. 
If so we will stop the motors and the function will exit.


### Quang Thanh Lai (Route Creation &  Driving Controls)
TODO


---


## TODO

- [x] Import task data
- [x] Pathfinding with Dijkstra Algorithm
- [x] Implement sound function
- [x] implement driveTile and turn functions
- [ ] optimize driveTile function with speed sensor values
- [ ] optimize Dijkstra results 
- [ ] port code to robot
