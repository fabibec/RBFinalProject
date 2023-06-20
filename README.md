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
This function is located in the motion.c file. 
It makes the robot move forward in a straight line. 
The input parameter tiles represents the number of tiles (each tile has a length of 25 cm) that the robot should move forward. 
Using a 14x14 map, the tiles datatype uint8_t will be sufficient because we cannot move more than 12 tiles before hitting a wall. 

Calculating the distance to travel is the first thing this function does. 
This calculation is quite simple, because we only have to multiply the tiles by 25 (cm) to get the total distance we want to move. We also multiply the already calculated distance by 1000 because we do not want to use floating point values.  

After calculating the distance, we declare two variables. We will use them to calculate the difference in degrees.  

Now we get the current degree of the wheels. We store this value in the prev_deg variable.  

The general logic of this drive function is: 
First we start the motors and then we check how much distance we have traveled since the last check. 
From the total distance we have to travel, we subtract the distance traveled. 
We stop the motors and set Motor_stop_float if the total distance is less than 2cm (represented as 2000 in our code due to the multiplication with 1000 earlier).  
So the first thing inside the while loop has to be a delay. So we do not get the same degree value as just before the while loop. 
We let the motors run for 200ms. So we can be sure that we get a bigger degree value.  
Now that we have the new degree value and have stored it in the deg variable, we need to calculate the distance that the robot has moved. 
This calculation is quite complex. So I want to break it down into smaller steps:

1) **Calculate the difference between the old degree value and the new degree value**. This can be done by subtracting the old value stored in prev_deg from the current degree value stored in deg. In our code we use the function getAbsDiff which calculated the absolute difference so we do not get any negative numbers.
2) **Multiply** the number we just calculated **by 2**. The Motor_Tacho_GetCounter function will return 1 for every two degrees the motor has rotated. 
3) **Divide it by 360.0**. 360 degrees would be a full turn of the motor and therefore a full turn of the wheel. What we want to calculate here is how many times the wheel has turned. The .0 guarantees, that the result will be of type double so we do not lose precision.
4) **Multiply by CIRCUMFERENCE**. CIRCUMFERENCE is the circumference of the wheel. After this step, we now know excactly how many centimeters the robot has moved since the last check. 
5) **Multiply by 1000**. If we did not multiply by 1000, we would lose the decimal places because we are subtracting a double from an int. Because of this step we also had to multiply by 1000 when we first calculated the total distance.

After calculating the distance we can simply subtract it from the total distance and set prev_deg to deg.

This procedure is repeated until the distance is less than or equal to 2cm. 
If this is the case, the motors will stop and the function will end.


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
